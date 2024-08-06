#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>
#include <stack>

namespace saneql {
class Type;
namespace algebra {
class IU;
}
}

using namespace saneql;
using namespace saneql::algebra;

namespace adapter {

class CppIU {
    public:
    enum Type {
        Struct,
        ScanOp,
        SelectOp,
        MapOp,
        JoinOp,
        GroupByOp,
        SortOp,
        OutputOp
    };

    private:
    /// The type
    Type type;
    /// The name
    std::string name;
    /// The ref
    std::string ref;

    public:
    /// The constructor
    CppIU(Type type, const std::string& name) : type(type), name(name), ref('&' + name) {}
    /// Get the type
    Type getType() const { return type; }
    /// Get the name
    const std::string& getName() const { return name; }
    /// Get the ref
    const std::string& getRef() const { return ref; }
};

class CppWriter {
    /// The target
    std::stack<std::string*> targetStack;
    /// The struct result
    std::string structResult;
    /// The IU result
    std::string iuResult;
    /// The operator result
    std::string operatorResult;
    /// The process result
    std::string processResult;
    /// The tab count
    std::size_t tabCount;

    /// All struct and operator IU's
    std::vector<std::unique_ptr<CppIU>> cppIUs;
    /// All assigned IU names
    std::unordered_map<const IU*, std::string> iuNames;

    public:
    /// The constructor
    CppWriter() : tabCount(0) {}
    /// Create a cpp IU
    const CppIU* createCppIU(CppIU::Type type);
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
    /// Write struct to structResult
    const CppIU* writeStruct(const std::vector<const IU*>& fields);
    /// Write operator to operatorResult
    const CppIU* writeOperator(CppIU::Type type, const std::vector<std::string>& params, const std::function<void()> lambda);
    /// Write template operator to operatorResult
    const CppIU* writeTemplateOperator(CppIU::Type type, const std::vector<std::string>& templates, const std::vector<std::string>& params, const std::function<void()> lambda);
    /// Write process
    void writeProcess(const CppIU* opIU);
    /// Write IU to operatorResult and declare it in iuResult
    void writeIU(const IU* iu);
    /// Clear IU from the writer
    void clearIU(const IU* iu);

    /// Get the final result
    std::string getResult() const;

    private:
    /// Save the target
    void saveTarget(std::string* target);
    /// Restore the target
    void restoreTarget();
};

} // namespace adapter