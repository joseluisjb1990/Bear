#ifndef DEFINITION_HH
#define DEFINITION_HH
#include <string>
#include <vector>
#include "expresion.hh"
#include "node.hh"
#include "type.hh"

using namespace std;

class Definition : public Node
{
public :

    Definition(){};
    virtual std::string to_string(){ return "DEFINICIÓN:"; };
};

class DefWithInit : public Definition
{
  public:
    DefWithInit(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr);
    std::string to_string();

  private:
    Type* _tipo;
    std::vector<std::string>*_ids;
    std::vector<Expression*>*_expr;

};

class ConstDef : public DefWithInit
{
  public:
    ConstDef(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr);

};

class DefVar : public DefWithInit
{
  public:
    DefVar(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr);

};

class DefVarNoInit : public Definition
{
  public:
    DefVarNoInit(Type* tipo, std::vector<std::string>* ids);
    std::string to_string();

  private:
    Type* _tipo;
    std::vector<std::string>*_ids;

};

class DefCueva : public Definition
{
  public:
    DefCueva(Type* tipo, std::string id, std::vector<std::string>* dimensiones);
    std::string to_string();

  private:
    Type* _tipo;
    std::string _id;
    std::vector<std::string>* _dimensiones;
};

#endif
