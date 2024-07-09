#ifndef H_saneql_Expression
#define H_saneql_Expression
//---------------------------------------------------------------------------
#include "infra/Schema.hpp"
#include "semana/Functions.hpp"
#include <memory>
#include <vector>
//---------------------------------------------------------------------------
// SaneQL
// (c) 2023 Thomas Neumann
// SPDX-License-Identifier: BSD-3-Clause
//---------------------------------------------------------------------------
namespace adapter {
class CppWriter;
}
//---------------------------------------------------------------------------
using namespace adapter;
//---------------------------------------------------------------------------
namespace saneql {
//---------------------------------------------------------------------------
enum class Collate : uint8_t;
class SQLWriter;
//---------------------------------------------------------------------------
namespace algebra {
//---------------------------------------------------------------------------
class IU;
class Operator;
//---------------------------------------------------------------------------
/// Base class for expressions
class Expression {
   private:
   /// The type
   Type type;

   public:
   /// Constructor
   explicit Expression(Type type) : type(type) {}
   /// Destructor
   virtual ~Expression();

   /// Get the result type
   Type getType() const { return type; }
   /// Get the IUs
   virtual std::vector<const IU*> getIUs() const = 0;

   /// Generate SQL
   virtual void generate(CppWriter& out) = 0;
   /// Generate SQL in a form that is suitable as operand
   virtual void generateOperand(CppWriter& out);

   protected:
   std::vector<const IU*> combineIUs(const std::vector<std::vector<const IU*>>& ius) const;
};
//---------------------------------------------------------------------------
/// An IU reference
class IURef : public Expression {
   /// The IU
   const IU* iu;

   public:
   /// Constructor
   IURef(const IU* iu);

   /// Get the IU
   const IU* getIU() const { return iu; }
   /// Get the IUs
   std::vector<const IU*> getIUs() const override { return {iu}; }

   /// Generate SQL
   void generate(CppWriter& out) override;
   /// Generate SQL in a form that is suitable as operand
   void generateOperand(CppWriter& out) override { generate(out); }
};
//---------------------------------------------------------------------------
/// A constant value
class ConstExpression : public Expression {
   /// The raw value
   std::string value;
   /// NULL?
   bool null;

   public:
   /// Constructor for non-null values
   ConstExpression(std::string value, Type type) : Expression(type), value(std::move(value)), null(false) {}
   /// Constructor for NULL values
   ConstExpression(std::nullptr_t, Type type) : Expression(type), null(true) {}

   /// Get the IUs
   std::vector<const IU*> getIUs() const override { return {}; }

   /// Generate SQL
   void generate(CppWriter& out) override;
   /// Generate SQL in a form that is suitable as operand
   void generateOperand(CppWriter& out) override { generate(out); }
};
//---------------------------------------------------------------------------
/// A cast expression
class CastExpression : public Expression {
   /// The input
   std::unique_ptr<Expression> input;

   public:
   /// Constructor
   CastExpression(std::unique_ptr<Expression> input, Type type) : Expression(type), input(move(input)) {}

   /// Get the IUs
   std::vector<const IU*> getIUs() const override { return input->getIUs(); }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A comparison expression
class ComparisonExpression : public Expression {
   public:
   /// Possible modes
   enum Mode {
      Equal,
      NotEqual,
      Is,
      IsNot,
      Less,
      LessOrEqual,
      Greater,
      GreaterOrEqual,
      Like
   };
   /// The input
   std::unique_ptr<Expression> left, right;
   /// The mode
   Mode mode;
   /// The collation
   Collate collate;

   public:
   /// Constructor
   ComparisonExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, Mode mode, Collate collate);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override {
      return combineIUs({left->getIUs(), right->getIUs()});
   }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A between expression
class BetweenExpression : public Expression {
   public:
   /// The input
   std::unique_ptr<Expression> base, lower, upper;
   /// The collation
   Collate collate;

   public:
   /// Constructor
   BetweenExpression(std::unique_ptr<Expression> base, std::unique_ptr<Expression> lower, std::unique_ptr<Expression> upper, Collate collate);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override {
      return combineIUs({base->getIUs(), lower->getIUs(), upper->getIUs()});
   }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// An in expression
class InExpression : public Expression {
   public:
   /// The input
   std::unique_ptr<Expression> probe;
   /// The values to check against
   std::vector<std::unique_ptr<Expression>> values;
   /// The collation
   Collate collate;

   public:
   /// Constructor
   InExpression(std::unique_ptr<Expression> probe, std::vector<std::unique_ptr<Expression>> values, Collate collate);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override;

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A binary expression
class BinaryExpression : public Expression {
   public:
   /// Possible operations
   enum Operation {
      Plus,
      Minus,
      Mul,
      Div,
      Mod,
      Power,
      Concat,
      And,
      Or
   };
   /// The input
   std::unique_ptr<Expression> left, right;
   /// The mode
   Operation op;

   public:
   /// Constructor
   BinaryExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, Type resultType, Operation op);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override {
      return combineIUs({left->getIUs(), right->getIUs()});
   }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// An unary expression
class UnaryExpression : public Expression {
   public:
   /// Possible operations
   enum Operation {
      Plus,
      Minus,
      Not
   };
   /// The input
   std::unique_ptr<Expression> input;
   /// The mode
   Operation op;

   public:
   /// Constructor
   UnaryExpression(std::unique_ptr<Expression> input, Type resultType, Operation op);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override { return input->getIUs(); }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// An extract expression
class ExtractExpression : public Expression {
   public:
   /// Possible parts
   enum Part {
      Year,
      Month,
      Day
   };
   /// The input
   std::unique_ptr<Expression> input;
   /// The part
   Part part;

   public:
   /// Constructor
   ExtractExpression(std::unique_ptr<Expression> input, Part part);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override { return input->getIUs(); }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A substring expression
class SubstrExpression : public Expression {
   public:
   /// The input
   std::unique_ptr<Expression> value, from, len;

   public:
   /// Constructor
   SubstrExpression(std::unique_ptr<Expression> value, std::unique_ptr<Expression> from, std::unique_ptr<Expression> len);

   /// Get the IUs
   std::vector<const IU*> getIUs() const override { 
      return combineIUs({value->getIUs(), from->getIUs(), len->getIUs()});
   }

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A simple case expression
class SimpleCaseExpression : public Expression {
   public:
   using Cases = std::vector<std::pair<std::unique_ptr<algebra::Expression>, std::unique_ptr<algebra::Expression>>>;

   /// The value to search
   std::unique_ptr<Expression> value;
   /// The cases
   Cases cases;
   /// The default result
   std::unique_ptr<Expression> defaultValue;

   public:
   /// Constructor
   SimpleCaseExpression(std::unique_ptr<Expression> value, Cases cases, std::unique_ptr<Expression> defaultValue);

   // TODO: implement
   /// Get the IUs
   std::vector<const IU*> getIUs() const override {}

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A searched case expression
class SearchedCaseExpression : public Expression {
   public:
   using Cases = SimpleCaseExpression::Cases;

   /// The cases
   Cases cases;
   /// The default result
   std::unique_ptr<Expression> defaultValue;

   public:
   /// Constructor
   SearchedCaseExpression(Cases cases, std::unique_ptr<Expression> defaultValue);

   // TODO: implement
   /// Get the IUs
   std::vector<const IU*> getIUs() const override {}

   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// Helper for aggregation steps
struct AggregationLike {
   /// A regular computation
   struct Entry {
      /// The expression
      std::unique_ptr<algebra::Expression> value;
      /// The result IU
      std::unique_ptr<algebra::IU> iu;
   };
   /// Known aggregation functions
   enum class Op {
      CountStar,
      Count,
      CountDistinct,
      Sum,
      SumDistinct,
      Min,
      Max,
      Avg,
      AvgDistinct
   };
   /// Known window functions
   enum class WindowOp {
      CountStar,
      Count,
      CountDistinct,
      Sum,
      SumDistinct,
      Min,
      Max,
      Avg,
      AvgDistinct,
      RowNumber,
      Rank,
      DenseRank,
      NTile,
      Lead,
      Lag,
      FirstValue,
      LastValue
   };
   static_assert(static_cast<unsigned>(Op::AvgDistinct) == static_cast<unsigned>(WindowOp::AvgDistinct));

   /// An aggregation
   struct Aggregation {
      /// The expression
      std::unique_ptr<algebra::Expression> value;
      /// The result IU
      std::unique_ptr<algebra::IU> iu;
      /// The operation
      Op op;
      /// The parameters
      std::vector<std::unique_ptr<algebra::Expression>> parameters{};
   };
};
//---------------------------------------------------------------------------
/// An aggregate expression
class Aggregate : public Expression, public AggregationLike {
   private:
   /// The input
   std::unique_ptr<Operator> input;
   /// The aggregates
   std::vector<Aggregation> aggregates;
   /// The final result computation
   std::unique_ptr<Expression> computation;

   public:
   /// Constructor
   Aggregate(std::unique_ptr<Operator> input, std::vector<Aggregation> aggregates, std::unique_ptr<Expression> computation);

   // TODO: implement
   /// Get the IUs
   std::vector<const IU*> getIUs() const override {}

   // Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
/// A foreign call expression
struct ForeignCall : public Expression {
   // Type of the generated call
   enum class CallType { Function, LeftAssocOperator, RightAssocOperator };
   static constexpr CallType defaultType() { return CallType::Function; }

   private:
   /// The name of the declared function
   std::string name;
   /// The function call arguments
   std::vector<std::unique_ptr<Expression>> arguments;
   /// The call type
   CallType callType;

   public:
   /// Constructor
   ForeignCall(std::string name, Type returnType, std::vector<std::unique_ptr<Expression>> arguments, CallType callType);

   // TODO: implement
   /// Get the IUs
   std::vector<const IU*> getIUs() const override {}
   
   /// Generate SQL
   void generate(CppWriter& out) override;
};
//---------------------------------------------------------------------------
}
}
//---------------------------------------------------------------------------
#endif
