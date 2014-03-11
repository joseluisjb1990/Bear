enum Tipos { POLAR, PANDA, KODIAK, MALAYO, GRIZZLI, PARDO, EXTINTO };
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

    Contenido ( Tipos         tipo
              , Categorias    categoria
              , unsigned int  alcance
              , unsigned int  linea
              , unsigned int  columna
              );

    virtual std::string to_string();

    unsigned int getAlcance();
};

class Contenedor : public Contenido
{

private:

  unsigned int _alcanceCampos;

public:

  Contenedor  ( Tipos         tipo
              , Categorias    categoria
              , unsigned int  alcance
              , unsigned int  linea
              , unsigned int  columna
              , unsigned int  alcanceCampos
              );

  virtual std::string to_string();
};
