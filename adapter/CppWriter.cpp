#include "CppWriter.hpp"
#include "algebra/Operator.hpp"

namespace adapter {

const CppIU* CppWriter::createCppIU(CppIU::Type type) {
    cppIUs.push_back(std::make_unique<CppIU>(type, "c_" + std::to_string(cppIUs.size() + 1)));
    return cppIUs[cppIUs.size() - 1].get();
}

void CppWriter::write(const std::string& content) {
    auto& writer = *(targetStack.top());
    if (content.starts_with('}') && tabCount > 0) {
        tabCount -= 1;
    }
    if (writer.ends_with('\n')) {
        writeTabs();
    }

    writer += content;

    if (writer.ends_with("{\n")) {
        tabCount += 1;
    }
}

void CppWriter::writeln(const std::string& content) {
    write(content + '\n');
}

void CppWriter::writeTabs() const {
    auto& writer = *(targetStack.top());
    for (std::size_t i = 0; i < tabCount; i++) {
        writer += '\t';
    }
}

void CppWriter::writeType(Type type) {
    auto& writer = *(targetStack.top());
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
    auto& writer = *(targetStack.top());
    switch (type) {
        case CppIU::Type::Struct: writer += "struct"; break;
        case CppIU::Type::ScanOp: writer += "ScanOp"; break;
        case CppIU::Type::SelectOp: writer += "SelectOp"; break;
        case CppIU::Type::OutputOp: writer += "OutputOp"; break;
    }
}

const CppIU* CppWriter::writeStruct(const std::vector<const CppIU*>& fields) {
    saveTarget(&structResult);
    const CppIU* iu = createCppIU(CppIU::Type::Struct);

    writeType(iu->getType());
    writeln(" " + iu->getName() + " {");

    for (auto& field : fields) {
        writeType(field->getType());
        writeln(" " + field->getName() + ";");
    }   

    writeln("};");

    restoreTarget();
    return iu;
}

const CppIU* CppWriter::writeOperator(CppIU::Type type, const std::vector<std::string>& params, std::function<void()> lambda) {
    saveTarget(&operatorResult);
    const CppIU* iu = createCppIU(type);

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

    if (!first) 
        write(", ");

    // produce lambda
    lambda();

    writeln(");");

    restoreTarget();
    return iu;
}

void CppWriter::writeBegin(const CppIU* opIU) {
    saveTarget(&beginResult);
    writeln(opIU->getName() + ".begin();");
    restoreTarget();
}

void CppWriter::writeIU(const IU* iu) {
    saveTarget(&operatorResult);

    if (auto iter = iuNames.find(iu); iter != iuNames.end()) {
        write(iter->second);
    } else {
        std::string name = "v_" + std::to_string(iuNames.size() + 1);
        write(name);

        saveTarget(&iuResult);
        writeType(iu->getType());
        writeln(" " + name + ";");
        restoreTarget();

        iuNames[iu] = move(name);
    }

    restoreTarget();
}

std::string CppWriter::getResult() const {
    return structResult
        + iuResult
        + operatorResult
        + beginResult;
}

void CppWriter::saveTarget(std::string* target) {
    targetStack.push(target);
}

void CppWriter::restoreTarget() {
    targetStack.pop();
}

} // namespace adapter