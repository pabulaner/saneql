// Viktor Leis, 2023
#pragma once

#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <source_location>
#include <string>
#include <string_view>
#include <sstream>
#include "types.hpp"
#include "tpch.hpp"
#include "../Util.hpp"

////////////////////////////////////////////////////////////////////////////////

// counter to make all IU names unique in generated code

namespace p2c {

using namespace std;
using namespace fmt;
using namespace adapter;

string genVar(const string& name);

struct IU {
   string name;
   string type;
   string varname;

   IU(const string& name, Type type) : name(name), type(tname(type)), varname(genVar(name)) {}
   IU(const string& name, string type) : name(name), type(type), varname(genVar(name)) {}
};

// format comma-separated list of IU types (helper function)
string formatTypes(const vector<IU*>& ius);

// format comma-separated list of IU varnames (helper function)
string formatVarnames(const vector<IU*>& ius);

// provide an IU by generating local variable (helper)
void provideIU(IU* iu, const string& value);

// an unordered set of IUs
struct IUSet {
   // set is represented as array; invariant: IUs are sorted by pointer value
   vector<IU*> v;

   // empty set constructor
   IUSet() {}

   // move constructor
   IUSet(IUSet&& x) {
      v = std::move(x.v);
   }

   // copy constructor
   IUSet(const IUSet& x) {
      v = x.v;
   }

   // convert vector to set of IUs (assumes vector is unique, but not sorted)
   explicit IUSet(const vector<IU*>& vv) {
      v = vv;
      sort(v.begin(), v.end());
   }

   // iterate over IUs
   IU** begin() { return v.data(); }
   IU** end() { return v.data() + v.size(); }
   IU* const* begin() const { return v.data(); }
   IU* const* end() const { return v.data() + v.size(); }

   void add(IU* iu) {
      auto it = lower_bound(v.begin(), v.end(), iu);
      if (it == v.end() || *it != iu)
         v.insert(it, iu); // O(n), not nice
   }

   bool contains (IU* iu) const {
      auto it = lower_bound(v.begin(), v.end(), iu);
      return (it != v.end() && *it == iu);
   }

   unsigned size() const { return v.size(); };
};

// set union operator
IUSet operator|(const IUSet& a, const IUSet& b);

// set intersection operator
IUSet operator&(const IUSet& a, const IUSet& b);

// set difference operator
IUSet operator-(const IUSet& a, const IUSet& b);

// set equality operator
bool operator==(const IUSet& a, const IUSet& b);

////////////////////////////////////////////////////////////////////////////////

// abstract base class of all expressions
struct Exp {
   // compile expression to string
   virtual string compile() = 0;
   // set of all IUs used in this expression
   virtual IUSet iusUsed() = 0;
   // destructor
   virtual ~Exp() {};
};

// expression that simply references an IU
struct IUExp : public Exp {
   IU* iu;

   // constructor
   IUExp(IU* iu) : iu(iu) {}
   // destructor
   ~IUExp() {}

   string compile() override { return iu->varname; }
   IUSet iusUsed() override { return IUSet({iu}); }
};

// expression that represent a constant value
template<typename T> requires is_p2c_type<T>
struct ConstExp : public Exp {
   T x;

   // constructor
   ConstExp(T x) : x(x) {};
   // destructor
   ~ConstExp() {}

   string compile() override { return format("{}", x); }
   IUSet iusUsed() override { return {}; }
};

// expression that represents function all
struct FnExp : public Exp {
   // function name
   string fnName;
   // arguments
   vector<unique_ptr<Exp>> args;

   // constructor
   FnExp(string fnName, vector<unique_ptr<Exp>>&& v) : fnName(fnName), args(std::move(v)) {}
   // destructor
   ~FnExp() {}

   string compile() override {
      vector<string> strs;
      for (auto& e : args)
         strs.emplace_back(e->compile());
      return format("{}({})", fnName, join(strs, ","));
   }

   IUSet iusUsed() override {
      IUSet result;
      for (auto& exp : args)
         for (IU* iu : exp->iusUsed())
            result.add(iu);
      return result;
   }
};

////////////////////////////////////////////////////////////////////////////////

// generate curly-brace block of C++ code (helper function)
template<class Fn>
void genBlock(const string& str, Fn fn, const std::source_location& location = std::source_location::current()) {
   cout << str << "{ //" << location.line() << "; " << location.function_name() << endl;
   fn();
   cout << "}" << endl;
}


// consumer callback function
typedef std::function<void(void)> ConsumerFn;

// abstract base class of all operators
struct Operator {
   // compute *all* IUs this operator produce
   virtual IUSet availableIUs() = 0;

   // generate code for operator providing 'required' IUs and pushing them to 'consume' callback
   virtual void produce(const IUSet& required, ConsumerFn consume) = 0;

   // destructor
   virtual ~Operator() {}
};

// table scan operator
struct Scan : public Operator {
   // IU storage for all available attributes
   vector<IU> keyIUs;
   vector<IU> ius;
   // relation name
   string relName;

   // constructor
   Scan(const string& relName, std::vector<IU> keyIUs, std::vector<IU> ius) : relName(relName), keyIUs(keyIUs), ius(ius) {
      // get relation info from schema
   }

   // destructor
   ~Scan() {}

   IUSet availableIUs() override {
      IUSet result;
      for (auto& iu : keyIUs)
         result.add(&iu);
      for (auto& iu : ius) 
         result.add(&iu);
      return result;
   }

   void produce(const IUSet& required, ConsumerFn consume) override {
      // ===============================================
      // Sets the scale of perf event counters.
      // Don't change this line.
      // print("perf.scale += db.{}.tupleCount;", relName);
      // ===============================================
      genBlock(format("db->{}.forEach([&](auto& key, auto& value)", relName), [&]() {
         for (IU* iu : required) {
            if (isKey(iu))
               print("{} {} = key.{};\n", iu->type, iu->varname, iu->name);
            else
               print("{} {} = value.{};\n", iu->type, iu->varname, iu->name);
         }
         consume();
      });
      print(");");
   }

   bool isKey(IU* iu) {
      for (auto& otherIU : keyIUs) {
         if (iu == &otherIU) {
            return true;
         }
      }

      return false;
   }

   IU* getIU(const string& attName) {
      for (auto& iu : keyIUs)
         if (iu.name == attName)
            return &iu;
      for (auto& iu : ius)
         if (iu.name == attName)
            return &iu;
      throw;
   }
};

// selection operator
struct Selection : public Operator {
   unique_ptr<Operator> input;
   std::string pred;

   // constructor
   Selection(unique_ptr<Operator> input, const std::string& pred) : input(std::move(input)), pred(pred) {}

   // destructor
   ~Selection() {}

   IUSet availableIUs() override {
      return input->availableIUs();
   }

   void produce(const IUSet& required, ConsumerFn consume) override {
      input->produce(required /* TODO | pred->iusUsed() */, [&]() {
         genBlock(format("if ({})", pred), [&]() {
            consume();
         });
      });
   }
};

// hash join operator
struct HashJoin : public Operator {
   unique_ptr<Operator> left;
   unique_ptr<Operator> right;
   vector<IU*> leftKeyIUs, rightKeyIUs;
   IU ht{"joinHT", Type::Undefined};

   // constructor
   HashJoin(unique_ptr<Operator> left, unique_ptr<Operator> right, const vector<IU*>& leftKeyIUs, const vector<IU*>& rightKeyIUs) :
      left(std::move(left)), right(std::move(right)), leftKeyIUs(leftKeyIUs), rightKeyIUs(rightKeyIUs) {}

   // destructor
   ~HashJoin() {}

   IUSet availableIUs() override {
      return left->availableIUs() | right->availableIUs();
   }

   void produce(const IUSet& required, ConsumerFn consume) override {
      // figure out where required IUs come from
      IUSet leftRequiredIUs = (required & left->availableIUs()) | IUSet(leftKeyIUs);
      IUSet rightRequiredIUs = (required & right->availableIUs()) | IUSet(rightKeyIUs);
      IUSet leftPayloadIUs = leftRequiredIUs - IUSet(leftKeyIUs); // these we need to store in hash table as payload

      // build hash table
      print("unordered_multimap<tuple<{}>, tuple<{}>> {};\n", formatTypes(leftKeyIUs), formatTypes(leftPayloadIUs.v), ht.varname);
      left->produce(leftRequiredIUs, [&]() {
         // insert tuple into hash table
         print("{}.insert({{{{{}}}, {{{}}}}});\n", ht.varname, formatVarnames(leftKeyIUs), formatVarnames(leftPayloadIUs.v));
      });

      // probe hash table
      right->produce(rightRequiredIUs, [&]() {
         // iterate over matches
         genBlock(format("for (auto range = {}.equal_range({{{}}}); range.first!=range.second; range.first++)", ht.varname, formatVarnames(rightKeyIUs)),
                  [&]() {
                     // unpack payload
                     unsigned countP = 0;
                     for (IU* iu : leftPayloadIUs)
                        provideIU(iu, format("get<{}>(range.first->second)", countP++));
                     // unpack keys if needed
                     for (unsigned i=0; i<leftKeyIUs.size(); i++) {
                        IU* iu = leftKeyIUs[i];
                        if (required.contains(iu))
                           provideIU(iu, format("get<{}>(range.first->first)", i));
                     }
                     // consume
                     consume();
                  });
      });
   }
};

// own operators

// sort operator
struct Sort : public Operator {
   unique_ptr<Operator> input;
   vector<IU*> keyIUs;
   IU v{"vector", Type::Undefined};
   bool desc;

   // constructor
   Sort(unique_ptr<Operator> input, const vector<IU*>& keyIUs, bool desc = false) : input(std::move(input)), keyIUs(keyIUs), desc(desc)  {}

   // destructor
   ~Sort() {}

   IUSet availableIUs() override {
      return input->availableIUs();
   }

   void produce(const IUSet& required, ConsumerFn consume) override {
      // indices of the ius in the tuple
      unordered_map<IU*, size_t> iuIndexMap;
      // all ius that need to be stored in the vector
      IUSet ius = IUSet{keyIUs} | required;
      string types = formatTypes(ius.v);
      string varnames = formatVarnames(ius.v);
      // comparer for sorting
      char firstComp = desc ? '>' : '<';
      char secondComp = desc ? '<' : '>';

      // init iuIndexMap
      for (IU* iu : ius) {
         iuIndexMap[iu] = iuIndexMap.size();
      }

      // init vector
      print("vector<tuple<{}>> {};", types, v.varname);

      // produce code for adding the tuple values
      input->produce(required, [&]{
         print("{}.push_back({{{}}});", v.varname, varnames);
      });

      // tuple ius for sorting
      IU t1{"t1", Type::Undefined};
      IU t2{"t2", Type::Undefined};

      // sort the tupples with std::sort
      genBlock(format("sort({0}.begin(), {0}.end(), [&](tuple<{1}> {2}, tuple<{1}> {3})", v.varname, types, t1.varname, t2.varname), [&]{
         for (IU* iu : keyIUs) {
            print("if (get<{0}>({1}) {3} get<{0}>({2})) return true;", iuIndexMap[iu], t1.varname, t2.varname, firstComp);
            print("if (get<{0}>({1}) {3} get<{0}>({2})) return false;", iuIndexMap[iu], t1.varname, t2.varname, secondComp);
         }
         print("return false;");
      });
      print(");");

      // result tuple
      IU t{"t", Type::Undefined};

      // consume the result tuples
      genBlock(format("for (auto& {} : {})", t.varname, v.varname), [&]{
         for (IU* iu : required) {
            provideIU(iu, format("get<{}>({})", iuIndexMap[iu], t.varname));
         }
         consume();
      });
   };
};

// map operator (compute new value)
struct Map : public Operator {
   unique_ptr<Operator> input;
   std::string exp;
   IU iu;

   // constructor
   Map(unique_ptr<Operator> input, const std::string& exp) : input(std::move(input)), exp(exp), iu{"map", Type::Undefined} {}

   // destructor
   ~Map() {}

   IUSet availableIUs() override {
      return input->availableIUs() | IUSet({&iu});
   }

   void produce(const IUSet& required, ConsumerFn consume) override {\
      IUSet req = required - IUSet({&iu});
      input->produce(req, [&]{
         provideIU(&iu, exp);
         consume();
      });
   }

   IU* getIU() {
      return &iu;
   }
};

// group by operator
struct GroupBy : public Operator {
   // TODO: Implement MAX and AVG
   enum AggFunction { Sum, Count, Avg, Max };

   struct Aggregate {
      AggFunction aggFn; // aggregate function
      IU* inputIU; // IU to aggregate (is nullptr when aggFn==Count)
      IU resultIU;
   };

   unique_ptr<Operator> input;
   IUSet groupKeyIUs;
   vector<Aggregate> aggs;
   IU ht{"aggHT", Type::Undefined};

   // constructor
   GroupBy(unique_ptr<Operator> input, const IUSet& groupKeyIUs) : input(std::move(input)), groupKeyIUs(groupKeyIUs) {}

   // destructor
   ~GroupBy() {}

   void addCount(const string& name) {
      aggs.push_back({AggFunction::Count, nullptr, {name, Type::Integer}});
   }

   void addSum(const string& name, IU* inputIU) {
      aggs.push_back({AggFunction::Sum, inputIU, {name, inputIU->type}});
   }

   void addAvg(const string& name, IU* inputIU) {
      aggs.push_back({AggFunction::Avg, inputIU, {name, Type::Double}});
      addSum(name, inputIU);
      addCount(name);
   }

   void addMax(const string& name, IU* inputIU) {
      aggs.push_back({AggFunction::Max, inputIU, {name, inputIU->type}});
   }

   vector<IU*> resultIUs() {
      vector<IU*> v;
      for (auto&[fn, inputIU, resultIU] : aggs)
         v.push_back(&resultIU);      
      return v;
   }

   IUSet inputIUs() {
      IUSet v;
      for (auto&[fn, inputIU, resultIU] : aggs)
         if (inputIU)
            v.add(inputIU);
      return v;
   }

   IUSet availableIUs() override {
      return groupKeyIUs | IUSet(resultIUs());
   }

   void produce(const IUSet& required, ConsumerFn consume) override {
      // build hash table
      print("unordered_map<tuple<{}>, tuple<{}>> {};\n", formatTypes(groupKeyIUs.v), formatTypes(resultIUs()), ht.varname);
      input->produce(groupKeyIUs | inputIUs(), [&]() {
         // insert tuple into hash table
         print("auto it = {}.find({{{}}});\n", ht.varname, formatVarnames(groupKeyIUs.v));
         genBlock(format("if (it == {}.end())", ht.varname), [&]() {
            vector<string> initValues;
            for (auto&[fn, inputIU, resultIU] : aggs) {
               switch (fn) {
                  case (AggFunction::Sum): initValues.push_back(inputIU->varname); break;
                  case (AggFunction::Count): initValues.push_back("1"); break;
                  case (AggFunction::Avg): initValues.push_back("0"); break;
                  case (AggFunction::Max): initValues.push_back(inputIU->varname); break;
               }
            }
            // insert new group
            print("{}.insert({{{{{}}}, {{{}}}}});\n", ht.varname, formatVarnames(groupKeyIUs.v), fmt::join(initValues, ","));
         });
         genBlock("else", [&]() {
            // update group
            unsigned i=0;
            for (auto&[fn, inputIU, resultIU] : aggs) {
               switch (fn) {
                  case (AggFunction::Sum): print("get<{}>(it->second) += {};\n", i, inputIU->varname); break;
                  case (AggFunction::Count): print("get<{}>(it->second)++;\n", i); break;
                  case (AggFunction::Avg): break;
                  case (AggFunction::Max): print("if (get<{0}>(it->second) < {1}) get<{0}>(it->second) = {1};\n", i, inputIU->varname); break;
               }
               i++;
            }
         });
      });

      // iterate over hash table
      genBlock(format("for (auto& it : {})", ht.varname), [&]() {
         for (unsigned i=0; i<groupKeyIUs.size(); i++) {
            IU* iu = groupKeyIUs.v[i];
            if (required.contains(iu))
               provideIU(iu, format("get<{}>(it.first)", i));
         }
         unsigned i=0;
         for (auto&[fn, inputIU, resultIU] : aggs) {
            if (fn == AggFunction::Avg) {
               // if average, use the two next arguments for the avg
               provideIU(&resultIU, format("(double) get<{}>(it.second) / get<{}>(it.second)", i + 1, i + 2));
            } else {
               provideIU(&resultIU, format("get<{}>(it.second)", i));
            }
            i++;
         }
         consume();
      });
   }

   IU* getIU(const string& attName) {
      for (auto&[fn, inputIU, resultIU] : aggs)
         if (resultIU.name == attName)
            return &resultIU;
      throw;
   }
};

////////////////////////////////////////////////////////////////////////////////

// create a function call expression (helper)
template<typename T> requires is_p2c_type<T>
unique_ptr<Exp> makeCallExp(const string& fn, IU* iu, const T& x) {
   vector<unique_ptr<Exp>> v;
   v.push_back(make_unique<IUExp>(iu));
   v.push_back(make_unique<ConstExp<T>>(x));
   return make_unique<FnExp>(fn, std::move(v));
}

template<typename... T>
unique_ptr<Exp> makeCallExp(const string& fn,  std::unique_ptr<T>... args) {
   vector<unique_ptr<Exp>> v;
   (v.push_back(std::move(args)), ...);
   return make_unique<FnExp>(fn, std::move(v));
}

// Print
void produceAndPrint(unique_ptr<Operator> root, const std::vector<IU*>& ius, unsigned perfRepeat = 2, uint64_t offset = 0, int64_t count = -1);

} // namespace p2c

////////////////////////////////////////////////////////////////////////////////
