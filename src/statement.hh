#ifndef STATEMENT_HH
#define STATEMENT_HH
#include <string>
#include <vector>
#include "expresion.hh"
#include "node.hh"

using namespace std;

class Statement : public Node
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

class Function : public Statement
{
  public:
    Function(std::string name, std::vector<Expression*>* parameters);
    std::string to_string();

  private:
    std::string               _name;
    std::vector<Expression*>* _parameters;
};

class If : public Statement
{
  public:
    If(Expression* condicion, Statement* instrucciones);
    std::string to_string();

  private:
    Expression* _condicion;
    Statement* _instrucciones;

};

class IfElse : public Statement
{
  public:
    IfElse(Expression* condicion, Statement* brazoTrue, Statement* brazoFalse);
    std::string to_string();

  private:
    Expression* _condicion;
    Statement* _brazoTrue;
    Statement* _brazoFalse;

};

class Write : public Statement
{
  public:
    Write(Expression* expr);
    std::string to_string();

  private:
    Expression* _expr;

};

class Read : public Statement
{
  public:
    Read(std::string id);
    std::string to_string();

  private:
    std::string _id;

};

class Body : public Statement
{
  public:
    Body( std::vector<Statement *>* listSta );
    std::string to_string();

  private:
    std::vector<Statement *>  * _listSta;
};

class ComplexFor : public Statement
{
  public:
    ComplexFor(std::string id, Expression* begin, Expression* end, Expression* step, Statement* body);
    std::string to_string();

  private:
    std::string _id;
    Expression* _begin;
    Expression* _end;
    Expression* _step;
    Statement*  _body;
};

class SimpleFor : public Statement
{
  public:
    SimpleFor(std::string id, Expression* begin, Expression* end, Statement* body);
    std::string to_string();

  private:
    std::string _id;
    Expression* _begin;
    Expression* _end;
    Statement*       _body;
};

class IdFor : public Statement
{
  public:
    IdFor(std::string id, std::string iterVar, Statement* body);
    std::string to_string();

  private:
    std::string _id;
    std::string _iterVar;
    Statement*       _body;
};

class Return : public Statement
{
  public:
    Return();
    std::string to_string();
};

class ReturnID : public Statement
{
  public:
    ReturnID(std::string id);
    std::string to_string();

  private:
    std::string _id;

};

class Increase : public Statement
{
  public:
    Increase(std::string id);
    std::string to_string();

  private:
    std::string _id;
};

class Decrement : public Statement
{
  public:
    Decrement(std::string id);
    std::string to_string();

  private:
    std::string _id;
};

class Continue : public Statement
{
  public:
    Continue();
    std::string to_string();
};

class ContinueID : public Statement
{
  public:
    ContinueID(std::string id);
    std::string to_string();

  private:
    std::string _id;
};

class Break : public Statement
{
  public:
    Break();
    std::string to_string();
};

class BreakID : public Statement
{
  public:
    BreakID(std::string id);
    std::string to_string();

  private:
    std::string _id;
};

class While : public Statement
{
  public:
    While(Expression* expr, Statement* body);
    std::string to_string();

  private:
    Expression* _expr;
    Statement*  _body;
};

class TagWhile : public Statement
{
  public:
    TagWhile(std::string id, Expression* expr, Statement* body);
    std::string to_string();

  private:
    std::string _id;
    Expression* _expr;
    Statement*  _body;
};

class Empty : public Statement
{
  public:
    Empty();
    std::string to_string();
};

#endif
