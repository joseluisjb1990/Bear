%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {MC}
%define parser_class_name {MC_Parser}

%code requires{
   namespace MC {
      class MC_Driver;
      class MC_Scanner;
   }
}

%lex-param   { MC_Scanner  &scanner  }
%parse-param { MC_Scanner  &scanner  }

%lex-param   { MC_Driver  &driver  }
%parse-param { MC_Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <cstdio>
   #include <string>
   #include <fstream>

   /* include for all driver functions */
   #include "mc_driver.hpp"

   /* this is silly, but I can't figure out a way around */
   static int yylex(MC::MC_Parser::semantic_type *yylval,
                    MC::MC_Scanner  &scanner,
                    MC::MC_Driver   &driver);

}

/* token types */
/*
%union {
   std::string *sval;
}

%token            END    0     "end of file"
%token            UPPER
%token            LOWER
%token   <sval>   WORD
%token            NEWLINE
%token            CHAR

*/

%token END    0     "end of file"

// Token identificador (de variable, función o box)
%token ID

// Token de un char cualquiera
%token CONSTMALAYO

// Token de un string cualquiera encerrado entre comillas
// No confundirse con TK_STRING que se refiere a la palabra reservada 'string'
%token CONSTHORMIGUERO

// Tokens de constantes numéricas
%token CONSTPOLAR
%token CONSTKODIAK

// Tokens de constantes booleanas
%token BLANCO
%token NEGRO

/* destructor rule for <sval> objects */
%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <sval>


%%
/*
list_option : END | list END;

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( *$1 ); }
  | NEWLINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;
*/

Programa : Expresiones
         ;

Expresiones: Expresion
           | Expresiones Expresion
           ;

Expresion : CONSTPOLAR      { std::cout << "Constante Polar \n"     ; }
          | CONSTKODIAK     { std::cout << "Constante Kodiak \n"    ; }
          | CONSTHORMIGUERO { std::cout << "Constante Hormiguero \n"; }
          | CONSTMALAYO     { std::cout << "Constante Malayo \n"    ; }
          | ID              { std::cout << "Constante ID \n"        ; }
          | BLANCO          { std::cout << "Constante Blanco \n"    ; }
          | NEGRO           { std::cout << "Constante Negro \n"     ; }
          ;

%%


void
MC::MC_Parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n";
}


/* include for access to scanner.yylex */
#include "mc_scanner.hpp"
static int
yylex( MC::MC_Parser::semantic_type *yylval,
       MC::MC_Scanner  &scanner,
       MC::MC_Driver   &driver )
{
   return( scanner.yylex(yylval) );
}
