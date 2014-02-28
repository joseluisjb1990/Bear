%{ /* -*- C++ -*- */
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include "bear_driver.hh"
#include "bear_parser.tab.hh"

using namespace std;

# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;
%}
%option noyywrap nounput batch debug noinput
/*
id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t]
*/
DIGIT    [0-9]
ID       [a-zA-Z][a-zA-Z0-9\?!_]*

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}


%%

%{
  // Code run each time yylex is called.
  loc.step ();
%}

{DIGIT}+  { return yy::bear_parser::make_CONSTPOLAR(yytext, loc); }

{DIGIT}+,{DIGIT}*  { return yy::bear_parser::make_CONSTKODIAK(yytext, loc); }

{DIGIT}+(,{DIGIT})?e-?{DIGIT}+  { return yy::bear_parser::make_CONSTKODIAK(yytext, loc);}

'.'|'\\n'   { return yy::bear_parser::make_CONSTMALAYO(yytext, loc);}

\"(\\.|[^\\\"])*\"  { return yy::bear_parser::make_CONSTHORMIGUERO(yytext, loc); }

blanco { return yy::bear_parser::make_BLANCO(yytext, loc); }
negro  { return yy::bear_parser::make_NEGRO(yytext, loc); }
no  { return yy::bear_parser::make_NO(loc); }

{ID}   { return yy::bear_parser::make_ID(yytext, loc); }

[\n]  { loc.lines(1); loc.step (); }

[ \t]+ { loc.step (); }


"("   { return yy::bear_parser::make_PARENTESISI(loc); }
")"   { return yy::bear_parser::make_PARENTESISD(loc); }
":"   { return yy::bear_parser::make_DOSPUNTOS(loc); }
"?"   { return yy::bear_parser::make_INTERROGACION(loc); }
"+"   { return yy::bear_parser::make_SUMA(loc); }
"-"   { return yy::bear_parser::make_MENOS(loc); }
"*"   { return yy::bear_parser::make_MULTIPLICACION(loc); }
"**"  { return yy::bear_parser::make_POTENCIA(loc); }
"/"   { return yy::bear_parser::make_DIVISION(loc); }
"%"   { return yy::bear_parser::make_MODULO(loc); }
"&"   { return yy::bear_parser::make_AND(loc); }
"|"   { return yy::bear_parser::make_OR(loc); }
"<"   { return yy::bear_parser::make_MENOR(loc); }
">"   { return yy::bear_parser::make_MAYOR(loc); }
"=<"  { return yy::bear_parser::make_MENORIGUAL(loc); }
">="  { return yy::bear_parser::make_MAYORIGUAL(loc); }
"=="  { return yy::bear_parser::make_IGUALDAD(loc); }
"=/=" { return yy::bear_parser::make_DIFERENCIA(loc); }
";"   { return yy::bear_parser::make_PUNTOCOMA(loc); }


<<EOF>>    return yy::bear_parser::make_END(loc);
%%

void
bear_driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}



void
bear_driver::scan_end ()
{
  fclose (yyin);
}
