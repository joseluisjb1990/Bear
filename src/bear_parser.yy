#line 11154 "./doc/bison.texi"
%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {bear_parser}
#line 11170 "./doc/bison.texi"
%define api.token.constructor
%define api.value.type variant
%define parse.assert
#line 11187 "./doc/bison.texi"
%code requires
{
# include <string>
class bear_driver;
}
#line 11201 "./doc/bison.texi"
// The parsing context.
%param { bear_driver& driver }
#line 11213 "./doc/bison.texi"
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
#line 11228 "./doc/bison.texi"
%define parse.trace
%define parse.error verbose
#line 11239 "./doc/bison.texi"
%code
{
# include "bear_driver.hh"
}
#line 11255 "./doc/bison.texi"
%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
/*
  ASSIGN  ":="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
*/
;
#line 11275 "./doc/bison.texi"
%token <std::string> ID
%token <std::string> CONSTPOLAR
%token <std::string> CONSTKODIAK
%token <std::string> CONSTHORMIGUERO
%token <std::string> CONSTMALAYO
%token <std::string> BLANCO
%token <std::string> NEGRO
%type  <std::string> Programa
%type  <std::string> Expresiones
%type  <std::string> Expresion
#line 11288 "./doc/bison.texi"
/* %printer { yyoutput << $$; } <*>; */
#line 11297 "./doc/bison.texi"
%%
%start Programa;

Programa: Expresiones       { $$ = $1; std::cout << $$; }
        ;

Expresiones: Expresion             { $$ = $1; }
           | Expresiones Expresion { $$ = std::string($1) + $2; }
           ;

Expresion: ID               { $$ = $1; std::cout << $$ << "\n"; }
         | CONSTPOLAR       { $$ = $1; std::cout << $$ << "\n"; }
         | CONSTKODIAK      { $$ = $1; std::cout << $$ << "\n"; }
         | CONSTHORMIGUERO  { $$ = $1; std::cout << $$ << "\n"; }
         | CONSTMALAYO      { $$ = $1; std::cout << $$ << "\n"; }
         | BLANCO           { $$ = $1; std::cout << $$ << "\n"; }
         | NEGRO            { $$ = $1; std::cout << $$ << "\n"; }
         ;

/*
unit: assignments exp  { driver.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" ":=" exp { driver.variables[$1] = $3; };

%left "+" "-";
%left "*" "/";
exp:
  exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { std::swap ($$, $2); }
| "identifier"  { $$ = driver.variables[$1]; }
| "number"      { std::swap ($$, $1); };
*/

%%
#line 11327 "./doc/bison.texi"
void
yy::bear_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
