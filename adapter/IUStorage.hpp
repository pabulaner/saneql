#pragma once

#include <unordered_map>

#include "p2c/foundations.hpp"

namespace saneql::algebra {
class IU;
}

using namespace saneql::algebra;

namespace adapter {

class IUStorage {
    /// The IU storage
    std::unordered_map<const IU*, p2c::IU*> storage;

public:
    IUStorage();

    IUStorage(const IUStorage& other) = delete;

    IUStorage& operator=(const IUStorage& other) = delete;

    void add(const IU* key, p2c::IU* value);

    p2c::IU* get(const IU* key) const;

    std::vector<p2c::IU*> get(const std::vector<const IU*> keys) const;
};

}