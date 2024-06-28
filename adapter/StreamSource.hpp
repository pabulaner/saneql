#pragma once

#include <functional>

template <typename T>
class IStreamSource {
public:
    // returned pointers are only guaranteed to be valid until
    // the next call to next()
    virtual const T* next() = 0;
};

template <typename T>
class DatabaseStreamSource : public IStreamSource<T> {
private:

};

template <typename T>
class FilterStreamSource : public IStreamSource<T> {
private:
    IStreamSource<T> source;

    std::function<bool(const T&)> predicate;

public:
    FilterStreamSource(IStreamSource<T> source, std::function<bool(const T&)> predicate) 
        : source(source)
        , predicate(predicate)
    {}

    virtual const T* next() override {
        const T* value;

        while (value = source.next()) {
            if (predicate(value)) {
                return value;
            }
        }

        return nullptr;
    }
};

template <typename TIn, typename TOut>
class MapStreamSource : IStreamSource<TOut> {
private:
    IStreamSource<TIn> source;

    std::function<TOut(const TIn&)> mapper;

    TOut out;

public:
    MapStreamSource(IStreamSource<TIn> source, std::function<TOut(const TIn&)> mapper) 
        : source(source)
        , mapper(mapper)
        , out()
    {}

    virtual const TOut* next() override {
        TIn* value;

        if (value = source.next()) {
            out = mapper(*value);
            return &out;
        }

        return nullptr;
    }
};

// implementation