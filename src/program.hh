#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "statement.hh"
#include "definition.hh"
class Program : public Node
{
  public:
    Program(std::vector<Definition*>* definitions, Definition* statement);
    Program() {};
    std::string to_string();
    void check();
  private:
    std::vector<Definition*>* _definitions;
    Definition* _statement;
};
#endif
