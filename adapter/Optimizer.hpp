#pragma once

#include <functional>
#include <queue>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

using namespace saneql::algebra;

class Optimizer {
private:
    Operator* tree;

public:
    Optimizer(Operator* tree) : tree(tree) {}

    // Optimize the provided tree and return the result
    virtual Operator* optimize() = 0;

private:
    /// Iterate over all operators of the given type
    template <typename TOp>
    void forEach(Operator* root, std::function<bool(TOp* op)> consumer) const {
        std::queue<Operator*> waiting = {root};
        std::vector<Operator*> visited;

        while (Operator* op = waiting.pop()) {
            if (util::contains(visited, op)) {
                waiting.push_range(op->getInputs());
            } else {
                if (TOp* casted = dynamic_cast<TOp*>(op)) {
                    if (!consumer(casted)) {
                        return;
                    }
                    // start the iteration from the beginning to account for possible modifications inside consume
                    waiting = {root};
                }
            }

            visited.push_back(op);
        }
    }

    /// Get the operator that consumes the output of op
    Operator* getOutputOperator(Operator* op) const;

    /// Get all conditions that must be true for the entire condition to be true
    std::vector<Expression*> getRequiredConditions(Expression* condition) const;

    /// Get the operator that provides all specified IUs and return nullptr if none or more than one provide the IUs
    Operator* getOperatorForIUs(std::vector<const IU*> ius) const;
};

class PredicateOptimizer : public Optimizer {
public:
    PredicateOptimizer(Operator* tree) : Optimizer(tree) {}

    Operator* optimize() override;
};

}