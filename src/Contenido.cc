# include <string>
# include "Contenido.hh"

using namespace std;

Contenido::Contenido (Type* tipo, Categorias categoria, unsigned int alcance, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, bool mut)
  : _tipo       ( tipo       )
  , _categoria  ( categoria  )
  , _alcance    ( alcance    )
  , _lineaDec   ( lineaDec   )
  , _columnaDec ( columnaDec )
  , _lineaDef   ( lineaDef   )
  , _columnaDef ( columnaDef )
  , _mutable    ( mut        )
  , _definido   ( true       )
  {}

Contenido::Contenido (Type* tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna, bool mut)
  : _tipo       ( tipo      )
  , _categoria  ( categoria )
  , _alcance    ( alcance   )
  , _lineaDec   ( linea     )
  , _columnaDec ( columna   )
  , _lineaDef   ( 0         )
  , _columnaDef ( 0         )
  , _mutable    ( mut       )
  , _definido   ( false     )
  {}

void Contenido::addType(Type* tipo) { _tipo = tipo; }

void Contenido::define(unsigned int linea, unsigned int columna) {
  _definido = true;
  _lineaDef = linea;
  _columnaDef = columna;
}

std::string Contenido::to_string()
{
  if (getDef()) {
    return "Tipo: " + _tipo->to_string() + ", Categoria: " + std::to_string(_categoria) + ", Alcance: " + std::to_string(_alcance) + ", Linea de Declaración: " + std::to_string(_lineaDec) + ", Columna de Declaración: " + std::to_string(_columnaDec) + ", Linea de Definición: " + std::to_string(_lineaDef) + ", Columna de Definición: " + std::to_string(_columnaDef) + ", Mutabilidad: " + std::to_string(_mutable) + "\n";
  } else {
    return "Tipo: " + _tipo->to_string() + ", Categoria: " + std::to_string(_categoria) + ", Alcance: " + std::to_string(_alcance) + ", Linea de Declaración: " + std::to_string(_lineaDec) + ", Columna de Declaración: " + std::to_string(_columnaDec) + ", Mutabilidad: " + std::to_string(_mutable) + "\n";
  }
}

Contenedor::Contenedor(Type* tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna)
  : Contenido(tipo, categoria, alcance, linea, columna, true)
  , _alcanceCampos ( 0 )
  {}

Contenedor::Contenedor(Type* tipo, Categorias categoria, unsigned int alcance, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, unsigned int alcanceCampos)
  : Contenido(tipo, categoria, alcance, lineaDec, columnaDec, lineaDef, columnaDef, true)
  , _alcanceCampos(alcanceCampos)
  {}

void Contenedor::define(unsigned int linea, unsigned int columna, Type* tipo, unsigned int alcanceCampos) {
  Contenido::define(linea, columna);
  this->addType(tipo);
  _alcanceCampos = alcanceCampos;
}

std::string Contenedor::to_string()
{
  if (getDef()) {
    return this->Contenido::to_string() + ", Alcance Campos: " + std::to_string(_alcanceCampos);
  } else {
    return " Categoria: " + std::to_string(getCategoria()) + ", Alcance: " + std::to_string(getAlcance()) + ", Linea de Declaración: " + std::to_string(getLineaDec()) + ", Columna de Declaración: " + std::to_string(getColumnaDec()) + ", Mutabilidad: " + std::to_string(getMutabilidad()) + "\n";
  }
}

Funcion::Funcion ( Type* tipo
                 , unsigned int alcance
                 , unsigned int linea
                 , unsigned int columna
                 , std::vector<Parameter*>* parametros
                 )
  : Contenido(tipo, Proc, alcance, linea, columna, false)
  , _parametros ( parametros )
  {}

Funcion::Funcion ( Type* tipo
                 , unsigned int alcance
                 , unsigned int lineaDec
                 , unsigned int columnaDec
                 , unsigned int lineaDef
                 , unsigned int columnaDef
                 , std::vector<Parameter*>* parametros
                 )
  : Contenido(tipo, Proc, alcance, lineaDec, columnaDec, lineaDef, columnaDef, false)
  , _parametros ( parametros )
  {}

std::string Funcion::to_string()
{
  std::string str =  "Funcion : " + this->Contenido::to_string() + "Definida: " + std::to_string( this->getDef() ) + " Parametros : ";
  for (unsigned int i=0; i<_parametros->size(); ++i)
    str += _parametros->at(i)->to_string() + " ";

  return str;
}
