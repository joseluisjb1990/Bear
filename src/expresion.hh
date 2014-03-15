#include <string>

using namespace std;

class Expression
{
public :

    Expression(){};
    virtual std::string to_string(){ return "EXPRESION BASE"; };
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
