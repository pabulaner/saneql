#pragma once

#include <functional>

#include "StreamSource.hpp"

template <typename T>
class Stream {
private:
    IStreamSource<T> source;

public:
    Stream(IStreamSource<T>& source);

    Stream<T> filter(std::function<bool(const T&)> predicate);

    void forEach(std::function<void(const T&)> consumer);
};

// implementation

template <typename T>
Stream<T>::Stream(IStreamSource<T>& source)
    : source(source)
{}

template <typename T>
Stream<T> Stream<T>::filter(std::function<bool(const T&)> predicate) {
    return Stream<T>(FilterStreamSource<T>(source, predicate));
}

template <typename T>
void Stream<T>::forEach(std::function<void(const T&)> consumer) {
    while (source.hasNext()) {
        consumer(source.next());
    }
}