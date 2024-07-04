#include "algebra/Operator.hpp"
#include "infra/Schema.hpp"
#include "parser/ASTBase.hpp"
#include "parser/SaneQLLexer.hpp"
#include "parser/SaneQLParser.hpp"
#include "semana/SemanticAnalysis.hpp"
#include "sql/SQLWriter.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
//---------------------------------------------------------------------------
using namespace std;
using namespace saneql;
//---------------------------------------------------------------------------
// (c) 2023 Thomas Neumann
//---------------------------------------------------------------------------
static string readFiles(unsigned count, char* files[]) {
   ostringstream output;
   for (unsigned i = 0; i != count; i++) {
      ifstream in(files[i]);
      if (!in.is_open()) {
         cerr << "unable to read " << files[i] << endl;
         exit(1);
      }
      output << in.rdbuf();
      output << "\n";
   }
   return output.str();
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
   if (argc < 2) {
      cerr << "usage: " << argv[0] << " file..." << endl;
      return 1;
   }

   Schema schema;
   schema.populateSchema();

   string query = readFiles(argc - 1, argv + 1);
   ASTContainer container;
   ast::AST* tree = nullptr;
   try {
      tree = SaneQLParser::parse(container, query);
   } catch (const exception& e) {
      cerr << e.what() << endl;
      return 1;
   }

   SemanticAnalysis semana(schema);
   try {
      auto res = semana.analyzeQuery(tree);
      SQLWriter sql;
      if (res.isScalar()) {
         res.scalar()->generate(sql);
      } else {
         auto tree = res.table().get();
         algebra::OperatorIU opIU = tree->generate(sql);

         sql.write("produceAndPrint(std::move(" + opIU.getName() + "), {");

         bool first = true;
         for (auto& c : res.getBinding().getColumns()) {
            if (first)
               first = false;
            else
               sql.write(", ");

            sql.writeIU(c.iu);
         }
         sql.write("});\n");
      }
      cout << sql.getResult() << endl;
   } catch (const exception& e) {
      cerr << e.what() << endl;
      return 1;
   }

   return 0;
}
