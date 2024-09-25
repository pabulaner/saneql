#include "algebra/Expression.hpp"
#include "algebra/Operator.hpp"
#include "sql/SQLWriter.hpp"
#include "adapter/CppWriter.hpp"
#include "adapter/TimeUtil.hpp"
#include <algorithm>
#include <utility>
#include <iostream>
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
void Expression::generateOperand(CppWriter& out)
// Generate SQL in a form that is suitable as operand
{
   out.write("(");
   generate(out);
   out.write(")");
}
//---------------------------------------------------------------------------
IURef::IURef(const IU* iu)
   : Expression(iu->getType()), iu(iu)
// Constructor
{
}
//---------------------------------------------------------------------------
void IURef::generate(CppWriter& out)
// Generate SQL
{
   out.writeIU(iu);
}
//---------------------------------------------------------------------------
void ConstExpression::generate(CppWriter& out)
// Generate SQL
{
   if (null) {
      out.write("NULL");
   } else {
      auto type = getType();
      if ((type.getType() != Type::Char) && (type.getType() != Type::Varchar) && (type.getType() != Type::Text)) {
         out.write(value);
      } else {
         out.write("Varchar<" + std::to_string(value.size()) + ">(\"" + value + "\")");
      }
   }
}
//---------------------------------------------------------------------------
void CastExpression::generate(CppWriter& out)
// Generate SQL
{
   ConstExpression* exp = dynamic_cast<ConstExpression*>(input.get());

   if (getType().getType() == Type::Date && exp) {
      std::string value = exp->getValue();
      out.write(std::to_string(tutil::parseDate(value)));
   } else {
      out.write("(");
      out.writeType(getType());
      out.write(")");
      input->generate(out);
   }
}
//---------------------------------------------------------------------------
ComparisonExpression::ComparisonExpression(unique_ptr<Expression> left, unique_ptr<Expression> right, Mode mode, Collate collate)
   : Expression(Type::getBool().withNullable((mode != Mode::Is) && (mode != Mode::IsNot) && (left->getType().isNullable() || right->getType().isNullable()))), left(move(left)), right(move(right)), mode(mode), collate(collate)
// Constructor
{
}
//---------------------------------------------------------------------------
void ComparisonExpression::generate(CppWriter& out)
// Generate SQL
{
   left->generateOperand(out);
   switch (mode) {
      case Mode::Equal: out.write(" == "); break;
      case Mode::NotEqual: out.write(" != "); break;
      case Mode::Is: throw std::runtime_error("ComparisionExpression Is is not implemented");
      case Mode::IsNot: throw std::runtime_error("ComparisionExpression IsNot is not implemented");
      case Mode::Less: out.write(" < "); break;
      case Mode::LessOrEqual: out.write(" <= "); break;
      case Mode::Greater: out.write(" > "); break;
      case Mode::GreaterOrEqual: out.write(" >= "); break;
      case Mode::Like: throw std::runtime_error("ComparisionExpression Like is not implemented");
   }
   right->generateOperand(out);
}
//---------------------------------------------------------------------------
BetweenExpression::BetweenExpression(unique_ptr<Expression> base, unique_ptr<Expression> lower, unique_ptr<Expression> upper, Collate collate)
   : Expression(Type::getBool().withNullable(base->getType().isNullable() || lower->getType().isNullable() || upper->getType().isNullable())), base(move(base)), lower(move(lower)), upper(move(upper)), collate(collate)
// Constructor
{
}
//---------------------------------------------------------------------------
void BetweenExpression::generate(CppWriter& out)
// Generate SQL
{
   base->generateOperand(out);
   out.write(" >= ");
   lower->generateOperand(out);
   out.write(" && ");
   base->generateOperand(out);
   out.write(" <= ");
   upper->generateOperand(out);
}
//---------------------------------------------------------------------------
InExpression::InExpression(unique_ptr<Expression> probe, vector<unique_ptr<Expression>> values, Collate collate)
   : Expression(Type::getBool().withNullable(probe->getType().isNullable() || any_of(values.begin(), values.end(), [](auto& e) { return e->getType().isNullable(); }))), probe(move(probe)), values(move(values)), collate(collate)
// Constructor
{
}
//---------------------------------------------------------------------------
void InExpression::generate(CppWriter& out)
// Generate SQL
{
   out.write("vutil::contains({");
   bool first = true;
   for (auto& v : values) {
      if (first)
         first = false;
      else
         out.write(", ");
      v->generate(out);
   }
   out.write("}, ");
   probe->generate(out);
   out.write(")");
}
//---------------------------------------------------------------------------
BinaryExpression::BinaryExpression(unique_ptr<Expression> left, unique_ptr<Expression> right, Type resultType, Operation op)
   : Expression(resultType), left(move(left)), right(move(right)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
void BinaryExpression::generate(CppWriter& out)
// Generate SQL
{
   if (op == Operation::Power) {
      out.write("std::pow(");
      left->generate(out);
      out.write(", ");
      right->generate(out);
      out.write(")");
   } else {
      left->generateOperand(out);
      switch (op) {
         case Operation::Plus: out.write(" + "); break;
         case Operation::Minus: out.write(" - "); break;
         case Operation::Mul: out.write(" * "); break;
         case Operation::Div: out.write(" / "); break;
         case Operation::Mod: out.write(" % "); break;
         case Operation::Concat: out.write(" || "); break;
         case Operation::And: out.write(" && "); break;
         case Operation::Or: out.write(" || "); break;
      }
      right->generateOperand(out);
   }
}
//---------------------------------------------------------------------------
UnaryExpression::UnaryExpression(unique_ptr<Expression> input, Type resultType, Operation op)
   : Expression(resultType), input(move(input)), op(op)
// Constructor
{
}
//---------------------------------------------------------------------------
void UnaryExpression::generate(CppWriter& out)
// Generate SQL
{
   switch (op) {
      case Operation::Plus: out.write("+"); break;
      case Operation::Minus: out.write("-"); break;
      case Operation::Not: out.write("!"); break;
   }
   input->generateOperand(out);
}
//---------------------------------------------------------------------------
ExtractExpression::ExtractExpression(unique_ptr<Expression> input, Part part)
   : Expression(Type::getInteger().withNullable(input->getType().isNullable())), input(move(input)), part(part)
// Constructor
{
}
//---------------------------------------------------------------------------
void ExtractExpression::generate(CppWriter& out)
// Generate SQL
{
   throw std::runtime_error("ExtractExpression is not implemented");
}
//---------------------------------------------------------------------------
SubstrExpression::SubstrExpression(unique_ptr<Expression> value, unique_ptr<Expression> from, unique_ptr<Expression> len)
   : Expression(value->getType().withNullable(value->getType().isNullable() || (from ? from->getType().isNullable() : false) || (len ? len->getType().isNullable() : false))), value(move(value)), from(move(from)), len(move(len))
// Constructor
{
}
//---------------------------------------------------------------------------
void SubstrExpression::generate(CppWriter& out)
// Generate SQL
{
   throw std::runtime_error("SubstrExpression is not implemented");
}
//---------------------------------------------------------------------------
SimpleCaseExpression::SimpleCaseExpression(unique_ptr<Expression> value, Cases cases, unique_ptr<Expression> defaultValue)
   : Expression(defaultValue->getType()), value(move(value)), cases(move(cases)), defaultValue(move(defaultValue))
// Constructor
{
}
//---------------------------------------------------------------------------
void SimpleCaseExpression::generate(CppWriter& out)
// Generate SQL
{
   throw std::runtime_error("SimpleCaseExpression is not implemented");
}
//---------------------------------------------------------------------------
SearchedCaseExpression::SearchedCaseExpression(Cases cases, unique_ptr<Expression> defaultValue)
   : Expression(defaultValue->getType()), cases(move(cases)), defaultValue(move(defaultValue))
// Constructor
{
}
//---------------------------------------------------------------------------
void SearchedCaseExpression::generate(CppWriter& out)
// Generate SQL
{
   throw std::runtime_error("SearchedCaseExpression is not implemented");
}
//---------------------------------------------------------------------------
Aggregate::Aggregate(unique_ptr<Operator> input, vector<Aggregation> aggregates, unique_ptr<Expression> computation)
   : Expression(computation->getType()), input(move(input)), aggregates(move(aggregates)), computation(move(computation))
// Constructor
{
}
//---------------------------------------------------------------------------
IUSet Aggregate::getIUs() const 
// Generate SQL
{ 
   return IUSet(); 
}
//---------------------------------------------------------------------------
void Aggregate::generate(CppWriter& out)
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
         default: throw std::runtime_error("Unsupported aggregate aggregation");
      }
   }

   out.writeln("[&]() {");

   for (auto& a : aggregates) {
      if (a.op == Op::Avg) {
         out.write("std::pair<");
         out.writeType(a.iu->getType());
         out.write(", ");
         out.writeType(Type::getInteger());
         out.write(">");
      } else {
         out.writeType(a.iu->getType());
      }

      out.write(" ");
      out.writeIU(a.iu.get());
      out.write(" = ");

      switch (a.op) {
         case Op::Sum: out.write("0"); break;
         case Op::Min: out.write("std::numeric_limits<"); out.writeType(a.iu->getType()); out.write(">::max()"); break;
         case Op::Max: out.write("std::numeric_limits<"); out.writeType(a.iu->getType()); out.write(">::min()"); break;
         case Op::Avg: out.write("{0, 0}"); break;
         case Op::CountStar: out.write("0"); break;
         default: throw;
      }

      out.writeln(";");
   }

   IUSet required;

   for (auto& a : aggregates) {
      if (a.value.get()) {
         required = required | IUSet(a.value->getIUs());
      }
   }

   input->generate(out, required, [&]() {
      for (size_t i = 0; i < aggregates.size(); i++) {
         Aggregation& a = aggregates[i];
         std::string name = out.getIUName(a.iu.get());

         out.write(name + " ");
         switch (a.op) {
            case Op::Sum: out.write("+= "); out.writeExpression(a.value.get()); break;
            case Op::Min: out.write("= std::min("); out.writeIU(a.iu.get()); out.write(", "); out.writeExpression(a.value.get()); out.write(")"); break;
            case Op::Max: out.write("= std::max("); out.writeIU(a.iu.get()); out.write(", "); out.writeExpression(a.value.get()); out.write(")"); break;
            case Op::Avg: out.write("= {" + name + ".first + "); out.writeExpression(a.value.get()); out.write(", " + name + ".second + 1}"); break;
            case Op::CountStar: out.write("+= 1"); break;
            default: throw;
         }
         out.writeln(";");
      }
   });

   out.write("return ");
   out.writeExpression(computation.get());
   out.writeln(";");
   out.write("}()");
}
//---------------------------------------------------------------------------
ForeignCall::ForeignCall(string name, Type returnType, vector<unique_ptr<Expression>> arguments, CallType callType)
   : Expression(returnType), name(std::move(name)), arguments(std::move(arguments)), callType(callType)
// Constructor
{
}
//---------------------------------------------------------------------------
void ForeignCall::generate(CppWriter& out) {
   throw std::runtime_error("ForeignCall is not implemented");
}
//---------------------------------------------------------------------------
}
//---------------------------------------------------------------------------
