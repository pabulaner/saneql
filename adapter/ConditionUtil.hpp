#pragma once

#include <vector>
#include <memory>

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

namespace cutil {

using namespace saneql::algebra;

// Struct used to store IU pairs for an index join
struct IndexJoinPair {
    // The IU that can be used with a index scan
    const IU* indexIU;
    // The IU that is compared to the index IU in the index join
    const IU* otherIU;
};

struct IndexJoinData {
    // The condition without the index join conditions
    std::unique_ptr<Expression> condition;
    // The index join pairs extracted from the condition
    std::vector<IndexJoinPair> indexJoinPairs;
};

// Splits the provided condition in the required conditions that need to be satisfied for the condition to be true
std::vector<std::unique_ptr<Expression>> splitRequired(std::unique_ptr<Expression> condition);

// Combines the provided required conditions into one condition that is connected with AND
std::unique_ptr<Expression> combineRequired(const std::vector<std::unique_ptr<Expression>>& required);

// Extracts the index join pairs from the provided condition if there are any
IndexJoinData extractIndexJoinConditions(Operator* tree, std::unique_ptr<Expression> condition);

}

}