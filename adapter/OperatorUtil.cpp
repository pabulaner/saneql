#include "OperatorUtil.hpp"

#include <iostream>

namespace adapter {

namespace outil {

void printTree(Operator* tree) {
    size_t tabs = 0;
    forEach<Operator>(tree, [&](Operator* op) {
        Operator* out = op;
        while (out = getOutputOperator(tree, out)) {
            std::cout << '\t';
        }

        if (dynamic_cast<TableScan*>(op)) {
            std::cout << "TableScan" << std::endl;
        }
        if (dynamic_cast<Select*>(op)) {
            std::cout << "Select" << std::endl;
        }
        if (dynamic_cast<Map*>(op)) {
            std::cout << "Map" << std::endl;
        }
        if (dynamic_cast<Join*>(op)) {
            std::cout << "Join" << std::endl;
        }
        if (dynamic_cast<GroupBy*>(op)) {
            std::cout << "GroupBy" << std::endl;
        }
        if (dynamic_cast<Sort*>(op)) {
            std::cout << "Sort" << std::endl;
        }

        return true;
    });
}

std::unique_ptr<Operator> insertSelectIfNotPresent(std::unique_ptr<Operator> tree, Operator* target) {
    if (tree.get() == target) {
        return std::make_unique<Select>(std::move(tree), nullptr);
    }
    
    Operator* out = getOutputOperator(tree.get(), target);

    // check if the output already is a select operator
    if (dynamic_cast<Select*>(out)) {
        return tree;
    }

    std::unique_ptr<Select> select = std::make_unique<Select>(std::unique_ptr<Operator>(target), nullptr);
    std::vector<Operator*> inputs = out->getInputs();

    for (size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] == target) {
            inputs[i] = select.get();
        }
    }

    select.release();
    out->setInputs(inputs);

    return tree;
}

std::unique_ptr<Operator> removeSelect(std::unique_ptr<Operator> tree, Select* target) {
    std::unique_ptr<Operator> input = std::unique_ptr<Operator>(target->getInputs()[0]);
    target->setInputs({nullptr});

    if (tree.get() == target) {
        return input;
    }

    Operator* out = getOutputOperator(tree.get(), target);
    std::vector<Operator*> inputs = out->getInputs();

    for (size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] == target) {
            inputs[i] = input.get();
        }
    }

    input.release();
    return tree;
}

Operator* getOutputOperator(Operator* tree, Operator* target) {
    for (auto input : tree->getInputs()) {
        if (input == target) {
            return tree;
        }
        return getOutputOperator(input, target);
    }

    return nullptr;
}

Operator* getIUOperator(Operator* tree, std::vector<const IU*> ius) {
    Operator* result = nullptr;

    forEach<Operator>(tree, [&](Operator* op) {
        std::vector<const IU*> opIUs = op->getIUs();

        for (auto iu : ius) {
            if (!vutil::contains(opIUs, iu)) {
                return true;
            }
        }

        result = op;
        return true;
    });

    return result;
}

std::pair<std::vector<const IU*>, std::vector<const IU*>> getJoinKeyIUs(Operator* left, Operator* right, Expression* exp) {
    BinaryExpression* b = dynamic_cast<BinaryExpression*>(exp);
    ComparisonExpression* c = dynamic_cast<ComparisonExpression*>(exp);

    if (b && b->op == BinaryExpression::And) {
        auto l = getJoinKeyIUs(left, right, b->left.get());
        auto r = getJoinKeyIUs(left, right, b->right.get());
        
        return {vutil::combine(l.first, r.first), vutil::combine(l.second, r.second)};
    }
    if (c && c->mode == ComparisonExpression::Equal) {
        IURef* l = dynamic_cast<IURef*>(c->left.get());
        IURef* r = dynamic_cast<IURef*>(c->right.get());
        auto leftIU = l->getIU();
        auto rightIU = r->getIU();
        auto leftIUs = left->getIUs();
        auto rightIUs = right->getIUs();

        if (l && r) {
            if (vutil::contains(leftIUs, leftIU) && vutil::contains(rightIUs, rightIU)) {
                return {{leftIU}, {rightIU}};
            }
            if (vutil::contains(leftIUs, rightIU) && vutil::contains(rightIUs, leftIU)) {
                return {{rightIU}, {leftIU}};
            }
        }
    }

    throw std::runtime_error("Unsupported join condition");
};

}

}