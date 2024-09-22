#include <vector>

namespace adapter {

class IU;

class IUSet {
    // The iu type
    typedef const IU* IUType
    // The ius
    std::vector<IUType> ius;

    IUSet();

    IUSet(const std::vector<IUType>& ius);

    template <typename T>
    IUSet(const std::vector<T>& container);

    IUType operator[](size_t index) const;

    IUSet operator|(const IUSet& other) const;

    IUSet operator&(const IUSet& other) const;

    bool contains(IUType iu) const;

    void add(const IU* iu) { ius.push_back(iu); }

    size_t size() { return ius.size(); }

    const std::vector<IUType>& data() const { return ius; }

    IUType begin() const { return ius.begin(); }

    IUType end() const { return ius.end(); }
};

}