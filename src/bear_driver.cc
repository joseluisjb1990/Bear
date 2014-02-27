#line 11104 "./doc/bison.texi"
#include "bear_driver.hh"
#include "bear_parser.tab.hh"

bear_driver::bear_driver ()
  : trace_scanning (false), trace_parsing (false)
{
  variables["one"] = 1;
  variables["two"] = 2;
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
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

void
bear_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void
bear_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
