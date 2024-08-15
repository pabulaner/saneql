#include "Optimizer.hpp"

#include "OperatorUtil.hpp"

namespace adapter {

void Optimizer::optimizeSelects() {
    outil::forEachModifiable<Select>(tree.get(), [&](Select* select) {
        // split the condition into the required parts
        std::vector<std::unique_ptr<Expression>> required = cutil::splitRequired(std::move(select->condition));

        // check for each required condition how far it can be pushed down
        for (size_t i = 0; i < required.size(); i++) {
            Operator* op = outil::getIUOperator(tree.get(), required[i]->getIUs());
            tree = outil::insertSelectIfNotPresent(std::move(tree), op);

            // cast is valid as a select statement was inserted after op
            Select* insertedSelect = (Select*) outil::getOutputOperator(tree.get(), op);
            insertedSelect->condition = insertedSelect->condition.get() 
                ? cutil::combineRequired(std::move(insertedSelect->condition), std::move(required[i]))
                : std::move(required[i]);

            required.erase(required.begin() + (i--));
        }

        if (required.size() > 0) {
            // move all left other required conditions back in the operator where they came from
            select->condition = std::move(required[0]);

            for (size_t i = 1; i < required.size(); i++) {
                select->condition = std::make_unique<BinaryExpression>(std::move(select->condition), std::move(required[i]), saneql::Type::getBool(), BinaryExpression::And);
            }
        } else {
            // remove empty select statement
            tree = outil::removeSelect(std::move(tree), select);
        }

        return true;
    });
}

void Optimizer::optimizeJoins() {
    outil::forEachModifiable<Join>(tree.get(), [&](Join* join) {
        // get the equi join key IUs
        auto keyIUs = outil::getJoinKeyIUs(join->left.get(), join->right.get(), join->condition.get());
        TableScan* left = dynamic_cast<TableScan*>(join->left.get());
        TableScan* right = dynamic_cast<TableScan*>(join->right.get());

        // returns true if the joinKeyIUs match the tableKeyIUs
        auto canBeIndexed = [](const std::vector<const IU*>& tableKeyIUs, const std::vector<const IU*>& joinKeyIUs) {
            if (tableKeyIUs.size() != joinKeyIUs.size()) {
                return false;
            }

            for (auto iu : tableKeyIUs) {
                if (!vutil::contains(joinKeyIUs, iu)) {
                    return false;
                }
            }

            return true;
        };

        // orders the key IUs from the joins to fit the order of the key IUs in the table
        auto orderKeyIUs = [](const std::vector<const IU*> tableKeyIUs, std::vector<const IU*>* indexIUs, std::vector<const IU*>* otherIUs) {
            std::vector<const IU*> indexResult;
            std::vector<const IU*> otherResult;

            for (auto iu : tableKeyIUs) {
                for (size_t i = 0; i < indexIUs->size(); i++) {
                    if (indexIUs->at(i) == iu) {
                        indexResult.push_back(indexIUs->at(i));
                        otherResult.push_back(otherIUs->at(i));
                    }
                }
            }

            *indexIUs = indexResult;
            *otherIUs = otherResult;
        };

        Operator* out = outil::getOutputOperator(tree.get(), join);
        std::unique_ptr<IndexJoin> indexJoin;

        // check if left or right can be index joined
        if (left && canBeIndexed(left->getKeyIUs(), keyIUs.first)) {
            orderKeyIUs(left->getKeyIUs(), &keyIUs.first, &keyIUs.second);
            indexJoin = std::make_unique<IndexJoin>(std::move(join->left), std::move(join->right), keyIUs.second);
        } else if (right && canBeIndexed(right->getKeyIUs(), keyIUs.second)) {
            orderKeyIUs(right->getKeyIUs(), &keyIUs.second, &keyIUs.first);
            indexJoin = std::make_unique<IndexJoin>(std::move(join->right), std::move(join->left), keyIUs.first);
        }

        if (indexJoin.get()) {
            if (out) {
                std::vector<Operator*> inputs = out->getInputs();

                for (size_t i = 0; i < inputs.size(); i++) {
                    if (inputs[i] == join) {
                        inputs[i] = indexJoin.get();
                    }
                }
            } else {
                indexJoin;
            }
        }

        return true;
    });
}

}