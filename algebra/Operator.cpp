#include "algebra/Operator.hpp"
#include "sql/SQLWriter.hpp"
#include "adapter/CppWriter.hpp"
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
const CppIU* TableScan::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   auto type = CppIU::Type::ScanOp;
   std::string nextParam = next->getRef();
   std::string dbParam = "&(db->" + name + ")";

   const CppIU* opIU = out.writeOperator(
      type, {nextParam, dbParam},
      [&]() {  
         std::string valueType = "const " + name + "_t";
         std::string keyType = valueType + "::Key";

         out.writeln("[&](" + keyType + "& key, " + valueType + "& value) {");

         for (auto& c : columns) {
            out.writeIU(c.iu.get());
            out.write(" = ");
            out.write(c.isKey ? "key" : "value");
            out.writeln("." + c.name + ";");
         }
         
         out.write("}");
      });

   out.writeProcess(opIU);
   return opIU;
}
//---------------------------------------------------------------------------
Select::Select(unique_ptr<Operator> input, unique_ptr<Expression> condition)
   : input(move(input)), condition(move(condition))
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* Select::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   auto type = CppIU::Type::SelectOp;
   std::string nextParam = next->getRef();

   const CppIU* opIU = out.writeOperator(
      type, {nextParam},
      [&]() {
         out.writeln("[&]() {");
         out.write("return ");
         condition->generate(out);
         out.writeln(";");
         out.write("}");
      });

   input->generate(out, opIU);
   return opIU;
}
//---------------------------------------------------------------------------
Map::Map(unique_ptr<Operator> input, vector<Entry> computations)
   : input(move(input)), computations(move(computations))
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* Map::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   auto type = CppIU::Type::MapOp;
   std::string nextParam = next->getRef();

   const CppIU* opIU = out.writeOperator(
      type, {nextParam},
      [&]() {
         out.writeln("[&]() {");

         for (auto& c : computations) {
            out.writeIU(c.iu.get());
            out.write(" = ");
            c.value->generate(out);
            out.writeln(";");
         }

         out.write("}");
      });

   input->generate(out, opIU);
   return opIU;
}
//---------------------------------------------------------------------------
SetOperation::SetOperation(unique_ptr<Operator> left, unique_ptr<Operator> right, vector<unique_ptr<Expression>> leftColumns, vector<unique_ptr<Expression>> rightColumns, vector<unique_ptr<IU>> resultColumns, Op op)
   : left(move(left)), right(move(right)), leftColumns(move(leftColumns)), rightColumns(move(rightColumns)), resultColumns(move(resultColumns)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* SetOperation::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   return nullptr;
}
//---------------------------------------------------------------------------
Join::Join(unique_ptr<Operator> left, unique_ptr<Operator> right, unique_ptr<Expression> condition, JoinType joinType)
   : left(move(left)), right(move(right)), condition(move(condition)), joinType(joinType)
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* Join::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   const CppIU* structIU = out.writeStruct(left->getIUs());

   auto type = CppIU::Type::JoinOp;
   std::string nextParam = next->getRef();
   std::string structParam = structIU->getName() + "{}";

   const CppIU* opIU = out.writeOperator(
      type, {nextParam, structParam},
      [&]() {
         out.writeln("[&]() {");
         out.write("return " + structIU->getName() + "{");

         bool first = true;
         for (auto iu : left->getIUs()) {
            if (first) 
               first = false;
            else
               out.write(", ");
            out.writeIU(iu);
         }

         out.writeln("};");
         out.writeln("}, [&](const " + structIU->getRef() + " row) {");

         for (auto iu : left->getIUs()) {
            out.writeIU(iu);
            out.write(" = row.");
            out.writeIU(iu);
            out.writeln(";");
         }

         out.writeln("}, [&]() {");
         out.write("return ");
         condition->generate(out);
         out.writeln(";");
         out.write("}");
      });

   left->generate(out, opIU);
   right->generate(out, opIU);

   return opIU;
}
//---------------------------------------------------------------------------
GroupBy::GroupBy(unique_ptr<Operator> input, vector<Entry> groupBy, vector<Aggregation> aggregates)
   : input(move(input)), groupBy(move(groupBy)), aggregates(move(aggregates))
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* GroupBy::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   std::vector<const IU*> keyStructIUs = util::map<const IU*>(groupBy, [](const Entry& e) { return e.iu.get(); });
   std::vector<const IU*> valueStructIUs = util::map<const IU*>(aggregates, [](const Aggregation& a) { return a.iu.get(); });
   std::unordered_map<const IU*, std::unique_ptr<IU>> avgCountIUs;

   for (auto& a : aggregates) {
      if (a.op == Op::Avg) {
         avgCountIUs[a.iu.get()] = std::make_unique<IU>(Type::getInteger());
         valueStructIUs.push_back(avgCountIUs[a.iu.get()].get());
      }
   }


   const CppIU* keyStructIU = out.writeStruct(keyStructIUs);
   const CppIU* valueStructIU = out.writeStruct(valueStructIUs);

   auto type = CppIU::Type::GroupByOp;
   std::string nextParam = next->getRef();
   std::string keyStructParam = keyStructIU->getName();
   std::string valueStructParam = valueStructIU->getName();

   const CppIU* opIU = out.writeOperator(
      type, {nextParam, keyStructParam, valueStructParam},
      [&]() {
         out.writeln("[&]() {");
         out.write("return " + keyStructIU->getName() + "{");

         bool first = true;
         for (auto iu : keyStructIUs) {
            if (first) 
               first = false;
            else
               out.write(", ");
            out.writeIU(iu);
         }

         out.writeln("};");
         out.writeln("}, [&](const " + valueStructIU->getRef() + " value) {");

         for (auto& a : aggregates) {
            out.write("value.");
            out.writeIU(a.iu.get());
            switch (a.op) {
               case Op::Count: out.write(" += 1"); break;
               case Op::Sum: out.write(" += "); a.value->generate(out);  break;
               // case Op::Avg: out.write(" += "); a.value->generate(out); break;
            }
            out.writeln(";");
         }

         out.writeln("}, [&](const " + keyStructIU->getRef() + " key, const " + valueStructIU->getRef() + " value) {");

         for (auto iu : keyStructIUs) {
            out.writeIU(iu);
            out.write(" = key.");
            out.writeIU(iu);
            out.writeln(";");
         }
         for (auto& a : aggregates) {
            out.writeIU(a.iu.get());
            out.write(" = value.");
            out.writeIU(a.iu.get());
            
            if (a.op == Op::Avg) {
               const IU* iu = avgCountIUs[a.iu.get()].get();
               out.write(" / (double) value.");
               out.writeIU(iu);
            }

            out.writeln(";");
         }

         out.write("}");
      });

   input->generate(out, opIU);
   return opIU;
}
//---------------------------------------------------------------------------
Sort::Sort(unique_ptr<Operator> input, vector<Entry> order, optional<uint64_t> limit, optional<uint64_t> offset)
   : input(move(input)), order(move(order)), limit(limit), offset(offset)
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* Sort::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   return nullptr;
}
//---------------------------------------------------------------------------
Window::Window(unique_ptr<Operator> input, vector<Aggregation> aggregates, vector<unique_ptr<Expression>> partitionBy, vector<Sort::Entry> orderBy)
   : input(move(input)), aggregates(move(aggregates)), partitionBy(move(partitionBy)), orderBy(move(orderBy))
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* Window::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   return nullptr;
}
//---------------------------------------------------------------------------
InlineTable::InlineTable(vector<unique_ptr<algebra::IU>> columns, vector<unique_ptr<algebra::Expression>> values, unsigned rowCount)
   : columns(move(columns)), values(move(values)), rowCount(move(rowCount))
// Constructor
{
}
//---------------------------------------------------------------------------
const CppIU* InlineTable::generate(CppWriter& out, const CppIU* next)
// Generate SQL
{
   return nullptr;
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
