#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"
#include "sql/SQLWriter.hpp"
#include "adapter/CppWriter.hpp"
#include <algorithm>
#include <utility>
//---------------------------------------------------------------------------
// (c) 2023 Thomas Neumann
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace saneql::algebra {
//---------------------------------------------------------------------------
Expression::~Expression()
// Destructor
{
}
//---------------------------------------------------------------------------
std::string Expression::generateOperand(IUStorage& s)
// Generate SQL in a form that is suitable as operand
{
   return "(" + generate(s) + ")";
}
//---------------------------------------------------------------------------
IURef::IURef(const IU* iu)
   : Expression(iu->getType()), iu(iu)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string IURef::generate(IUStorage& s)
// Generate SQL
{
   return s.get(iu)->varname;
}
//---------------------------------------------------------------------------
std::string ConstExpression::generate(IUStorage& s)
// Generate SQL
{
   if (null) {
      return "nullptr";
   } else {
      auto type = getType();
      if ((type.getType() != Type::Char) && (type.getType() != Type::Varchar) && (type.getType() != Type::Text)) {
         return value;
      } else {
         return "\"" + value + "\"";
      }
   }
}
//---------------------------------------------------------------------------
std::string CastExpression::generate(IUStorage& s)
// Generate SQL
{
   // TODO: make cast
   return input->generate(s);
}
//---------------------------------------------------------------------------
ComparisonExpression::ComparisonExpression(unique_ptr<Expression> left, unique_ptr<Expression> right, Mode mode, Collate collate)
   : Expression(Type::getBool().withNullable((mode != Mode::Is) && (mode != Mode::IsNot) && (left->getType().isNullable() || right->getType().isNullable()))), left(move(left)), right(move(right)), mode(mode), collate(collate)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string ComparisonExpression::generate(IUStorage& s)
// Generate SQL
{
   std::string result = left->generateOperand(out);
   switch (mode) {
      case Mode::Equal: result += " == "; break;
      case Mode::NotEqual: result += " != "; break;
      case Mode::Is: result += " is not distinct from "; break;
      case Mode::IsNot: result += " is distinct from "; break;
      case Mode::Less: result += " < "; break;
      case Mode::LessOrEqual: result += " <= "; break;
      case Mode::Greater: result += " > "; break;
      case Mode::GreaterOrEqual: result += " >= "; break;
      case Mode::Like: result += " like "; break;
   }
   return result + right->generateOperand(out);
}
//---------------------------------------------------------------------------
BetweenExpression::BetweenExpression(unique_ptr<Expression> base, unique_ptr<Expression> lower, unique_ptr<Expression> upper, Collate collate)
   : Expression(Type::getBool().withNullable(base->getType().isNullable() || lower->getType().isNullable() || upper->getType().isNullable())), base(move(base)), lower(move(lower)), upper(move(upper)), collate(collate)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string BetweenExpression::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
InExpression::InExpression(unique_ptr<Expression> probe, vector<unique_ptr<Expression>> values, Collate collate)
   : Expression(Type::getBool().withNullable(probe->getType().isNullable() || any_of(values.begin(), values.end(), [](auto& e) { return e->getType().isNullable(); }))), probe(move(probe)), values(move(values)), collate(collate)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string InExpression::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
BinaryExpression::BinaryExpression(unique_ptr<Expression> left, unique_ptr<Expression> right, Type resultType, Operation op)
   : Expression(resultType), left(move(left)), right(move(right)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string BinaryExpression::generate(IUStorage& s)
// Generate SQL
{
   std::string result = left->generateOperand(out);
   switch (op) {
      case Operation::Plus: result += " + "; break;
      case Operation::Minus: result += " - "; break;
      case Operation::Mul: result += " * "; break;
      case Operation::Div: result += " / "; break;
      case Operation::Mod: result += " % "; break;
      case Operation::Power: result += " ^ "; break;
      case Operation::Concat: result += " + "; break;
      case Operation::And: result += " && "; break;
      case Operation::Or: result += " || "; break;
   }
   return result + right->generateOperand(out);
}
//---------------------------------------------------------------------------
UnaryExpression::UnaryExpression(unique_ptr<Expression> input, Type resultType, Operation op)
   : Expression(resultType), input(move(input)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string UnaryExpression::generate(IUStorage& s)
// Generate SQL
{
   std::string result = "";
   switch (op) {
      case Operation::Plus: result += "+"; break;
      case Operation::Minus: result += "-"; break;
      case Operation::Not: result += "!"; break;
   }
   return result + input->generateOperand(out);
}
//---------------------------------------------------------------------------
ExtractExpression::ExtractExpression(unique_ptr<Expression> input, Part part)
   : Expression(Type::getInteger().withNullable(input->getType().isNullable())), input(move(input)), part(part)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string ExtractExpression::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
SubstrExpression::SubstrExpression(unique_ptr<Expression> value, unique_ptr<Expression> from, unique_ptr<Expression> len)
   : Expression(value->getType().withNullable(value->getType().isNullable() || (from ? from->getType().isNullable() : false) || (len ? len->getType().isNullable() : false))), value(move(value)), from(move(from)), len(move(len))
// Constructor
{
}
//---------------------------------------------------------------------------
std::string SubstrExpression::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
SimpleCaseExpression::SimpleCaseExpression(unique_ptr<Expression> value, Cases cases, unique_ptr<Expression> defaultValue)
   : Expression(defaultValue->getType()), value(move(value)), cases(move(cases)), defaultValue(move(defaultValue))
// Constructor
{
}
//---------------------------------------------------------------------------
std::string SimpleCaseExpression::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
SearchedCaseExpression::SearchedCaseExpression(Cases cases, unique_ptr<Expression> defaultValue)
   : Expression(defaultValue->getType()), cases(move(cases)), defaultValue(move(defaultValue))
// Constructor
{
}
//---------------------------------------------------------------------------
std::string SearchedCaseExpression::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
Aggregate::Aggregate(unique_ptr<Operator> input, vector<Aggregation> aggregates, unique_ptr<Expression> computation)
   : Expression(computation->getType()), input(move(input)), aggregates(move(aggregates)), computation(move(computation))
// Constructor
{
}
//---------------------------------------------------------------------------
std::string Aggregate::generate(IUStorage& s)
// Generate SQL
{
   return "";
}
//---------------------------------------------------------------------------
ForeignCall::ForeignCall(string name, Type returnType, vector<unique_ptr<Expression>> arguments, CallType callType)
   : Expression(returnType), name(std::move(name)), arguments(std::move(arguments)), callType(callType)
// Constructor
{
}
//---------------------------------------------------------------------------
std::string ForeignCall::generate(IUStorage& s) {
   return "";
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
