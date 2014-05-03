#ifndef EXPRESSION_HH
#define EXPRESSION_HH
#include <string>
#include <vector>
#include <iostream>
#include "type.hh"
#include "node.hh"

using namespace std;

class Expression : public Node
{
  public :

    Expression();
    virtual void check() {};
    virtual std::string to_string();
};

class Constant : public Expression
{};

class PolarExpr : public Constant
{
  private :
    std::string valor;

  public :
    PolarExpr(std::string valor);
    std::string to_string();
    std::string getValue();

};

class KodiakExpr : public Constant
{
  private :
    std::string valor;

  public :
    KodiakExpr(std::string valor);
    std::string to_string();
    std::string getValue();

};

class HormigueroExpr : public Constant
{
  private :
    std::string valor;

  public :
    HormigueroExpr(std::string valor);
    std::string to_string();
    std::string getValue();

};

class MalayoExpr : public Constant
{
  private :
    std::string valor;

  public :
    MalayoExpr(std::string valor);
    std::string to_string();
    std::string getValue();

};

class PandaExpr : public Constant
{
  private :
    std::string valor;

  public :
    PandaExpr(std::string valor);
    std::string to_string();
    std::string getValue();

};

class Sum : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Sum(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Substraction : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Substraction(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Multiplication : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Multiplication(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Division : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Division(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Remainder : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Remainder(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Power : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Power(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Minus : public Expression
{
  private :
    Expression* operando;

  public :
    Minus(Expression* operando);
    std::string to_string();
    void check();

};

class Less : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Less(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class LessEqual : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    LessEqual(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Greater : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Greater(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class GreaterEqual : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    GreaterEqual(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Equal : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Equal(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class NotEqual : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    NotEqual(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class And : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    And(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Or : public Expression
{
  private :
    Expression* izq;
    Expression* der;

  public :
    Or(Expression* izq, Expression* der);
    std::string to_string();
    void check();

};

class Not : public Expression
{
  private :
    Expression* operando;

  public :
    Not(Expression* operando);
    std::string to_string();
    void check();

};

class SelectorExpr : public Expression
{
  private:
    Expression *_condicion;
    Expression *_brazoTrue;
    Expression *_brazoFalse;

  public:
    SelectorExpr(Expression* condicion, Expression* brazoTrue, Expression* brazoFalse);
    std::string to_string();

};

class LValueExpr : public Expression
{
  public:
    LValueExpr(){};
};

class EmptyExpr : public LValueExpr
{
  public:
    EmptyExpr(){};
};

class IDExpr : public LValueExpr
{
  private:
    std::string _nombre;

  public:
    IDExpr(std::string nombre);
    std::string to_string();

};

class FunctionExpr : public Expression
{
  public:
    FunctionExpr(std::string name, std::vector<Expression*>* parameters);
    std::string to_string();

  private:
    std::string               _name;
    std::vector<Expression*>* _parameters;
};

class PardoExpr : public LValueExpr
{
  public:
    PardoExpr(LValueExpr* izquierda, LValueExpr* derecha);
    std::string to_string();

  private:
   LValueExpr* _izquierda;
   LValueExpr* _derecha;

};

class GrizzliExpr : public LValueExpr
{
  public:
    GrizzliExpr(LValueExpr* izquierda, LValueExpr* derecha);
    std::string to_string();

  private:
   LValueExpr* _izquierda;
   LValueExpr* _derecha;

};

class CuevaExpr : public LValueExpr
{
  public:
    CuevaExpr(std::string nombre, std::vector<Expression*>* dimensions);
    std::string to_string();
    void addDimension(Expression* dimension);

  private:
    std::string               _nombre;
    std::vector<Expression*>* _dimensions;

};
#endif
