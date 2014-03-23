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
# include "node.hh"
# include "expresion.hh"
# include "statement.hh"
# include "definition.hh"
# include "type.hh"
class bear_driver;

typedef struct {
  std::string nombre;
  unsigned int linea;
  unsigned int columna;
} elementoLista;
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

bool chequearLongitudListas(std::vector<elementoLista>* ids, std::vector<Expression*>* expr);
std::vector<std::string>* extraerIds(std::vector<elementoLista>* ids);

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
%type  <Definition*> DefConstante
%type  <std::vector<Definition*>*> Locales
%type  <Definition*> DefVariable
%type  <DefArray*> DefCueva
%type  <Definition*> DefCompleja
%type  <Definition*> DefFuncion
%type  <Definition*> DefLocales
%type  <std::vector<std::string>*> Cuevas
%type  <std::vector<elementoLista>*> Identificadores
%type  <Type*> Tipo
%type  <std::vector<Parameter*>*> Campos
%type  <std::vector<Definition*>*> DefParametros
%type  <Definition*> DefParametro
%type  <std::string> ParametroCueva
%type  <CuevaExpr*>  AccesoCueva
%type  <std::string> FuncionPredef
%type  <std::string> Funcion
%type  <std::string> Cuerpo
%type  <std::string> IteracionIndeterminada

/* %printer { yyoutput << $$; } <*>; */

%%
%start Programa;

Programa : DefCompleja Locales Instrucciones { $$ = $3; driver.AST = $$; }
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

*/

DefFuncion: ID "(" DefParametros ")" "=>" Tipo                       { $$ = new DefFunction($1, $3, $6);
                                                                       driver.tabla.add_function($1, $6, @1.begin.line, @1.begin.column, $3, false);
                                                                     }
         /* | ID "(" DefParametros ")" "=>" Tipo Instruccion           { $$ = "Nombre: " + $1 + "\nParametros:\n" + $3 + "\nRetorna: " + $6 + $8; } */
          ;

Locales: Locales DefLocales ";"  { $$ = $1; $$->push_back($2);                             }
       | DefLocales ";"          { $$ = new std::vector<Definition*>(); $$->push_back($1); }
       ;


DefLocales: DefVariable  { $$ = $1; }
          | DefConstante { $$ = $1; }
          ;

DefParametros: DefParametro                   { $$ = new std::vector<Definition*> (); $$->push_back($1);               }
             | DefParametros "," DefParametro { $$ = $1; $$->push_back($3);                                           }
             ;

DefParametro: Tipo ID                  { $$ = new Parameter($2, $1, false);       }
            | "^" Tipo ID              { $$ = new Parameter($3, $2, true);        }
           /* | ParametroCueva Tipo ID   { $$ = "Tipo: " + $1 + $2 + " Nombre: " + $3; }*/
            ;

/*
ParametroCueva: CUEVA "[" "]" DE                           { $$ = $1 + " [] " + $4 + " ";                }
              | ParametroCueva CUEVA "[" CONSTPOLAR "]" DE { $$ = $1 + $2 + " [" + $4 + "] " + $6 + " "; }
              ;
*/

DefConstante: CONST Tipo Identificadores "=" Expresiones {
                                                            if (chequearLongitudListas ($3,$5))
                                                            {
                                                              driver.agregarConInicializacion($3, Const, $2);
                                                              std::vector<string>* l = extraerIds($3);
                                                              $$ = new ConstDef($2, l, $5);
                                                            } else
                                                            {
                                                              driver.error(@1, @5, "El numero de identificadores y de expresiones no se corresponde.");
                                                              $$ = nullptr;
                                                            }
                                                         }
            ;


DefVariable: Tipo Identificadores "=" Expresiones {
                                                    if (chequearLongitudListas ($2,$4))
                                                    {
                                                      driver.agregarConInicializacion($2, Var, $1);
                                                      std::vector<string>* l = extraerIds($2);
                                                      $$ = new DefVar($1, l, $4);
                                                    } else
                                                    {
                                                      driver.error(@1, @4, "El numero de identificadores y de expresiones no se corresponde.");
                                                      $$ = nullptr;
                                                    }
                                                  }
           | Tipo Identificadores                 {
                                                      driver.agregarSinInicializacion($2, Var, $1);
                                                      std::vector<string>* l = extraerIds($2);
                                                      $$ = new DefVarNoInit($1, l);
                                                  }
           | DefCueva                             { $$ = $1;                                                      }
           ;


Identificadores: ID                     { $$ = new std::vector<elementoLista>(); elementoLista e; e.nombre = $1; e.linea = @1.begin.line; e.columna = @1.begin.column; $$->push_back(e); }
               | Identificadores "," ID { $$ = $1; elementoLista e; e.nombre = $3; e.linea = @3.begin.line; e.columna = @3.begin.column; $$->push_back(e); }
               ;



DefCueva: Cuevas Tipo ID {
                            $$ = new DefArray($2,$3,$1);
                            Type* tipoCueva = new CuevaType($2,$1);
                            driver.tabla.add_symbol($3,tipoCueva,Cueva, @3.begin.line, @3.begin.column);
                          }
        ;

Cuevas: CUEVA "[" CONSTPOLAR "]" DE          { $$ = new std::vector<std::string>(); $$->push_back($3);      }
       |  Cuevas CUEVA "[" CONSTPOLAR "]" DE { $$ = $1; $$->push_back($4); }
       ;


DefCompleja: PARDO ID "{" { Grizzli* g = new Grizzli();
                            $<Contenedor*>$ = driver.tabla.add_container($2, g, Compuesto, @1.begin.line,@1.begin.column,0);
                            driver.tabla.enter_scope(); } Campos "}" {
                                                                        int alcanceCampos = driver.tabla.get_actual_scope();
                                                                        Contenedor* c = $<Contenedor*>4;
                                                                        c->set_alcanceCampos(alcanceCampos);
                                                                        driver.tabla.exit_scope();
                                                                        $$ = nullptr;
                                                                      }

      /*     | GRIZZLI ID "{" Campos "}" { $$ = "Grizzli:\nNombre: " + $2 + "\nCampos:\n" + $4; } */
           ;

Campos: Tipo ID ";"        {
                              $$ = new std::vector<Parameter*>; Parameter* p = new Parameter($2,$1,false); $$->push_back(p);
                              driver.tabla.add_symbol($2, $1, Campo, @2.begin.line, @2.begin.column);
                           }

      | Campos Tipo ID ";" {
                              $$ = $1; Parameter* p = new Parameter($3, $2, false); $$->push_back(p);
                              driver.tabla.add_symbol($3, $2, Campo, @2.begin.line, @2.begin.column);
                            }
      ;

Tipo: PANDA       { $$ = new PandaType();      }
    | POLAR       { $$ = new PolarType();      }
    | KODIAK      { $$ = new KodiakType();     }
    | MALAYO      { $$ = new MalayoType();     }
    | HORMIGUERO  { $$ = new HormigueroType(); }
    | EXTINTO     { $$ = new ExtintoType();    }
/*    | ID          { $$ = $1; }*/
    ;

Instrucciones: Instruccion ";"               { $$ = new std::vector<Statement*>(); $$->push_back($1); }
             | Instrucciones Instruccion ";" { $$ = $1; $$->push_back($2);                            }
             | error                         { $$ = new std::vector<Statement*>(); yyerrok;           }
             ;

%right ENTONCES SINO;
Instruccion: LValues "=" Expresiones                                                  { $$ = new Assign($1, $3);             }
/*           | LEER "(" ID ")"                                                        { $$ = "Leer: variable: " + $3 + ";";  }
           | ESCRIBIR "(" Expresion ")"                                               { $$ = "Escribir: valor: " + $3 + ";"; }
           | Funcion                                                                  { $$ = "Funcion:\n" + $1 + ";";        }*/
/*           | SI Expresion ENTONCES Instruccion                                        { $$ = new If($2, $4);                 }
           | SI Expresion ENTONCES Instruccion SINO Instruccion                       { $$ = new IfElse($2, $4, $6);         }
           | "{" Locales Instrucciones "}"                                            { $$ = new Body($2, $3);               }
           | PARA ID EN "(" Expresion ";" Expresion ")" Instruccion                         { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nDesde: " + $5 + "\nHasta:\n" + $7 + "\nInstrucciones:\n" + $10;                       }
           | PARA ID EN "(" Expresion ";" Expresion ";" Expresion ")" Instruccion           { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nDesde: " + $5 + "\nHasta:\n" + $9 + "\nCon Paso: " + $7 + "\nInstrucciones:\n" + $12; }
           | PARA ID EN ID "{" Cuerpo  "}"                                                  { $$ = "Iteración acotada:\nVariable de iteración: " + $2 + "\nArreglo sobre el cual iterar: " + $4 + "\nInstrucciones:\n" + $6;                     }
           | IteracionIndeterminada                                                         { $$ = "Iteración indeterminada:\n" + $1;                                                                                                            }
           | ID "++"                                                                        { $$ = "Incremento de la variable: " + $1 + ";";                                                                                                     }
           | ID "--"                                                                        { $$ = "Decremento de la variable: " + $1 + ";";                                                                                                     }
           | VOMITA                                                                         { $$ = "Vomita;";                                                                                                                                    }
           | VOMITA ID                                                                      { $$ = "Vomita a la etiqueta: " + $2 + ";";                                                                                                          }
           | FONDOBLANCO                                                                    { $$ = "fondoBlanco;";                                                                                                                               }
           | FONDOBLANCO ID                                                                 { $$ = "fondoBlanco a la etiqueta: " + $2 + ";";                                                                                                     }
           | ROLOEPEA                                                                       { $$ = "roloePea;";                                                                                                                                  }
           | ROLOEPEA ID                                                                    { $$ = "roloePea a la etiqueta: " + $2 + ";";                                                                                                        }*/
           ;
/*
IteracionIndeterminada: ID ":" MIENTRAS "(" Expresion ")" Instruccion    { $$ = "Etiqueta: " + $1 + "\nCondición: " + $5 + "\nInstrucciones: " + $8; }
                      | MIENTRAS "(" Expresion ")" Instruccion           { $$ = "Condición: " + $3 + "\nInstrucciones: " + $6;                       }
                      ;
*/
LValues: LValue             { $$ = new std::vector<Expression*>(); $$->push_back($1); }
       | LValues "," LValue { $$ = $1; $$->push_back($3);                             }
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

void yy::bear_parser::error ( const location_type& l,
                              const std::string& m  )
{
  driver.error (l, m);
}

bool chequearLongitudListas(std::vector<elementoLista>* ids, std::vector<Expression*>* expr){ return ids->size() == expr->size(); }

std::vector<std::string>* extraerIds(std::vector<elementoLista>* ids)
{
  std::vector<std::string>* l = new std::vector<std::string>();
  for(unsigned int i = 0; i < ids->size(); ++i)
  {
    l->push_back(ids->at(i).nombre);
  }
  return l;

}
