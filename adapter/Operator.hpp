#pragma once

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

template <typename TNext, typename TRow, typename TGetFn, typename TSetFn, typename TConditionFn>
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
    std::function<void()> process;
    /// The rows
    std::vector<TRow> rows;

    JoinOp(TNext* next, TRow row, TGetFn get, TSetFn set, TConditionFn condition) : next(next), get(get), set(set), condition(condition), first(true) {}

    void begin() {
        if (first) {
            process = [&]() {
                rows.push_back(get());
            };
        } else {
            next->begin();
            process = [&]() {
                for (auto it = rows.begin(); it != rows.end(); it++) {
                    set(*it);
                    if (condition()) {
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