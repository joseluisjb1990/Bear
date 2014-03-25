#include "type.hh"
#include "definition.hh"

typedef enum { Var, Const, Proc, Campo, Cueva, Compuesto} Categorias;

class Contenido
{
private:

    Type* _tipo;
    Categorias _categoria;
    unsigned int _alcance;
    unsigned int _lineaDec;
    unsigned int _columnaDec;
    unsigned int _lineaDef;
    unsigned int _columnaDef;
    bool _mutable;

   //Posiblemente haya otros dependiendo del tipo o la categoria.

public:

    Contenido ( Type*         tipo
              , Categorias    categoria
              , unsigned int  alcance
              , unsigned int  lineaDec
              , unsigned int  columnaDec
              , unsigned int  lineaDef
              , unsigned int  columnaDef
              , bool          mut
              );

    Contenido ( Type*         tipo
              , Categorias    categoria
              , unsigned int  alcance
              , unsigned int  linea
              , unsigned int  columna
              , bool          mut
              );

    virtual std::string to_string();

    unsigned int getAlcance();
    bool esMutable();
    Categorias get_categoria() { return _categoria; };
};

class Contenedor : public Contenido
{

private:

  unsigned int _alcanceCampos;

public:

  Contenedor  ( Type*         tipo
              , Categorias    categoria
              , unsigned int  alcance
              , unsigned int  linea
              , unsigned int  columna
              , unsigned int  alcanceCampos
              );

  virtual std::string to_string();
  void set_alcanceCampos(unsigned int alcanceCampos) { _alcanceCampos = alcanceCampos; };
};

class Funcion : public Contenido
{

public:
    Funcion ( Type* tipo
            , unsigned int alcance
            , unsigned int linea
            , unsigned int columna
            , bool def
            , std::vector<Parameter*>* parametros
            );

    std::string to_string();
    bool get_def()  { return _def; };
    void define()   { _def = true; };
    std::vector<Parameter*> * get_parameters() { return _parametros; };
private:
    bool                _def;
    std::vector<Parameter*>* _parametros;
};
