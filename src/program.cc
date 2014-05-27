#ifndef PROGRAM_CC
#define PROGRAM_CC

#include "program.hh"

Program::Program(std::vector<Definition*>* definitions, Definition* statement)
  : Node()
  , _definitions( definitions )
  , _statement  ( statement   )
{}

std::string Program::to_string(int nesting)
{
  cout << "PROGRAM \n";

  if(_definitions)
    for(std::vector<Definition*>::iterator it = _definitions->begin(); it != _definitions->end(); ++it)
      cout << (*it)->to_string(nesting+1);

  cout << _statement->to_string(nesting+1);

  return "";
}

void Program::check()
{
  if(_definitions) {
    for(std::vector<Definition*>::iterator it = _definitions->begin(); it != _definitions->end(); ++it)
      (*it)->check();
  }

  if(_statement) _statement->check();
}
#endif
