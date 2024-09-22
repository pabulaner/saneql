#include "IUSet.hpp"

#include "VectorUtil.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

IUSet::IUSet() {}

IUSet::IUSet(std::initializer_list<IUType> ius) 
    : ius(ius) 
{}

IUSet::IUSet(const std::vector<IUType>& ius) 
    : ius(ius) 
{}

template <typename T>
IUSet::IUSet(const std::vector<T>& container) {
    for (const T& value : container) {
        ius.push_back(value.iu.get());
    }
}

IUSet::IUType IUSet::operator[](size_t index) const {
    return ius[index];
}

IUSet IUSet::operator|(const IUSet& other) const {
    IUSet result = ius;

    for (IUType value : other.ius) {
        if (!result.contains(value)) {
            result.add(value);
        }
    }

    return result;
}

IUSet IUSet::operator&(const IUSet& other) const {
    IUSet result;

    for (IUType value : ius) {
        if (other.contains(value)) {
            result.add(value);
        }
    }

    return result;
}

bool IUSet::contains(IUType iu) const {
    return vutil::contains(ius, iu);
}

std::vector<Type> IUSet::getTypes() const { 
    return vutil::map<Type>(ius, [](IUType iu) { return iu->getType(); }); 
}

}