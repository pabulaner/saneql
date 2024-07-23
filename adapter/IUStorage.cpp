#include "IUStorage.hpp"

namespace adapter {

IUStorage::IUStorage() {}

void IUStorage::add(const IU* key, const p2c::IU* value) {
    storage[key] = value;
}

const p2c::IU* IUStorage::get(const IU* key) const {
    return storage[key];
}

std::vector<const p2c::IU*> IUStorage::get(const std::vector<const IU*> keys) const {
    std::vector<const p2c::IU*> result;
    for (auto k : keys) {
        result.push_back(storage[k]);
    }
    return result;
}

}