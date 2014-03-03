%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {bear_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
# include <string>
class bear_driver;
}
// The parsing context.
%param { bear_driver& driver }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
# include "bear_driver.hh"
}
%define api.token.prefix {TOK_}
%token
  END  0            "fin del programa"
  MENOS             "-"
  SUMA              "+"
  MULTIPLICACION    "*"
  POTENCIA          "**"
  DIVISION          "/"
  MENOR             "<"
  MENORIGUAL        "=<"
  MAYOR             ">"
  MAYORIGUAL        ">="
  IGUALDAD          "=="
  DIFERENCIA        "=/="
  CIERRAPARENTESIS  ")"
  ABREPARENTESIS    "("
  CIERRALLAVE       "}"
  ABRELLAVE         "{"
  CIERRACORCHETE    "]"
  ABRECORCHETE      "["
  DOSPUNTOS         ":"
  INTERROGACION     "?"
  MODULO            "%"
  AND               "&"
  OR                "|"
  NO                "no"
  PUNTOCOMA         ";"
  ASIGNACION        "="
  OSO               "oso"
  FLECHARETORNO     "=>"
  COMA              ","
;

%token <std::string> ID
%token <std::string> CONSTPOLAR
%token <std::string> CONSTKODIAK
%token <std::string> CONSTHORMIGUERO
%token <std::string> CONSTMALAYO
%token <std::string> BLANCO
%token <std::string> NEGRO
%token <std::string> PANDA
%token <std::string> POLAR
%token <std::string> KODIAK
%token <std::string> MALAYO
%token <std::string> HORMIGUERO
%token <std::string> EXTINTO
%token <std::string> CONST
%token <std::string> CUEVA
%token <std::string> DE
%type  <std::string> Programa
%type  <std::string> Expresion
%type  <std::string> Expresiones
%type  <std::string> ExpresionBooleana
%type  <std::string> ExpresionAritmetica
%type  <std::string> Instrucciones
%type  <std::string> Instruccion
%type  <std::string> LValue
%type  <std::string> LValues
%type  <std::string> Definiciones
%type  <std::string> ListaDefGlobales
%type  <std::string> DefinicionGlobal
%type  <std::string> DefConstante
%type  <std::string> DefVariable
%type  <std::string> DefCueva
%type  <std::string> Cuevas
%type  <std::string> Identificadores
%type  <std::string> Tipo

/* %printer { yyoutput << $$; } <*>; */

%%
%start Programa;

Programa: Definiciones "oso" "(" ")" "=>" EXTINTO "{" Instrucciones "}" { $$ = $1 + $8; std::cout << $1 << "Funcion principal oso:" << std::endl << $8; }
        ;

Definiciones: %empty /* Vacio */
            | ListaDefGlobales   { $$ = "Definiciones:\n" + $1; }
            ;

ListaDefGlobales: DefinicionGlobal ";"                  { $$ = $1 + ";\n";      }
                | ListaDefGlobales DefinicionGlobal ";" { $$ = $1 + $2 + ";\n"; }
                ;

DefinicionGlobal: DefConstante  { $$ = $1; }
                | DefVariable   { $$ = $1; }
/*                | DefFuncion*/
                ;

DefConstante: CONST Tipo ID "=" Expresion { $$ = "Declaración de constante:\nTipo: " + $2 + ". Nombre: " + $3 + ". Valor: " + $5; }
            ;

DefVariable: Tipo Identificadores "=" Expresiones { $$ = "Declaración de variable con inicialización:\nTipo: " + $1 + ".\nIdentificadores: " + $2 + ".\nExpresiones: " + $4; }
           | Tipo Identificadores                 { $$ = "Declaración de variable sin inicialización:\nTipo: " + $1 + ".\nIdentificadores: " + $2;                           }
           | DefCueva                             { $$ = "Declaración de cueva:\n" + $1;                                                                                     }
/*           | DefCompleja*/
           ;

Identificadores: ID                     { $$ = $1;             }
               | Identificadores "," ID { $$ = $1 + ", " + $3; }
               ;

DefCueva: Cuevas Tipo ID { $$ = $1 + $2 + ". Nombre: " + $3; }
        ;

Cuevas: CUEVA "[" CONSTPOLAR "]" DE          { $$ = $1 + " [" + $3 + "] " + $5 + " ";      }
       |  Cuevas CUEVA "[" CONSTPOLAR "]" DE { $$ = $1 + $2 + " [" + $4 + "] " + $6 + " "; }
       ;

/*
DefCompleja -> 'pardo'   ID '{' Campos '}'
            |  'grizzli' ID '{' Campos '}'

Campos -> Tipo ID ';'
       |  Campos Tipo ID ';'
*/

Tipo: ID          { $$ = $1; }
    | PANDA       { $$ = $1; }
    | POLAR       { $$ = $1; }
    | KODIAK      { $$ = $1; }
    | MALAYO      { $$ = $1; }
    | HORMIGUERO  { $$ = $1; }
    | EXTINTO     { $$ = $1; }
    ;

Instrucciones: Instruccion ";"               { $$ = $1 + ";\n";      }
             | Instrucciones Instruccion ";" { $$ = $1 + $2 + ";\n"; }
             ;

/* Aqui hay el problema de que hay que asegurar que la cantidad de lvalues y de expresiones sea la misma, no tengo manera de hacerlo ahorita */

Instruccion: LValues "=" Expresiones { $$ = "Asignación:\nl-values: " + $1 + "\n" + ". r-values:  " + $3; }
           ;

LValues: LValue             { $$ = $1;             }
       | LValues "," LValue { $$ = $1 + ", " + $3; }
       ;

LValue: ID { $$ = $1; }
      ;

Expresiones: Expresion                 { $$ = $1 ;            }
           | Expresiones "," Expresion { $$ = $1 + ", " + $3; }
           ;

Expresion: CONSTPOLAR           { $$ = $1;             }
         | CONSTKODIAK          { $$ = $1;             }
         | CONSTHORMIGUERO      { $$ = $1;             }
         | CONSTMALAYO          { $$ = $1;             }
         | LValue               { $$ = $1;             }
         | ExpresionBooleana    { $$ = $1;             }
         | ExpresionAritmetica  { $$ = $1;             }
         | "(" Expresion ")"    { $$ = "(" + $2 + ")"; }
         ;

%left "==" "=/=";
%nonassoc "<" "=<" ">" ">=";
%left "+" "-";
%left "*" "/";
%left "&";
%left "|";
%nonassoc "no";
%nonassoc UNARIO;
%right "**";
ExpresionBooleana: BLANCO                      { $$ = $1;              }
                 | NEGRO                       { $$ = $1;              }
                 | Expresion   "<"   Expresion { $$ = $1 + "<" + $3;   }
                 | Expresion   "=<"  Expresion { $$ = $1 + "=<" + $3;  }
                 | Expresion   ">"   Expresion { $$ = $1 + ">" + $3;   }
                 | Expresion   ">="  Expresion { $$ = $1 + ">=" + $3;  }
                 | Expresion   "=="  Expresion { $$ = $1 + "==" + $3;  }
                 | Expresion   "=/=" Expresion { $$ = $1 + "=/=" + $3; }
                 | Expresion   "|"   Expresion { $$ = $1 + "|" + $3;   }
                 | Expresion   "&"   Expresion { $$ = $1 + "&" + $3;   }
                 | "no" Expresion              { $$ = "no " + $2;      }
                 ;

ExpresionAritmetica: Expresion "+"  Expresion       { $$ = $1 + "+" + $3;  }
                   | Expresion "-"  Expresion       { $$ = $1 + "-" + $3;  }
                   | Expresion "**" Expresion       { $$ = $1 + "**" + $3; }
                   | Expresion "*"  Expresion       { $$ = $1 + "*" + $3;  }
                   | Expresion "/"  Expresion       { $$ = $1 + "/" + $3;  }
                   | "-" Expresion %prec UNARIO     { $$ = "-" + $2;       }
                   ;

%%

void
yy::bear_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
