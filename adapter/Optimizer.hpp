#pragma once

#include <functional>
#include <queue>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"
#include "ConditionUtil.hpp"

namespace adapter {

using namespace saneql::algebra;

/// A tree operator that just forwards all calls to the input operator
/// It is used for making optimization algorithms easier as the root of the operator tree will never change
class TreeOperator : public Operator {
    /// The input
    std::unique_ptr<Operator> input;

    public:
    /// Constructor
    TreeOperator(std::unique_ptr<Operator> input)
        : input(std::move(input)) {}

    // Get the IUs
    std::vector<const IU*> getIUs() const override { return input->getIUs(); }
    // Get the inputs
    std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(input)); }
    // Set the inputs
    void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { input = std::move(inputs[0]); }
    // Generate Cpp
    void generate(CppWriter& out, std::function<void()> consume) override { input->generate(out, consume); }
};

class Optimizer {
private:
    std::unique_ptr<Operator> tree;

public:
    Optimizer(std::unique_ptr<Operator> tree) : tree(std::make_unique<TreeOperator>(std::move(tree))) {}

    // Optimizes the selects by pushing them down
    void optimizeSelects();

    // Optimizes the scans by using index scans
    void optimizeScans();

    // Optimizes joins by using index joins
    void optimizeJoins();

    Operator* get() { return tree.get(); }
};

}