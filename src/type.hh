#ifndef TYPE_HH
#define TYPE_HH
#include <string>
#include <vector>

using namespace std;

class Type
{
  private:
    int _tam;

  public:
    Type(int tam);
    virtual std::string to_string();
    virtual int getSize();
};

class PandaType : public Type
{
  public:
    PandaType();
    std::string to_string();
};

class PolarType : public Type
{
  public:
    PolarType();
    std::string to_string();
};

class KodiakType : public Type
{
  public:
    KodiakType();
    std::string to_string();
};

class MalayoType : public Type
{
  public:
    MalayoType();
    std::string to_string();
};

class ExtintoType : public Type
{
  public:
    ExtintoType();
    std::string to_string();
};

class HormigueroType : public Type
{
  public:
    HormigueroType();
    std::string to_string();
};

class CuevaType : public Type
{
  private:
    Type* _tipo;
    std::vector<int>*   _longitudes;

  public:
    CuevaType(Type* tipo, std::vector<int>* longitudes);
    int getSize();
    std::string to_string();
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
};

class PardoType : public Type
{
  private:
    std::vector<CampoType*>* _campos;
    std::string         _nombre;

  public:
    PardoType(std::vector<CampoType*>* campos, std::string nombre);
    std::string to_string();
    int getSize();
};

class ErrorType : public Type
{
  public:
    ErrorType()
    std::string to_string();
};

#endif
