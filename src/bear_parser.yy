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
# include <vector>
# include "expresion.hh"
# include "statement.hh"
# include "definition.hh"
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
  DECREMENTO        "--"
  SUMA              "+"
  INCREMENTO        "++"
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
%token <std::string> VOMITA
%token <std::string> FONDOBLANCO
%token <std::string> ROLOEPEA
%token <std::string> APOLAR
%token <std::string> APANDA
%token <std::string> AKODIAK
%token <std::string> AMALAYO
%token <std::string> LON
%token <std::string> MIENTRAS
%type  <std::vector<Statement*>*> Programa
%type  <Expression*> Expresion
%type  <std::vector<Expression*>*> Expresiones
%type  <std::vector<Statement*>*> Instrucciones
%type  <Statement*> Instruccion
%type  <LValueExpr*> LValue
%type  <std::vector<Expression*>*> LValues
%type  <std::string> Definiciones
%type  <std::string> ListaDefGlobales
%type  <std::string> DefinicionGlobal
%type  <ConstDef*>   DefConstante
%type  <std::string> Locales
%type  <std::string> DefVariable
%type  <std::string> DefCueva
%type  <std::string> DefCompleja
%type  <std::string> DefFuncion
%type  <std::string> DefLocales
%type  <std::string> Cuevas
%type  <std::vector<std::string>*> Identificadores
%type  <std::string> Tipo
%type  <std::string> Campos
%type  <std::string> DefParametros
%type  <std::string> DefParametro
%type  <std::string> ParametroCueva
%type  <CuevaExpr*>  AccesoCueva
%type  <std::string> FuncionPredef
%type  <std::string> Funcion
%type  <std::string> Cuerpo
%type  <std::string> IteracionIndeterminada

/* %printer { yyoutput << $$; } <*>; */

%%
%start Programa;

Programa : DefConstante Instrucciones { $$ = $2; driver.AST = $$; }
/*
Programa: Definiciones "oso" "(" ")" "=>" EXTINTO "{" Cuerpo "}" { $$ = $1 + $8; std::cout << $1 << "Funcion principal oso:" << std::endl << $8; }
        ;

Definiciones:
            | ListaDefGlobales   { $$ = "Definiciones:\n" + $1; }
            ;

ListaDefGlobales: DefinicionGlobal ";"                  { $$ = $1 + ";\n";      }
                | ListaDefGlobales DefinicionGlobal ";" { $$ = $1 + $2 + ";\n"; }
                ;

DefinicionGlobal: DefConstante  { $$ = $1;                             }
                | DefVariable   { $$ = $1;                             }
                | DefFuncion    { $$ = $1;                             }
                | DefCompleja   { $$ = "Declaración compleja:\n" + $1; }
                ;

DefFuncion: ID "(" DefParametros ")" "=>" Tipo                       { $$ = "Nombre: " + $1 + "\nParametros:\n" + $3 + "\nRetorna: " + $6;      }
          | ID "(" DefParametros ")" "=>" Tipo "{" Cuerpo "}"        { $$ = "Nombre: " + $1 + "\nParametros:\n" + $3 + "\nRetorna: " + $6 + $8; }
          ;

Cuerpo: Locales Instrucciones { $$ = "\nDeclaraciones Locales:\n" + $1 + "\nInstrucciones:\n" + $2; }
      | Instrucciones         { $$ = "\nInstrucciones:\n" + $1;                                     }
      ;

Locales: Locales DefLocales ";"  { $$ = "\nDeclaracion de variables locales a una funcion:\n" + $1; }
       | DefLocales ";" { $$ = $1; }
       ;

DefLocales: DefVariable  { $$ = $1; }
          | DefConstante { $$ = $1; }
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
*/

DefConstante: CONST Tipo Identificadores "=" Expresiones { $$ = new ConstDef($2, $3, $5); }
            ;

/*

DefVariable: Tipo Identificadores "=" Expresiones {
                                                    if ($2->size() == $4->size()) {
                                                      for (unsigned int i=0; i < $2->size(); ++i) {
                                                        driver.tabla.add_symbol($2->at(i).nombre, $1, Var, $2->at(i).linea, $2->at(i).columna);
                                                      }
                                                    }
                                                    $$ = "Declaración de variable con inicialización:\nTipo: " + $1 + ".\nIdentificadores: " + ".\nExpresiones: ";
                                                  }
           | Tipo Identificadores                 { $$ = "Declaración de variable sin inicialización:\nTipo: " + $1 + ".\nIdentificadores: "; }
           | DefCueva                             { $$ = "Declaración de cueva:\n" + $1;                                                      }
           ;

*/

Identificadores: ID                     { $$ = new std::vector<std::string>(); $$->push_back($1); }
               | Identificadores "," ID { $$ = $1; $$->push_back($3); }
               ;

/*

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

*/

Tipo: ID          { $$ = $1; }
    | PANDA       { $$ = $1; }
    | POLAR       { $$ = $1; }
    | KODIAK      { $$ = $1; }
    | MALAYO      { $$ = $1; }
    | HORMIGUERO  { $$ = $1; }
    | EXTINTO     { $$ = $1; }
    ;

Instrucciones: Instruccion               { $$ = new std::vector<Statement*>(); $$->push_back($1); }
             | Instrucciones Instruccion { $$ = $1; $$->push_back($2);                            }
             | error                     { yyerrok;                                               }
             ;

Instruccion: LValues "=" Expresiones ";"                                                    { $$ = new Assign($1, $3);                                                                                                                                     }
/*           | LEER "(" ID ")" ";"                                                            { $$ = "Leer: variable: " + $3 + ";";                                                                                                                }
           | ESCRIBIR "(" Expresion ")" ";"                                                 { $$ = "Escribir: valor: " + $3 + ";";                                                                                                               }
           | Funcion ";"                                                                    { $$ = "Funcion:\n" + $1 + ";";                                                                                                                      }*/
           | SI Expresion ENTONCES "{" Instrucciones "}"                                    { $$ = new If($2, $5);                                                                                                                               }
           | SI Expresion ENTONCES "{" Instrucciones "}" SINO "{" Instrucciones "}"         { $$ = new IfElse($2, $5, $9);                                                                                                                       }
/*           | PARA ID EN "(" Expresion ";" Expresion ")" "{" Cuerpo "}"                      { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nDesde: " + $5 + "\nHasta:\n" + $7 + "\nInstrucciones:\n" + $10;                       }
           | PARA ID EN "(" Expresion ";" Expresion ";" Expresion ")" "{" Cuerpo "}"        { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nDesde: " + $5 + "\nHasta:\n" + $9 + "\nCon Paso: " + $7 + "\nInstrucciones:\n" + $12; }
           | PARA ID EN ID "{" Cuerpo  "}"                                                  { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nArreglo sobre el cual iterar: " + $4 + "\nInstrucciones:\n" + $6;                     }
           | IteracionIndeterminada                                                         { $$ = "Iteración indeterminada:\n" + $1;                                                                                                            }
           | ID "++" ";"                                                                    { $$ = "Incremento de la variable: " + $1 + ";";                                                                                                     }
           | ID "--" ";"                                                                    { $$ = "Decremento de la variable: " + $1 + ";";                                                                                                     }
           | VOMITA ";"                                                                     { $$ = "Vomita;";                                                                                                                                    }
           | VOMITA ID ";"                                                                  { $$ = "Vomita a la etiqueta: " + $2 + ";";                                                                                                          }
           | FONDOBLANCO ";"                                                                { $$ = "fondoBlanco;";                                                                                                                               }
           | FONDOBLANCO ID ";"                                                             { $$ = "fondoBlanco a la etiqueta: " + $2 + ";";                                                                                                     }
           | ROLOEPEA ";"                                                                   { $$ = "roloePea;";                                                                                                                                  }
           | ROLOEPEA ID ";"                                                                { $$ = "roloePea a la etiqueta: " + $2 + ";";                                                                                                        }*/
           ;
/*
IteracionIndeterminada: ID ":" MIENTRAS "(" Expresion ")" "{" Instrucciones "}" { $$ = "Etiqueta: " + $1 + "\nCondición: " + $5 + "\nInstrucciones: " + $8; }
                      | MIENTRAS "(" Expresion ")" "{" Instrucciones "}"        { $$ = "Condición: " + $3 + "\nInstrucciones: " + $6;                       }
                      ;
*/
LValues: LValue             { $$ = new std::vector<Expression*>(); $$->push_back($1); }
       | LValues "," LValue { $$ = $1; $$->push_back($3);                                      }
       ;

%left "->" ".";
LValue: ID                 { $$ = new IDExpr($1);          }
      | LValue "->" LValue { $$ = new PardoExpr($1, $3);   }
      | LValue "."  LValue { $$ = new GrizzliExpr($1, $3); }
      | AccesoCueva        { $$ = $1;                      }
      ;

AccesoCueva: ID "[" Expresion "]"          { $$ = new CuevaExpr($1, $3); }
           | AccesoCueva "[" Expresion "]" { $$ = $1; $$->addDimension($3); }
           ;


Expresiones: Expresion                 { $$ = new std::vector<Expression*>(); $$->push_back($1); }
           | Expresiones "," Expresion { $$ = $1; $$->push_back($3); }
           ;

%nonassoc ":" "?";
%left "==" "=/=";
%nonassoc "<" "=<" ">" ">=";
%left "+" "-";
%left "*" "/" "%";
%left "&";
%left "|";
%nonassoc "no";
%nonassoc UNARIO;
%right "**";

Expresion: CONSTPOLAR                            { $$ = new ConstantExpr(std::string("polar")     , $1); }
         | CONSTKODIAK                           { $$ = new ConstantExpr(std::string("kodiak")    , $1); }
         | CONSTHORMIGUERO                       { $$ = new ConstantExpr(std::string("hormiguero"), $1); }
         | CONSTMALAYO                           { $$ = new ConstantExpr(std::string("malayo")    , $1); }
         | LValue                                { $$ = $1;                                               }
        /* | Funcion                             { $$ = $1;                                                                }*/
        /* | FuncionPredef                       { $$ = $1;                                                                }*/
         | BLANCO                                { $$ = new ConstantExpr(std::string("panda"), $1    );  }
         | NEGRO                                 { $$ = new ConstantExpr(std::string("panda"), $1    );  }
         | Expresion "<"   Expresion             { $$ = new BinaryExpr  (std::string("<"  )  , $1, $3);  }
         | Expresion "=<"  Expresion             { $$ = new BinaryExpr  (std::string("=<" )  , $1, $3);  }
         | Expresion ">"   Expresion             { $$ = new BinaryExpr  (std::string(">"  )  , $1, $3);  }
         | Expresion ">="  Expresion             { $$ = new BinaryExpr  (std::string(">=" )  , $1, $3);  }
         | Expresion "=="  Expresion             { $$ = new BinaryExpr  (std::string("==" )  , $1, $3);  }
         | Expresion "=/=" Expresion             { $$ = new BinaryExpr  (std::string("=/=")  , $1, $3);  }
         | Expresion "|"   Expresion             { $$ = new BinaryExpr  (std::string("|"  )  , $1, $3);  }
         | Expresion "&"   Expresion             { $$ = new BinaryExpr  (std::string("&"  )  , $1, $3);  }
         | "no" Expresion                        { $$ = new UnaryExpr   (std::string("no" )  , $2    );  }
         | Expresion "+"  Expresion              { $$ = new BinaryExpr  (std::string("+"  )  , $1, $3);  }
         | Expresion "-"  Expresion              { $$ = new BinaryExpr  (std::string("-"  )  , $1, $3);  }
         | Expresion "**" Expresion              { $$ = new BinaryExpr  (std::string("**" )  , $1, $3);  }
         | Expresion "*"  Expresion              { $$ = new BinaryExpr  (std::string("*"  )  , $1, $3);  }
         | Expresion "/"  Expresion              { $$ = new BinaryExpr  (std::string("/"  )  , $1, $3);  }
         | Expresion "%"  Expresion              { $$ = new BinaryExpr  (std::string("%"  )  , $1, $3);  }
         | "-" Expresion %prec UNARIO            { $$ = new UnaryExpr   (std::string("-"  )  , $2    );  }
         | "(" Expresion ")"                     { $$ = $2;                                                                       }
         | Expresion "?" Expresion ":" Expresion { $$ = new SelectorExpr ($1                  , $3, $5);  }
         ;

/*
Funcion: ID "(" Expresiones ")" { $$ = "Nombre de funcion: " + $1 + "\nArgumentos:\n"; }

FuncionPredef: APANDA  "(" Expresion ")" { $$ = "Funcion predefinida: " + $1 + ". Argumento: "  }
             | AKODIAK "(" Expresion ")" { $$ = "Funcion predefinida: " + $1 + ". Argumento: "  }
             | AMALAYO "(" Expresion ")" { $$ = "Funcion predefinida: " + $1 + ". Argumento: "  }
             | APOLAR  "(" Expresion ")" { $$ = "Funcion predefinida: " + $1 + ". Argumento: "  }
             | LON     "(" Expresion ")" { $$ = "Funcion predefinida: " + $1 + ". Argumento: "  }
             ;

*/
%%

void
yy::bear_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
