#pragma once

#include <vector>
#include <memory>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

namespace outil {

/// Iterate over all operators of the given type
template <typename TOp>
void forEach(Operator* tree, std::function<bool(TOp* op)> consumer) {
    TOp* op = dynamic_cast<TOp*>(tree);

    if (op && !consumer(op)) {
        return;
    }

    for (auto input : tree->getInputs()) {
        forEach(input, consumer);
    }
}

// Insert the select operator after the target operator and return the new tree
std::unique_ptr<Operator> insertSelectIfNotPresent(std::unique_ptr<Operator> tree, Operator* target);

// Remove the target select operator and return the new tree
std::unique_ptr<Operator> removeSelect(std::unique_ptr<Operator> tree, Select* target);

// Get the output operator for the target operator
Operator* getOutputOperator(Operator* tree, Operator* target);

// Get the operator that provides the specified ius
Operator* getIUOperator(Operator* tree, std::vector<const IU*> ius);

}

}