#ifndef STATEMENT_HH
#define STATEMENT_HH
#include <string>
#include <vector>
#include "expresion.hh"
#include "node.hh"
#include "definition.hh"

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

class Body : public Node
{
  public:
    Body(std::vector<Definition *>* listDef, std::vector<Statement *>* listSta);
    std::string to_string();

  private:
    std::vector<Definition *> * _listDef;
    std::vector<Statement *>  * _listSta;
};

class ComplexFor : Statement
{
  public:
    ComplexFor(std::string id, Expression* begin, Expression* end, Expression* step, Body* body);
    std::string to_string();

  private:
    std::string _id;
    Expression* _begin;
    Expression* _end;
    Expression* _step;
    Body*       _body;
};

class SimpleFor : Statement
{
  public:
    SimpleFor(std::string id, Expression* begin, Expression* end, Body* body);
    std::string to_string();

  private:
    std::string _id;
    Expression* _begin;
    Expression* _end;
    Body*       _body;
};

class IdFor : Statement
{
  public:
    IdFor(std::string id, std::string iterVar, Body* body);
    std::string to_string();

  private:
    std::string _id;
    std::string _iterVar;
    Body*       _body;
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
    While(Expression* expr, Body* body);
    std::string to_string();

  private:
    Expression* _expr;
    Body*       _body;
};

class TagWhile : public Statement
{
  public:
    TagWhile(Expression* expr, Body* body, std::string id);
    std::string to_string();

  private:
    Expression* _expr;
    Body*       _body;
    std::string _id;
};
#endif
