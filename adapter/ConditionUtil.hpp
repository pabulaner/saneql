#pragma once

#include <vector>
#include <memory>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

namespace cutil {

using namespace saneql::algebra;

typedef std::pair<const IU*, const IU*> IUPair;

struct EqualBinaryExpressionData {
    // The condition without the equal binary expressions
    std::unique_ptr<Expression> condition;
    // The IU pairs from the equal binary expressions
    std::vector<IUPair> pairs;
};

// Splits the provided condition in the required conditions that need to be satisfied for the condition to be true
std::vector<std::unique_ptr<Expression>> splitRequired(std::unique_ptr<Expression> condition);

// Combines the provided required conditions into one condition that is connected with AND
std::unique_ptr<Expression> combineRequired(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);

}

}