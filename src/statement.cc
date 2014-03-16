#ifndef STATEMENT_CC
#define STATEMENT_CC
#include "statement.hh"
#include <iostream>

using namespace std;

Assign::Assign(std::vector<Expression *>* ids, std::vector<Expression*>* expr)
  : Statement()
  , _ids  ( ids  )
  , _expr ( expr )
  {}

std::string Assign::to_string()
{
  std::string str = "";
  for (unsigned int i=0; i < _ids->size(); ++i) {
    str += "l-value: " + _ids->at(i)->to_string() + " Valor: " + _expr->at(i)->to_string() + "\n";
  }
  return str;
}

If::If(Expression* condicion, std::vector<Statement*>* instrucciones)
  : Statement()
  , _condicion     ( condicion     )
  , _instrucciones ( instrucciones )
  {}

std::string If::to_string()
{
  std::string str = "if " + _condicion->to_string() + "then: \n";
  for (unsigned int i=0; i < _instrucciones->size(); ++i) {
    str += _instrucciones->at(i)->to_string();
  }
  return str;
}

IfElse::IfElse(Expression* condicion, std::vector<Statement*>* brazoTrue, std::vector<Statement*>* brazoFalse)
  : Statement()
  , _condicion  ( condicion  )
  , _brazoTrue  ( brazoTrue  )
  , _brazoFalse ( brazoFalse )
  {}

std::string IfElse::to_string()
{
  std::string str = "if " + _condicion->to_string() + "then: \n";
  for (unsigned int i=0; i < _brazoTrue->size(); ++i) {
    str += _brazoTrue->at(i)->to_string();
  }
  str += "else: \n";
  for (unsigned int i=0; i < _brazoFalse->size(); ++i) {
    str += _brazoFalse->at(i)->to_string();
  }
  return str;
}
#endif
