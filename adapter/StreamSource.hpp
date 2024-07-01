#pragma once

#include <functional>

#include "Row.hpp"

namespace adapter {

template <typename T>
class IStreamSourceBase {
public:
    // returned pointers are only guaranteed to be valid until
    // the next call to next()
    virtual const T* next() = 0;
};

template <typename TIn, typename TOut>
class IStreamSource : IStreamSourceBase<TOut> {
protected:
    TIn source;

    IStreamSource(TIn& source) 
        : source(source)
    {}
};

template <std::size_t TSize, RowIndexMap<TSize> TMap, typename TIn, typename TIterator, typename... TArgs>
class IteratorStreamSource : public IStreamSource<TIn, Row<TSize, TMap, TIn, TArgs...>> {
private:
    typedef Row<TSize, TMap, TIn, TArgs...> TRow;

    TIterator iterator;

    TRow row;

public:
    IteratorStreamSource(TIn source, TArgs... args) 
        : IStreamSource<TIn, Row<TSize, TMap, TIn, TArgs...>>(source)
        , row(TRow(args...))
        , iterator(source.begin())
    {}

    virtual const TRow* next() override {
        if (iterator != this->source.end()) {
            row->setKey(iterator->first);
            row->setValue(iterator->second);

            iterator++;
            return &row;
        }

        return nullptr;
    }
};

/*
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

*/

// implementation

} // namespace adapter