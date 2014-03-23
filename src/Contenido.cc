# include <string>
# include "Contenido.hh"

using namespace std;

Contenido::Contenido (Type* tipo, Categorias categoria, unsigned int alcance, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef)
  : _tipo       ( tipo       )
  , _categoria  ( categoria  )
  , _alcance    ( alcance    )
  , _lineaDec   ( lineaDec   )
  , _columnaDec ( columnaDec )
  , _lineaDef   ( lineaDef   )
  , _columnaDef ( columnaDef )
  {}

Contenido::Contenido (Type* tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna)
  : _tipo       ( tipo      )
  , _categoria  ( categoria )
  , _alcance    ( alcance   )
  , _lineaDec   ( linea     )
  , _columnaDec ( columna   )
  , _lineaDef   ( 0         )
  , _columnaDef ( 0         )
  {}

unsigned int Contenido::getAlcance() { return _alcance; }

std::string Contenido::to_string()
{
  return "Tipo: " + _tipo->to_string() + ", Categoria: " + std::to_string(_categoria) + ", Alcance: " + std::to_string(_alcance) + ", Linea de Declaración: " + std::to_string(_lineaDec) + ", Columna de Declaración: " + std::to_string(_columnaDec) + ", Linea de Definición: " + std::to_string(_lineaDef) + ", Columna de Definición: " + std::to_string(_columnaDef) + "\n";
}

Contenedor::Contenedor(Type* tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna, unsigned int alcanceCampos)
  : Contenido(tipo, categoria, alcance, linea, columna)
  , _alcanceCampos(alcanceCampos)
  {}

std::string Contenedor::to_string()
{
  return this->Contenido::to_string() + " " + std::to_string(_alcanceCampos);
}

Funcion::Funcion ( Type* tipo
                 , unsigned int alcance
                 , unsigned int linea
                 , unsigned int columna
                 , bool def
                 , std::vector<Definition*>* parametros
                 )
  : Contenido(tipo, Proc, alcance, linea, columna)
  , _def        ( def        )
  , _parametros ( parametros )
  {}

std::string Funcion::to_string()
{
  std::string str =  "Funcion : " + this->Contenido::to_string() + "Definida: " + std::to_string( _def ) + " Parametros : ";
  for (unsigned int i=0; i<_parametros->size(); ++i)
    str += _parametros->at(i)->to_string() + " ";

  return str;
}
