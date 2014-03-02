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

    friend inline std::ostream& operator<<(std::ostream& os, const Contenido &cont);

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

std::ostream& operator<<(std::ostream& os, const Contenido& cont)
{
  os << cont._tipo << " " << cont._categoria << " " << cont._alcance << " " << cont._linea<< " " << cont._columna << '\n';
  return os;
}
