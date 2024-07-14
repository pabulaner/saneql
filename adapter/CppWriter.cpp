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
    if (&writer == &iuResult) {
        return;
    }
    for (std::size_t i = 0; i < tabCount; i++) {
        writer += '\t';
    }
}

void CppWriter::writeType(Type type) {
    switch (type.getType()) {
        case Type::Unknown: write("auto"); break; // this can only happen for NULL values
        case Type::Bool: write("bool"); break;
        case Type::Integer: write("int"); break;
        case Type::Decimal: write("double"); break;
        case Type::Char: write("Varchar<" + std::to_string(type.getLength()) + ">"); break;
        case Type::Varchar: write("Varchar<" + std::to_string(type.getLength()) + ">"); break;
        case Type::Text: write("text"); break;
        case Type::Date: write("date"); break;
        case Type::Interval: write("interval"); break;
    }
}

void CppWriter::writeType(CppIU::Type type) {
    using enum CppIU::Type;
    
    switch (type) {
        case Struct: write("struct"); break;
        case ScanOp: write("ScanOp"); break;
        case SelectOp: write("SelectOp"); break;
        case MapOp: write("MapOp"); break;
        case JoinOp: write("JoinOp"); break;
        case OutputOp: write("OutputOp"); break;
    }
}

const CppIU* CppWriter::writeStruct(const std::vector<const IU*>& fields) {
    saveTarget(&structResult);
    const CppIU* iu = createCppIU(CppIU::Type::Struct);

    writeType(iu->getType());
    writeln(" " + iu->getName() + " {");

    for (auto field : fields) {
        writeType(field->getType());
        write(" ");
        writeIU(field);
        writeln(";");
    }   

    writeln("};");

    restoreTarget();
    return iu;
}

const CppIU* CppWriter::writeOperator(CppIU::Type type, const std::vector<std::string>& params, std::function<void()> lambda) {
    return writeTemplateOperator(type, {}, params, lambda);
}

const CppIU* CppWriter::writeTemplateOperator(CppIU::Type type, const std::vector<std::string>& templates, const std::vector<std::string>& params, const std::function<void()> lambda) {
    saveTarget(&operatorResult);
    const CppIU* iu = createCppIU(type);

    writeType(type);

    if (templates.size() > 0)
        write("<");

    bool first = true;
    for (auto& t : templates) {
        if (first) 
            first = false;
        else
            write(", ");
        write(t);
    }

    if (templates.size() > 0)
        write(">");

    write(" " + iu->getName() + "(");

    first = true;
    for (auto& p : params) {
        if (first) 
            first = false;
        else
            write(", ");
        write(p);
    }

    if (!first) 
        write(", ");

    // produce lambda
    lambda();

    writeln(");");

    restoreTarget();
    return iu;
}

void CppWriter::writeProcess(const CppIU* opIU) {
    saveTarget(&processResult);
    writeln(opIU->getName() + ".process();");
    restoreTarget();
}

void CppWriter::writeIU(const IU* iu) {
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
}

std::string CppWriter::getResult() const {
    return structResult
        + iuResult
        + operatorResult
        + processResult;
}

void CppWriter::saveTarget(std::string* target) {
    targetStack.push(target);
}

void CppWriter::restoreTarget() {
    targetStack.pop();
}

} // namespace adapter