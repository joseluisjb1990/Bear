#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include "Contenedor.cc"

using namespace std;

typedef std::multimap<std::string, Contenido*> Diccionario;
typedef std::vector<unsigned int> Stack;

class TablaSimbolos
{
private:

    Diccionario _dicc;
    Stack       _pila;
    unsigned int _alcance;

public:

    TablaSimbolos();
    unsigned int add_symbol (string nombre, Tipos tipo, Categorias categoria, unsigned int linea, unsigned int columna);
    unsigned int add_container (string nombre, Tipos tipo, Categorias categoria, unsigned int linea, unsigned int columna, unsigned int alcanceCampos);
    friend inline std::ostream& operator<<(std::ostream& os, TablaSimbolos &ts);
    unsigned int enter_scope();
    unsigned int exit_scope();
    bool check_scope(string nombre);
    Contenido* find_symbol(string nombre);
};

unsigned int TablaSimbolos::add_container (string nombre, Tipos tipo, Categorias categoria, unsigned int linea, unsigned int columna, unsigned int alcanceCampos)
{
  Contenido *cont;
  cont = new  Contenedor(tipo, categoria,_alcance, linea, columna, alcanceCampos);
  _dicc.insert(std::make_pair(nombre,cont)); 
  return _alcance;
}

TablaSimbolos::TablaSimbolos ()
  :_alcance( 0 )
  { _pila.push_back( 0 ); }

Contenido* TablaSimbolos::find_symbol(string nombre)
{
  Contenido* constante = nullptr;
  Contenido* mejor = nullptr;
  Contenido* e = nullptr;

  for(Diccionario::iterator it = _dicc.lower_bound(nombre); it != _dicc.upper_bound(nombre); ++it)
  {
    if (it->first == nombre)
    {
      e = it->second;
      if ( e->getAlcance() == 0 ) { constante = e; }
      else
      {
        for( Stack::reverse_iterator itPila = _pila.rbegin(); itPila != _pila.rend(); ++itPila )
        {
          if( *itPila == e->getAlcance() ) { mejor = e; break; }
          else if ( mejor != nullptr and *itPila == mejor->getAlcance() ) { break; }
          else { break; }
        }
      }
    }
  }

  if (mejor != nullptr) { return mejor; }
  else if (constante != nullptr) { return constante; }
  else { return nullptr; }
}
bool TablaSimbolos::check_scope(string nombre)
{
  Contenido *cont;
  unsigned int topePila = _pila.back();

  for(Diccionario::iterator it = _dicc.lower_bound(nombre); it != _dicc.upper_bound(nombre); ++it)
  {
    cont = it->second;
    if(cont->getAlcance() == topePila) { return true; }
  }
  return false;
}
unsigned int TablaSimbolos::exit_scope()
{
  _pila.pop_back();
  _pila.back();
}
unsigned int TablaSimbolos::enter_scope()
{
  _pila.push_back(++_alcance);
  return _alcance;
}

std::ostream& operator<<(std::ostream& os, TablaSimbolos &ts)
{
  for (Diccionario::iterator pos = ts._dicc.begin(); pos != ts._dicc.end(); ++pos)
  {
    os << pos->first << " : " << pos->second->to_string() << '\n';
  }
  os << ts._alcance << '\n';

  for (Stack::iterator pos = ts._pila.begin(); pos != ts._pila.end(); ++pos)
  {
    os << *pos << " ";
  }

  os << '\n';
  return os;
}
unsigned int TablaSimbolos::add_symbol (string nombre, Tipos tipo, Categorias categoria, unsigned int linea, unsigned int columna)
{
  Contenido *cont = new Contenido(tipo, categoria,_alcance, linea, columna);
  _dicc.insert(std::make_pair(nombre,cont)); 
  return _alcance;
}
