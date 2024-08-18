#include "Optimizer.hpp"

#include <iostream>
#include "OperatorUtil.hpp"

namespace adapter {

void Optimizer::optimizeSelects() {
    std::vector<std::unique_ptr<Expression>> conditions;

    std::function<std::unique_ptr<Operator>(std::unique_ptr<Operator>)> extractConditions = [&](std::unique_ptr<Operator> tree) {
        std::vector<std::unique_ptr<Operator>> inputs = tree->getInputs();

        for (auto& in : inputs) {
            in = extractConditions(std::move(in));
        }

        tree->setInputs(std::move(inputs));

        Select* select = dynamic_cast<Select*>(tree.get());

        if (select) {
            std::vector<std::unique_ptr<Expression>> required = cutil::splitRequired(std::move(select->condition));

            for (auto& r : required) {
                conditions.push_back(std::move(r));
            }

            return std::move(select->input);
        } else {
            return tree;
        }
    };

    auto insertAndGetSelect = [&](Operator* op) {
        Operator* out = outil::getOutputOperator(tree.get(), op);
        bool isSelect = dynamic_cast<Select*>(out);

        if (!isSelect) {
            if (out) {
                std::vector<std::unique_ptr<Operator>> inputs = out->getInputs();

                for (auto& in : inputs) {
                    if (in.get() == op) {
                        in = std::make_unique<Select>(std::move(in), nullptr);
                    }
                }

                out->setInputs(std::move(inputs));
            } else {
                tree = std::make_unique<Select>(std::move(tree), nullptr);
            }
        }

        return static_cast<Select*>(outil::getOutputOperator(tree.get(), op));
    };

    tree = extractConditions(std::move(tree)); 

    for (auto& c : conditions) {
        Operator* op = outil::getIUOperator(tree.get(), c->getIUs());
        Select* select = insertAndGetSelect(op);

        if (select->condition.get()) {
            select->condition = cutil::combineRequired(std::move(select->condition), std::move(c));
        } else {
            select->condition = std::move(c);
        }
    }
}

void Optimizer::optimizeJoins() {
    std::vector<Join*> joins;

    outil::forEach<Join>(tree.get(), [&](Join* join) {
        joins.push_back(join);
        return true;
    });

    for (Join* join : joins) {
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

        std::unique_ptr<Operator> scan;
        std::unique_ptr<Operator> input;
        std::vector<const IU*> indexIUs;

        // check if left or right can be index joined
        if (left && canBeIndexed(left->getKeyIUs(), keyIUs.first)) {
            orderKeyIUs(left->getKeyIUs(), &keyIUs.first, &keyIUs.second);
            scan = std::move(join->left);
            input = std::move(join->right);
            indexIUs = std::move(keyIUs.second);
        } else if (right && canBeIndexed(right->getKeyIUs(), keyIUs.second)) {
            orderKeyIUs(right->getKeyIUs(), &keyIUs.second, &keyIUs.first);
            scan = std::move(join->right);
            input = std::move(join->left);
            indexIUs = std::move(keyIUs.first);
        }

        if (indexIUs.size() > 0) {
            Operator* out = outil::getOutputOperator(tree.get(), join);
            TableScan* scanCasted = static_cast<TableScan*>(scan.get());
            std::unique_ptr<IndexJoin> indexJoin = std::make_unique<IndexJoin>(std::move(scanCasted->name), std::move(scanCasted->columns), std::move(input), std::move(indexIUs));
            
            if (out) {
                std::vector<std::unique_ptr<Operator>> inputs = out->getInputs();

                for (auto& in : inputs) {
                    if (in.get() == join) {
                        in = std::move(indexJoin);
                        break;
                    }
                }

                out->setInputs(std::move(inputs));
            } else {
                tree = std::move(indexJoin);
            }
        }
    }
}

}