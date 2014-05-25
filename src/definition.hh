#ifndef DEFINITION_HH
#define DEFINITION_HH
#include <string>
#include <vector>
#include "expresion.hh"
#include "statement.hh"
#include "type.hh"

class Expression;

using namespace std;

class Definition : public Statement
{
public :

    Definition(){};
    virtual std::string to_string(){ return "DEFINICIÓN:"; };
};

class EmptyDef : public Definition
{
  public:
    EmptyDef(){};
    std::string to_string() { return "Empty definition"; };

};

class DefWithInit : public Definition
{
  public:
    DefWithInit(Type* tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr);
    std::string to_string();
    void check();

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
    void check();

  private:
    Type* _tipo;
    std::vector<std::string>*_ids;

};

class DefArray : public Definition
{
  public:
    DefArray(Type* tipo, std::string id);
    std::string to_string();
    void check();

  private:
    Type* _tipo;
    std::string _id;
};

class Parameter : public Definition
{
  public:
    Parameter ( std::string id
              , Type* tipo
              , bool ref
              );
    Parameter(){};
    bool compareTypes(Type* tipo);

    std::string to_string();
    std::string get_id();
    Type*       get_tipo();
    bool        get_ref();
    void        check();
    bool        compareParameters(Parameter* p2);

  private:
    std::string _id;
    Type*       _tipo;
    bool        _ref;
};

class EmptyParam : public Parameter
{
  public:
    EmptyParam(){};
    std::string to_string() { return "No parameters"; };
    void check() { set_type(ExtintoType::getInstance()); }

};

class DecFunction : public Definition
{
  private:
    std::string                _name;
    std::vector<Parameter*>*   _parametros;
    Type*                      _tipoRetorno;

  public:
    DecFunction ( std::string               name
                , std::vector<Parameter*>*  parametros
                , Type*                     tipoRetorno
                );

    std::string to_string();
    void check();

};

class DefFunction : public Definition
{
  public:
    DefFunction( std::string               id
               , std::vector<Parameter*>*  parameters
               , Type*                     type
               , Statement*                statements
               );

    std::string to_string();
    void check();

  private:
    std::string               _id;
    std::vector<Parameter*>*  _parameters;
    Type*                     _type;
    Statement*                _statements;
};
#endif
