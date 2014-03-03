#include "Contenido.cc"

class Contenedor : public Contenido
{

private:

  unsigned int _alcanceCampos;

public:

  Contenedor(Tipos tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna, unsigned int alcanceCampos);
  virtual std::string to_string();
};

Contenedor::Contenedor(Tipos tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna, unsigned int alcanceCampos)
  : Contenido(tipo, categoria, alcance, linea, columna)
  , _alcanceCampos(alcanceCampos)
  {}

std::string Contenedor::to_string()
{
  return this->Contenido::to_string() + " " + std::to_string(_alcanceCampos);
}
