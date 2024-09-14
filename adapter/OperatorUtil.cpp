#include "OperatorUtil.hpp"

#include <iostream>

namespace adapter {

namespace outil {

void printTree(Operator* tree, size_t tabs) {
    for (size_t i = 0; i < tabs; i++) {
        std::cout << '\t';
    }

    if (!tree) {
        std::cout << "nullptr" << std::endl;
        return;
    } else if (dynamic_cast<TableScan*>(tree)) {
        std::cout << "TableScan" << std::endl;
    } else if (dynamic_cast<Select*>(tree)) {
        std::cout << "Select" << std::endl;
    } else if (dynamic_cast<Map*>(tree)) {
        std::cout << "Map" << std::endl;
    } else if (dynamic_cast<Join*>(tree)) {
        std::cout << "Join" << std::endl;
    } else if (dynamic_cast<GroupBy*>(tree)) {
        std::cout << "GroupBy" << std::endl;
    } else if (dynamic_cast<Sort*>(tree)) {
        std::cout << "Sort" << std::endl;
    } else if (dynamic_cast<IndexScan*>(tree)) {
        std::cout << "IndexScan" << std::endl;
    } else if (dynamic_cast<IndexJoin*>(tree)) {
        std::cout << "IndexJoin" << std::endl;
    } else {
        std::cout << "Unknown" << std::endl;
    }

    for (auto in : getInputOperators(tree)) {
        printTree(in, tabs + 1);
    }
}

std::vector<Operator*> getInputOperators(Operator* target) {
    std::vector<std::unique_ptr<Operator>> inputs = target->getInputs();
    std::vector<Operator*> result = vutil::map<Operator*>(inputs, [](const std::unique_ptr<Operator>& op) { return op.get(); });

    target->setInputs(std::move(inputs));
    return result;
}


Operator* getOutputOperator(Operator* tree, Operator* target) {
    if (!tree || !target) {
        return nullptr;
    }
    
    for (auto in : getInputOperators(tree)) {
        if (in == target) {
            return tree;
        } 

        Operator* out = getOutputOperator(in, target);

        if (out) {
            return out;
        }
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