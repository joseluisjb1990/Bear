#ifndef TYPE_CC
#define TYPE_CC
#include "type.hh"

using namespace std;

Type::Type(int tam)
  : _tam (tam)
  {}

std::string Type::to_string()
{
  return "tipo";
}

int Type::getSize()
{
  return _tam;
}

PandaType::PandaType()
  : Type(4)
  {}

std::string PandaType::to_string()
{
  return "panda";
}

PolarType::PolarType()
  : Type(4)
  {}

std::string PolarType::to_string()
{
  return "polar";
}

KodiakType::KodiakType()
  : Type(4)
  {}

std::string KodiakType::to_string()
{
  return "kodiak";
}

MalayoType::MalayoType()
  : Type(4)
  {}

std::string MalayoType::to_string()
{
  return "malayo";
}

ExtintoType::ExtintoType()
  : Type(4)
  {}

std::string ExtintoType::to_string()
{
  return "extinto";
}

HormigueroType::HormigueroType()
  : Type(4)
  {}

std::string HormigueroType::to_string()
{
  return "hormiguero";
}

CuevaType::CuevaType(Type* tipo, std::vector<int>* longitudes)
  : _tipo       ( tipo       )
  , _longitudes ( longitudes )
  , Type(0)
  {}

int CuevaType::getSize()
{
  int size = _tipo->getSize();
  for (unsigned int i; i<_longitudes->size(); ++i)
    size = size * _longitudes->at(i);
  return size;
}

std::string CuevaType::to_string()
{
  return "cueva";
}

CampoType::CampoType(Type* tipo, std::string nombre)
  : Type(0)
  , _tipo   ( tipo   )
  , _nombre ( nombre )
  {}

std::string CampoType::to_string()
{
  return _tipo->to_string() + " " + _nombre;
}

int CampoType::getSize()
{
  return _tipo->getSize();
}

PardoType::PardoType(std::vector<CampoType*>* campos, std::string nombre)
  : Type(0)
  , _campos ( campos )
  , _nombre ( nombre )
  {}

std::string PardoType::to_string()
{
  std::string str = _nombre + ":\n";
  for (unsigned int i; i < _campos->size(); ++i)
    str += _campos->at(i)->to_string() + "\n";
  return str;
}

int PardoType::getSize()
{
  int size = 0;
  for (unsigned int i; i < _campos->size(); ++i)
    size += _campos->at(i)->getSize();
  return size;
}

ErrorType::ErrorType()
  : Type(4)
  {}

std::string to_string()
{
  return "error";
}

#endif
