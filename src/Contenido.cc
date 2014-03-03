enum Tipos {POLAR, PANDA, KODIAK, MALAYO, GRIZZLI, PARDO, EXTINTO };
enum Categorias { VAR, CONST, PROC, CAMPO, CUEVA};

class Contenido
{
private:

    Tipos _tipo;
    Categorias _categoria;
    unsigned int _alcance;
    unsigned int _linea;
    unsigned int _columna;
   //Posiblemente haya otros dependiendo del tipo o la categoria.

public:

    Contenido(Tipos tipo, Categorias categoria, unsigned int alcance, unsigned int linea, unsigned int columna);

    ~Contenido(){};

    virtual std::string to_string();

    unsigned int getAlcance();
};

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
