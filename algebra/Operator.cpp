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
std::vector<const IU*> TableScan::getKeyIUs() const 
// Get the key IUs
{ 
   std::vector<const IU*> result;

   for (auto& c : columns) {
      if (c.isKey) {
         result.push_back(c.iu.get());
      }
   }

   return result;
}
//---------------------------------------------------------------------------
void TableScan::generate(CppWriter& out, std::function<void()> consume)
// Generate SQL
{
   out.writeln("db->" + name + ".forEach([&](auto& key, auto& value) {");

   for (auto& c : columns) {
      out.writeType(c.iu->getType());
      out.write(" ");
      out.writeIU(c.iu.get());
      out.write(" = ");
      out.write(c.isKey ? "key" : "value");
      out.writeln("." + c.name + ";");
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
void Select::generate(CppWriter& out, std::function<void()> consume)
// Generate SQL
{
   input->generate(out, [&]() {
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
void Map::generate(CppWriter& out, std::function<void()> consume)
// Generate SQL
{
   input->generate(out, [&]() {
      for (auto& c : computations) {
         out.writeType(c.iu->getType());
         out.write(" ");
         out.writeIU(c.iu.get());
         out.write(" = ");
         out.writeExpression(c.value.get());
         out.writeln(";");
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
void Join::generate(CppWriter& out, std::function<void()> consume)
// Generate SQL
{
   // validate
   if (joinType != JoinType::Inner) {
      throw std::runtime_error("Unsupported join type");
   }

   std::pair<std::vector<const IU*>, std::vector<const IU*>> keyIUs = outil::getJoinKeyIUs(left.get(), right.get(), condition.get());
   std::vector<const IU*> leftKeyIUs = std::move(keyIUs.first);
   std::vector<const IU*> rightKeyIUs = std::move(keyIUs.second);

   std::vector<const IU*> leftPayloadIUs;
   std::vector<const IU*> rightPayloadIUs;

   for (auto iu : left->getIUs()) {
      if (!vutil::contains(leftKeyIUs, iu)) {
         leftPayloadIUs.push_back(iu);
      }
   }
   for (auto iu : right->getIUs()) {
      if (!vutil::contains(rightKeyIUs, iu)) {
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

   left->generate(out, [&]() {
      out.writeIU(&mapIU);
      out.write(".insert({{");
      out.writeIUs(leftKeyIUs);
      out.write("}, {");
      out.writeIUs(leftPayloadIUs);
      out.writeln("}});");
   });
   right->generate(out, [&]() {
      out.write("for (auto range = ");
      out.writeIU(&mapIU);
      out.write(".equal_range({");
      out.writeIUs(rightKeyIUs);
      out.writeln("}); range.first!=range.second; range.first++) {");

      for (size_t i = 0; i < leftKeyIUs.size(); i++) {
         auto iu = leftKeyIUs[i];
         out.writeType(iu->getType());
         out.write(" ");
         out.writeIU(iu);
         out.writeln(" = std::get<" + std::to_string(i) + ">(range.first->first);");
      }
      for (size_t i = 0; i < leftPayloadIUs.size(); i++) {
         auto iu = leftPayloadIUs[i];
         out.writeType(iu->getType());
         out.write(" ");
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
void GroupBy::generate(CppWriter& out, std::function<void()> consume)
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

   const IU mapIU{Type::getUnknown()};

   out.write("std::unordered_map<std::tuple<");
   out.writeTypes(vutil::map<Type>(groupBy, [](const Entry& e) { return e.iu->getType(); }));
   out.write(">, std::tuple<");

   bool first = true;
   for (auto& a : aggregates) {
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

   out.write(">> ");
   out.writeIU(&mapIU);
   out.writeln(";");

   input->generate(out, [&]() {
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
      for (auto& a : aggregates) {
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

      out.writeln("}});");
      out.writeln("} else {");

      for (size_t i = 0; i < aggregates.size(); i++) {
         std::string value = "std::get<" + std::to_string(i) + ">(it->second)";
         Aggregation& a = aggregates[i];

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
         out.writeType(iu->getType());
         out.write(" ");
         out.writeIU(iu);
         out.writeln(" = std::get<" + std::to_string(i) + ">(it.first);");
   }
   for (size_t i = 0; i < aggregates.size(); i++) {
      Aggregation& a = aggregates[i];

      out.writeType(a.iu->getType());
      out.write(" ");
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
void Sort::generate(CppWriter& out, std::function<void()> consume)
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

   std::vector<const IU*> ius = input->getIUs();
   const IU vecIU{Type::getUnknown()};

   bool first = true;
   out.write("std::vector<std::tuple<");
   out.writeTypes(vutil::map<Type>(order, [&](const Entry& e) { first = false; return e.value->getType(); }));
   for (auto iu : ius) {
      if (first) 
         first = false;
      else 
         out.write(", ");
      out.writeType(iu->getType());
   }
   out.write(">> ");
   out.writeIU(&vecIU);
   out.writeln(";");

   input->generate(out, [&]() {
      out.writeIU(&vecIU);
      out.write(".push_back({");
      out.writeExpressions(vutil::map<Expression*>(order, [&](const Entry& e) { first = false; return e.value.get(); }));
      for (auto iu : input->getIUs()) {
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
   out.writeln(".end(), [](const auto& t1, const auto& t2) { return t1 < t2; });");

   out.write("for (auto& t : ");
   out.writeIU(&vecIU);
   out.writeln(") {");
   
   for (size_t i = 0; i < ius.size(); i++) {
      auto iu = ius[i];
      out.writeType(iu->getType());
      out.write(" ");
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
IndexJoin::IndexJoin(string name, vector<TableScan::Column> columns, unique_ptr<Operator> input, vector<const IU*> indexIUs) 
   : name(move(name)), columns(move(columns)), input(move(input)), indexIUs(move(indexIUs))
// Constructor
{
}
//---------------------------------------------------------------------------
void IndexJoin::generate(CppWriter& out, std::function<void()> consume)
// Generate SQL
{
   input->generate(out, [&]() {
      out.write("db->" + name + ".lookup1({");
      
      bool first = true;
      for (auto iu : indexIUs) {
         if (first)
            first = false;
         else
            out.write(", ");
         out.writeIU(iu);
      }

      out.writeln("}, [&](auto& value) {");

      size_t i = 0;
      for (auto& c : columns) {
         out.writeType(c.iu->getType());
         out.write(" ");
         out.writeIU(c.iu.get());
         out.write(" = ");

         // assumes that the key IUs are the same order as the index IUs
         if (c.isKey) {
            out.writeIU(indexIUs[i++]);
         } else {
            out.write("value." + c.name);
         }

         out.writeln(";");
      }

      consume();
      out.writeln("});");
   });
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
