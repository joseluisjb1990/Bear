%{
/* C++ string header, for string ops below */
#include <string>
/* Implementation of yyFlexScanner */
#include "mc_scanner.hpp"

/* typedef to make the returns for the tokens shorter */
typedef MC::MC_Parser::token token;

/* define to keep from re-typing the same code over and over */
#define STOKEN( x ) ( new std::string( x ) )

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

//////////////////////////////////////////////////////////
#include<iostream>
#include<fstream>
using namespace std;
int num_linea = 1;
int num_columna = 1;
%}

%option debug
%option nodefault
%option yyclass="MC_Scanner"
%option noyywrap
%option c++

/**/
DIGIT    [0-9]
ID       [a-zA-Z][a-zA-Z0-9\?!_]*

%x comentario

%%
{DIGIT}+  { cout << "Entero " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); return (token::CONSTPOLAR); }

{DIGIT}+,{DIGIT}*  { cout << "Flotante " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); return (token::CONSTKODIAK);}

{DIGIT}+(,{DIGIT})?e-?{DIGIT}+  { cout << "Notacion Cientifica " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); return (token::CONSTKODIAK);}

'.'|'\\n'   { cout << "Caracter " << YYText() << " " << num_linea << '\n'; num_columna += YYLeng(); return (token::CONSTMALAYO);}

\"(\\.|[^\\\"])*\"  { cout << "String " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); return (token::CONSTHORMIGUERO); }

blanco { return (token::BLANCO); }
negro  { return (token::NEGRO);  }

{ID}     { cout << "ID " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); return (token::ID); }

[\n]  { num_linea++; num_columna = 1; }

%%
