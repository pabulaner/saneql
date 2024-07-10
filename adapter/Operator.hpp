#pragma once

#include "vmcache/vmcache.hpp"

namespace adapter {

template <typename TNext, typename TRecord, typename TFn>
struct ScanOp {
    /// The next operator
    TNext* next;
    /// The input
    vmcacheAdapter<TRecord>& adapter;
    /// The scan function
    TFn scan;

    public:
    /// The constructor
    ScanOp(TNext* next, vmcacheAdapter<TRecord>& adapter, TFn scan) : next(next), adapter(adapter), scan(scan) {}

    void process() {
        next->begin();
        adapter.forEach([&](auto& key, auto& value) {
            scan(key, value);
            next->process();
        });
        next->end();
    }
};

template <typename TNext, typename TFn>
struct SelectOp {
    /// The next operator
    TNext* next;
    /// The select function
    TFn select;

    SelectOp(TNext* next, TFn select) : next(next), select(select) {}

    void begin() { next->begin(); }

    void end() { next->end(); }

    void process() {
        if (select()) {
            next->process();
        }
    }
};

template <typename TNext, typename TFn>
struct MapOp {
    /// The next operator
    TNext* next;
    /// The map function
    TFn map;

    MapOp(TNext* next, TFn map) : next(next), map(map) {}

    void begin() { next->begin(); }

    void end() { next->end(); }

    void process() {
        map();
        next->process();
    }
};

template <typename TFn>
struct OutputOp {
    /// The output function
    TFn output;

    OutputOp(TFn output) : output(output) {}

    void begin() {}

    void end() {}

    void process() {
        output();
    }
};

}