#include "ConditionUtil.hpp"

namespace adapter {

namespace cutil {

std::vector<std::unique_ptr<Expression>> splitRequired(std::unique_ptr<Expression> condition) {
    std::vector<std::unique_ptr<Expression>> result;
    BinaryExpression* bin = dynamic_cast<BinaryExpression*>(condition.get());

    if (bin && bin->op == BinaryExpression::And) {
        auto left = splitRequired(std::move(bin->left));
        auto right = splitRequired(std::move(bin->right));

        for (auto& l : left) {
            result.push_back(std::move(l));
        }
        for (auto& r : right) {
            result.push_back(std::move(r));
        }
    } else {
        result.push_back(std::move(condition));
    }

    return result;
}

std::unique_ptr<Expression> combineRequired(std::vector<std::unique_ptr<Expression>>* required) {
    if (required->size() == 0) {
        return nullptr;
    } else if (required->size() == 1) {
        return std::move(required->at(0));
    }

    auto left = std::move(required->back());
    required->pop_back();
    auto right = std::move(required->back());
    required->pop_back();

    required->push_back(std::make_unique<BinaryExpression>(left, right, saneql::Type::Bool, BinaryExpression::And));
    return combineRequired(required);
}

EqualBinaryExpressionData extractEqualBinaryExpressionPairs(Operator* tree, std::unique_ptr<Expression> condition) {
    EqualBinaryExpressionData result;
    std::vector<std::unique_ptr<Expression>> required = splitRequired(std::move(condition));

    for (size_t i = 0; i < required.size(); i++) {
        BinaryExpression* exp = dynamic_cast<BinaryExpression*>(required[i].get());

        if (exp) {
            IURef* left = dynamic_cast<IURef*>(exp->left.get());
            IURef* right = dynamic_cast<IURef*>(exp->right.get());

            if (left && right) {
                result.pairs.push_back({left->getIU(), right->getIU()});
                required.erase(required.begin() + (i--));
            }
        }
    }

    result.condition = combineRequired(&required);
    return result;
}

}

}