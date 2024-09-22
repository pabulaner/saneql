#include "algebra/Operator.hpp"
#include "sql/SQLWriter.hpp"
#include "adapter/CppWriter.hpp"
#include "adapter/OperatorUtil.hpp"
//---------------------------------------------------------------------------
// (c) 2023 Thomas Neumann
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace saneql::algebra {
//---------------------------------------------------------------------------
Operator::~Operator()
// Destructor
{
}
//---------------------------------------------------------------------------
TableScan::TableScan(string name, vector<Column> columns)
   : name(move(name)), columns(move(columns))
// Constructor
{
}
//---------------------------------------------------------------------------
IUSet TableScan::getKeyIUs() const 
// Get the key IUs
{ 
   IUSet result;

   for (auto& c : columns) {
      if (c.isKey) {
         result.push_back(c.iu.get());
      }
   }

   return result;
}
//---------------------------------------------------------------------------
void TableScan::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   out.writeln("db->" + name + ".forEach([&](auto& key, auto& value) {");

   for (auto& c : columns) {
      if (required.contains(c.iu.get())) {
         out.write("const ");
         out.writeType(c.iu->getType());
         out.write("& ");
         out.writeIU(c.iu.get());
         out.write(" = ");
         out.write(c.isKey ? "key" : "value");
         out.writeln("." + c.name + ";");
      }
   }
   consume();

   out.writeln("});");
}
//---------------------------------------------------------------------------
Select::Select(unique_ptr<Operator> input, unique_ptr<Expression> condition)
   : input(move(input)), condition(move(condition))
// Constructor
{
}
//---------------------------------------------------------------------------
void Select::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   input->generate(out, required | condition->getIUs(), [&]() {
      out.write("if (");
      out.writeExpression(condition.get());
      out.writeln(") {");
      consume();
      out.writeln("}");
   });
}
//---------------------------------------------------------------------------
Map::Map(unique_ptr<Operator> input, vector<Entry> computations)
   : input(move(input)), computations(move(computations))
// Constructor
{
}
//---------------------------------------------------------------------------
void Map::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   input->generate(out, required | IUSet(computations), [&]() {
      for (auto& c : computations) {
         if (required.contains(c.iu.get())) {
            out.writeType(c.iu->getType());
            out.write(" ");
            out.writeIU(c.iu.get());
            out.write(" = ");
            out.writeExpression(c.value.get());
            out.writeln(";");
         }
      }
      consume();
   });
}
//---------------------------------------------------------------------------
SetOperation::SetOperation(unique_ptr<Operator> left, unique_ptr<Operator> right, vector<unique_ptr<Expression>> leftColumns, vector<unique_ptr<Expression>> rightColumns, vector<unique_ptr<IU>> resultColumns, Op op)
   : left(move(left)), right(move(right)), leftColumns(move(leftColumns)), rightColumns(move(rightColumns)), resultColumns(move(resultColumns)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
void SetOperation::generate(CppWriter&, std::function<void()>)
// Generate SQL
{
   throw std::runtime_error("SetOperation is not implemented");
}
//---------------------------------------------------------------------------
Join::Join(unique_ptr<Operator> left, unique_ptr<Operator> right, unique_ptr<Expression> condition, JoinType joinType)
   : left(move(left)), right(move(right)), condition(move(condition)), joinType(joinType)
// Constructor
{
}
//---------------------------------------------------------------------------
void Join::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   // validate
   if (joinType != JoinType::Inner) {
      throw std::runtime_error("Unsupported join type");
   }

   std::pair<IUSet, IUSet> keyIUs = outil::getJoinKeyIUs(left.get(), right.get(), condition.get());
   IUSet leftKeyIUs = std::move(keyIUs.first);
   IUSet rightKeyIUs = std::move(keyIUs.second);

   IUSet leftPayloadIUs;
   IUSet rightPayloadIUs;

   for (auto iu : left->getIUs()) {
      if (!vutil::contains(leftKeyIUs, iu) && required.contains(iu)) {
         leftPayloadIUs.push_back(iu);
      }
   }
   for (auto iu : right->getIUs()) {
      if (!vutil::contains(rightKeyIUs, iu) && required.contains(iu)) {
         rightPayloadIUs.push_back(iu);
      }
   }

   const IU mapIU{Type::getUnknown()};

   out.write("std::unordered_multimap<std::tuple<");
   out.writeTypes(vutil::map<Type>(leftKeyIUs, [](const IU* iu) { return iu->getType(); }));
   out.write(">, std::tuple<");
   out.writeTypes(vutil::map<Type>(leftPayloadIUs, [](const IU* iu) { return iu->getType(); }));
   out.write(">> ");
   out.writeIU(&mapIU);
   out.writeln(";");

   left->generate(out, required | leftKeyIUs, [&]() {
      out.writeIU(&mapIU);
      out.write(".insert({{");
      out.writeIUs(leftKeyIUs);
      out.write("}, {");
      out.writeIUs(leftPayloadIUs);
      out.writeln("}});");
   });
   right->generate(out, required | rightKeyIUs, [&]() {
      out.write("for (auto range = ");
      out.writeIU(&mapIU);
      out.write(".equal_range({");
      out.writeIUs(rightKeyIUs);
      out.writeln("}); range.first!=range.second; range.first++) {");

      for (size_t i = 0; i < leftKeyIUs.size(); i++) {
         auto iu = leftKeyIUs[i];
         
         if (required.contains(iu)) {
            out.write("const ");
            out.writeType(iu->getType());
            out.write("& ");
            out.writeIU(iu);
            out.writeln(" = std::get<" + std::to_string(i) + ">(range.first->first);");
         }
      }
      for (size_t i = 0; i < leftPayloadIUs.size(); i++) {
         auto iu = leftPayloadIUs[i];
         out.write("const ");
         out.writeType(iu->getType());
         out.write("& ");
         out.writeIU(iu);
         out.writeln(" = std::get<" + std::to_string(i) + ">(range.first->second);");
      }

      consume();
      out.writeln("}");
   });
}
//---------------------------------------------------------------------------
GroupBy::GroupBy(unique_ptr<Operator> input, vector<Entry> groupBy, vector<Aggregation> aggregates)
   : input(move(input)), groupBy(move(groupBy)), aggregates(move(aggregates))
// Constructor
{
}
//---------------------------------------------------------------------------
void GroupBy::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   // validate
   for (auto& a : aggregates) {
      switch (a.op) {
         case Op::Sum:
         case Op::Avg:
         case Op::Min:
         case Op::Max:
         case Op::CountStar: break;
         default: throw std::runtime_error("Unsupported groupby aggregation");
      }
   }

   std::vector<Aggregate> requiredAggregates = vutil::filter(aggregates, [](const Aggregate& a) { return required.contains(a.iu.get()); })
   const IU mapIU{Type::getUnknown()};

   out.write("std::unordered_map<std::tuple<");
   out.writeTypes(vutil::map<Type>(groupBy, [](const Entry& e) { return e.iu->getType(); }));
   out.write(">, std::tuple<");

   bool first = true;
   for (auto& a : requiredAggregates) {
      if (required.contains(a.iu.get())) {
         if (first)
            first = false;
         else
            out.write(", ");
         
         if (a.op == Op::Avg) {
            out.write("std::pair<");
            out.writeType(a.iu->getType());
            out.write(", ");
            out.writeType(Type::getInteger());
            out.write(">");
         } else {
            out.writeType(a.iu->getType());
         }
      }
   }

   out.write(">> ");
   out.writeIU(&mapIU);
   out.writeln(";");

   input->generate(out, required | IUSet(groupBy) | IUSet(requiredAggregates), [&]() {
      out.write("auto it = ");
      out.writeIU(&mapIU);
      out.write(".find({");
      out.writeExpressions(vutil::map<Expression*>(groupBy, [](const Entry& e) { return e.value.get(); }));
      out.writeln("});");

      out.write("if (it == ");
      out.writeIU(&mapIU);
      out.writeln(".end()) {");

      out.writeIU(&mapIU);
      out.write(".insert({{");
      out.writeExpressions(vutil::map<Expression*>(groupBy, [](const Entry& e) { return e.value.get(); }));
      out.write("}, {");

      bool first = true;
      for (auto& a : requiredAggregates) {
         if (required.contains(a.iu.get())) {
            if (first)
               first = false;
            else 
               out.write(", ");

            switch (a.op) {
               case Op::Sum: 
               case Op::Min: 
               case Op::Max: out.writeExpression(a.value.get()); break;
               case Op::Avg: out.write("{"); out.writeExpression(a.value.get()); out.write(", 1}"); break;
               case Op::CountStar: out.write("1"); break;
               default: throw;
            }
         }
      }

      out.writeln("}});");
      out.writeln("} else {");

      for (size_t i = 0; i < requiredAggregates.size(); i++) {
         std::string value = "std::get<" + std::to_string(i) + ">(it->second)";
         Aggregation& a = requiredAggregates[i];

         out.write(value + " ");
         switch (a.op) {
            case Op::Sum: out.write("+= "); out.writeExpression(a.value.get()); break;
            case Op::Min: out.write("= std::min(get<" + std::to_string(i) + ">(it->second), "); out.writeExpression(a.value.get()); out.write(")"); break;
            case Op::Max: out.write("= std::max(get<" + std::to_string(i) + ">(it->second), "); out.writeExpression(a.value.get()); out.write(")"); break;
            case Op::Avg: out.write("= {" + value + ".first + "); out.writeExpression(a.value.get()); out.write(", " + value + ".second + 1}"); break;
            case Op::CountStar: out.write("+= 1"); break;
            default: throw;
         }
         out.writeln(";");
      }

      out.writeln("}");
   });

   out.write("for (auto& it : ");
   out.writeIU(&mapIU);
   out.writeln(") {");
   for (size_t i = 0; i < groupBy.size(); i++) {
         auto iu = groupBy[i].iu.get();
         
         if (required.contains(iu)) {
            out.write("const ");
            out.writeType(iu->getType());
            out.write("& ");
            out.writeIU(iu);
            out.writeln(" = std::get<" + std::to_string(i) + ">(it.first);");
         }
   }
   for (size_t i = 0; i < requiredAggregates.size(); i++) {
      Aggregation& a = requiredAggregates[i];

      out.write("const ");
      out.writeType(a.iu->getType());
      out.write(a.op == Op::Avg ? " " : "& ");
      out.writeIU(a.iu.get());
      out.write(" = std::get<" + std::to_string(i) + ">(it.second)");

      if (a.op == Op::Avg) {
         out.write(".first / (double)std::get<" + std::to_string(i) + ">(it.second).second");
      }

      out.writeln(";");
   }
   consume();
   out.writeln("}");
}
//---------------------------------------------------------------------------
Sort::Sort(unique_ptr<Operator> input, vector<Entry> order, optional<uint64_t> limit, optional<uint64_t> offset)
   : input(move(input)), order(move(order)), limit(limit), offset(offset)
// Constructor
{
}
//---------------------------------------------------------------------------
void Sort::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   // validate
   for (auto& e : order) {
      if (e.descending) {
         throw std::runtime_error("Unsupported orderby ordering");
      }
   }
   if (offset.has_value() || limit.has_value()) {
      throw std::runtime_error("Unsupported orderby offset or limit");
   }

   const IU vecIU{Type::getUnknown()};

   bool first = true;
   out.write("std::vector<std::tuple<");
   out.writeTypes(vutil::map<Type>(order, [&](const Entry& e) { first = false; return e.value->getType(); }));
   for (auto iu : required) {
      if (first) 
         first = false;
      else 
         out.write(", ");
      out.writeType(iu->getType());
   }
   out.write(">> ");
   out.writeIU(&vecIU);
   out.writeln(";");

   input->generate(out, required | IUSet(order), [&]() {
      out.writeIU(&vecIU);
      out.write(".push_back({");
      out.writeExpressions(vutil::map<Expression*>(order, [&](const Entry& e) { first = false; return e.value.get(); }));
      for (auto iu : required) {
         if (first) 
            first = false;
         else 
            out.write(", ");
         out.writeIU(iu);
      }
      out.writeln("});");
   });

   out.write("std::sort(");
   out.writeIU(&vecIU);
   out.write(".begin(), ");
   out.writeIU(&vecIU);
   out.writeln(".end(), [](const auto& t1, const auto& t2) {");
   
   for (size_t i = 0; i < order.size(); i++) {
      std::string istr = std::to_string(i);
      out.writeln("if (get<" + istr + ">(t1) < get<" + istr + ">(t2)) return true;");
      out.writeln("if (get<" + istr + ">(t2) < get<" + istr + ">(t1)) return false;");
   }

   out.writeln("return false;");
   out.writeln("});");

   out.write("for (auto& t : ");
   out.writeIU(&vecIU);
   out.writeln(") {");
   
   for (size_t i = 0; i < required.size(); i++) {
      auto iu = required[i];
      out.write("const ");
      out.writeType(iu->getType());
      out.write("& ");
      out.writeIU(iu);
      out.writeln(" = std::get<" + std::to_string(order.size() + i) + ">(t);");
   }
   consume();

   out.writeln("}");
}
//---------------------------------------------------------------------------
Window::Window(unique_ptr<Operator> input, vector<Aggregation> aggregates, vector<unique_ptr<Expression>> partitionBy, vector<Sort::Entry> orderBy)
   : input(move(input)), aggregates(move(aggregates)), partitionBy(move(partitionBy)), orderBy(move(orderBy))
// Constructor
{
}
//---------------------------------------------------------------------------
void Window::generate(CppWriter&, std::function<void()>)
// Generate SQL
{
   throw std::runtime_error("Window is not implemented");
}
//---------------------------------------------------------------------------
InlineTable::InlineTable(vector<unique_ptr<algebra::IU>> columns, vector<unique_ptr<algebra::Expression>> values, unsigned rowCount)
   : columns(move(columns)), values(move(values)), rowCount(move(rowCount))
// Constructor
{
}
//---------------------------------------------------------------------------
void InlineTable::generate(CppWriter&, std::function<void()>)
// Generate SQL
{
   throw std::runtime_error("InlineTable is not implemented");
}
//---------------------------------------------------------------------------
IndexScan::IndexScan(std::string name, std::vector<TableScan::Column> columns, std::vector<std::unique_ptr<Expression>> indexExpressions) 
   : name(move(name)), columns(move(columns)), indexExpressions(move(indexExpressions))
// Constructor
{
}
//---------------------------------------------------------------------------
void IndexScan::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   out.write("db->" + name + ".lookup1({");
      
   bool first = true;
   for (auto& e : indexExpressions) {
      if (first)
         first = false;
      else
         out.write(", ");
      out.writeExpression(e.get());
   }

   out.writeln("}, [&](auto& value) {");

   size_t i = 0;
   for (auto& c : columns) {
      if (required.contains(c.iu.get())) {
         out.writeType(c.iu->getType());
         out.write(" ");
         out.writeIU(c.iu.get());
         out.write(" = ");

         // assumes that the key IUs are the same order as the index expressions
         if (c.isKey) {
            out.writeExpression(indexExpressions[i].get());
         } else {
            out.write("value." + c.name);
         }

         out.writeln(";");
      }

      i += 1;
   }

   consume();
   out.writeln("});");
}
//---------------------------------------------------------------------------
IndexJoin::IndexJoin(unique_ptr<Operator> input, unique_ptr<IndexScan> indexScan) 
   : input(move(input)), indexScan(std::move(indexScan))
// Constructor
{
}
//---------------------------------------------------------------------------
void IndexJoin::generate(CppWriter& out, const IUSet& required, std::function<void()> consume)
// Generate SQL
{
   input->generate(out, required, [&]() {
      indexScan->generate(out, required, consume);
   });
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
