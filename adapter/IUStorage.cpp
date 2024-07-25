#include "IUStorage.hpp"

#include "algebra/Operator.hpp"

namespace adapter {

IUStorage::IUStorage() {}

void IUStorage::add(const IU* key, p2c::IU* value) {
    using enum saneql::Type::Tag;

    switch (key->getType().getType()) {
        case Unknown: value->type = "auto"; break; // this can only happen for NULL values
        case Bool: value->type = "bool"; break;
        case Integer: value->type = "int"; break;
        case Decimal: value->type = "double"; break;
        case Char: value->type = "Varchar<" + std::to_string(key->getType().getLength()) + ">"; break;
        case Varchar: value->type = "Varchar<" + std::to_string(key->getType().getLength()) + ">"; break;
        case Text: value->type = "text"; break;
        case Date: value->type = "date"; break;
        case Interval: value->type = "interval"; break;
    }

    storage[key] = value;
}

p2c::IU* IUStorage::get(const IU* key) const {
    return storage.at(key);
}

std::vector<p2c::IU*> IUStorage::get(const std::vector<const IU*> keys) const {
    std::vector<p2c::IU*> result;
    for (auto k : keys) {
        result.push_back(storage.at(k));
    }
    return result;
}

}