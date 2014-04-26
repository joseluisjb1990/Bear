#ifndef NODE_HH
#define NODE_HH
#include <string>

using namespace std;

class Type;

class Node
{
public:
  Node() {}
  Node(Type* type) : _type( type ) {}
  Type* get_type() { return _type; }
  virtual std::string to_string() = 0;

private:
  Type* _type;
};
#endif
