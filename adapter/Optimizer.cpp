#include "Optimizer.hpp"

#include "OperatorUtil.hpp"

namespace adapter {

void Optimizer::pushDownPredicates() {
    outil::forEach<Select>(tree.get(), [&](Select* select) {
        std::vector<std::unique_ptr<Expression>> required = cutil::splitRequired(std::move(select->condition));

        for (size_t i = 0; i < required.size(); i++) {
            Operator* op = outil::getIUOperator(tree.get(), required[i]->getIUs());
            tree = outil::insertSelectIfNotPresent(std::move(tree), op);

            // cast is valid as a select statement was inserted after op
            Select* insertedSelect = (Select*) outil::getOutputOperator(tree.get(), op);
            insertedSelect->condition = cutil::combineRequired({std::move(insertedSelect->condition), std::move(required[i])});

            required.erase(required.begin() + (i--));
        }

        if (required.size() > 0) {
            select->condition = cutil::combineRequired(&required);
        } else {
            tree = outil::removeSelect(std::move(tree), select);
        }

        return true;
    });
}

void Optimizer::makeIndexJoins() {
    outil::forEach<Join>(tree.get(), [&](Join* join) {
        
        cutil::EqualBinaryExpressionData data = cutil::extractEqualBinaryExpressionPairs(tree.get(), std::move(join->condition));
        

        return true;
    });
}

std::vector<IndexJoin::Pair> Optimizer::getIndexJoinIUs(Join* join, Operator* joinInput, const cutil::EqualBinaryExpressionData& data) const {
    TableScan* scan = dynamic_cast<TableScan*>(joinInput);
    std::vector<IndexJoin::Pair> result;

    if (!scan) {
        return result;
    }

    for (auto& p : data.pairs) {
        if (scan->isKey(p.first))
            result.push_back({p.first, p.second});
        if (scan->isKey(p.second))
            result.push_back({p.second, p.first});
    }

    if (result.size() == scan->getKeyCount()) {
        return result;
    }
    
    return {};
}

}