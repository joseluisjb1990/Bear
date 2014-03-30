# include <iostream>
# include <string>
# include "Contenido.hh"

using namespace std;

Contenido::Contenido( Type* tipo
                    , Categorias categoria
                    , unsigned int alcance
                    , unsigned int lineaDec
                    , unsigned int columnaDec
                    , unsigned int lineaDef
                    , unsigned int columnaDef
                    , bool mut
                    )
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

Contenido::Contenido( Type* tipo
                    , Categorias categoria
                    , unsigned int alcance
                    , unsigned int linea
                    , unsigned int columna
                    , bool mut
                    )
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

void Contenido::define( unsigned int linea
                      , unsigned int columna
                      )
{
  _definido = true;
  _lineaDef = linea;
  _columnaDef = columna;
}


Contenedor::Contenedor( Type* tipo
                      , Categorias categoria
                      , unsigned int alcance
                      , unsigned int linea
                      , unsigned int columna
                      )
  : Contenido(tipo, categoria, alcance, linea, columna, true)
  , _alcanceCampos ( 0 )
  {}

Contenedor::Contenedor( Type* tipo
                      , Categorias categoria
                      , unsigned int alcance
                      , unsigned int lineaDec
                      , unsigned int columnaDec
                      , unsigned int lineaDef
                      , unsigned int columnaDef
                      , unsigned int alcanceCampos
                      )
  : Contenido(tipo, categoria, alcance, lineaDec, columnaDec, lineaDef, columnaDef, true)
  , _alcanceCampos(alcanceCampos)
  {}

void Contenedor::define( unsigned int linea
                       , unsigned int columna
                       , Type* tipo
                       , unsigned int alcanceCampos
                       )
{
  Contenido::define(linea, columna);
  this->addType(tipo);
  _alcanceCampos = alcanceCampos;
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

std::string Contenido::to_string()
{
  std::string tipo        = std::string(_tipo->to_string());
  std::string categoria   = std::to_string(_categoria);
  std::string alcance     = std::to_string(_alcance);
  std::string lineaDec    = std::to_string(_lineaDec);
  std::string columnaDec  = std::to_string(_columnaDec);
  std::string lineaDef    = std::to_string(_lineaDef);
  std::string columnaDef  = std::to_string(_columnaDef);
  std::string mutab       = std::to_string(_mutable);
  std::string def         = std::to_string(_definido);

  if(_definido)
  {

    return  tipo        + std::string(BIG_WIDTH / 2 - tipo.size()       , ' ') + SEPARADOR
          + alcance     + std::string(SMALL_WIDTH   - alcance.length()    , ' ') + SEPARADOR
          + lineaDec    + std::string(SMALL_WIDTH   - lineaDec.length()   , ' ') + SEPARADOR
          + columnaDec  + std::string(SMALL_WIDTH   - columnaDec.length() , ' ') + SEPARADOR
          + lineaDef    + std::string(SMALL_WIDTH   - lineaDef.length()   , ' ') + SEPARADOR
          + columnaDef  + std::string(SMALL_WIDTH   - columnaDef.length() , ' ') + SEPARADOR
          + mutab       + std::string(SMALL_WIDTH   - mutab.length()      , ' ') + SEPARADOR
          +               std::string(SMALL_WIDTH                         , ' ') + SEPARADOR
          + def         + std::string(SMALL_WIDTH   - def.length()        , ' ') + SEPARADOR
          ;
  }
  else
  {
    return  tipo        + std::string(BIG_WIDTH / 2 - tipo.size()       , ' ') + SEPARADOR
          + alcance     + std::string(SMALL_WIDTH   - alcance.length()    , ' ') + SEPARADOR
          + lineaDec    + std::string(SMALL_WIDTH   - lineaDec.length()   , ' ') + SEPARADOR
          + columnaDec  + std::string(SMALL_WIDTH   - columnaDec.length() , ' ') + SEPARADOR
          +               std::string(SMALL_WIDTH                         , ' ') + SEPARADOR
          +               std::string(SMALL_WIDTH                         , ' ') + SEPARADOR
          + mutab       + std::string(SMALL_WIDTH   - mutab.length()      , ' ') + SEPARADOR
          +               std::string(SMALL_WIDTH                         , ' ') + SEPARADOR
          + def         + std::string(SMALL_WIDTH   - def.length()        , ' ') + SEPARADOR
          ;

  }
}

std::string Contenedor::to_string()
{

  std::string tipo;
  if      (dynamic_cast<GrizzliType*>(getTipo())) { tipo = "grizzli"; }
  else if (dynamic_cast<PardoType*>  (getTipo())) { tipo = "pardo"; }

  std::string categoria     = std::to_string(getCategoria()         );
  std::string alcance       = std::to_string(getAlcance()           );
  std::string lineaDec      = std::to_string(getLineaDec()          );
  std::string columnaDec    = std::to_string(getColumnaDec()        );
  std::string lineaDef      = std::to_string(getLineaDef()          );
  std::string columnaDef    = std::to_string(getColumnaDef()        );
  std::string mutab         = std::to_string(getMutabilidad()       );
  std::string alcanceCampos = std::to_string(_alcanceCampos         );
  std::string def           = std::to_string(getDef()               );

  if(getDef())
  {

    return  tipo          + std::string(BIG_WIDTH / 2 - tipo.size()             , ' ') + SEPARADOR
          + alcance       + std::string(SMALL_WIDTH   - alcance.length()        , ' ') + SEPARADOR
          + lineaDec      + std::string(SMALL_WIDTH   - lineaDec.length()       , ' ') + SEPARADOR
          + columnaDec    + std::string(SMALL_WIDTH   - columnaDec.length()     , ' ') + SEPARADOR
          + lineaDef      + std::string(SMALL_WIDTH   - lineaDef.length()       , ' ') + SEPARADOR
          + columnaDef    + std::string(SMALL_WIDTH   - columnaDef.length()     , ' ') + SEPARADOR
          + mutab         + std::string(SMALL_WIDTH   - mutab.length()          , ' ') + SEPARADOR
          + alcanceCampos + std::string(SMALL_WIDTH   - alcanceCampos.length()  , ' ') + SEPARADOR
          + def           + std::string(SMALL_WIDTH   - def.length()            , ' ') + SEPARADOR
          ;
  }
  else
  {
    return  tipo          + std::string(BIG_WIDTH / 2 - tipo.size()             , ' ') + SEPARADOR
          + alcance       + std::string(SMALL_WIDTH   - alcance.length()        , ' ') + SEPARADOR
          + lineaDec      + std::string(SMALL_WIDTH   - lineaDec.length()       , ' ') + SEPARADOR
          + columnaDec    + std::string(SMALL_WIDTH   - columnaDec.length()     , ' ') + SEPARADOR
          +                 std::string(SMALL_WIDTH                             , ' ') + SEPARADOR
          +                 std::string(SMALL_WIDTH                             , ' ') + SEPARADOR
          + mutab         + std::string(SMALL_WIDTH   - mutab.length()          , ' ') + SEPARADOR
          + alcanceCampos + std::string(SMALL_WIDTH   - alcanceCampos.length()  , ' ') + SEPARADOR
          + def           + std::string(SMALL_WIDTH   - def.length()            , ' ') + SEPARADOR
          ;

  }
}

std::string Funcion::to_string()
{
  std::string tipo          = std::string   (getTipo()->to_string()  );
  std::string categoria     = std::to_string(getCategoria()         );
  std::string alcance       = std::to_string(getAlcance()           );
  std::string lineaDec      = std::to_string(getLineaDec()          );
  std::string columnaDec    = std::to_string(getColumnaDec()        );
  std::string lineaDef      = std::to_string(getLineaDef()          );
  std::string columnaDef    = std::to_string(getColumnaDef()        );
  std::string mutab         = std::to_string(getMutabilidad()       );
  std::string def           = std::to_string(getDef()               );

  std::string param = "";
  for(std::vector<Parameter*>::iterator it = _parametros->begin(); it != _parametros->end(); ++it)
  {
    param += (*it)->to_string() + SEPARADOR;
  }

   if(getDef())
  {
    return  tipo          + std::string(BIG_WIDTH / 2 - tipo.size()             , ' ') + SEPARADOR
          + alcance       + std::string(SMALL_WIDTH   - alcance.length()        , ' ') + SEPARADOR
          + lineaDec      + std::string(SMALL_WIDTH   - lineaDec.length()       , ' ') + SEPARADOR
          + columnaDec    + std::string(SMALL_WIDTH   - columnaDec.length()     , ' ') + SEPARADOR
          + lineaDef      + std::string(SMALL_WIDTH   - lineaDef.length()       , ' ') + SEPARADOR
          + columnaDef    + std::string(SMALL_WIDTH   - columnaDef.length()     , ' ') + SEPARADOR
          + mutab         + std::string(SMALL_WIDTH   - mutab.length()          , ' ') + SEPARADOR
          +                 std::string(SMALL_WIDTH                             , ' ') + SEPARADOR
          + def           + std::string(SMALL_WIDTH   - def.length()            , ' ') + SEPARADOR
          + param
          ;
  }
  else
  {
    return  tipo          + std::string(BIG_WIDTH / 2 - tipo.size()             , ' ') + SEPARADOR
          + alcance       + std::string(SMALL_WIDTH   - alcance.length()        , ' ') + SEPARADOR
          + lineaDec      + std::string(SMALL_WIDTH   - lineaDec.length()       , ' ') + SEPARADOR
          + columnaDec    + std::string(SMALL_WIDTH   - columnaDec.length()     , ' ') + SEPARADOR
          +                 std::string(SMALL_WIDTH                             , ' ') + SEPARADOR
          +                 std::string(SMALL_WIDTH                             , ' ') + SEPARADOR
          + mutab         + std::string(SMALL_WIDTH   - mutab.length()          , ' ') + SEPARADOR
          +                 std::string(SMALL_WIDTH                             , ' ') + SEPARADOR
          + def           + std::string(SMALL_WIDTH   - def.length()            , ' ') + SEPARADOR
          + param
          ;

  }
}
