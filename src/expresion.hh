#ifndef EXPRESSION_HH
#define EXPRESSION_HH
#include <string>
#include <vector>

using namespace std;

class Expression
{
public :

    Expression(){};
    virtual std::string to_string(){ return "EXPRESIÓN BASE"; };
};

class BinaryExpr : public Expression
{
private:

  std::string _operador;
  Expression *_izq;
  Expression *_der;

public:

  BinaryExpr(std::string operador, Expression *izq, Expression *der);
  std::string to_string();
};

class UnaryExpr : public Expression
{
public:

  UnaryExpr(std::string operador, Expression *operando);
  std::string to_string();

private:
  std::string _operador;
  Expression *_operando;
};

class ConstantExpr : public Expression
{
public:

  ConstantExpr(std::string tipo, std::string valor);
  std::string to_string();

private:

  std::string _tipo;
  std::string _valor;
};

class SelectorExpr : public Expression
{
public:

  SelectorExpr(Expression* condicion, Expression* brazoTrue, Expression* brazoFalse);
  std::string to_string();

private:

  Expression *_condicion;
  Expression *_brazoTrue;
  Expression *_brazoFalse;

};

class LValueExpr : public Expression
{
  public:
    LValueExpr(){};
};

class IDExpr : public LValueExpr
{
  public:
    IDExpr(std::string nombre);
    std::string to_string();

  private:
    std::string _nombre;

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
    CuevaExpr(std::string nombre, Expression* dimension);
    std::string to_string();
    void addDimension(Expression* dimension);

  private:
    std::string               _nombre;
    std::vector<Expression*>* _dimensions;

};
#endif
