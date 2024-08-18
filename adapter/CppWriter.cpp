#include "CppWriter.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

void CppWriter::write(const std::string& content) {
    if (result.ends_with('\n')) {
        if (content.starts_with('}') && tabCount > 0) {
            tabCount -= 1;
        }
        writeTabs();
    }

    result += content;

    if (result.ends_with("{\n")) {
        tabCount += 1;
    }
}

void CppWriter::writeln(const std::string& content) {
    write(content + '\n');
}

void CppWriter::writeTabs() {
    for (std::size_t i = 0; i < tabCount; i++) {
        result += '\t';
    }
}

void CppWriter::writeType(Type type) {
    switch (type.getType()) {
        case Type::Unknown: write("auto"); break; // this can only happen for NULL values
        case Type::Bool: write("bool"); break;
        case Type::Integer: write("Integer"); break;
        case Type::Decimal: write("Numeric"); break;
        case Type::Char: write("Varchar<" + std::to_string(type.getLength()) + ">"); break;
        case Type::Varchar: write("Varchar<" + std::to_string(type.getLength()) + ">"); break;
        case Type::Text: throw std::runtime_error("Unsupported type Text");
        case Type::Date: write("Timestamp"); break;
        case Type::Interval: throw std::runtime_error("Unsupported type Interval");
    }
}

void CppWriter::writeTypes(const std::vector<Type>& types) {
    bool first = true;
    for (auto& type : types) {
        if (first) 
            first = false;
        else
            write(", ");
        writeType(type);
    }
}

void CppWriter::writeIU(const IU* iu) {
    if (auto iter = iuNames.find(iu); iter != iuNames.end()) {
        write(iter->second);
    } else {
        std::string name = "v_" + std::to_string(iuNames.size() + 1);
        write(name);

        iuNames[iu] = move(name);
    }
}

void CppWriter::writeIUs(const std::vector<const IU*>& ius) {
    bool first = true;
    for (auto iu : ius) {
        if (first) 
            first = false;
        else
            write(", ");
        writeIU(iu);
    }
}

void CppWriter::writeExpression(Expression* exp) {
    exp->generate(*this);
}

void CppWriter::writeExpressions(const std::vector<Expression*>& exp) {
    bool first = true;
    for (auto e : exp) {
        if (first) 
            first = false;
        else
            write(", ");
        writeExpression(e);
    }
}


} // namespace adapter