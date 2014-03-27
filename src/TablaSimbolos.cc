#include "TablaSimbolos.hh"
#include <algorithm>

using namespace std;

Contenedor* TablaSimbolos::add_container (std::string nombre, Categorias categoria, unsigned int linea, unsigned int columna)
{
  Contenedor *cont = new  Contenedor(nullptr, categoria, _pila.back(), linea, columna);
  _dicc.insert(std::make_pair(nombre,cont));
  return cont;
}

Contenedor* TablaSimbolos::add_container (std::string nombre, Type* tipo, Categorias categoria, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, unsigned int alcanceCampos)
{
  Contenedor *cont = new Contenedor(tipo, categoria, _pila.back(), lineaDec, columnaDec, lineaDef, columnaDef, alcanceCampos);
  _dicc.insert(std::make_pair(nombre,cont));
  return cont;
}

TablaSimbolos::TablaSimbolos ()
  :_alcance( 0 )
  { _pila.push_back( 0 ); }

Contenido* TablaSimbolos::find_symbol(std::string nombre)
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
        }
      }
    }
  }

  if (mejor != nullptr) { return mejor; }
  else if (constante != nullptr) { return constante; }
  else { return nullptr; }
}
bool TablaSimbolos::check_scope(std::string nombre)
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
  return _pila.back();
}
unsigned int TablaSimbolos::enter_scope()
{
  _pila.push_back(++_alcance);
  return _alcance;
}

typedef std::pair<std::string, Contenido*> pair_str_cont;
typedef std::vector<pair_str_cont> vector_str_cont;

bool compare_pairs(pair_str_cont pair1, pair_str_cont pair2)
{
  return pair1.second->getAlcance() < pair2.second->getAlcance();
}

std::ostream& operator<<(std::ostream& os, TablaSimbolos &ts)
{
  vector_str_cont pairs_vector;

  for (Diccionario::iterator pos = ts._dicc.begin(); pos != ts._dicc.end(); ++pos)
  {
    pairs_vector.push_back(std::make_pair(std::string(pos->first), pos->second));
  }

  std::sort(pairs_vector.begin(), pairs_vector.end(), compare_pairs);

  for (vector_str_cont::iterator pos = pairs_vector.begin(); pos != pairs_vector.end(); ++pos)
  {
    os << pos->first << " : " << pos->second->to_string() << '\n';
  }

  os << '\n';
  return os;
}
unsigned int TablaSimbolos::add_symbol (std::string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna, bool mut)
{
  Contenido *cont = new Contenido(tipo, categoria, _pila.back(), linea, columna, mut);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}
unsigned int TablaSimbolos::add_symbol (std::string nombre, Type* tipo, Categorias categoria, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, bool mut)
{
  Contenido *cont = new Contenido(tipo, categoria, _pila.back(), lineaDec, columnaDec, lineaDef, columnaDef, mut);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}

unsigned int TablaSimbolos::add_function  (
                                            std::string nombre
                                          , Type* tipo
                                          , unsigned int linea
                                          , unsigned int columna
                                          , vector<Parameter*>* parametros
                                          )
{
  Contenido *cont = new Funcion(tipo, _pila.back(), linea, columna, parametros);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}

unsigned int TablaSimbolos::add_function  (
                                            std::string nombre
                                          , Type* tipo
                                          , unsigned int lineaDec
                                          , unsigned int columnaDec
                                          , unsigned int lineaDef
                                          , unsigned int columnaDef
                                          , vector<Parameter*>* parametros
                                          )
{
  Contenido *cont = new Funcion(tipo, _pila.back(), lineaDec, columnaDec, lineaDef, columnaDef, parametros);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}

unsigned int TablaSimbolos::get_actual_scope() { return _alcance; }

Funcion* TablaSimbolos::get_function(std::string nombre)
{

  for(Diccionario::iterator it = _dicc.lower_bound(nombre); it != _dicc.upper_bound(nombre); ++it)
  {
    if (it->first == nombre)
    {
      if(it->second->getCategoria() == Proc)
      {
        Funcion* f = dynamic_cast <Funcion *>(it->second);
        return f;
      }
    }
  }
  return nullptr;
}

Contenedor* TablaSimbolos::update_container (string nombre, Type* tipo, unsigned int lineaDef, unsigned int columnaDef, unsigned int alcanceCampos)
{
  for(Diccionario::iterator it = _dicc.lower_bound(nombre); it != _dicc.upper_bound(nombre); ++it)
  {
    if (it->first == nombre)
    {
      if(it->second->getCategoria() == Compuesto)
      {
        Contenedor* c = dynamic_cast <Contenedor *>(it->second);
        c->define(lineaDef, columnaDef, tipo, alcanceCampos);
        return c;
      }
    }
  }
  return nullptr;
}

Contenedor* TablaSimbolos::find_container (string nombre)
{
  for(Diccionario::iterator it = _dicc.lower_bound(nombre); it != _dicc.upper_bound(nombre); ++it)
  {
    if (it->first == nombre)
    {
      if(it->second->getCategoria() == Compuesto)
      {
        Contenedor* c = dynamic_cast <Contenedor *>(it->second);
        return c;
      }
    }
  }
  return nullptr;
}
