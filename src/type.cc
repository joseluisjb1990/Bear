/**
 *  Nombre del archivo = type.cc
 *
 *  Autores:
 *    Gabriela Limonta
 *    José Luis Jiménez
 *
 *  Descripción:
 *    Implementación de las funciones de la clase
 *    Type definida en el archivo
 *    type.hh
 *
 *  Última fecha de modificación:
 *    30/03/2014
 */

#ifndef TYPE_CC
#define TYPE_CC
#include "type.hh"
#include "expresion.hh"

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

PandaType* PandaType::_instance = 0;

bool PandaType::compareTypes (Type* t2)
{
  return t2 == getInstance();
}

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

PolarType* PolarType::_instance = 0;

bool PolarType::compareTypes (Type* t2)
{
  return t2 == getInstance();
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

KodiakType* KodiakType::_instance = 0;

bool KodiakType::compareTypes (Type* t2)
{
  return t2 == getInstance();
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

MalayoType* MalayoType::_instance = 0;

bool MalayoType::compareTypes (Type* t2)
{
  return t2 == getInstance();
}

ExtintoType::ExtintoType()
  : Type(4)
  {}

std::string ExtintoType::to_string()
{
  return "extinto";
}

ExtintoType* ExtintoType::_instance = 0;

bool ExtintoType::isSimple()
{
  return true;
}

bool ExtintoType::compareTypes (Type* t2)
{
  return t2 == getInstance();
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

bool HormigueroType::compareTypes (Type* t2)
{
  return dynamic_cast<HormigueroType*> (t2);
}

CuevaType::CuevaType(Type* tipo, std::vector<Expression*>* longitudes)
  : Type(0)
  , _tipo       ( tipo       )
  , _longitudes ( longitudes )
  {}

int CuevaType::getSize()
{
  int size = _tipo->getSize();
  return size;
}

bool CuevaType::compareTypes (Type* t2)
{
  return this == t2;
}

std::string CuevaType::to_string()
{
  std::string str = "cueva ";
  for (unsigned int i=0; i<_longitudes->size(); ++i)
    str += "[" + _longitudes->at(i)->to_string() + "]";
  str += " de " + _tipo->to_string();
  return str;
}

std::vector<Expression*>* CuevaType::getLongitudes();

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

bool CampoType::compareTypes (Type* t2)
{
  return dynamic_cast<CampoType*> (t2);
}

PardoType::PardoType(std::vector<Type*>* campos, std::string nombre)
  : Type(0)
  , _campos ( campos )
  , _nombre ( nombre )
  {}

PardoType::PardoType(std::string nombre)
  : Type(0)
  , _nombre ( nombre )
  {}

std::string PardoType::to_string()
{
  return "pardo " + _nombre;
}

int PardoType::getSize()
{
  int size = 0;
  for (unsigned int i=0; i < _campos->size(); ++i)
    size += _campos->at(i)->getSize();
  return size;
}

bool PardoType::compareTypes (Type* t2)
{
  return dynamic_cast<PardoType*> (t2);
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

GrizzliType::GrizzliType(std::string nombre)
  : Type(0)
  , _nombre ( nombre )
  {}

std::string GrizzliType::to_string()
{
  return "grizzli " + _nombre;
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

bool GrizzliType::compareTypes (Type* t2)
{
  return dynamic_cast<GrizzliType*> (t2);
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

ErrorType* ErrorType::_instance = 0;

bool ErrorType::compareTypes (Type* t2)
{
  return t2 == getInstance();
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

bool TagType::compareTypes (Type* t2)
{
  return dynamic_cast<TagType*> (t2);
}


Tuple::Tuple(Type* izq, Type* der)
  : Type(0)
  , _izq( izq )
  , _der( der )
  {}
#endif
