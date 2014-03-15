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
