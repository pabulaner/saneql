#include "CppCompiler.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include "algebra/Operator.hpp"
#include "infra/Schema.hpp"
#include "parser/ASTBase.hpp"
#include "parser/SaneQLLexer.hpp"
#include "parser/SaneQLParser.hpp"
#include "semana/SemanticAnalysis.hpp"
#include "CppWriter.hpp"
#include "Optimizer.hpp"

namespace adapter {

CppCompiler::CppCompiler(unsigned count, char** files, bool addDefaultOutput) {
    for (unsigned i = 0; i < count; i++) {
        std::ostringstream output;
        std::ifstream in(files[i]);

        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file '" + std::string(files[i]) + "'");
        }

        output << in.rdbuf() << "\n";
        inputs.push_back({files[i], output.str()});
    }

    if (addDefaultOutput) {
        addOutput("", 0);
    }
}

void CppCompiler::addOutput(const std::string& name, uint8_t flags) {
    for (auto& out : outputs) {
        if (out.name == name) {
            throw new std::runtime_error("Output with name '" + name + "' is already present");
        }
    }

    outputs.push_back({name, flags});
}

void CppCompiler::compile(const std::string& output) const {
    CppWriter writer;
    writer.writeln("std::map<std::string, std::map<std::string, std::function<void(Database*, size_t)>>> queries = {");

    for (auto& output : outputs) {
        CppWriter w;
        writeOutput(w, output);
        writer.writeln(w.getResult() + ",");
    }

    writer.writeln("};");
    std::ofstream outputFile(output);
    outputFile << writer.getResult();
    outputFile.close();
}

void CppCompiler::writeOutput(CppWriter& writer, const Output& output) const {
    Schema schema;
    schema.populateSchema();
    
    writer.writeln("{\"" + output.name + "\", {");

    for (auto& in : inputs) {
        writer.writeln("{\"" + in.name + "\", [](Database* db, size_t limit) {");

        ASTContainer container;
        ast::AST* tree = nullptr;
        tree = SaneQLParser::parse(container, in.content);

        SemanticAnalysis semana(schema);
        auto res = semana.analyzeQuery(tree);

        if (res.isScalar()) {
            writer.write("std::cout << ");
            res.scalar()->generate(writer);
            writer.writeln(" << std::endl;");
        } else {
            Optimizer opt(std::move(res.table()));

            if (output.flags & OptimizeSelects) opt.optimizeSelects();
            if (output.flags & OptimizeScans) opt.optimizeScans();
            if (output.flags & OptimizeJoins) opt.optimizeJoins();

            writer.writeln("if (limit > 0) {");
            writer.write("std::cout << ");
            bool first = true;
            for (auto c : res.getBinding().getColumns()) {
                if (first) 
                        first = false;
                else
                    writer.write(" << \", \" << ");
                writer.write(c.name);
            }
            writer.writeln(" << std::endl;");
            writer.writeln("}");

            auto tree = opt.get();

            tree->generate(writer, IUSet(res.getBinding().getColumns()), [&]() {
                writer.writeln("if (limit > 0) {");
                writer.writeln("limit -= 1;");
                writer.write("std::cout << ");
                bool first = true;
                for (auto iu : tree->getIUs()) {
                    if (first) 
                            first = false;
                    else
                        writer.write(" << \", \" << ");
                    writer.writeIU(iu);
                }
                writer.writeln(" << std::endl;");
                writer.writeln("}");
            });
        }

        writer.writeln("}},");
    }

    writer.write("}}");
}

}