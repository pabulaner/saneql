#pragma once

#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"

class OperatorTree {
public:
    // Insert the predicate after the input operator
    void insertPredicate(Operator* input, Select* predicate);
    // Remove the predicate
    void removePredicate(Select* predicate);

    // Get the required conditions of the target
    std::vector<Expression*> getRequiredConditions(Operator* target);
    // Set the required conditions of the target
    void setRequiredConditions(Operator* target, const std::vector<Expression*>& conditions);

    // Get the input operators for the target
    std::vector<Operator*> getInputOperators(Operator* target);
    // Get the output operator of the target
    Operator* getOutputOperator(Operator* target);

    // Get last operator that provides all IUs required for the condition
    Operator* getInputOperatorForCondition(Expression* condition);
};