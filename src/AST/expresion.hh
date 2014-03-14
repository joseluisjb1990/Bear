#include <string>

using namespace std;

class Expresion
{
public :

    Expresion(){};
    virtual std::string to_string(){ return "EXPRESION BASE"; };
};

class ExprBinaria : public Expresion
{
private:

  std::string _operador;
  Expresion *_izq;
  Expresion *_der;

public:

  ExprBinaria(std::string operador, Expresion *izq, Expresion *der);
  std::string to_string();
};

class ExprUnaria : public Expresion
{
public:

  ExprUnaria(std::string operador, Expresion *operando);
  std::string to_string();

private:
  std::string _operador;
  Expresion *_operando;
};

class ExprConstante : public Expresion
{
public:

  ExprConstante(std::string tipo, std::string valor);
  std::string to_string();

private:

  std::string _tipo;
  std::string _valor;
};
