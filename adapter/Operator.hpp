#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

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

template <typename TNext, typename TRow, typename TGetFn, typename TSetFn, typename TJoinFn>
struct JoinOp {
    /// The next operator
    TNext* next;
    /// The add function
    TGetFn get;
    /// The set function
    TSetFn set;
    /// The join function
    TJoinFn join;
    /// Is first call
    bool first;
    /// The process function
    std::function<void()> process;
    /// The rows
    std::vector<TRow> rows;

    JoinOp(TNext* next, TRow row, TGetFn get, TSetFn set, TJoinFn join) : next(next), get(get), set(set), join(join), first(true) {}

    void begin() {
        if (first) {
            process = [&]() {
                rows.push_back(get());
            };
        } else {
            next->begin();
            process = [&]() {
                for (auto& row : rows) {
                    set(row);
                    if (join()) {
                        next->process();
                    }
                }
            };
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

template <typename TNext, typename TKey, typename TValue, typename TGetFn, typename TSetFn, typename TGroupByFn>
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

    GroupByOp(TNext* next, TKey key, TValue value, TGetFn get, TSetFn set, TGroupByFn groupBy);

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

template <typename TNext, typename TRow, typename TGetFn, typename TSetFn, typename TSortFn>
struct SortOp {
    /// The next operator
    TNext* next;
    /// The get function
    TGetFn get;
    /// The set function
    TSetFn set;
    /// The order by function
    TSortFn sort;
    /// The rows
    std::vector<TRow> rows;

public:
    SortOp(TNext* next, TRow row, TGetFn get, TSetFn set, TSortFn sort) : next(next), get(get), set(set), sort(sort) {}

    void begin() {}

    void end() {
        std::sort(rows.begin(), rows.end(), sort);

        next->begin();
        for (auto& row : rows) {
            set(row);
            next->process();
        }
        next->end();
    }

    void process() {
        rows.push_back(get());
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