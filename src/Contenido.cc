# include <string>
# include "Contenido.hh"

using namespace std;

Contenido::Contenido (Tipos tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna)
  :_tipo( tipo )
  ,_categoria( categoria )
  ,_alcance( alcance )
  ,_columna( columna )
  ,_linea( linea )
  {}

unsigned int Contenido::getAlcance() { return _alcance; }

std::string Contenido::to_string()
{
  return std::to_string(_tipo) + " " + std::to_string(_categoria) + " " + std::to_string(_alcance) + " " + std::to_string(_linea) + " " + std::to_string(_columna);
}

Contenedor::Contenedor(Tipos tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna, unsigned int alcanceCampos)
  : Contenido(tipo, categoria, alcance, linea, columna)
  , _alcanceCampos(alcanceCampos)
  {}

std::string Contenedor::to_string()
{
  return this->Contenido::to_string() + " " + std::to_string(_alcanceCampos);
}
