#ifndef DEFINITION_CC
#define DEFINITION_CC
#include "definition.hh"

using namespace std;

DefWithInit::DefWithInit(std::string tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : Definition()
  , _tipo ( tipo )
  , _ids  ( ids  )
  , _expr ( expr )
{}

std::string DefWithInit::to_string()
{
  std::string str = "tipo: " + _tipo + " inicializaciones:\n";
  for (unsigned int i=0; i < _ids->size(); ++i) {
    str += "nombre: " + _ids->at(i) + " Valor: " + _expr->at(i)->to_string() + "\n";
  }
  return str;
}

ConstDef::ConstDef(std::string tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : DefWithInit(tipo, ids, expr)
  {}

DefVar::DefVar(std::string tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : DefWithInit(tipo, ids, expr)
  {}

DefVarNoInit::DefVarNoInit(std::string tipo, std::vector<std::string>* ids)
  : _tipo( tipo )
  , _ids( ids )
  {}

std::string DefVarNoInit::to_string()
{
  std::string str = "tipo: " + _tipo + " Variables sin incializacion :\n";
  for (unsigned int i=0; i < _ids->size(); ++i) {
    str += "nombre: " + _ids->at(i) + "\n";
  }
  return str;
}

DefCueva::DefCueva(std::string tipo, std::string id, std::vector<std::string>* dimensiones)
  : _tipo( tipo )
  , _id( id )
  , _dimensiones( dimensiones )
  {}

std::string DefCueva::to_string()
{
  std::string str =  "Definicion de cueva : \n Tipo : " + _tipo + "\n Dimensiones : ";
 for (unsigned int i=0; i < _dimensiones->size(); ++i) {
    str += _dimensiones->at(i) + " ";
  }
  return str;
}
#endif
