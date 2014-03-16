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

class ExprBinaria : public Expression
{
private:

  std::string _operador;
  Expression *_izq;
  Expression *_der;

public:

  ExprBinaria(std::string operador, Expression *izq, Expression *der);
  std::string to_string();
};

class ExprUnaria : public Expression
{
public:

  ExprUnaria(std::string operador, Expression *operando);
  std::string to_string();

private:
  std::string _operador;
  Expression *_operando;
};

class ExprConstante : public Expression
{
public:

  ExprConstante(std::string tipo, std::string valor);
  std::string to_string();

private:

  std::string _tipo;
  std::string _valor;
};

class ExprSelector : public Expression
{
public:

  ExprSelector(Expression* condicion, Expression* brazoTrue, Expression* brazoFalse);
  std::string to_string();

private:

  Expression *_condicion;
  Expression *_brazoTrue;
  Expression *_brazoFalse;

};

class ExprLValue : public Expression
{
  public:
    ExprLValue(){};
};

class ExprID : public ExprLValue
{
  public:
    ExprID(std::string nombre);
    std::string to_string();

  private:
    std::string _nombre;

};

class ExprPardo : public ExprLValue
{
  public:
    ExprPardo(ExprLValue* izquierda, ExprLValue* derecha);
    std::string to_string();

  private:
   ExprLValue* _izquierda;
   ExprLValue* _derecha;

};

class ExprGrizzli : public ExprLValue
{
  public:
    ExprGrizzli(ExprLValue* izquierda, ExprLValue* derecha);
    std::string to_string();

  private:
   ExprLValue* _izquierda;
   ExprLValue* _derecha;

};

class ExprCueva : public ExprLValue
{
  public:
    ExprCueva(std::string nombre, Expression* dimension);
    std::string to_string();
    void addDimension(Expression* dimension);

  private:
    std::string               _nombre;
    std::vector<Expression*>* _dimensions;

};
#endif
