#ifndef H_saneql_Operator
#define H_saneql_Operator
//---------------------------------------------------------------------------
#include "adapter/VectorUtil.hpp"
#include "algebra/Expression.hpp"
#include "infra/Schema.hpp"
#include <memory>
#include <optional>
#include <vector>
#include <functional>
//---------------------------------------------------------------------------
// SaneQL
// (c) 2023 Thomas Neumann
// SPDX-License-Identifier: BSD-3-Clause
//---------------------------------------------------------------------------
namespace adapter {
class CppIU;
class CppWriter;
class Optimizer;
}
//---------------------------------------------------------------------------
using namespace adapter;
//---------------------------------------------------------------------------
namespace saneql {
//---------------------------------------------------------------------------
class SQLWriter;
//---------------------------------------------------------------------------
namespace algebra {
//---------------------------------------------------------------------------
/// An information unit
class IU {
   /// The type
   Type type;

   public:
   /// Constructor
   explicit IU(Type type) : type(type) {}

   /// Get the type
   const Type& getType() const { return type; }
};
//---------------------------------------------------------------------------
/// Base class for operators
class Operator {
   public:
   /// Destructor
   virtual ~Operator();

   // Get the IUs
   virtual std::vector<const IU*> getIUs() const { return {}; };
   // Get the inputs
   virtual std::vector<std::unique_ptr<Operator>> getInputs() { return {}; }
   // Set the inputs
   virtual void setInputs(std::vector<std::unique_ptr<Operator>> inputs) {}
   // Generate SQL
   virtual void generate(CppWriter& out, std::function<void()> consume) = 0;
};
//---------------------------------------------------------------------------
/// A table scan operator
class TableScan : public Operator {
   public:
   /// A column entry
   struct Column {
      /// Is key
      bool isKey;
      /// The name
      std::string name;
      /// The IU
      std::unique_ptr<IU> iu;
   };

   private:
   /// The table name
   std::string name;
   /// The columns
   std::vector<Column> columns;

   public:
   /// Constructor
   TableScan(std::string name, std::vector<Column> columns);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return vutil::map<const IU*>(columns, [](const Column& c) { return c.iu.get(); }); }
   // Get the key IUs
   std::vector<const IU*> getKeyIUs() const;
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;

   friend class adapter::Optimizer;
};
//---------------------------------------------------------------------------
/// A select operator
class Select : public Operator {
   /// The input
   std::unique_ptr<Operator> input;
   /// The filter condition
   std::unique_ptr<Expression> condition;

   public:
   /// Constructor
   Select(std::unique_ptr<Operator> input, std::unique_ptr<Expression> condition);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return input->getIUs(); }
   // Get the inputs
   std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(input)); }
   // Set the inputs
   void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { input = std::move(inputs[0]); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;

   friend class adapter::Optimizer;
};
//---------------------------------------------------------------------------
/// A map operator
class Map : public Operator {
   public:
   using Entry = AggregationLike::Entry;

   private:
   /// The input
   std::unique_ptr<Operator> input;
   /// The computations
   std::vector<Entry> computations;

   public:
   /// Constructor
   Map(std::unique_ptr<Operator> input, std::vector<Entry> computations);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return vutil::combine(input->getIUs(), vutil::map<const IU*>(computations, [](const Entry& e) { return e.iu.get(); })); }
   // Get the inputs
   std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(input)); }
   // Set the inputs
   void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { input = std::move(inputs[0]); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// A set operation operator
class SetOperation : public Operator {
   public:
   /// Operation types
   enum class Op {
      Union,
      UnionAll,
      Except,
      ExceptAll,
      Intersect,
      IntersectAll
   };

   private:
   /// The input
   std::unique_ptr<Operator> left, right;
   /// The input columns
   std::vector<std::unique_ptr<Expression>> leftColumns, rightColumns;
   /// The result columns
   std::vector<std::unique_ptr<IU>> resultColumns;
   /// The operation
   Op op;

   public:
   /// Constructor
   SetOperation(std::unique_ptr<Operator> left, std::unique_ptr<Operator> right, std::vector<std::unique_ptr<Expression>> leftColumns, std::vector<std::unique_ptr<Expression>> rightColumns, std::vector<std::unique_ptr<IU>> resultColumns, Op op);

   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// A join operator
class Join : public Operator {
   public:
   /// Join types
   enum class JoinType {
      Inner,
      LeftOuter,
      RightOuter,
      FullOuter,
      LeftSemi,
      RightSemi,
      LeftAnti,
      RightAnti
   };

   private:
   /// The input
   std::unique_ptr<Operator> left, right;
   /// The join condition
   std::unique_ptr<Expression> condition;
   /// The join type
   JoinType joinType;

   public:
   /// Constructor
   Join(std::unique_ptr<Operator> left, std::unique_ptr<Operator> right, std::unique_ptr<Expression> condition, JoinType joinType);

   /// Get the join type
   JoinType getJoinType() const { return joinType; }

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return vutil::combine(left->getIUs(), right->getIUs()); }
   // Get the inputs
   std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(left), std::move(right)); }
   // Set the inputs
   void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { left = std::move(inputs[0]); right = std::move(inputs[1]); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;

   friend class adapter::Optimizer;
};
//---------------------------------------------------------------------------
/// A group by operator
class GroupBy : public Operator, public AggregationLike {
   private:
   /// The input
   std::unique_ptr<Operator> input;
   /// The group by expressions
   std::vector<Entry> groupBy;
   /// The aggregates
   std::vector<Aggregation> aggregates;

   public:
   /// Constructor
   GroupBy(std::unique_ptr<Operator> input, std::vector<Entry> groupBy, std::vector<Aggregation> aggregates);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return vutil::combine(vutil::map<const IU*>(groupBy, [](auto& value) { return value.iu.get(); }), vutil::map<const IU*>(aggregates, [](auto& value) { return value.iu.get(); })); }
   // Get the inputs
   std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(input)); }
   // Set the inputs
   void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { input = std::move(inputs[0]); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// A sort operator
class Sort : public Operator {
   public:
   struct Entry {
      /// The value to order by
      std::unique_ptr<algebra::Expression> value;
      /// The collate
      Collate collate;
      /// Descending?
      bool descending;
   };

   /// The input
   std::unique_ptr<Operator> input;
   /// The order
   std::vector<Entry> order;
   /// View
   std::optional<uint64_t> limit, offset;

   public:
   /// Constructor
   Sort(std::unique_ptr<Operator> input, std::vector<Entry> order, std::optional<uint64_t> limit, std::optional<uint64_t> offset);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return input->getIUs(); }
   // Get the inputs
   std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(input)); }
   // Set the inputs
   void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { input = std::move(inputs[0]); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// A window operator
class Window : public Operator, public AggregationLike {
   public:
   using Op = WindowOp;

   private:
   /// The input
   std::unique_ptr<Operator> input;
   /// The aggregates
   std::vector<Aggregation> aggregates;
   /// The partition by expressions
   std::vector<std::unique_ptr<Expression>> partitionBy;
   /// The order by expression
   std::vector<Sort::Entry> orderBy;

   public:
   /// Constructor
   Window(std::unique_ptr<Operator> input, std::vector<Aggregation> aggregates, std::vector<std::unique_ptr<Expression>> partitionBy, std::vector<Sort::Entry> orderBy);

   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// An inline table definition
class InlineTable : public Operator {
   public:
   /// The columns
   std::vector<std::unique_ptr<algebra::IU>> columns;
   /// The values
   std::vector<std::unique_ptr<algebra::Expression>> values;
   /// The row count
   unsigned rowCount;

   public:
   /// Constructor
   InlineTable(std::vector<std::unique_ptr<algebra::IU>> columns, std::vector<std::unique_ptr<algebra::Expression>> values, unsigned rowCount);

   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// A index scan operator
class IndexScan : public Operator {
   private:
   /// The table name
   std::string name;
   /// The columns
   std::vector<TableScan::Column> columns;
   /// The index expressions
   std::vector<std::unique_ptr<Expression>> indexExpressions;

   public:
   /// Constructor
   IndexScan(std::string name, std::vector<TableScan::Column> columns, std::vector<std::unique_ptr<Expression>> indexExpressions);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return vutil::map<const IU*>(columns, [](const TableScan::Column& c) { return c.iu.get(); }); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
/// A index join operator
class IndexJoin : public Operator {
   private:
   /// The table name
   std::string name;
   /// The columns
   std::vector<TableScan::Column> columns;
   /// The input
   std::unique_ptr<Operator> input;
   /// The index IUs
   std::vector<const IU*> indexIUs;

   public:
   /// Constructor
   IndexJoin(std::string name, std::vector<TableScan::Column> columns, std::unique_ptr<Operator> input, std::vector<const IU*> indexIUs);

   // Get the IUs
   std::vector<const IU*> getIUs() const override { return vutil::combine(vutil::map<const IU*>(columns, [](const TableScan::Column& c) { return c.iu.get(); }), input->getIUs()); }
   // Get the inputs
   std::vector<std::unique_ptr<Operator>> getInputs() override { return vutil::make(std::move(input)); }
   // Set the inputs
   void setInputs(std::vector<std::unique_ptr<Operator>> inputs) override { input = std::move(inputs[0]); }
   // Generate SQL
   void generate(CppWriter& out, std::function<void()> consume) override;
};
//---------------------------------------------------------------------------
}
}
//---------------------------------------------------------------------------
#endif
