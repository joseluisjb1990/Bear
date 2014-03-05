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
  PUNTO             "."
  FLECHA            "->"
  TECHO             "^"
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
%token <std::string> PARDO
%token <std::string> GRIZZLI
%token <std::string> LEER
%token <std::string> ESCRIBIR
%token <std::string> SI
%token <std::string> ENTONCES
%token <std::string> SINO
%token <std::string> PARA
%token <std::string> EN
%type  <std::string> Programa
%type  <std::string> Expresion
%type  <std::string> Expresiones
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
%type  <std::string> DefCompleja
%type  <std::string> DefFuncion
%type  <std::string> Cuevas
%type  <std::string> Identificadores
%type  <std::string> Tipo
%type  <std::string> Campos
%type  <std::string> DefParametros
%type  <std::string> DefParametro
%type  <std::string> ParametroCueva
%type  <std::string> AccesoCueva

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
                | DefFuncion    { $$ = $1; }
                ;

DefFuncion: ID "(" DefParametros ")" "=>" Tipo                       { $$ = "Nombre: " + $1 + "\nParametros:\n" + $3 + "\nRetorna: " + $6;                             }
          | ID "(" DefParametros ")" "=>" Tipo "{" Instrucciones "}" { $$ = "Nombre: " + $1 + "\nParametros:\n" + $3 + "\nRetorna: " + $6 + "\nInstrucciones:\n" + $8; }
          ;

DefParametros: DefParametro                   { $$ = $1;              }
             | DefParametros "," DefParametro { $$ = $1 + ",\n" + $3; }
             ;

DefParametro: Tipo ID                  { $$ = "Tipo: " + $1 + " Nombre: " + $2;      }
            | "^" Tipo ID              { $$ = "Tipo: ^" + $2 + " Nombre: " + $3;     }
            | ParametroCueva Tipo ID   { $$ = "Tipo: " + $1 + $2 + " Nombre: " + $3; }
            ;

ParametroCueva: CUEVA "[" "]" DE                           { $$ = $1 + " [] " + $4 + " ";                }
              | ParametroCueva CUEVA "[" CONSTPOLAR "]" DE { $$ = $1 + $2 + " [" + $4 + "] " + $6 + " "; }
              ;

DefConstante: CONST Tipo ID "=" Expresion { $$ = "Declaración de constante:\nTipo: " + $2 + ". Nombre: " + $3 + ". Valor: " + $5; }
            ;

DefVariable: Tipo Identificadores "=" Expresiones { $$ = "Declaración de variable con inicialización:\nTipo: " + $1 + ".\nIdentificadores: " + $2 + ".\nExpresiones: " + $4; }
           | Tipo Identificadores                 { $$ = "Declaración de variable sin inicialización:\nTipo: " + $1 + ".\nIdentificadores: " + $2;                           }
           | DefCueva                             { $$ = "Declaración de cueva:\n" + $1;                                                                                     }
           | DefCompleja                          { $$ = "Declaración compleja:\n" + $1;                                                                                     }
           ;

Identificadores: ID                     { $$ = $1;             }
               | Identificadores "," ID { $$ = $1 + ", " + $3; }
               ;

DefCueva: Cuevas Tipo ID { $$ = $1 + $2 + ". Nombre: " + $3; }
        ;

Cuevas: CUEVA "[" CONSTPOLAR "]" DE          { $$ = $1 + " [" + $3 + "] " + $5 + " ";      }
       |  Cuevas CUEVA "[" CONSTPOLAR "]" DE { $$ = $1 + $2 + " [" + $4 + "] " + $6 + " "; }
       ;


DefCompleja: PARDO   ID "{" Campos "}" { $$ = "Pardo:\nNombre: " + $2 + "\nCampos:\n" + $4;   }
           | GRIZZLI ID "{" Campos "}" { $$ = "Grizzli:\nNombre: " + $2 + "\nCampos:\n" + $4; }
           ;

Campos: Tipo ID ";"        { $$ = "Tipo: " + $1 + " Nombre: " + $2 + ";\n";      }
      | Campos Tipo ID ";" { $$ = $1 + "Tipo: " + $2 + " Nombre: " + $3 + ";\n"; }
      ;

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

Instruccion: LValues "=" Expresiones                                                        { $$ = "Asignación:\nl-values: " + $1 + ".\n" + "r-values:  " + $3;                                                                                  }
           | LEER "(" ID ")"                                                                { $$ = "Leer: variable: " + $3;                                                                                                                      }
           | ESCRIBIR "(" Expresion ")"                                                     { $$ = "Escribir: valor: " + $3;                                                                                                                     }
/*           | Funcion       */
           | SI Expresion ENTONCES "{" Instrucciones "}"                                    { $$ = "Condicional sin else:\nCondición: " + $2 + "\nInstrucciones: " + $5;                                                                         }
           | SI Expresion ENTONCES "{" Instrucciones "}" SINO "{" Instrucciones "}"         { $$ = "Condicional con else:\nCondición: " + $2 + "\nBrazo true:\n" + $5 + "\nBrazo false:\n" + $9;                                                 }
           | PARA ID EN "(" Expresion "," Expresion ")" "{" Instrucciones "}"               { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nDesde: " + $5 + "\nHasta:\n" + $7 + "\nInstrucciones:\n" + $10;                       }
           | PARA ID EN "(" Expresion "," Expresion "," Expresion ")" "{" Instrucciones "}" { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nDesde: " + $5 + "\nHasta:\n" + $9 + "\nCon Paso: " + $7 + "\nInstrucciones:\n" + $12; }
           | PARA ID EN ID "{" Instrucciones "}"                                            { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nArreglo sobre el cual iterar: " + $4 + "\nInstrucciones:\n" + $6;                     }
           ;



/*
Instruccion -> ListaLValues '=' Expresiones
            |  'leer' '(' ID ')'
            |  'escribir' '(' Expresion ')'
            |  Funcion
            |  'si' ExpresionBooleana 'entonces' '{' ListaInstrucciones '}'
            |  'si' ExpresionBooleana 'entonces' '{' ListaInstrucciones '}' sino '{' ListaInstrucciones '}'
            |  'para' ID 'en' '(' Expresion ',' Expresion ')' '{' ListaInstrucciones '}'
            |  'para' ID 'en' '(' Expresion ',' Expresion ',' Expresion ')' '{' ListaInstrucciones '}'
            |  'para' ID 'en' ID '{' ListaInstrucciones '}'
            |  IteracionIndeterminada
            |  ID '++'
            |  ID '--'
            |  'vomita'
            |  'vomita' ID
            |  'fondoBlanco'
            |  'fondoBlanco' ID
            |  'roloePea'
            |  'roloePea' ID
*/


LValues: LValue             { $$ = $1;             }
       | LValues "," LValue { $$ = $1 + ", " + $3; }
       ;

%left "->" ".";
LValue: ID                 { $$ = $1;             }
      | LValue "->" LValue { $$ = $1 + "->" + $3; }
      | LValue "."  LValue { $$ = $1 + "."  + $3; }
      | AccesoCueva        { $$ = $1;             }
      ;

AccesoCueva: ID "[" CONSTPOLAR "]"          { $$ = $1 + "[" + $3 + "]"; }
           | AccesoCueva "[" CONSTPOLAR "]" { $$ = $1 + "[" + $3 + "]"; }
           ;


Expresiones: Expresion                 { $$ = $1 ;            }
           | Expresiones "," Expresion { $$ = $1 + ", " + $3; }
           ;

Expresion: CONSTPOLAR                                    { $$ = $1;                                                                            }
         | CONSTKODIAK                                   { $$ = $1;                                                                            }
         | CONSTHORMIGUERO                               { $$ = $1;                                                                            }
         | CONSTMALAYO                                   { $$ = $1;                                                                            }
         | LValue                                        { $$ = $1;                                                                            }
/*         | Funcion                                       { $$ = $1;                                                                            }
         | FuncionPredef                                 { $$ = $1;                                                                            }*/
         | BLANCO                                        { $$ = $1;                                                                            }
         | NEGRO                                         { $$ = $1;                                                                            }
         | Expresion   "<"   Expresion                   { $$ = $1 + "<" + $3;                                                                 }
         | Expresion   "=<"  Expresion                   { $$ = $1 + "=<" + $3;                                                                }
         | Expresion   ">"   Expresion                   { $$ = $1 + ">" + $3;                                                                 }
         | Expresion   ">="  Expresion                   { $$ = $1 + ">=" + $3;                                                                }
         | Expresion   "=="  Expresion                   { $$ = $1 + "==" + $3;                                                                }
         | Expresion   "=/=" Expresion                   { $$ = $1 + "=/=" + $3;                                                               }
         | Expresion   "|"   Expresion                   { $$ = $1 + "|" + $3;                                                                 }
         | Expresion   "&"   Expresion                   { $$ = $1 + "&" + $3;                                                                 }
         | "no" Expresion                                { $$ = "no " + $2;                                                                    }
         | Expresion "+"  Expresion                      { $$ = $1 + "+" + $3;                                                                 }
         | Expresion "-"  Expresion                      { $$ = $1 + "-" + $3;                                                                 }
         | Expresion "**" Expresion                      { $$ = $1 + "**" + $3;                                                                }
         | Expresion "*"  Expresion                      { $$ = $1 + "*" + $3;                                                                 }
         | Expresion "/"  Expresion                      { $$ = $1 + "/" + $3;                                                                 }
         | "-" Expresion %prec UNARIO                    { $$ = "-" + $2;                                                                      }
         | "(" Expresion ")"                             { $$ = "(" + $2 + ")";                                                                }
/*         | Expresion "?" Expresion ":" Expresion { $$ = "Condición: " + $1 + "\nCondición cierta: " + $3 + "\nCondición falsa: " + $5; }*/
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


%%

void
yy::bear_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
