enum Categorias { Var, Const, Proc, Campo, Cueva};

class Contenido
{
private:

    std::string _tipo;
    Categorias _categoria;
    unsigned int _alcance;
    unsigned int _linea;
    unsigned int _columna;
   //Posiblemente haya otros dependiendo del tipo o la categoria.

public:

    Contenido ( std::string   tipo
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

  Contenedor  ( std::string   tipo
              , Categorias    categoria
              , unsigned int  alcance
              , unsigned int  linea
              , unsigned int  columna
              , unsigned int  alcanceCampos
              );

  virtual std::string to_string();
};
