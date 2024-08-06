#include "Optimizer.hpp"

namespace adapter {

void Optimizer::pushDownPredicates() {
    forEach<Select>(tree, [&](Select* value) {
        std::vector<Expression*> required = getRequiredConditions(value->condition.get());

        for (auto exp : required) {
            Operator* target;
            // check if predicate may be pushed down to target
            if ((target = getOperatorForIUs(exp->getIUs())) && target != value->input.get()) { 
                Operator* output = getOutputOperator(target);
                Select* select = dynamic_cast<Select*>(output);

                // check if output operator already is a predicate and if not, create and add the predicate as output
                if (!select) {
                    std::vector<Operator*> inputs = output->getInputs();
                    util::replace(&inputs, target, predicate);
                    output->setInputs(inputs);
                }
            }
        }

        return true;
    });
}

Operator* Optimizer::getOutputOperator(Operator* op) const {
    Operator* result = nullptr;

    forEach<Operator>(tree, [&](Operator* value) {
        if (value == op) {
            return false;
        }

        for (auto input : value->getInputs()) {
            if (input == op) {
                result = value;
                return false;
            }
        }

        return true;
    });

    return result;
}

}