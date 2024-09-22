#pragma once

#include <vector>

namespace saneql {
class Type;
namespace algebra {
class IU;
}
}
namespace adapter {

using namespace saneql;
using namespace saneql::algebra;

class IUSet {
    // The iu type
    typedef const IU* IUType;
    // The ius
    std::vector<IUType> ius;

public:
    IUSet();

    IUSet(std::initializer_list<IUType> ius);

    IUSet(const std::vector<IUType>& ius);

    template <typename T>
    IUSet(const std::vector<T>& container);

    IUType operator[](size_t index) const;

    IUSet operator|(const IUSet& other) const;

    IUSet operator&(const IUSet& other) const;

    bool contains(IUType iu) const;

    void add(const IU* iu) { ius.push_back(iu); }

    size_t size() const { return ius.size(); }

    const std::vector<IUType>& data() const { return ius; }

    std::vector<Type> getTypes() const;

    auto begin() const { return ius.begin(); }

    auto end() const { return ius.end(); }
};

}