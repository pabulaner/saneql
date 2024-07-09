#include "CppWriter.hpp"

#include "algebra/Operator.hpp"

namespace adapter {

CppIU* CppWriter::createCppIU(CppIU::Type type) {
    cppIUs.push_back(std::make_unique<CppIU>(type, "c_" + std::to_string(cppIUs.size() + 1)));
    return cppIUs[cppIUs.size() - 1].get();
}

void CppWriter::write(const std::string& content) {
    auto& writer = *target;
    if (writer.starts_with('}') && tabCount > 0) {
        tabCount -= 1;
    }

    writeTabs();
    writer += content;

    if (writer.ends_with("}\n")) {
        tabCount += 1;
    }
}

void CppWriter::writeln(const std::string& content) {
    write(content + '\n');
}

void CppWriter::writeTabs() const {
    auto& writer = *target;
    for (std::size_t i = 0; i < tabCount; i++) {
        writer += '\t';
    }
}

void CppWriter::writeType(Type type) {
    auto& writer = *target;
    switch (type.getType()) {
        case Type::Unknown: writer += "auto"; break; // this can only happen for NULL values
        case Type::Bool: writer += "bool"; break;
        case Type::Integer: writer += "int"; break;
        case Type::Decimal: writer += "double"; break;
        case Type::Char: writer += "varchar<" + std::to_string(type.getLength()) + ">"; break;
        case Type::Varchar: writer += "varchar<" + std::to_string(type.getLength()) + ">"; break;
        case Type::Text: writer += "text"; break;
        case Type::Date: writer += "date"; break;
        case Type::Interval: writer += "interval"; break;
    }
}

void CppWriter::writeType(CppIU::Type type) {
    auto& writer = *target;
    switch (type) {
        case CppIU::Type::Struct: writer += "struct"; break;
    }
}

const CppIU* CppWriter::writeStruct(const std::vector<const CppIU*>& fields) {
    target = &structResult;
    CppIU* iu = createCppIU(CppIU::Type::Struct);

    writeType(iu->getType());
    writeln(" " + iu->getName() + " {");

    for (auto& field : fields) {
        writeType(field->getType());
        writeln(" " + field->getName() + ";");
    }   

    writeln("};");
    return iu;
}

const CppIU* CppWriter::writeOperator(CppIU::Type type, const std::vector<std::string>& params, std::function<void()> lambda) {
    target = &structResult;
    CppIU* iu = createCppIU(CppIU::Type::Struct);

    writeType(type);
    write(" " + iu->getName() + "(");

    bool first = true;
    for (auto& param : params) {
        if (first) 
            first = false;
        else
            write(", ");

        write(param);
    }

    // produce lambda
    lambda();

    writeln(");");
    return iu;
}

void CppWriter::writeLambda(std::function<void()> lambda) {
    lambda();
}

void CppWriter::writeIU(const IU* iu) {
    target = &operatorResult;
    auto& writer = *target;
    if (auto iter = iuNames.find(iu); iter != iuNames.end()) {
        writer += iter->second;
    } else {
        std::string name = "v_" + std::to_string(iuNames.size() + 1);
        writer += name;

        target = &iuResult;
        writeType(iu->getType());
        writeln(" " + name + ";");

        iuNames[iu] = move(name);
    }
}

std::string CppWriter::getResult() const {
    return structResult + iuResult + operatorResult;
}

} // namespace adapter