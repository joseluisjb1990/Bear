# include <string>
# include "Contenido.hh"

using namespace std;

Contenido::Contenido (std::string tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna)
  :_tipo( tipo )
  ,_categoria( categoria )
  ,_alcance( alcance )
  ,_linea( linea )
  ,_columna( columna )
  {}

unsigned int Contenido::getAlcance() { return _alcance; }

std::string Contenido::to_string()
{
  return _tipo + " " + std::to_string(_categoria) + " " + std::to_string(_alcance) + " " + std::to_string(_linea) + " " + std::to_string(_columna);
}

Contenedor::Contenedor(std::string tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna, unsigned int alcanceCampos)
  : Contenido(tipo, categoria, alcance, linea, columna)
  , _alcanceCampos(alcanceCampos)
  {}

std::string Contenedor::to_string()
{
  return this->Contenido::to_string() + " " + std::to_string(_alcanceCampos);
}
