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

void Optimizer::optimizeScans() {
    std::vector<TableScan*> scans = outil::getAll<TableScan>(tree.get());

    // iterate over all scans to check if they can be converted to index scans and if so, convert them
    for (TableScan* scan : scans) {
        Select* select = dynamic_cast<Select*>(outil::getOutputOperator(tree.get(), scan));

        if (!select) {
            continue;
        }

        std::vector<const IU*> keyIUs = scan->getKeyIUs();
        std::vector<std::unique_ptr<Expression>> required = cutil::splitRequired(std::move(select->condition));
        std::vector<const IU*> indexIUs;
        std::vector<std::unique_ptr<Expression>> indexExpressions;
        std::vector<std::unique_ptr<Expression>> remainingExpressions;

        // iterate over all required conditions and see if they contain all IUs required as the key to the table scan
        for (auto& r : required) {
            ComparisonExpression* c = dynamic_cast<ComparisonExpression*>(r.get());

            // if true, comparison could be used as an index expression
            if (c && c->mode == ComparisonExpression::Equal) {
                IURef* leftAsIURef = dynamic_cast<IURef*>(c->left.get());
                IURef* rightAsIURef = dynamic_cast<IURef*>(c->right.get());
                size_t leftIUCount = c->left->getIUs().size();
                size_t rightIUCount = c->right->getIUs().size();

                if (leftAsIURef && rightIUCount == 0 && vutil::contains(keyIUs, leftAsIURef->getIU()) && !vutil::contains(indexIUs, leftAsIURef->getIU())) {
                    indexIUs.push_back(leftAsIURef->getIU());
                    indexExpressions.push_back(std::move(c->right));
                } else if (rightAsIURef && leftIUCount == 0 && vutil::contains(keyIUs, rightAsIURef->getIU()) && !vutil::contains(indexIUs, rightAsIURef->getIU())) {
                    indexIUs.push_back(rightAsIURef->getIU());
                    indexExpressions.push_back(std::move(c->left));
                }
            } else {
                remainingExpressions.push_back(std::move(r));
            }
        }

        std::unique_ptr<Operator> indexScan;

        // if true, scan can be converted to an index scan
        if (indexIUs.size() == scan->getKeyIUs().size()) {
            std::vector<std::unique_ptr<Expression>> sortedIndexExpressions;

            for (auto iu : keyIUs) {
                for (size_t i = 0; i < indexIUs.size(); i++) {
                    if (indexIUs[i] == iu) {
                        sortedIndexExpressions.push_back(std::move(indexExpressions[i]));
                        break;
                    }
                }
            }

            indexScan = std::make_unique<IndexScan>(std::move(scan->name), std::move(scan->columns), std::move(sortedIndexExpressions));
        } else {
            for (auto& exp : indexExpressions) {
                remainingExpressions.push_back(std::move(exp));
            }
        }

        // insert the remaining expressions back into the select operator
        if (remainingExpressions.size() > 0) {
            select->condition = std::move(remainingExpressions[0]);

            for (size_t i = 1; i < remainingExpressions.size(); i++) {
                select->condition = cutil::combineRequired(std::move(select->condition), std::move(remainingExpressions[i]));
            }
        }

        if (indexScan.get()) {
            if (select->condition.get()) {
                select->setInputs({std::move(indexScan)});
            } else {
                if (select == tree.get()) {
                    tree = std::move(indexScan);
                    break;
                }
                
                Operator* out = outil::getOutputOperator(tree.get(), select);
                std::vector<std::unique_ptr<Operator>> inputs = out->getInputs();

                for (auto& in : inputs) {
                    if (in.get() == select) {
                        in = std::move(indexScan);
                        break;
                    }
                }

                out->setInputs(std::move(inputs));
            }
        }
    }
}

void Optimizer::optimizeJoins() {
    std::vector<Join*> joins = outil::getAll<Join>(tree.get());

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