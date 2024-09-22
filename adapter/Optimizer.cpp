#include "Optimizer.hpp"

#include <iostream>
#include "OperatorUtil.hpp"
#include "semana/SemanticAnalysis.hpp"

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
            std::vector<std::unique_ptr<Operator>> inputs = out->getInputs();

            for (auto& in : inputs) {
                if (in.get() == op) {
                    in = std::make_unique<Select>(std::move(in), nullptr);
                }
            }

            out->setInputs(std::move(inputs));
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
    std::cout << "before:" << std::endl;
    outil::printTree(tree.get());

    // iterate over all scans to check if they can be converted to index scans and if so, convert them
    for (TableScan* scan : scans) {
        Select* select = dynamic_cast<Select*>(outil::getOutputOperator(tree.get(), scan));

        if (!select) {
            continue;
        }

        IUSet keyIUs = scan->getKeyIUs();
        std::vector<std::unique_ptr<Expression>> required = cutil::splitRequired(std::move(select->condition));
        IUSet indexIUs;
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

                if (leftAsIURef && rightIUCount == 0 && keyIUs.contains(leftAsIURef->getIU()) && !indexIUs.contains(leftAsIURef->getIU())) {
                    indexIUs.add(leftAsIURef->getIU());
                    indexExpressions.push_back(std::move(c->right));
                } else if (rightAsIURef && leftIUCount == 0 && keyIUs.contains(rightAsIURef->getIU()) && !indexIUs.contains(rightAsIURef->getIU())) {
                    indexIUs.add(rightAsIURef->getIU());
                    indexExpressions.push_back(std::move(c->left));
                } else {
                    remainingExpressions.push_back(std::move(r));
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
            for (size_t i = 0; i < indexIUs.size(); i++) {
                remainingExpressions.push_back(std::make_unique<ComparisonExpression>(std::make_unique<IURef>(indexIUs[i]), std::move(indexExpressions[i]), ComparisonExpression::Equal, saneql::Collate::None));
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
                select->setInputs(vutil::make(std::move(indexScan)));
            } else {
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

    std::cout << "after:" << std::endl;
    outil::printTree(tree.get());
}

void Optimizer::optimizeJoins() {
    std::vector<Join*> joins = outil::getAll<Join>(tree.get());

    for (Join* join : joins) {
        // get the equi join key IUs
        auto keyIUs = outil::getJoinKeyIUs(join->left.get(), join->right.get(), join->condition.get());
        TableScan* left = dynamic_cast<TableScan*>(join->left.get());
        TableScan* right = dynamic_cast<TableScan*>(join->right.get());

        // returns true if the joinKeyIUs match the tableKeyIUs
        auto canBeIndexed = [](const IUSet& tableKeyIUs, const IUSet& joinKeyIUs) {
            if (tableKeyIUs.size() != joinKeyIUs.size()) {
                return false;
            }

            for (auto iu : tableKeyIUs) {
                if (!joinKeyIUs.contains(iu)) {
                    return false;
                }
            }

            return true;
        };

        // orders the key IUs from the joins to fit the order of the key IUs in the table
        auto orderKeyIUs = [](const IUSet tableKeyIUs, IUSet* indexIUs, IUSet* otherIUs) {
            IUSet indexResult;
            IUSet otherResult;

            for (auto iu : tableKeyIUs) {
                for (size_t i = 0; i < indexIUs->size(); i++) {
                    if ((*indexIUs)[i] == iu) {
                        indexResult.add((*indexIUs)[i]);
                        otherResult.add((*otherIUs)[i]);
                    }
                }
            }

            *indexIUs = indexResult;
            *otherIUs = otherResult;
        };

        std::unique_ptr<Operator> scan;
        std::unique_ptr<Operator> input;
        IUSet indexIUs;

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
            
            std::vector<std::unique_ptr<Expression>> indexIURefs = vutil::map<std::unique_ptr<Expression>>(indexIUs.data(), [](const IU* iu) { return std::make_unique<IURef>(iu); });
            std::unique_ptr<IndexScan> indexScan = std::make_unique<IndexScan>(std::move(scanCasted->name), std::move(scanCasted->columns), std::move(indexIURefs));
            std::unique_ptr<IndexJoin> indexJoin = std::make_unique<IndexJoin>(std::move(input), std::move(indexScan));
            std::vector<std::unique_ptr<Operator>> inputs = out->getInputs();

            for (auto& in : inputs) {
                if (in.get() == join) {
                    in = std::move(indexJoin);
                    break;
                }
            }

            out->setInputs(std::move(inputs));
        }
    }
}

}