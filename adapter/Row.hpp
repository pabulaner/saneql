#pragma once

#include <cstddef>
#include <tuple>
#include <array>
#include <stdexcept>

namespace adapter {

template <std::size_t TSize>
struct RowIndexMap {
    const std::array<std::size_t, TSize> data;

    constexpr std::size_t get(std::size_t key) const {
        for (std::size_t i = 0; i < TSize; i++) {
            if (data[i] == key) {
                return i;
            }
        }

        throw std::runtime_error("Invalid key");
    }
};

template <std::size_t TSize, RowIndexMap<TSize> TMap, typename TValue, typename... TArgs>
struct Row {
    TValue* value;
    std::tuple<TArgs...> fields;

public:
    inline Row(std::tuple<TArgs...> fields) 
        : fields(fields)
    {}

    inline void setValue(TValue* value) {
        this->value = value;
    }

    template <std::size_t TIndex>
    inline constexpr auto& get() const {
        return value->*(std::get<TMap.get(TIndex)>(fields));
    }
};

} // namespace adapter