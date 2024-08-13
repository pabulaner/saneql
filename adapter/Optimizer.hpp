#pragma once

#include <functional>
#include <queue>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"
#include "ConditionUtil.hpp"

namespace adapter {

using namespace saneql::algebra;

class Optimizer {
private:
    std::unique_ptr<Operator> tree;

public:
    Optimizer(std::unique_ptr<Operator> tree) : tree(std::move(tree)) {}

    void optimizeSelects();

    void optimizeJoins();

    std::unique_ptr<Operator> get() { return std::move(tree); }
};

}