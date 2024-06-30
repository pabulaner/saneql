#pragma once

#include <functional>

#include "Row.hpp"
#include "vmcache.hpp"

namespace adapter {

template <typename TIn, typename TOut>
class IStreamSource {
protected:
    TIn source;

public:
    // returned pointers are only guaranteed to be valid until
    // the next call to next()
    virtual const T* next() = 0;
};

template <typename TSize, typename TMap, typename TIn, typename... TArgs>
class DatabaseStreamSource : public IStreamSource<vmcacheAdapter<TIn>*, TRow> {
private:
    typedef Row<TSize, TMap, TIn, TArgs...> TRow;

    TRow row;

public:
    DatabaseStreamSource(vmcacheAdapter<TIn>* source, TArgs... args) 
        : source(source)
        , row(TRow(args...))
    {}

    virtual const TRow* next() override {
        return nullptr;
    }
};

template <typename T>
class SelectStreamSource : public IStreamSource<IStreamSource<T>, T> {
private:
    std::function<bool(const T&)> predicate;

public:
    SelectStreamSource(IStreamSource<T> source, std::function<bool(const T&)> predicate) 
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
class MapStreamSource : IStreamSource<IStreamSource<TIn>, TOut> {
private:
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

} // namespace adapter