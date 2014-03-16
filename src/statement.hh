#ifndef STATEMENT_HH
#define STATEMENT_HH
#include <string>
#include <vector>
#include "expresion.hh"

using namespace std;

class Statement
{
public :

    Statement(){};
    virtual std::string to_string(){ return "INSTRUCCIÓN:"; };
};

class Assign : public Statement
{
  private:
    std::vector<Expression*>* _ids;
    std::vector<Expression*>*  _expr;

  public:
    Assign(std::vector<Expression*>* ids, std::vector<Expression*>* expr);
    std::string to_string();

};

class If : public Statement
{
  public:
    If(Expression* condicion, std::vector<Statement*>* instrucciones);
    std::string to_string();

  private:
    Expression* _condicion;
    std::vector<Statement*>* _instrucciones;

};

class IfElse : public Statement
{
  public:
    IfElse(Expression* condicion, std::vector<Statement*>* brazoTrue, std::vector<Statement*>* brazoFalse);
    std::string to_string();

  private:
    Expression* _condicion;
    std::vector<Statement*>* _brazoTrue;
    std::vector<Statement*>* _brazoFalse;

};
#endif
