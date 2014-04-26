#ifndef EXPRESSION_CC
#define EXPRESSION_CC
#include "expresion.hh"

using namespace std;

BinaryExpr::BinaryExpr(std::string operador, Expression *izq, Expression *der)
  : Expression()
  , _operador( operador )
  , _izq( izq )
  , _der( der )
  {}

std::string BinaryExpr::to_string()
{
  return _operador + " expr izquierda " + _izq->to_string() + " expr derecha " + _der->to_string() + '\n';
}

UnaryExpr::UnaryExpr(std::string operador, Expression *operando)
  : Expression()
  , _operador( operador )
  , _operando( operando )
  {}

std::string UnaryExpr::to_string()
{
  return _operador + " operando " + _operando->to_string() + '\n';
}

ConstantExpr::ConstantExpr(std::string tipo, std::string valor)
  : Expression()
  , _tipo( tipo )
  , _valor( valor )
  {}

std::string ConstantExpr::to_string()
{
  return _valor;
}

SelectorExpr::SelectorExpr(Expression* condicion, Expression* brazoTrue, Expression* brazoFalse)
  : Expression()
  , _condicion( condicion )
  , _brazoTrue( brazoTrue )
  , _brazoFalse( brazoFalse )
  {}

std::string SelectorExpr::to_string()
{
  return _condicion->to_string() + " ? " + _brazoTrue->to_string() + " : " + _brazoFalse->to_string() + "\n";
}

IDExpr::IDExpr(std::string nombre)
  : LValueExpr()
  , _nombre( nombre )
  {}

std::string IDExpr::to_string()
{
  return _nombre;
}

FunctionExpr::FunctionExpr(std::string name, std::vector<Expression*>* parameters)
  : Expression()
  , _name       ( name       )
  , _parameters ( parameters )
  {}

std::string FunctionExpr::to_string()
{
  std::string str = "Nombre: " + _name + ", Parametros: ";
  for (unsigned int i=0; i < _parameters->size(); ++i)
    str += _parameters->at(i)->to_string();
  return str;
}

PardoExpr::PardoExpr(LValueExpr* izquierda, LValueExpr* derecha)
  : LValueExpr()
  , _izquierda( izquierda )
  , _derecha  ( derecha   )
  {}

std::string PardoExpr::to_string()
{
  return "Acceso a pardo: Izquierda: " + _izquierda->to_string() + " Derecha: " + _derecha->to_string() + "\n";
}

GrizzliExpr::GrizzliExpr(LValueExpr* izquierda, LValueExpr* derecha)
  : LValueExpr()
  , _izquierda( izquierda )
  , _derecha  ( derecha   )
  {}

std::string GrizzliExpr::to_string()
{
  return "Acceso a grizzli: Izquierda: " + _izquierda->to_string() + " Derecha: " + _derecha->to_string() + "\n";
}

CuevaExpr::CuevaExpr(std::string nombre, std::vector<Expression*>* dimensions)
  : LValueExpr()
  , _nombre     ( nombre     )
  , _dimensions ( dimensions )
  {}

std::string CuevaExpr::to_string()
{
  std::string str = "Acceso a cueva: Nombre: " + _nombre + " Dimensiones: ";
  for (unsigned int i=0; i < _dimensions->size(); ++i) {
    str +="[" + _dimensions->at(i)->to_string() + "]";
  }
  return str;
}

void CuevaExpr::addDimension(Expression* dimension)
{
  _dimensions->push_back(dimension);
}
#endif
