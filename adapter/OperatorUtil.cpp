#include "OperatorUtil.hpp"

namespace adapter {

namespace outil {

std::unique_ptr<Operator> insertSelectIfNotPresent(std::unique_ptr<Operator> tree, Operator* target) {
    if (tree.get() == target) {
        return std::make_unique<Select>(std::move(tree), nullptr);
    }
    
    Operator* out = getOutputOperator(tree.get(), target);

    // check if the output already is a select operator
    if (dynamic_cast<Select*>(out)) {
        return tree;
    }

    std::unique_ptr<Select> select = std::make_unique<Select>(std::unique_ptr<Operator>(target), std::unique_ptr<Expression>(nullptr));
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

}

}