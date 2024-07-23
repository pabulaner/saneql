#pragma once

#include <unordered_map>

#include "algebra/Operator.hpp"
#include "p2c/foundations.hpp"

using namespace saneql::algebra;

namespace adapter {

class IUStorage {
    /// The IU storage
    std::unordered_map<const IU*, const p2c::IU*> storage;

public:
    IUStorage();

    IUStorage(const IUStorage& other) = delete;

    IUStorage& operator=(const IUStorage& other) = delete;

    void add(const IU* key, const p2c::IU* value);

    const p2c::IU* get(const IU* key) const;

    std::vector<const p2c::IU*> get(const std::vector<const IU*> keys) const;
};

}