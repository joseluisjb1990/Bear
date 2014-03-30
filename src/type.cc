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

bool PandaType::isSimple()
{
  return true;
}

PolarType::PolarType()
  : Type(4)
  {}

std::string PolarType::to_string()
{
  return "polar";
}

bool PolarType::isSimple()
{
  return true;
}

KodiakType::KodiakType()
  : Type(4)
  {}

std::string KodiakType::to_string()
{
  return "kodiak";
}

bool KodiakType::isSimple()
{
  return true;
}

MalayoType::MalayoType()
  : Type(4)
  {}

std::string MalayoType::to_string()
{
  return "malayo";
}

bool MalayoType::isSimple()
{
  return true;
}

ExtintoType::ExtintoType()
  : Type(4)
  {}

std::string ExtintoType::to_string()
{
  return "extinto";
}

bool ExtintoType::isSimple()
{
  return true;
}

HormigueroType::HormigueroType()
  : Type(4)
  {}

std::string HormigueroType::to_string()
{
  return "hormiguero";
}

bool HormigueroType::isSimple()
{
  return true;
}

CuevaType::CuevaType(Type* tipo, std::vector<std::string>* longitudes)
  : Type(0)
  , _tipo       ( tipo       )
  , _longitudes ( longitudes )
  {}

int CuevaType::getSize()
{
  int size = _tipo->getSize();
  for (unsigned int i=0; i<_longitudes->size(); ++i)
    size = size * std::stoi(_longitudes->at(i));
  return size;
}

std::string CuevaType::to_string()
{
  std::string str(_tipo->to_string());
  for (unsigned int i=0; i<_longitudes->size(); ++i)
    str += "[" + _longitudes->at(i) + "]";
  return str;
}

bool CuevaType::isSimple()
{
  return true;
}

Type* CuevaType::getTipo()
{
  return _tipo;
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

bool CampoType::isSimple()
{
  return true;
}

PardoType::PardoType(std::vector<Type*>* campos, std::string nombre)
  : Type(0)
  , _campos ( campos )
  , _nombre ( nombre )
  {}

std::string PardoType::to_string()
{
  return _nombre;
}

int PardoType::getSize()
{
  int size = 0;
  for (unsigned int i=0; i < _campos->size(); ++i)
    size += _campos->at(i)->getSize();
  return size;
}

bool PardoType::isSimple()
{
  return false;
}

std::string PardoType::getName()
{
  return _nombre;
}

GrizzliType::GrizzliType(std::vector<Type*>* campos, std::string nombre)
  : Type(0)
  , _campos ( campos )
  , _nombre ( nombre )
  {}

std::string GrizzliType::to_string()
{
  return _nombre;
}

int GrizzliType::getSize()
{
  int max = 0;
  for (unsigned int i=0; i < _campos->size(); ++i) {
    if (max < _campos->at(i)->getSize() )
      max = _campos->at(i)->getSize();
  }
  return max;
}

bool GrizzliType::isSimple()
{
  return false;
}

std::string GrizzliType::getName()
{
  return _nombre;
}

ErrorType::ErrorType()
  : Type(4)
  {}

std::string ErrorType::to_string()
{
  return "error";
}

bool ErrorType::isSimple()
{
  return true;
}

TagType::TagType()
  : Type(4)
  {}

std::string TagType::to_string()
{
  return "etiqueta";
}

bool TagType::isSimple()
{
  return true;
}
#endif
