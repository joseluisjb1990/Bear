#ifndef CALCXX_DRIVER_HH
# define CALCXX_DRIVER_HH
# include <string>
# include <map>
# include "bear_parser.tab.hh"
# include "TablaSimbolos.hh"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
  yy::bear_parser::symbol_type yylex (bear_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Calc++.
class bear_driver
{
public:
  bear_driver ();
  virtual ~bear_driver ();

  TablaSimbolos tabla;
  int errores = 0;
  std::vector<Statement*>* AST;

  int result;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;

  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  // Whether parser traces should be generated.
  bool trace_parsing;

  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const yy::location& l1, const yy::location& l2, const std::string& m);
  void error (const std::string& m);
  void agregarConInicializacion(std::vector<elementoLista>* ids, Categorias categoria, Type* tipo);
  void agregarSinInicializacion(std::vector<elementoLista>* ids, Categorias categoria, Type* tipo);
};
#endif // ! CALCXX_DRIVER_HH
