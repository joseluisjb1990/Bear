#ifndef DEFINITION_HH
#define DEFINITION_HH
#include <string>
#include <vector>
#include "expresion.hh"

using namespace std;

class Definition
{
public :

    Definition(){};
    virtual std::string to_string(){ return "DEFINICIÓN:"; };
};

class ConstDef : public Definition
{
  public:
    ConstDef(std::string tipo, std::vector<std::string>* ids, std::vector<Expression*>* expr);
    std::string to_string();

  private:
    std::string _tipo;
    std::vector<std::string>*_ids;
    std::vector<Expression*>*_expr;

};
#endif
