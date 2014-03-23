#include "TablaSimbolos.hh"

Contenedor* TablaSimbolos::add_container (std::string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna, unsigned int alcanceCampos)
{
  Contenedor *cont;
  cont = new  Contenedor(tipo, categoria, _pila.back(), linea, columna, alcanceCampos);
  _dicc.insert(std::make_pair(nombre,cont));
  return cont;
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
  return _pila.back();
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
unsigned int TablaSimbolos::add_symbol (string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna, bool mut)
{
  Contenido *cont = new Contenido(tipo, categoria, _pila.back(), linea, columna, mut);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}
unsigned int TablaSimbolos::add_symbol (string nombre, Type* tipo, Categorias categoria, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, bool mut)
{
  Contenido *cont = new Contenido(tipo, categoria, _pila.back(), lineaDec, columnaDec, lineaDef, columnaDef, mut);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}

unsigned int TablaSimbolos::add_function  (
                                            string nombre
                                          , Type* tipo
                                          , unsigned int linea
                                          , unsigned int columna
                                          , vector<Definition*>* parametros
                                          , bool definida
                                          )
{
  Contenido *cont = new Funcion(tipo, _pila.back(), linea, columna, definida, parametros);
  _dicc.insert(std::make_pair(nombre,cont));
  return _alcance;
}

unsigned int TablaSimbolos::get_actual_scope() { return _alcance; }
