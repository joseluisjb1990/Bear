#ifndef NODE_HH
#define NODE_HH
#include <string>
#include "TablaSimbolos.hh"
#include "type.hh"
using namespace std;

class Type;

class Node
{
public:
  Node()
    : _type     ( nullptr )
    , _filaI    ( 0 )
    , _columnaI ( 0 )
    , _filaF    ( 0 )
    , _columnaF ( 0 )
    {};
  Node(Type* type) : _type( type ) {}
  Type* get_type() { return _type; }
  void set_type(Type* type) { _type = type; }
  virtual std::string to_string() = 0;
  void set_table(TablaSimbolos* table) { _table = table; }
  TablaSimbolos* get_table() { return _table; }
  virtual bool check_type() { return true; }
  void set_location(unsigned int filaI, unsigned int columnaI, unsigned int filaF, unsigned int columnaF) { _filaI = filaI; _columnaI = columnaI; _filaF = filaF; _columnaF = columnaF; }
  unsigned int get_first_line()   { return _filaI;    }
  unsigned int get_first_column() { return _columnaI; }
  unsigned int get_last_line()    { return _filaF;    }
  unsigned int get_last_column()  { return _columnaF; }
  void error(std::string msg) { cout << "Error between " << get_first_line() << "." << get_first_column() << " and " << get_last_line() << "." << get_last_column() << msg; }

private:
  Type* _type;
  TablaSimbolos* _table;
  unsigned int   _filaI;
  unsigned int   _columnaI;
  unsigned int   _filaF;
  unsigned int   _columnaF;

};
#endif
