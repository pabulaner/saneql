#pragma once

#include <vector>
#include <memory>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

namespace outil {

using namespace saneql::algebra;

/// Iterate over all operators of the given type
template <typename TOp>
void forEach(Operator* tree, std::function<bool(TOp* op)> consumer) {
    TOp* op = dynamic_cast<TOp*>(tree);

    if (op && !consumer(op)) {
        return;
    }

    std::vector<std::unique_ptr<Operator>> inputs = tree->getInputs();

    for (auto& input : inputs) {
        forEach(input.get(), consumer);
    }

    tree->setInputs(std::move(inputs));
}

template <typename TOp>
void forEachModifiable(Operator* tree, std::function<bool(TOp* op)> consumer) {
    std::vector<TOp*> ops;

    forEach<TOp>(tree, [&](TOp* op) {
        ops.push_back(op);
        return true;
    });

    for (TOp* op : ops) {
        if (op && !consumer(op)) {
            return;
        }
    }
}

// Print the operator tree
void printTree(Operator* tree);

// Insert the select operator after the target operator and return the new tree
std::unique_ptr<Operator> insertSelectIfNotPresent(std::unique_ptr<Operator> tree, Operator* target);

// Remove the target select operator and return the new tree
std::unique_ptr<Operator> removeSelect(std::unique_ptr<Operator> tree, Select* target);

// Get the output operator for the target operator
Operator* getOutputOperator(Operator* tree, Operator* target);

// Get the operator that provides the specified ius
Operator* getIUOperator(Operator* tree, std::vector<const IU*> ius);

// Get the join key IU pairs
std::pair<std::vector<const IU*>, std::vector<const IU*>> getJoinKeyIUs(Operator* left, Operator* right, Expression* exp);

}

}