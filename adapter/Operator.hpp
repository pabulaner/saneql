#pragma once

namespace adapter {

template <typename TNext, typename TFn>
class ScanOp {
    /// The next operator
    TNext* next;
    /// The input
    int input;
    /// The scan function
    TFn scan;

    public:
    /// The constructor
    ScanOp(TNext* next, TFn scan) : next(next), scan(scan) {}

    void begin() {
        next->begin();
        input->forEach([&](auto& key, auto& value) {
            scan(key, value);
            next->process();
        });
        next->end();
    }
};

template <typename TNext, typename TFn>
class SelectOp {
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

template <typename TFn>
class OutputOp {
    /// The output function
    TFn output;

    OutputOp(TFn select) : select(select) {}

    void begin() {}

    void end() {}

    void process() {
        output();
    }
};

}