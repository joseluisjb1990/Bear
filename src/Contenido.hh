#include "type.hh"
#include "definition.hh"

typedef enum { Var, Const, Proc, Campo, Cueva, Compuesto, Etiqueta} Categorias;

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
    bool _definido;

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

    void addType(Type* tipo);
    void define(unsigned int linea, unsigned int columna);
    bool getDef() { return _definido; };
    Type* getTipo() { return _tipo; };
    bool getMutabilidad() { return _mutable; };
    unsigned int getAlcance() { return _alcance; };
    unsigned int getLineaDec() { return _lineaDec; };
    unsigned int getColumnaDec() { return _columnaDec; };
    unsigned int getLineaDef() { return _lineaDef; };
    unsigned int getColumnaDef() { return _columnaDef; };
    Categorias getCategoria() { return _categoria; };
};

class Contenedor : public Contenido
{

private:

  unsigned int _alcanceCampos;

public:

  Contenedor  ( Type*        tipo
              , Categorias   categoria
              , unsigned int alcance
              , unsigned int linea
              , unsigned int columna
              );

  Contenedor  ( Type*        tipo
              , Categorias   categoria
              , unsigned int alcance
              , unsigned int lineaDec
              , unsigned int columnaDec
              , unsigned int lineaDef
              , unsigned int columnaDef
              , unsigned int alcanceCampos
              );

  virtual std::string to_string();
  void define(unsigned int linea, unsigned int columna, Type* tipo, unsigned int alcanceCampos);
  void set_alcanceCampos(unsigned int alcanceCampos) { _alcanceCampos = alcanceCampos; };
};

class Funcion : public Contenido
{

public:
    Funcion ( Type* tipo
            , unsigned int alcance
            , unsigned int linea
            , unsigned int columna
            , std::vector<Parameter*>* parametros
            );

    Funcion ( Type* tipo
            , unsigned int alcance
            , unsigned int lineaDec
            , unsigned int columnaDec
            , unsigned int lineaDef
            , unsigned int columnaDef
            , std::vector<Parameter*>* parametros
            );

    std::string to_string();
    std::vector<Parameter*> * get_parameters() { return _parametros; };

private:
    std::vector<Parameter*>* _parametros;
};
