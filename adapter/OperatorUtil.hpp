#pragma once

#include <vector>
#include <memory>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

namespace outil {

using namespace saneql::algebra;

// Print the operator tree
void printTree(Operator* tree, size_t tabs = 0);

// Get the raw input operator pointers
std::vector<Operator*> getInputOperators(Operator* target);

// Get the output operator for the target operator
Operator* getOutputOperator(Operator* tree, Operator* target);

// Get the operator that provides the specified ius
Operator* getIUOperator(Operator* tree, std::vector<const IU*> ius);

// Get the join key IU pairs
std::pair<std::vector<const IU*>, std::vector<const IU*>> getJoinKeyIUs(Operator* left, Operator* right, Expression* exp);

// Iterate over all operators of the given type
template <typename TOp>
void forEach(Operator* tree, std::function<bool(TOp* op)> consumer) {
    TOp* op = dynamic_cast<TOp*>(tree);

    if (op && !consumer(op)) {
        return;
    }

    for (auto in : getInputOperators(tree)) {
        forEach(in, consumer);
    }
}

}

}