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
int num_linea = 1;
int num_columna = 1;

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

{DIGIT}+  { printf("Entero: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_CONSTPOLAR(yytext, loc); }

{DIGIT}+,{DIGIT}*  { printf("Flotante: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_CONSTKODIAK(yytext, loc); }

{DIGIT}+(,{DIGIT})?e-?{DIGIT}+  { printf("Flotante: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_CONSTKODIAK(yytext, loc);}

'.'|'\\n'   { printf("Caracter: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_CONSTMALAYO(yytext, loc);}

\"(\\.|[^\\\"])*\"  { printf("String: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_CONSTHORMIGUERO(yytext, loc); }

blanco { printf("palabra reservada: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_BLANCO(yytext, loc); }
negro  { printf("palabra reservada: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_NEGRO(yytext, loc); }

{ID}   { printf("identificador: %s %d %d\n", yytext, num_linea, num_columna); num_columna += yyleng; return yy::bear_parser::make_ID(yytext, loc); }

[\n]  { num_linea++; num_columna = 1; }

[ \t] { num_columna += yyleng; }

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
