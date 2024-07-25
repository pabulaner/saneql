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
std::unique_ptr<p2c::Operator> TableScan::generate(IUStorage& s)
// Generate SQL
{
   std::vector<p2c::IU> keyIUs;
   std::vector<p2c::IU> ius;

   for (auto& c : columns) {
      auto iu = p2c::IU{c.name, p2c::Type::Undefined};
      if (c.isKey) 
         keyIUs.push_back(iu);
      else
         ius.push_back(iu);
   }

   auto op = std::make_unique<p2c::Scan>(name, keyIUs, ius);
   
   for (auto& c : columns) {
      s.add(c.iu.get(), op->getIU(c.name));
   }

   return op;
}
//---------------------------------------------------------------------------
Select::Select(unique_ptr<Operator> input, unique_ptr<Expression> condition)
   : input(move(input)), condition(move(condition))
// Constructor
{
}
//---------------------------------------------------------------------------
std::unique_ptr<p2c::Operator> Select::generate(IUStorage& s)
// Generate SQL
{
   auto inOp = input->generate(s);
   return std::make_unique<p2c::Selection>(std::move(inOp), condition->generate(s));
}
//---------------------------------------------------------------------------
Map::Map(unique_ptr<Operator> input, vector<Entry> computations)
   : input(move(input)), computations(move(computations))
// Constructor
{
}
//---------------------------------------------------------------------------
std::unique_ptr<p2c::Operator> Map::generate(IUStorage& s)
// Generate SQL
{
   auto op = input->generate(s);
   for (auto& c : computations) {
      auto mapOp = std::make_unique<p2c::Map>(std::move(op), c.value->generate(s));
      s.add(c.iu.get(), mapOp->getIU());
      op = std::move(mapOp);
   }
   return op;
}
//---------------------------------------------------------------------------
SetOperation::SetOperation(unique_ptr<Operator> left, unique_ptr<Operator> right, vector<unique_ptr<Expression>> leftColumns, vector<unique_ptr<Expression>> rightColumns, vector<unique_ptr<IU>> resultColumns, Op op)
   : left(move(left)), right(move(right)), leftColumns(move(leftColumns)), rightColumns(move(rightColumns)), resultColumns(move(resultColumns)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
std::unique_ptr<p2c::Operator> SetOperation::generate(IUStorage& s)
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
std::unique_ptr<p2c::Operator> Join::generate(IUStorage& s)
// Generate SQL
{
   if (!condition->equiJoinProperty()) {
      throw;
   }

   auto inLeftOp = left->generate(s);
   auto inRightOp = right->generate(s);

   std::vector<const IU*> ius = condition->getIUs();
   std::vector<p2c::IU*> leftKeyIUs;
   std::vector<p2c::IU*> rightKeyIUs;

   for (auto iu : left->getIUs()) {
      if (std::find(ius.begin(), ius.end(), iu) != ius.end()) {
         leftKeyIUs.push_back(s.get(iu));
      }
   }
   for (auto iu : right->getIUs()) {
      if (std::find(ius.begin(), ius.end(), iu) != ius.end()) {
         rightKeyIUs.push_back(s.get(iu));
      }
   }

   return std::make_unique<p2c::HashJoin>(std::move(inLeftOp), std::move(inRightOp), leftKeyIUs, rightKeyIUs);
}
//---------------------------------------------------------------------------
GroupBy::GroupBy(unique_ptr<Operator> input, vector<Entry> groupBy, vector<Aggregation> aggregates)
   : input(move(input)), groupBy(move(groupBy)), aggregates(move(aggregates))
// Constructor
{
}
//---------------------------------------------------------------------------
std::unique_ptr<p2c::Operator> GroupBy::generate(IUStorage& s)
// Generate SQL
{
   return nullptr;
}
//---------------------------------------------------------------------------
Sort::Sort(unique_ptr<Operator> input, vector<Entry> order, optional<uint64_t> limit, optional<uint64_t> offset)
   : input(move(input)), order(move(order)), limit(limit), offset(offset)
// Constructor
{
}
//---------------------------------------------------------------------------
std::unique_ptr<p2c::Operator> Sort::generate(IUStorage& s)
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
std::unique_ptr<p2c::Operator> Window::generate(IUStorage& s)
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
std::unique_ptr<p2c::Operator> InlineTable::generate(IUStorage& s)
// Generate SQL
{
   return nullptr;
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
