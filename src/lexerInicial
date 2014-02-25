%{
#include<iostream>
#include<fstream>
using namespace std;
int num_linea = 1;
int num_columna = 1;
%}

DIGIT    [0-9]
ID       [a-zA-Z][a-zA-Z0-9\?!_]*


%option noyywrap

%x comentario
%%


"<3".*   { cout << "Comentario " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); };

"--<3"   { cout << "Comentario Bloque " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); BEGIN(comentario); }

<comentario>{
  "<3->"   { cout << "Fin del comentario " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); BEGIN(INITIAL); }
  [^<\n]+  { cout << "Comentario multiple " << YYText() << '\n'; num_columna += YYLeng(); }
  "<"      { cout << "Comentario < " << YYText() << '\n'; num_columna += YYLeng(); }
  \n       { cout << "Salto de linea " << YYText(); num_linea   += 1; num_columna = 1; }
  <<EOF>>  { cout << "Comentario sin terminar :(\n"; yyterminate(); }
}



{DIGIT}+  { cout << "Entero " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }

{DIGIT}+,{DIGIT}*  { cout << "Flotante " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }

{DIGIT}+(,{DIGIT})?e-?{DIGIT}+  { cout << "Notacion Cientifica " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }

'.'|'\\n'   { cout << "Caracter " << YYText() << " " << num_linea << '\n'; num_columna += YYLeng(); }


a_kodiak|a_malayo|a_panda|a_polar|blanco|const|cueva   |
de|entonces|escribir|extinto|fondoBlanco|grizzli      |
hormiguero|kodiak|leer|lon|malayo|mientras|negro|no   |
oso|panda|pardo|polar|vomita|roloePea|si|sino         { cout << "Palabra Reservada " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }


{ID}     { cout << "ID " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }

\"(\\.|[^\\\"])*\"  { cout << "String " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }

"["        { cout << "[ "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"]"        { cout << "] "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"("        { cout << "( "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
")"        { cout << ") "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"{"        { cout << "{ "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"}"        { cout << "} "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"=>"       { cout << "=> " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"="        { cout << "= "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"."        { cout << ". "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
";"        { cout << "; "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
":"        { cout << ": "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"->"       { cout << "-> " << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
","        { cout << ", "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"?"        { cout << "? "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }
"^"        { cout << "^ "  << YYText() << " " << num_linea << " " << num_columna << '\n'; num_columna += YYLeng(); }

"+"|"-"|"*"|"/"|"%"|"++"|"&"|"|"|"<"|">"|"=<"|">="|"=="|"=/="   { cout << "Operador " << YYText() << " " << YYLeng() << " " << num_linea << '\n'; num_columna += YYLeng(); }

[\n]  { num_linea++; num_columna = 1; }

[ \t]+ num_columna += YYLeng();          /* eat up whitespace */

.           { cout << "Caracter no reconocido " << YYText() << " " << YYLeng() << " " << num_linea << '\n'; num_columna += YYLeng(); }

%%

int main( int argc, char** argv )
{
  std::filebuf fb;
  fb.open (argv[1],std::ios::in);
  std::istream input(&fb);
  FlexLexer* lexer = new yyFlexLexer(&input);
  while(lexer->yylex() != 0)
          ;
  return 0;
}
