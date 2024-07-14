#pragma once

#include <vector>
#include <unordered_map>

#include "vmcache/vmcache.hpp"

namespace adapter {

template <typename TNext, typename TRecord, typename TScanFn>
struct ScanOp {
    /// The next operator
    TNext* next;
    /// The input
    vmcacheAdapter<TRecord>* adapter;
    /// The scan function
    TScanFn scan;

    public:
    /// The constructor
    ScanOp(TNext* next, vmcacheAdapter<TRecord>* adapter, TScanFn scan) : next(next), adapter(adapter), scan(scan) {}

    void process() {
        next->begin();
        adapter->forEach([&](auto& key, auto& value) {
            scan(key, value);
            next->process();
        });
        next->end();
    }
};

template <typename TNext, typename TSelectFn>
struct SelectOp {
    /// The next operator
    TNext* next;
    /// The select function
    TSelectFn select;

    SelectOp(TNext* next, TSelectFn select) : next(next), select(select) {}

    void begin() { next->begin(); }

    void end() { next->end(); }

    void process() {
        if (select()) {
            next->process();
        }
    }
};

template <typename TNext, typename TMapFn>
struct MapOp {
    /// The next operator
    TNext* next;
    /// The map function
    TMapFn map;

    MapOp(TNext* next, TMapFn map) : next(next), map(map) {}

    void begin() { next->begin(); }

    void end() { next->end(); }

    void process() {
        map();
        next->process();
    }
};

template <typename TRow, typename TNext, typename TGetFn, typename TSetFn, typename TConditionFn>
struct JoinOp {
    /// The next operator
    TNext* next;
    /// The add function
    TGetFn get;
    /// The set function
    TSetFn set;
    /// The condition function
    TConditionFn condition;
    /// Is first call
    bool first;
    /// The process function
    void(process*)();
    /// The rows
    std::vector<TRow> rows;

    JoinOp(TNext* next, TGetFn get, TSetFn set, TConditionFn condition) : next(next), get(get), set(set), condition(condition), first(true) {}

    void begin() {
        if (first) {
            process = [&]() {
                rows.push_back(get());
            }
        } else {
            next->begin();
            process = [&]() {
                for (auto& row : rows) {
                    set(row);
                    if (condition()) {
                        next->process();
                    }
                }
            }
        }
    }

    void end() {
        if (first) {
            first = false;
        } else {
            next->end();
        }
    }
};

template <typename TNext, typename TKey, typename TValue, typename TGetFn, typename TGroupByFn, typename TSetFn>
struct GroupByOp {
    /// The next operator
    TNext* next;
    /// The get function
    TGetFn get;
    /// The group by function
    TGroupByFn groupBy;
    /// The set function
    TSetFn set;
    /// The group by map
    std::unordered_map<TKey, TValue> rows;

    GroupByOp(TNext* next, TKey key, TValue value, TGetFn get, TGroupByFn groupBy, TSetFn set);

    void begin() {}

    void end() {
        next->begin();
        for (auto& keyValue : rows) {
            set(keyValue.first(), keyValue.second());
            next->process();
        }
        next->end();
    }

    void process() {
        TKey key = get();
        if (!rows.contains(key)) {
            rows[key] = {};
        }
        groupBy(key, rows[key]);
    }
};

template <typename TOutputFn>
struct OutputOp {
    /// The output function
    TOutputFn output;

    OutputOp(TOutputFn output) : output(output) {}

    void begin() {}

    void end() {}

    void process() {
        output();
    }
};

}