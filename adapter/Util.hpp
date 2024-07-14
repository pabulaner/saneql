#pragma once

#include <vector>

namespace adapter {

namespace util {

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

} // namespace util

} // namespace adapter