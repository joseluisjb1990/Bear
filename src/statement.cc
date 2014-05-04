#ifndef STATEMENT_CC
#define STATEMENT_CC
#include "statement.hh"
#include <iostream>
#include "type.hh"

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

Function::Function(std::string name, std::vector<Expression*>* parameters)
  : Statement()
  , _name       ( name       )
  , _parameters ( parameters )
  {}

std::string Function::to_string()
{
  std::string str = "Nombre: " + _name + ", Parametros: ";
  for (unsigned int i=0; i < _parameters->size(); ++i)
    str += _parameters->at(i)->to_string();
  return str;
}

If::If(Expression* condicion, Statement* instrucciones)
  : Statement()
  , _condicion     ( condicion     )
  , _instrucciones ( instrucciones )
  {}

std::string If::to_string()
{
  return "if " + _condicion->to_string() + "then: " + _instrucciones->to_string() + '\n';
}

IfElse::IfElse(Expression* condicion, Statement* brazoTrue, Statement* brazoFalse)
  : Statement()
  , _condicion  ( condicion  )
  , _brazoTrue  ( brazoTrue  )
  , _brazoFalse ( brazoFalse )
  {}

std::string IfElse::to_string()
{
  return "if " + _condicion->to_string() + "then: " + _brazoTrue->to_string() + '\n' + "else:" + _brazoFalse->to_string() ;
}

void IfElse::check()
{
  _condicion->check();
  Type* t = _condicion->get_type();

  if (t != PandaType::getInstance() and t != ErrorType::getInstance()) {
    error("Condicion must be a panda type, instead of '" + t->to_string() + "'");
  }

  _brazoTrue->check();
  _brazoFalse->check();

  if (_brazoTrue->get_type() == ErrorType::getInstance() or _brazoFalse->get_type() == ErrorType::getInstance()) {
    this->set_type(ErrorType::getInstance());
  } else {
    this->set_type(ExtintoType::getInstance());
  }

}


Write::Write(Expression* expr)
  : Statement()
  , _expr( expr )
  {}

std::string Write::to_string()
{
  return "Escribir : " + _expr->to_string();
}

Read::Read(Expression* id)
  : Statement()
  , _id( id )
  {}

std::string Read::to_string()
{
  return "Read : " + _id->to_string() + '\n';
}

void Read::check()
{
  _id->check();

  Type* t = _id->get_type();

  if (t == HormigueroType::getInstance() or
      dynamic_cast<CuevaType*>(t) or
      dynamic_cast<PardoType*>(t) or
      dynamic_cast<GrizzliType*>(t)) {
    error("Cannot read a variable of type '" + t->to_string() + "'");
  }

  this->set_type(ExtintoType::getInstance());
}

Body::Body( std::vector<Statement *>* listSta )
  : _listSta( listSta )
  {}

std::string Body::to_string()
{

  std::string str = "Lista de Instrucciones: \n";
  for (unsigned int i=0; i < _listSta->size(); ++i) {
    str += _listSta->at(i)->to_string() + '\n';
  }
  return str;
}

void Body::check()
{
  if (_listSta)
    for(std::vector<Statement*>::iterator it = _listSta->begin(); it != _listSta->end(); it++)
      (*it)->check();
}

ComplexFor::ComplexFor(std::string id, Expression* begin, Expression* end, Expression* step, Statement* body)
  : Statement()
  , _id( id )
  , _begin( begin )
  , _end( end )
  , _step( step )
  , _body( body )
  {}

std::string ComplexFor::to_string()
{
  return  std::string("Iteracion Acotada con salto :\n")
        + "Variable de iteracion :"           + _id                 + '\n'
        + "Expresion de Inicio :"             + _begin->to_string() + '\n'
        + "Expresion Final :"                 + _end->to_string()   + '\n'
        + "Paso :"                            + _step->to_string()  + '\n'
        + "Cuerpo :"                          + _body->to_string()  + '\n'
        ;
}

void ComplexFor::check()
{
  _begin->check();
  Type* tbegin = _begin->get_type();

  if (tbegin != PolarType::getInstance() or tbegin != ErrorType::getInstance()) {
    error("Lower bound of the para must be of type 'polar' instead of '" + tbegin->to_string() + "'");
  }

  _end->check();
  Type* tend = _end->get_type();

  if (tend != PolarType::getInstance() or tend != ErrorType::getInstance()) {
    error("Lower bound of the para must be of type 'polar' instead of '" + tend->to_string() + "'");
  }

  _step->check();
  Type* tstep = _step->get_type();

  if (tstep != PolarType::getInstance() or tstep != ErrorType::getInstance()) {
    error("Lower bound of the para must be of type 'polar' instead of '" + tstep->to_string() + "'");
  }

  _body->check();
  Type* tbody = _body->get_type();

  if (tbegin == ErrorType::getInstance() or
      tend == ErrorType::getInstance() or
      tstep == ErrorType::getInstance() or
      tbody == ErrorType::getInstance()) {
    this->set_type(ErrorType::getInstance());
  } else {
    this->set_type(ExtintoType::getInstance());
  }
}

SimpleFor::SimpleFor(std::string id, Expression* begin, Expression* end, Statement* body)
  : Statement()
  , _id( id )
  , _begin( begin )
  , _end( end )
  , _body( body )
  {}

std::string SimpleFor::to_string()
{
  return  std::string("Iteracion Acotada simple :\n")
        + "Variable de iteracion :"           + _id                 + '\n'
        + "Expresion de Inicio :"             + _begin->to_string() + '\n'
        + "Expresion Final :"                 + _end->to_string()   + '\n'
        + "Cuerpo :"                          + _body->to_string()  + '\n'
        ;
}

IdFor::IdFor(std::string id, std::string iterVar, Statement* body)
  : Statement()
  , _id( id )
  , _iterVar( iterVar )
  , _body( body )
  {}

std::string IdFor::to_string()
{
  return  std::string("Iteracion Acotada simple :\n")
        + "Variable de iteracion :"           + _id                 + '\n'
        + "Cueva de Iteracion :"              + _iterVar            + '\n'
        + "Cuerpo :"                          + _body->to_string()  + '\n'
        ;
}

void IdFor::check()
{
  // AQUI FALTA QUE PASA SI LA VARIABLE A ITERAR NO ES UNA CUEVA, PARA ESO NECESITO LA TABLA.
  _body->check();
  Type* t = _body->get_type();

  if (t == ErrorType::getInstance()) {
    this->set_type(ErrorType::getInstance());
  } else {
    this->set_type(ExtintoType::getInstance());
  }
}

Return::Return()
  : Statement()
  {}

std::string Return::to_string()
{
  return "Nodo Vomita sin etiqueta";
}

ReturnExpr::ReturnExpr(Expression* expr)
  : Statement()
  , _expr( expr )
  {}

std::string ReturnExpr::to_string()
{
  return "Nodo Vomita la expresion " + _expr->to_string() + '\n';
}

void ReturnExpr::check()
{
  _expr->check();
  Type* t = _expr->get_type();

  if (t == ErrorType::getInstance()) {
    this->set_type(ErrorType::getInstance());
  } else {
    this->set_type(ExtintoType::getInstance());
  }
}

Increase::Increase(std::string id)
  : Statement()
  , _id( id )
  {}

std::string Increase::to_string()
{
  return "Nodo incremento a la variable " + _id + '\n';
}

void Increase::check()
{
  Type* type = get_type();
  if(type != PolarType::getInstance())
  {
    error("attempt to increase a variable which is not of type POLAR");
    set_type(ErrorType::getInstance());
  }
}

Decrement::Decrement(std::string id)
  : Statement()
  , _id( id )
  {}

std::string Decrement::to_string()
{
  return "Nodo decremento a la variable " + _id + '\n';
}

Continue::Continue()
  : Statement()
  {}

std::string Continue::to_string()
{
  return "Nodo fondoBlanco sin etiqueta";
}

ContinueID::ContinueID(std::string id)
  : Statement()
  , _id( id )
  {}

std::string ContinueID::to_string()
{
  return "Nodo fondoBlanco a la etiqueta " + _id + '\n';
}

Break::Break()
  : Statement()
  {}

std::string Break::to_string()
{
  return "Nodo roloePea sin etiqueta";
}

BreakID::BreakID(std::string id)
  : Statement()
  , _id( id )
  {}

std::string BreakID::to_string()
{
  return "Nodo roloePea a la etiqueta " + _id + '\n';
}

While::While(Expression* expr, Statement* body)
  : _expr( expr )
  , _body( body )
  {}

std::string While::to_string()
{
  return  "Iteracion Indeterminada\nCondicion :"
        + _expr->to_string()
        + "Bloque\n"
        + _body->to_string()
        ;
}

void While::check()
{
  _expr->check();
  Type* texp = _expr->get_type();

  if (texp != PandaType::getInstance() or texp != ErrorType::getInstance()) {
    error("Condition for 'mientras' must be a 'panda' type instead of '" + texp->to_string() + "'");
  }

  _body->check();
  Type* tbody = _body->get_type();

  if (texp == ErrorType::getInstance() or tbody == ErrorType::getInstance()) {
    this->set_type(ErrorType::getInstance());
  } else {
    this->set_type(ExtintoType::getInstance());
  }
}

TagWhile::TagWhile(std::string id, Expression* expr, Statement* body)
  : _id   ( id )
  , _expr ( expr )
  , _body ( body )
  {}

std::string TagWhile::to_string()
{
  return  std::string("Iteracion Indeterminada con Etiqueta\n")
        + "Condicion" + _expr->to_string()
        + "Cuerpo "   + _body->to_string()
        + "Etiqueta " + _id
        ;
}


Empty::Empty()
  : Statement()
  {}

Empty::Empty(Type* type)
  : Statement( ErrorType::getInstance() )
  {}

std::string Empty::to_string()
{
  return "vacia";
}

#endif
