#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "algebra/Operator.hpp"

using namespace saneql;
using namespace saneql::algebra;

namespace adapter {

class CppIU {
    public:
    enum Type {
        Struct,
        UnorderedMap,
        ScanOp,
        SelectOp,
        MapOp,
        OutputOp
    };

    private:
    /// The type
    Type type;
    /// The name
    std::string name;

    public:
    /// The constructor
    CppIU(Type type, const std::string& name) : type(type), name(name) {}
    /// Get the type
    Type getType() const { return type; }
    /// Get the name
    const std::string& getName() const { return name; }
};

class Lambda {
    /// The params
    std::vector<const IU*> params;

    public:
    /// Get the params
    const std::vector<const IU*>& getParams() const { return params; }
};

class CppWriter {
    /// The target
    std::string* target;
    /// The struct result
    std::string structResult;
    /// The IU result
    std::string iuResult;
    /// The operator result
    std::string operatorResult;
    /// The tab count
    std::size_t tabCount;

    /// All struct and operator IU's
    std::vector<std::unique_ptr<CppIU>> cppIUs;
    /// All assigned IU names
    std::unordered_map<const IU*, std::string> iuNames;

    /// Create a cpp IU
    CppIU* createCppIU(CppIU::Type type);

    /// Write a string
    void write(const std::string& content);
    /// Write a string with a linebreak
    void writeln(const std::string& content);
    /// Write tabs
    void writeTabs() const;
    /// Write type
    void writeType(Type type);
    /// Write cpp type
    void writeType(CppIU::Type type);

public:
    /// Write struct to structResult
    const CppIU* writeStruct(const std::vector<CppIU*>& fields);
    /// Write operator to operatorResult
    const CppIU* writeOperator(const std::vector<const IU*>& params, const std::vector<Lambda>& lambdas);
    /// Write IU to operatorResult and declare it in iuResult
    void writeIU(const IU* iu);

    // void writeLambda(const std::vector<IU*>& params, );
};

} // namespace adapter