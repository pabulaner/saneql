#pragma once

#include <vector>
#include <algorithm>
#include <memory>

namespace adapter {

namespace vutil {

template <typename T>
std::vector<T> make(T&& arg) {
    std::vector<T> result;
    result.push_back(std::move(arg));

    return result;
}

template <typename T, typename... TArgs>
std::vector<T> make(T&& arg, TArgs&&... args) {
    std::vector<T> result = make<T>(std::forward<TArgs>(args)...);
    result.push_back(std::move(arg));

    return result;
}

template <typename T>
bool contains(const std::vector<T>& vec, const T& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

template <typename TOut, typename TIn, typename TMapFn>
std::vector<TOut> map(const std::vector<TIn>& in, TMapFn map) {
    std::vector<TOut> result;
    for (auto it = in.begin(); it != in.end(); it++) {
        result.push_back(map(*it));
    }
    return result;
}

template <typename T>
std::vector<T> combine(const std::vector<T>& arg) {
    return arg;
}

template <typename T, typename... TArgs>
std::vector<T> combine(const std::vector<T>& arg, const TArgs&... args) {
    std::vector<T> result = combine(args...);
    result.insert(result.end(), arg.begin(), arg.end());

    return result;
}

} // namespace vutil

} // namespace adapter