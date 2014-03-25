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

Write::Write(Expression* expr)
  : Statement()
  , _expr( expr )
  {}

std::string Write::to_string()
{
  return "Escribir : " + _expr->to_string();
}

Read::Read(std::string id)
  : Statement()
  , _id( id )
  {}

std::string Read::to_string()
{
  return "Read : " + _id + '\n';
}

Body::Body(std::vector<Definition *>* listDef, std::vector<Statement *>* listSta)
  : _listDef( listDef )
  , _listSta( listSta )
  {}

std::string Body::to_string()
{

  std::string str = "Lista de Definiciones:\n ";
  for (unsigned int i=0; i < _listDef->size(); ++i) {
    str += _listDef->at(i)->to_string() + '\n';
  }
  str += "Lista de Instrucciones: \n";
  for (unsigned int i=0; i < _listSta->size(); ++i) {
    str += _listSta->at(i)->to_string() + '\n';
  }
  return str;
}

SimpleBody::SimpleBody( std::vector<Statement *>* listSta )
  : _listSta( listSta )
  {}

std::string SimpleBody::to_string()
{

  std::string str = "Lista de Instrucciones: \n";
  for (unsigned int i=0; i < _listSta->size(); ++i) {
    str += _listSta->at(i)->to_string() + '\n';
  }
  return str;
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

Return::Return()
  : Statement()
  {}

std::string Return::to_string()
{
  return "Nodo Vomita sin etiqueta";
}

ReturnID::ReturnID(std::string id)
  : Statement()
  , _id( id )
  {}

std::string ReturnID::to_string()
{
  return "Nodo Vomita a la etiqueta " + _id + '\n';
}

Increase::Increase(std::string id)
  : Statement()
  , _id( id )
  {}

std::string Increase::to_string()
{
  return "Nodo incremento a la variable " + _id + '\n';
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

std::string Empty::to_string()
{
  return "vacia";
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
#endif
