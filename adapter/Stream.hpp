#pragma once

#include <functional>

#include "StreamSource.hpp"

namespace adapter {

template <typename T>
class Stream {
private:
    IStreamSourceBase<T>* source;

public:
    Stream(IStreamSourceBase<T>* source);

    Stream<T> select(std::function<bool(const T&)> predicate);

    template <typename TOut>
    Stream<TOut> map(std::function<TOut(const T&)> mapper);

    void forEach(std::function<void(const T&)> consumer);
};

// implementation

template <typename T>
Stream<T>::Stream(IStreamSourceBase<T>* source)
    : source(source)
{}

template <typename T>
Stream<T> Stream<T>::select(std::function<bool(const T&)> predicate) {
    return Stream<T>(SelectStreamSource<T>(source, predicate));
}

template <typename T>
template <typename TOut>
Stream<TOut> Stream<T>::map(std::function<TOut(const T&)> mapper) {
    return Stream<T>(MapStreamSource<TOut>(source, mapper));
}

template <typename T>
void Stream<T>::forEach(std::function<void(const T&)> consumer) {
    T* value;

    while (value = source->next()) {
        consumer(*value);
    }
}

} // namespace adapter