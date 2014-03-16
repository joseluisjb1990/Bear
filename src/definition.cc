#ifndef DEFINITION_CC
#define DEFINITION_CC
#include "definition.hh"

using namespace std;

ConstDef::ConstDef(std::string tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : Definition()
  , _tipo ( tipo )
  , _ids  ( ids  )
  , _expr ( expr )
{}

std::string ConstDef::to_string()
{
  std::string str = "tipo: " + _tipo + " inicializaciones:\n";
  for (unsigned int i=0; i < _ids->size(); ++i) {
    str += "nombre: " + _ids->at(i) + " Valor: " + _expr->at(i)->to_string() + "\n";
  }
  return str;
}

#endif
