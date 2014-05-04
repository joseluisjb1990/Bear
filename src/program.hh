#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "statement.hh"
#include "definition.hh"
class Program : public Node
{
  public:
    Program(std::vector<Definition*>* definitions, Statement* statement);
    Program() {};
    std::string to_string();
    void check();
    static TablaSimbolos* get_table()
    {
      if(!_table)
        _table = new TablaSimbolos();

      return _table;
    }
  private:
    static TablaSimbolos* _table;
    std::vector<Definition*>* _definitions;
    Statement* _statement;
};
#endif
