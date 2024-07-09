#include "algebra/Operator.hpp"
#include "sql/SQLWriter.hpp"
#include "cpp/CppWriter.hpp"
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
   auto type = adapter::CppIU::Type::ScanOp;
   std::string nextParam = next->getName();
   std::string dbParam = "db." + name;

   const adapter::CppIU* opIU = out.writeOperator(
      type, {nextParam, dbParam},
      [&]() {  
         out.writeln("[&](auto& key, auto& value) {");

         for (auto& c : columns) {
            out.writeIU(c.iu.get());
            out.write(" = ");
            out.write(c.isKey ? "key" : "value");
            out.writeln("." + c.name + ";");
         }
         
         out.write("}");
      });

   out.writeBegin(opIU);
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
   auto type = adapter::CppIU::Type::SelectOp;
   std::string nextParam = next->getName();

   const adapter::CppIU* opIU = out.writeOperator(
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
   
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
