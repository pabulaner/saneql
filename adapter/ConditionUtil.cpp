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

std::unique_ptr<Expression> combineRequired(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
    return std::make_unique<BinaryExpression>(std::move(left), std::move(right), saneql::Type::getBool(), BinaryExpression::And);
}

}

}