#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include "Contenido.hh"
#include "type.hh"

using namespace std;

typedef std::multimap<std::string, Contenido*> Diccionario;
typedef std::vector<unsigned int> Stack;

class TablaSimbolos
{
private:

    Diccionario _dicc;
    Stack       _pila;
    unsigned int _alcance;

public:

    TablaSimbolos();
    unsigned int add_symbol (string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna, bool mut);
    unsigned int add_symbol (string nombre, Type* tipo, Categorias categoria, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, bool mut);
    Contenedor* add_container (std::string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna);
    Contenedor* add_container (string nombre, Type* tipo, Categorias categoria, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, unsigned int alcanceCampos);
    Contenedor* find_container (string nombre);
    Contenedor* update_container (string nombre, Type* tipo, unsigned int lineaDef, unsigned int columnaDef, unsigned int alcanceCampos);
    unsigned int add_function (string nombre, Type* tipo, unsigned int linea, unsigned int columna, vector<Parameter*>* parametros);
    unsigned int add_function (string nombre, Type* tipo, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef, vector<Parameter*>* parametros);
    unsigned int add_tag (string nombre, Categorias categoria, unsigned int linea, unsigned int columna, unsigned int alcance);
    friend std::ostream& operator<<(std::ostream& os, TablaSimbolos &ts);
    unsigned int enter_scope();
    unsigned int exit_scope();
    bool check_scope(string nombre);
    unsigned int get_actual_scope();
    Funcion* get_function(std::string nombre);
    Contenido* find_symbol(std::string nombre, Categorias cat);
    Contenido* find_scope(std::string nombre, Categorias cat, unsigned int alcance);
};
