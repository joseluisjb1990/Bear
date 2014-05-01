#ifndef NODE_HH
#define NODE_HH
#include <string>
#include "TablaSimbolos.hh"
using namespace std;

class Type;

class Node
{
public:
  Node() {}
  Node(Type* type) : _type( type ) {}
  Type* get_type() { return _type; }
  virtual std::string to_string() = 0;
  void set_table(TablaSimbolos* table) { _table = table; }
  TablaSimbolos* get_table() { return _table; }

private:
  Type* _type;
  TablaSimbolos* _table;
};
#endif
