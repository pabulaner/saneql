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

template <std::size_t TSize, RowIndexMap<TSize> TMap, typename TKey, typename TValue, typename TKeyTuple, typename TValueTuple>
class Row {
private:
    inline Row() {};
};

template <std::size_t TSize, RowIndexMap<TSize> TMap, typename TKey, typename TValue, typename... TKeyArgs, typename... TValueArgs>
class Row<TSize, TMap, TKey, TValue, std::tuple<TKeyArgs...>, std::tuple<TValueArgs...>> {
private:
    TKey* key;
    TValue* value;

    const std::tuple<TKeyArgs...> keyFields;
    const std::tuple<TValueArgs...> valueFields;

public:
    inline Row(const std::tuple<TKeyArgs...>& keyFields, const std::tuple<TValueArgs...>& valueFields) 
        : keyFields(keyFields)
        , valueFields(valueFields)
    {}

    inline void set(TKey* key, TValue* value) {
        this->key = key;
        this->value = value;
    }

    template <std::size_t TIndex>
    inline constexpr auto& getKey() const {
        return key->*(std::get<TMap.get(TIndex)>(keyFields));
    }

    template <std::size_t TIndex>
    inline constexpr auto& getValue() const {
        return value->*(std::get<TMap.get(TIndex)>(valueFields));
    }
};

} // namespace adapter