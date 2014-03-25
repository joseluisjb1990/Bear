#ifndef DEFINITION_CC
#define DEFINITION_CC
#include "definition.hh"

using namespace std;

DefWithInit::DefWithInit(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : Definition()
  , _tipo ( tipo )
  , _ids  ( ids  )
  , _expr ( expr )
{}

std::string DefWithInit::to_string()
{
  std::string str = "tipo: " + _tipo->to_string() + " inicializaciones:\n";
  for (unsigned int i=0; i < _ids->size(); ++i) {
    str += "nombre: " + _ids->at(i) + " Valor: " + _expr->at(i)->to_string() + "\n";
  }
  return str;
}

ConstDef::ConstDef(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : DefWithInit(tipo, ids, expr)
  {}

DefVar::DefVar(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr)
  : DefWithInit(tipo, ids, expr)
  {}

DefVarNoInit::DefVarNoInit(Type* tipo, std::vector<std::string>* ids)
  : _tipo( tipo )
  , _ids( ids )
  {}

std::string DefVarNoInit::to_string()
{
  std::string str = "tipo: " + _tipo->to_string() + " Variables sin incializacion :\n";
  for (unsigned int i=0; i < _ids->size(); ++i) {
    str += "nombre: " + _ids->at(i) + "\n";
  }
  return str;
}

DefArray::DefArray(Type* tipo, std::string id, std::vector<std::string>* dimensiones)
  : _tipo( tipo )
  , _id( id )
  , _dimensiones( dimensiones )
  {}

std::string DefArray::to_string()
{
  std::string str =  "Definicion de cueva : \n Tipo : " + _tipo->to_string() + "\n Dimensiones : ";
 for (unsigned int i=0; i < _dimensiones->size(); ++i) {
    str += _dimensiones->at(i) + " ";
  }
  return str;
}

DecFunction::DecFunction ( std::string         name
                         , std::vector<Parameter*>* parametros
                         , Type*               tipoRetorno
                         )
  : Definition  ()
  , _name       ( name        )
  , _parametros ( parametros  )
  , _tipoRetorno( tipoRetorno )
  {}

std::string DecFunction::to_string()
{
  std::string str =  "Nodo Funcion\nNombre de la funcion " + _name + "\nParametros : ";

  for (unsigned int i=0; i<_parametros->size(); ++i)
    str += _parametros->at(i)->to_string() + " ";

  str = str + '\n' + _tipoRetorno->to_string();
  return str;
}

Parameter::Parameter ( std::string id
                     , Type* tipo
                     , bool ref
                     )
  : Definition()
  , _id       ( id    )
  , _tipo     ( tipo  )
  , _ref      ( ref   )
  {}

std::string Parameter::to_string()
{
  return "Parametro:\n Nombre " + _id + "\n Tipo: " + _tipo->to_string() + "Por Referencia: " + std::to_string( _ref );
}

std::string Parameter::get_id()   { return _id;   }
Type*       Parameter::get_tipo() { return _tipo; }
bool        Parameter::get_ref()  { return _ref;  }

#endif
