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
  //cout << tabla;
  scan_end ();
  return res;
}

void
bear_driver::error (const yy::location& l, const std::string& m)
{
  ++errores;
  std::cerr << "Error entre " << l.begin.line << "." << l.begin.column << " y " << l.end.line << "." << l.end.column << ": " << m << std::endl;
}

void
bear_driver::error (const std::string& m)
{
  ++errores;
  std::cerr << m << std::endl;
}
