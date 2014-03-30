#ifndef TYPE_HH
#define TYPE_HH
#include <string>
#include <vector>
#include "expresion.hh"

using namespace std;

class Type
{
  private:
    int _tam;

  public:
    Type(int tam);
    virtual std::string to_string();
    virtual int getSize();
    virtual bool isSimple() = 0;
    virtual std::string getName() { return ""; }
};

class PandaType : public Type
{
  public:
    PandaType();
    std::string to_string();
    bool isSimple();
};

class PolarType : public Type
{
  public:
    PolarType();
    std::string to_string();
    bool isSimple();
};

class KodiakType : public Type
{
  public:
    KodiakType();
    std::string to_string();
    bool isSimple();
};

class MalayoType : public Type
{
  public:
    MalayoType();
    std::string to_string();
    bool isSimple();
};

class ExtintoType : public Type
{
  public:
    ExtintoType();
    std::string to_string();
    bool isSimple();
};

class HormigueroType : public Type
{
  public:
    HormigueroType();
    std::string to_string();
    bool isSimple();
};

class CuevaType : public Type
{
  private:
    Type* _tipo;
    std::vector<Expression*>*   _longitudes;

  public:
    CuevaType(Type* tipo, std::vector<Expression*>* longitudes);
    int getSize();
    std::string to_string();
    bool isSimple();
    Type* getTipo();
};

class CampoType : public Type
{
  private:
    Type*       _tipo;
    std::string _nombre;

  public:
    CampoType(Type* tipo, std::string nombre);
    std::string to_string();
    int getSize();
    bool isSimple();
};

class PardoType : public Type
{
  private:
    std::vector<Type*>* _campos;
    std::string         _nombre;

  public:
    PardoType(std::vector<Type*>* campos, std::string nombre);
    PardoType(std::string nombre);
    std::string to_string();
    int getSize();
    bool isSimple();
    std::string getName();
};

class GrizzliType : public Type
{
  private:
    std::vector<Type*>* _campos;
    std::string              _nombre;

  public:
    GrizzliType(std::vector<Type*>* campos, std::string nombre);
    GrizzliType(std::string nombre);
    std::string to_string();
    int getSize();
    bool isSimple();
    std::string getName();
};

class ErrorType : public Type
{
  public:
    ErrorType();
    std::string to_string();
    bool isSimple();
};

class TagType : public Type
{
  public:
    TagType();
    std::string to_string();
    bool isSimple();
};
#endif
