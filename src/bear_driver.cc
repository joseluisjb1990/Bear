#include "bear_driver.hh"
#include "bear_parser.tab.hh"

bear_driver::bear_driver ()
  : trace_scanning (false), trace_parsing (false)
{
}

bear_driver::~bear_driver ()
{
}

int
bear_driver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::bear_parser parser (*this);
  //parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  if (0 == errores) {
    for (unsigned int i=0; i < AST->size(); ++i) {
      cout << AST->at(i)->to_string() << std::endl;
    }
    cout << tabla;
  }

  scan_end();
  return res;
}

void
bear_driver::error (const yy::location& l, const std::string& m)
{
  ++errores;
  std::cerr << "Error entre " << l.begin.line << "." << l.begin.column << " y " << l.end.line << "." << l.end.column << ": " << m << std::endl;
}

void
bear_driver::error (const yy::location& l1, const yy::location& l2, const std::string& m)
{
  ++errores;
  std::cerr << "Error entre " << l1.begin.line << "." << l1.begin.column << " y " << l2.end.line << "." << l2.end.column << ": " << m << std::endl;
}

void
bear_driver::error (const std::string& m)
{
  ++errores;
  std::cerr << m << std::endl;
}

void bear_driver::agregarConInicializacion(std::vector<elementoLista>* ids, Categorias categoria, Type* tipo)
{
  elementoLista e;
  for (unsigned int i = 0; i < ids->size(); ++i)
  {
    cout << i << '\n';

    e = ids->at(i);
    tabla.add_symbol(e.nombre, tipo, categoria, e.linea, e.columna, e.linea, e.columna);
  }
}

void bear_driver::agregarSinInicializacion(std::vector<elementoLista>* ids, Categorias categoria, Type* tipo)
{
  elementoLista e;
  for (unsigned int i = 0; i < ids->size(); ++i)
  {
    e = ids->at(i);
    tabla.add_symbol(e.nombre, tipo, categoria, e.linea, e.columna);
  }
}

