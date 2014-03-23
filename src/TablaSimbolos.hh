#include <iostream>
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
    unsigned int add_symbol (string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna);
    unsigned int add_symbol (string nombre, Type* tipo, Categorias categoria, unsigned int lineaDec, unsigned int columnaDec, unsigned int lineaDef, unsigned int columnaDef);
    Contenedor* add_container (string nombre, Type* tipo, Categorias categoria, unsigned int linea, unsigned int columna, unsigned int alcanceCampos);
    unsigned int add_function (string nombre, Type* tipo, unsigned int linea, unsigned int columna, vector<Definition*>* parametros, bool definida);
    friend std::ostream& operator<<(std::ostream& os, TablaSimbolos &ts);
    unsigned int enter_scope();
    unsigned int exit_scope();
    bool check_scope(string nombre);
    unsigned int get_actual_scope();
    Contenido* find_symbol(string nombre);
};
