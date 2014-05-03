/**
 *  Nombre del archivo = type.hh
 *
 *  Autores:
 *    Gabriela Limonta
 *    José Luis Jiménez
 *
 *  Descripción:
 *    Definición de la clase Type usada en bear_parser.yy y en la
 *    tabla de simbolos para representar los tipos de las cosas en
 *    el lenguaje Bear.
 *
 *  Última fecha de modificación:
 *    30/03/2014
 */

#ifndef TYPE_HH
#define TYPE_HH
#include <string>
#include <vector>
#include "expresion.hh"

class Expression;

using namespace std;

class Type
{
  private:
    int _tam; // Guarda el tamaño en bytes del tipo.

  public:

    /**
     * Constructor para la clase.
     *
     *  Parámetros:
     *   tam: tamaño del tipo en bytes.
     */
    Type(int tam);

    /**
     * Retorna una representación en string del tipo
     *
     *  Parámetros:
     *   Ninguno.
     */
    virtual std::string to_string();

    /**
     * Retorna el tamaño en bytes del tipo
     *
     *  Parámetros:
     *   Ninguno.
     */
    virtual int getSize();

    /**
     * Retorna true si el tipo es simple y
     * false si es uno de los tipos compuestos (grizzli, pardo)
     *
     *  Parámetros:
     *   Ninguno.
     */
    virtual bool isSimple() = 0;

    /**
     * Retorna una representación en string del nombre del tipo.
     *
     *  Parámetros:
     *   Ninguno.
     */
    virtual std::string getName() { return ""; };
};

class PandaType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static PandaType* getInstance()
    {
      if(!_instance)
        _instance = new PandaType();

      return _instance;
    }

  private:
    PandaType();
    static PandaType* _instance;
};

class PolarType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static PolarType* getInstance()
    {
      if(!_instance)
        _instance = new PolarType();

      return _instance;
    }

  private:
    PolarType();
    static PolarType* _instance;

};

class KodiakType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static KodiakType*getInstance()
    {
      if(!_instance)
        _instance = new KodiakType();

      return _instance;
    }

  private:
    KodiakType();
    static KodiakType* _instance;
};

class MalayoType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static MalayoType* getInstance()
    {
      if(!_instance)
        _instance = new MalayoType();

      return _instance;
    }

  private:
    MalayoType();
    static MalayoType* _instance;
};

class ExtintoType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static ExtintoType* getInstance()
    {
      if(!_instance)
        _instance = new ExtintoType();

      return _instance;
    }

  private:
    ExtintoType();
    static ExtintoType* _instance;
};

class HormigueroType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static HormigueroType* getInstance()
    {
      if(!_instance)
        _instance = new HormigueroType();

      return _instance;
    }

  private:
    HormigueroType();
    static HormigueroType* _instance;
};

class CuevaType : public Type
{
  private:
    Type*                      _tipo;       // Tipo de los elementos de la cueva
    std::vector<Expression*>*  _longitudes; // Lista que contiene las longitudes de cada dimension de la cueva

  public:

    /**
     * Constructor para la clase.
     *
     *  Parámetros:
     *   tipo:       tipo de los elementos de la cueva.
     *   longitudes: lista que contiene las longitudes de cada dimensión de la cueva.
     */
    CuevaType(Type* tipo, std::vector<Expression*>* longitudes);
    int getSize();
    std::string to_string();
    bool isSimple();

    /**
     * Retorna tipo de los elementos de la cueva.
     *
     *  Parámetros:
     *   Ninguno.
     */
    Type* getTipo();
};

class CampoType : public Type
{
  private:
    Type*       _tipo;   // Tipo del campo
    std::string _nombre; // Nombre del campo

  public:

    /**
     * Constructor para la clase
     *
     *  Parámetros:
     *   tipo:   tipo del campo.
     *   nombre: nombre del campo.
     */
    CampoType(Type* tipo, std::string nombre);
    std::string to_string();
    int getSize();
    bool isSimple();
};

class PardoType : public Type
{
  private:
    std::vector<Type*>* _campos; // Lista de campos del tipo pardo.
    std::string         _nombre; // Nombre del tipo pardo.

  public:

    /**
     * Constructor para la clase
     *
     *  Parámetros:
     *   campos: lista de campos del tipo.
     *   nombre: nombre del tipo pardo.
     */
    PardoType(std::vector<Type*>* campos, std::string nombre);

    /**
     * Constructor para la clase
     *
     *  Parámetros:
     *   nombre: nombre del tipo pardo.
     */
    PardoType(std::string nombre);
    std::string to_string();
    int getSize();
    bool isSimple();

    /**
     * Retorna una representación en string del nombre del tipo.
     *
     *  Parámetros:
     *    Ninguno.
     */
    std::string getName();
};

class GrizzliType : public Type
{
  private:
    std::vector<Type*>* _campos; // Lista de campos del tipo grizzli.
    std::string         _nombre; // Nombre del tipo grizzli.

  public:

    /**
     * Constructor para la clase
     *
     *  Parámetros:
     *   campos: lista de campos del tipo.
     *   nombre: nombre del tipo grizzli.
     */
    GrizzliType(std::vector<Type*>* campos, std::string nombre);

    /**
     * Constructor para la clase
     *
     *  Parámetros:
     *   nombre: nombre del tipo grizzli.
     */
    GrizzliType(std::string nombre);
    std::string to_string();
    int getSize();
    bool isSimple();

    /**
     * Retorna una representación en string del nombre del tipo.
     *
     *  Parámetros:
     *    Ninguno.
     */
    std::string getName();
};

/**
 * Representa un error de tipos.
 *
 */
class ErrorType : public Type
{
  public:
    std::string to_string();
    bool isSimple();
    static ErrorType* getInstance()
    {
      if(!_instance)
        _instance = new ErrorType();

      return _instance;
    }
  private:
    ErrorType();
    static ErrorType* _instance;
};

/**
 * Representa el tipo de una etiqueta.
 *
 */
class TagType : public Type
{
  public:
    TagType();
    std::string to_string();
    bool isSimple();
};

class Tuple : public Type
{
  public:
    Tuple(Type* izq, Type* der);
  private:
    Type* _izq;
    Type* _der;
};

#endif
