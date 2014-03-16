#ifndef EXPRESSION_CC
#define EXPRESSION_CC
#include "expresion.hh"

using namespace std;

ExprBinaria::ExprBinaria(std::string operador, Expression *izq, Expression *der)
  : Expression()
  , _operador( operador )
  , _izq( izq )
  , _der( der )
  {}

std::string ExprBinaria::to_string()
{
  return _operador + " expr izquierda " + _izq->to_string() + " expr derecha " + _der->to_string() + '\n';
}

ExprUnaria::ExprUnaria(std::string operador, Expression *operando)
  : Expression()
  , _operador( operador )
  , _operando( operando )
  {}

std::string ExprUnaria::to_string()
{
  return _operador + " operando " + _operando->to_string() + '\n';
}

ExprConstante::ExprConstante(std::string tipo, std::string valor)
  : Expression()
  , _tipo( tipo )
  , _valor( valor )
  {}

std::string ExprConstante::to_string()
{
  return "Tipo: " + _tipo + "Valor: " + _valor + '\n';
}

ExprSelector::ExprSelector(Expression* condicion, Expression* brazoTrue, Expression* brazoFalse)
  : Expression()
  , _condicion( condicion )
  , _brazoTrue( brazoTrue )
  , _brazoFalse( brazoFalse )
  {}

std::string ExprSelector::to_string()
{
  return _condicion->to_string() + " ? " + _brazoTrue->to_string() + " : " + _brazoFalse->to_string() + "\n";
}

ExprID::ExprID(std::string nombre)
  : ExprLValue()
  , _nombre( nombre )
  {}

std::string ExprID::to_string()
{
  return "Nombre del ID: " + _nombre;
}

ExprPardo::ExprPardo(ExprLValue* izquierda, ExprLValue* derecha)
  : ExprLValue()
  , _izquierda( izquierda )
  , _derecha  ( derecha   )
  {}

std::string ExprPardo::to_string()
{
  return "Acceso a pardo: Izquierda: " + _izquierda->to_string() + " Derecha: " + _derecha->to_string() + "\n";
}

ExprGrizzli::ExprGrizzli(ExprLValue* izquierda, ExprLValue* derecha)
  : ExprLValue()
  , _izquierda( izquierda )
  , _derecha  ( derecha   )
  {}

std::string ExprGrizzli::to_string()
{
  return "Acceso a grizzli: Izquierda: " + _izquierda->to_string() + " Derecha: " + _derecha->to_string() + "\n";
}

ExprCueva::ExprCueva(std::string nombre, Expression* dimension)
  : ExprLValue()
  , _nombre       ( nombre )
  {
    _dimensions = new std::vector<Expression*>();
    _dimensions->push_back(dimension);
  }

std::string ExprCueva::to_string()
{
  std::string str = "Acceso a cueva: Nombre: " + _nombre + " Dimensiones: ";
  for (unsigned int i=0; i < _dimensions->size(); ++i) {
    str +="[" + _dimensions->at(i)->to_string() + "]";
  }
  return str;
}

void ExprCueva::addDimension(Expression* dimension)
{
  _dimensions->push_back(dimension);
}
#endif
