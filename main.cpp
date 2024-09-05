#include <iostream>
#include "adapter/CppCompiler.hpp"

int main(int argc, char* argv[]) {
   try {
      adapter::CppCompiler compiler(argc - 1, argv + 1);

      compiler.addOutput("none", compiler.None);
      compiler.addOutput("selects", compiler.OptimizeSelects);
      compiler.addOutput("scans", compiler.OptimizeScans);
      compiler.addOutput("joins", compiler.OptimizeJoins);
      compiler.addOutput("all", compiler.OptimizeSelects | compiler.OptimizeScans | compiler.OptimizeJoins);

      compiler.compile("./adapter/resource/query.hpp");
   } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   }

   return 0;
}
