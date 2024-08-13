#include "Optimizer.hpp"

#include "OperatorUtil.hpp"

namespace adapter {

void Optimizer::optimizeSelects() {
    outil::forEach<Select>(tree.get(), [&](Select* select) {
        std::vector<std::unique_ptr<Expression>> required = cutil::splitRequired(std::move(select->condition));

        for (size_t i = 0; i < required.size(); i++) {
            Operator* op = outil::getIUOperator(tree.get(), required[i]->getIUs());
            tree = outil::insertSelectIfNotPresent(std::move(tree), op);

            // cast is valid as a select statement was inserted after op
            Select* insertedSelect = (Select*) outil::getOutputOperator(tree.get(), op);
            insertedSelect->condition = cutil::combineRequired(std::move(insertedSelect->condition), std::move(required[i]));

            required.erase(required.begin() + (i--));
        }

        if (required.size() > 0) {
            select->condition = std::move(required[0]);

            for (size_t i = 1; i < required.size(); i++) {
                select->condition = std::make_unique<BinaryExpression>(std::move(select->condition), std::move(required[i]), saneql::Type::getBool(), BinaryExpression::And);
            }

            return true;
        } else {
            tree = outil::removeSelect(std::move(tree), select);
            optimizeSelects();

            return false;
        }
    });
}

void Optimizer::optimizeJoins() {
    outil::forEach<Join>(tree.get(), [&](Join* join) {
        return true;
    });
}

}