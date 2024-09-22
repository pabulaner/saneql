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
class Expression;
}
}

using namespace saneql;
using namespace saneql::algebra;

namespace adapter {

class IUSet;

class CppWriter {
    /// The result
    std::string result;
    /// The tab count
    size_t tabCount;

    /// All assigned IU names
    std::unordered_map<const IU*, std::string> iuNames;

    public:
    /// The constructor
    CppWriter() : tabCount(0) {}
    /// Write a string
    void write(const std::string& content);
    /// Write a string with a linebreak
    void writeln(const std::string& content);
    /// Write tabs
    void writeTabs();
    /// Write type
    void writeType(Type type);
    /// Write types
    void writeTypes(const std::vector<Type>& types);
    /// Write IU
    void writeIU(const IU* iu);
    /// Write IUs
    void writeIUs(const IUSet& ius);
    /// Write expression
    void writeExpression(Expression* exp);
    /// Write expressions
    void writeExpressions(const std::vector<Expression*>& exp);

    /// Get IU name
    std::string getIUName(const IU* iu) const;
    /// Get the final result
    std::string getResult() const { return result; }
};

} // namespace adapter