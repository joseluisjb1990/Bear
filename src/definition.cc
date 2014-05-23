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

void DefWithInit::check()
{
  bool errortype = false;
  for(std::vector<Expression*>::iterator it = _expr->begin(); it != _expr->end(); ++it)
  {
    Expression* exp = *it;
    exp->check();
    if(!_tipo->compareTypes(exp->get_type()))
    {
      errortype = true;
      if (exp->get_type() != ErrorType::getInstance()) {
        error("expression " + exp->to_string() + " is not of type " + _tipo->to_string());
      }
    }
  }

  if(errortype) set_type(ErrorType::getInstance());
  else          set_type(_tipo);
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

void DefVarNoInit::check() { set_type(_tipo); }

DefArray::DefArray(Type* tipo, std::string id)
  : _tipo( tipo )
  , _id( id )
  {}

std::string DefArray::to_string()
{
  return "Definicion de cueva : \n Nombre: " + _id + ", Tipo : " + _tipo->to_string();
}

void DefArray::check() { set_type(_tipo); }

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

void DecFunction::check()
{
  for(std::vector<Parameter*>::iterator it = _parametros->begin(); it != _parametros->end(); ++it)
    (*it)->check();

  set_type(_tipoRetorno);
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
  std::string str;
  if (_ref) str = "*"; else str = " ";
  str += _id + " " + _tipo->to_string() + " ";
  return str;
}

std::string Parameter::get_id()   { return _id;      }
Type*       Parameter::get_tipo() { return _tipo;    }
bool        Parameter::get_ref()  { return _ref;     }
void        Parameter::check()    { set_type(_tipo); }

bool        Parameter::compareParameters(Parameter* p2)
{
  if (!_tipo->compareTypes(p2->get_tipo()) or !(_id == p2->get_id()))
  {
    error("parameter " + to_string() + " in function definition don't match parameter " + p2->to_string() + " in function declaration");
    return false;
  }
  return true;
}

DefFunction::DefFunction ( std::string               id
                         , std::vector<Parameter*>*  parameters
                         , Type*                     type
                         , Statement*                statements
                         )
  : _id         ( id )
  , _parameters ( parameters )
  , _type       ( type )
  , _statements ( statements )
  {}

std::string DefFunction::to_string()
{
  return "Defincion de funcion\nNombre: " + _id + "\nParametros: " + "CICLO DE LOS PARAMETROS" + "\nTipo: " + _type->to_string() + "\nInstrucciones: " + _statements->to_string();
}

void DefFunction::check()
{
  bool ok = true;

  for(std::vector<Parameter*>::iterator it = _parameters->begin(); it != _parameters->end(); it++)
  {
    (*it)->check();
    if((*it)->get_type() == ErrorType::getInstance()) ok = false;
  }

  _statements->check();
  _statements->checkReturn(_type);

  if(!_statements->getReturn())
  {
    if(ExtintoType::getInstance() != _type)
    {
      error("function does not contain any explicit return statement");
      ok = false;
    } else
    {
      ok = ok and true;
    }
  }

  if(_statements->get_type() == ErrorType::getInstance() or !ok)
    set_type(ErrorType::getInstance());
  else
    set_type(_type);
}
#endif
