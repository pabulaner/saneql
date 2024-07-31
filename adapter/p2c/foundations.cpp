#include "foundations.hpp"

namespace p2c {

string genVar(const string& name) {
   static unsigned varCounter = 1;
   return format("{}{}", name, varCounter++);
}

// format comma-separated list of IU types (helper function)
string formatTypes(const vector<IU*>& ius) {
   stringstream ss;
   for (IU* iu : ius)
      ss << iu->type << ",";
   string result = ss.str();
   if (result.size())
      result.pop_back(); // remove last ','
   return result;
}

// format comma-separated list of IU varnames (helper function)
string formatVarnames(const vector<IU*>& ius) {
   stringstream ss;
   for (IU* iu : ius)
      ss << iu->varname << ",";
   string result = ss.str();
   if (result.size())
      result.pop_back(); // remove last ','
   return result;
}

// provide an IU by generating local variable (helper)
void provideIU(IU* iu, const string& value) {
   print("{} {} = {};\n", iu->type, iu->varname, value);
}

// set union operator
IUSet operator|(const IUSet& a, const IUSet& b) {
   IUSet result;
   set_union(a.v.begin(), a.v.end(), b.v.begin(), b.v.end(), back_inserter(result.v));
   return result;
}

// set intersection operator
IUSet operator&(const IUSet& a, const IUSet& b) {
   IUSet result;
   set_intersection(a.v.begin(), a.v.end(), b.v.begin(), b.v.end(), back_inserter(result.v));
   return result;
}

// set difference operator
IUSet operator-(const IUSet& a, const IUSet& b) {
   IUSet result;
   set_difference(a.v.begin(), a.v.end(), b.v.begin(), b.v.end(), back_inserter(result.v));
   return result;
}

// set equality operator
bool operator==(const IUSet& a, const IUSet& b) {
   return equal(a.v.begin(), a.v.end(), b.v.begin(), b.v.end());
}

void produceAndPrint(unique_ptr<Operator> root, const std::vector<IU*>& ius, unsigned perfRepeat, uint64_t offset, int64_t count) {
   IU mat{"row", Type::BigInt};
   provideIU(&mat, "0");
   print("std::cout << \"[QUERY_BEGIN]\" << std::endl;\n");
   for (IU* iu : ius) {
      print("std::cout << \"{},\";", iu->name);
   }
   print("std::cout << std::endl;\n");
   root->produce(IUSet(ius), [&]() {
      auto if_in_offset = format("if ({0} >= {1} && {0} < {2})", mat.varname, to_string(offset), to_string(offset+count));
      if (count == -1) {
         if_in_offset  = format("if ({0} >= {1})", mat.varname, to_string(offset));
      }
      genBlock(if_in_offset,
      [&]() {
         for (IU *iu : ius)
            print("std::cout << {} << \",\";", iu->varname);
         print("std::cout << std::endl;\n");
      });
      print("{}++;", mat.varname);
   });
   print("std::cout << \"[QUERY_END]\" << std::endl;\n");
}

}