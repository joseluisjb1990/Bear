#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include "Contenido.hh"

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
    unsigned int add_symbol (string nombre, Tipos tipo, Categorias categoria, unsigned int linea, unsigned int columna);
    unsigned int add_container (string nombre, Tipos tipo, Categorias categoria, unsigned int linea, unsigned int columna, unsigned int alcanceCampos);
    friend std::ostream& operator<<(std::ostream& os, TablaSimbolos &ts);
    unsigned int enter_scope();
    unsigned int exit_scope();
    bool check_scope(string nombre);
    Contenido* find_symbol(string nombre);
};
