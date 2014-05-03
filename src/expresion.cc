#ifndef EXPRESSION_CC
#define EXPRESSION_CC
#include "expresion.hh"

using namespace std;

Expression::Expression() {}

std::string Expression::to_string()
{
  return "";
}

PolarExpr::PolarExpr(std::string valor)
  : valor ( valor )
  {}

std::string PolarExpr::to_string()
{
  return "Constante polar, valor: " + getValue();
}

std::string PolarExpr::getValue()
{
  return valor;
}

KodiakExpr::KodiakExpr(std::string valor)
  : valor ( valor )
  {}

std::string KodiakExpr::to_string()
{
  return "Constante kodiak, valor: " + getValue();
}

std::string KodiakExpr::getValue()
{
  return valor;
}

HormigueroExpr::HormigueroExpr(std::string valor)
  : valor ( valor )
  {}

std::string HormigueroExpr::to_string()
{
  return "Constante hormiguero, valor: " + getValue();
}

std::string HormigueroExpr::getValue()
{
  return valor;
}

MalayoExpr::MalayoExpr(std::string valor)
  : valor ( valor )
  {}

std::string MalayoExpr::to_string()
{
  return "Constante malayo, valor: " + getValue();
}

std::string MalayoExpr::getValue()
{
  return valor;
}

PandaExpr::PandaExpr(std::string valor)
  : valor ( valor )
  {}

std::string PandaExpr::to_string()
{
  return "Constante panda, valor: " + getValue();
}

std::string PandaExpr::getValue()
{
  return valor;
}

Sum::Sum(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Sum::to_string()
{
  return "Operación: Suma.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Sum::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance()) ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator + between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Substraction::Substraction(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Substraction::to_string()
{
  return "Operación: Resta.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Substraction::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance()) ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator - between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Multiplication::Multiplication(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Multiplication::to_string()
{
  return "Operación: Multiplicación.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Multiplication::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance()) ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator * between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Division::Division(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Division::to_string()
{
  return "Operación: División.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Division::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance()) ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator / between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Remainder::Remainder(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Remainder::to_string()
{
  return "Operación: Módulo.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Remainder::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance()) ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator % between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Power::Power(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Power::to_string()
{
  return "Operación: Potenciación.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Power::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance()) ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator ** between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Minus::Minus(Expression* operando)
  : operando ( operando )
  {}

std::string Minus::to_string()
{
  return "Operación: Menos.\nOperando: " + operando->to_string();
}

void Minus::check()
{
  operando->check();
  Type* t = operando->get_type();

  if ( t == PolarType::getInstance() or t == KodiakType::getInstance() or t == ErrorType::getInstance() ) {
    this->set_type(t);
  } else {
    error("Cannot apply operator - to " + t->to_string() + " types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

Less::Less(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Less::to_string()
{
  return "Operación: Menor que.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Less::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance() or t1 == MalayoType::getInstance()) ) {
    this->set_type(PandaType::getInstance());
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator < between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}

LessEqual::LessEqual(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string LessEqual::to_string()
{
  return "Operación: Menor igual que.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void LessEqual::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance() or t1 == MalayoType::getInstance()) ) {
    this->set_type(PandaType::getInstance());
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator =< between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


Greater::Greater(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Greater::to_string()
{
  return "Operación: Mayor que.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Greater::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance() or t1 == MalayoType::getInstance()) ) {
    this->set_type(PandaType::getInstance());
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator > between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


GreaterEqual::GreaterEqual(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string GreaterEqual::to_string()
{
  return "Operación: Mayor igual que.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void GreaterEqual::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance() or t1 == MalayoType::getInstance()) ) {
    this->set_type(PandaType::getInstance());
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator >= between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


Equal::Equal(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Equal::to_string()
{
  return "Operación: Igualdad.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Equal::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance() or t1 == MalayoType::getInstance()) ) {
    this->set_type(PandaType::getInstance());
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator == between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


NotEqual::NotEqual(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string NotEqual::to_string()
{
  return "Operación: Desigualdad.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void NotEqual::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and (t1 == PolarType::getInstance() or t1 == KodiakType::getInstance() or t1 == MalayoType::getInstance()) ) {
    this->set_type(PandaType::getInstance());
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator =/= between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


And::And(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string And::to_string()
{
  return "Operación: And.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void And::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and t1 == PandaType::getInstance() ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator & between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


Or::Or(Expression* izq, Expression* der)
  : izq ( izq )
  , der ( der )
  {}

std::string Or::to_string()
{
  return "Operación: Or.\nOperando izquierdo: " + izq->to_string() + "\nOperando derecho: " + der->to_string() + "\n";
}

void Or::check()
{
  izq->check();
  der->check();
  Type* t1 = izq->get_type();
  Type* t2 = der->get_type();

  if ( t1 == t2 and t1 == PandaType::getInstance() ) {
    this->set_type(t1);
  } else if ( t1 == ErrorType::getInstance() or t2 == ErrorType::getInstance() ) {
    this->set_type(ErrorType::getInstance());
  } else {
    error("Cannot apply operator | between " + t1->to_string() + " and " + t2->to_string() + "types.\n");
    this->set_type(ErrorType::getInstance());
  }
}


Not::Not(Expression* operando)
  : operando ( operando )
  {}

std::string Not::to_string()
{
  return "Operación: Not.\nOperando: " + operando->to_string();
}

void Not::check()
{
  operando->check();
  Type* t = operando->get_type();

  if ( t == PandaType::getInstance() ) {
    this->set_type(t);
  } else {
    error("Cannot apply operator not to " + t->to_string() + " types.\n");
    this->set_type(ErrorType::getInstance());
  }
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
