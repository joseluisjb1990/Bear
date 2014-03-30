%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {bear_parser}
%define api.token.constructor
%define api.value.type variant
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
  unsigned int lineaI;
  unsigned int columnaI;
  unsigned int lineaF;
  unsigned int columnaF;
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
int ALCANCE_LVALUE;

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

%token <std::string>                 ID
%token <std::string>                 CONSTPOLAR
%token <std::string>                 CONSTKODIAK
%token <std::string>                 CONSTHORMIGUERO
%token <std::string>                 CONSTMALAYO
%token <std::string>                 BLANCO
%token <std::string>                 NEGRO
%token <std::string>                 PANDA
%token <std::string>                 POLAR
%token <std::string>                 KODIAK
%token <std::string>                 MALAYO
%token <std::string>                 HORMIGUERO
%token <std::string>                 EXTINTO
%token <std::string>                 CONST
%token <std::string>                 CUEVA
%token <std::string>                 DE
%token <std::string>                 PARDO
%token <std::string>                 GRIZZLI
%token <std::string>                 LEER
%token <std::string>                 ESCRIBIR
%token <std::string>                 SI
%token <std::string>                 ENTONCES
%token <std::string>                 SINO
%token <std::string>                 PARA
%token <std::string>                 EN
%token <std::string>                 VOMITA
%token <std::string>                 FONDOBLANCO
%token <std::string>                 ROLOEPEA
%token <std::string>                 APOLAR
%token <std::string>                 APANDA
%token <std::string>                 AKODIAK
%token <std::string>                 AMALAYO
%token <std::string>                 LON
%token <std::string>                 MIENTRAS
%type  <Statement*>                  programa
%type  <Expression*>                 expresion
%type  <std::vector<Expression*>*>   expresiones
%type  <std::vector<Statement*>*>    instrucciones
%type  <Statement*>                  instruccion
%type  <LValueExpr*>                 lvalue
%type  <std::vector<Expression*>*>   lvalues
%type  <std::vector<Definition*>*>   definiciones
%type  <std::vector<Definition*>*>   listadefglobales
%type  <Definition*>                 definicionglobal
%type  <Definition*>                 defconstante
%type  <Statement*>                  bloque
%type  <Statement*>                  bloqueespecial
%type  <Definition*>                 defvariable
%type  <Type*>                       defcueva
%type  <Definition*>                 defcompleja
%type  <Definition*>                 deffuncion
%type  <std::vector<std::string>*>   cuevas
%type  <std::vector<elementoLista>*> identificadores
%type  <Type*>                       tipo
%type  <std::vector<Type*>*>         campos
%type  <Type*>                       campo
%type  <std::vector<Parameter*>*>    defparametros
%type  <Parameter*>                  defparametro
%type  <std::vector<std::string>*>   parametrocueva
%type  <Type*>                       tipocueva
%type  <std::vector<Expression*>*>   accesocueva
%type  <std::vector<Expression*>*>   maybecueva
%type  <Expression*>                 funcionpredef
%type  <Statement*>                  iteracionindeterminada

%%
%start programa;

programa : definiciones "oso" "(" ")" "=>" EXTINTO                       { driver.tabla.enter_scope();
                                                                           std::vector<Parameter*>* paramVacio = new std::vector<Parameter*>();
                                                                           driver.tabla.add_function("oso",new ExtintoType(),@2.begin.line,@2.begin.column, @2.begin.line, @2.begin.column, paramVacio);
                                                                         }
           bloqueespecial                                                { driver.tabla.exit_scope();
                                                                           $$ = $8;/* driver.AST = $$;*/
                                                                         }
         | definiciones "oso" "(" error ")" "=>" EXTINTO bloqueespecial  { driver.error(@4, "Main function oso must not recieve parameters.");
                                                                           yyerrok;
                                                                           $$ = new Empty();
                                                                         }
         | definiciones "oso" "(" ")" "=>" error         bloqueespecial  { driver.error(@6, "Return type for main function oso must be extinto.");
                                                                           yyerrok;
                                                                           $$ = new Empty();
                                                                         }
         | definiciones "oso" "(" error ")" "=>" error   bloqueespecial  { driver.error(@4, "Main function oso must not recieve parameters.");
                                                                           driver.error(@7, "The return type for main function oso must be extinto.");
                                                                           yyerrok;
                                                                           $$ = new Empty();
                                                                         }
         | END                                                           { driver.error(@1, "Program can't be empty, it must have at least the declaration of the main function oso with no parameters and return type extinto.");
                                                                           yyerrok;
                                                                           $$ = new Empty();
                                                                         }
         ;

definiciones:                    { $$ = $$; }
            | listadefglobales   { $$ = $1; }
            ;

listadefglobales: definicionglobal                   { $$ = new std::vector<Definition*>(); $$->push_back($1); }
                | listadefglobales definicionglobal  { $$ = $1; $$->push_back($2);                             }
                ;

definicionglobal: defconstante  { $$ = $1; }
                | defvariable   { $$ = $1; }
                | deffuncion    { $$ = $1; }
                | defcompleja   { $$ = $1; }
                ;

deffuncion: ID "(" defparametros ")" "=>" tipo ";" { $$ = new DecFunction($1, $3, $6);
                                                     driver.tabla.add_function($1, $6, @1.begin.line, @1.begin.column, $3);
                                                   }

          | ID "(" defparametros ")" "=>" tipo     { Funcion* f = driver.tabla.get_function($1);
                                                     if(f) {
                                                       if (!(f->getDef())) {
                                                         if (driver.compare_parameters($3, f->get_parameters())) {
                                                           f->define(@1.begin.line, @1.begin.column);
                                                           driver.tabla.enter_scope();
                                                           for(std::vector<Parameter*>::iterator it = $3->begin(); it != $3->end(); ++it) {
                                                             driver.tabla.add_symbol((*it)->get_id(), (*it)->get_tipo(),Var,@3.begin.line, @3.begin.column, true);
                                                           }
                                                         } else {
                                                           driver.error(@3, "Parameters in function definition don't match the ones in declaration" + $1 + " ");
                                                         }
                                                       } else {
                                                         driver.error(@1, "Function "+ $1 + " is redefined " + '\n');
                                                       }
                                                     } else {
                                                       driver.tabla.add_function($1,$6,@1.begin.line,@1.begin.column, @1.begin.line, @1.begin.column, $3);
                                                       driver.tabla.enter_scope();
                                                       for(std::vector<Parameter*>::iterator it = $3->begin(); it != $3->end(); ++it)
                                                       {
                                                         driver.tabla.add_symbol((*it)->get_id(), (*it)->get_tipo(),Var,@3.begin.line, @3.begin.column, true);
                                                       }
                                                     }
                                                   }
            bloqueespecial                            { driver.tabla.exit_scope(); $$ = new DefFunction($1, $3, $6, $8); }
          | ID "(" defparametros ")" "=>" tipo error  { driver.error(@6, "expected ;"); yyerrok; }
          ;

defparametros: defparametro                   { $$ = new std::vector<Parameter*> (); $$->push_back($1);               }
             | defparametros "," defparametro { $$ = $1; $$->push_back($3);                                           }
             ;

defparametro: tipo ID        { $$ = new Parameter($2, $1, false); }
            | "^" tipo ID    { $$ = new Parameter($3, $2, true);  }
            | tipocueva ID   { $$ = new Parameter($2, $1, false); }
            ;

tipocueva: parametrocueva tipo { $$ = new CuevaType($2, $1); }
         ;

/* Aqui voy a devolver "vacio" para el caso base porque puedo, seguro hay que cambiarlo */
parametrocueva: CUEVA "[" "]" DE                           { $$ = new std::vector<std::string>(); $$->push_back(""); }
              | parametrocueva CUEVA "[" CONSTPOLAR "]" DE { $$ = $1; $$->push_back($4);                                  }
              ;

defconstante: CONST tipo identificadores "=" expresiones ";" {
                                                                if ($3->size() == $5->size())
                                                                {
                                                                  driver.agregarConInicializacion($3, Var, $2, false);
                                                                std::vector<string>* l = extraerIds($3);
                                                              $$ = new ConstDef($2, l, $5);
                                                            } else
                                                            {
                                                              driver.error(@1, @5, "The number of l-values and expressions is not the same.");
                                                              $$ = new EmptyDef();
                                                            }
                                                         }
            ;


defvariable: tipo identificadores "=" expresiones ";" {
                                                    if ($2->size() == $4->size())
                                                    {
                                                      driver.agregarConInicializacion($2, Var, $1, true);
                                                      std::vector<string>* l = extraerIds($2);
                                                      $$ = new DefVar($1, l, $4);
                                                    } else
                                                    {
                                                      driver.error(@1, @4, "The number of l-values and expressions is not the same.");
                                                      $$ = new EmptyDef();
                                                    }
                                                  }
           | tipo identificadores ";"                 {
                                                      driver.agregarSinInicializacion($2, Var, $1);
                                                      std::vector<string>* l = extraerIds($2);
                                                      $$ = new DefVarNoInit($1, l);
                                                  }
           | defcueva ID ";"                      { $$ = new DefArray($1, $2);
                                                    driver.tabla.add_symbol($2, $1, Cueva, @2.begin.line, @2.begin.column, true);
                                                  }
           ;


identificadores: ID                     { $$ = new std::vector<elementoLista>(); elementoLista e; e.nombre = $1; e.lineaI = @1.begin.line; e.columnaI = @1.begin.column; e.lineaF = @1.end.line; e.columnaF = @1.end.column; $$->push_back(e); }
               | identificadores "," ID { $$ = $1; elementoLista e; e.nombre = $3; e.lineaI = @3.begin.line; e.columnaI = @3.begin.column; e.lineaF = @3.end.line; e.columnaF = @3.end.column; $$->push_back(e); }
               ;



defcueva: cuevas tipo { $$ = new CuevaType($2,$1); }
        ;

cuevas: CUEVA "[" CONSTPOLAR "]" DE          { $$ = new std::vector<std::string>(); $$->push_back($3); }
       |  cuevas CUEVA "[" CONSTPOLAR "]" DE { $$ = $1; $$->push_back($4);                             }
       ;


defcompleja: PARDO ID "{" { driver.tabla.enter_scope(); }
             campos "}"   {
                            int alcanceCampos = driver.tabla.get_actual_scope();
                            driver.tabla.exit_scope();
                            PardoType* p = new PardoType($5, $2);
                            Contenedor* c = driver.tabla.find_container($2);
                            if (c) {
                              if (c->getDef()) {
                                driver.error(@1, @6, "Attempt to redefine the type " + $2 + ".");
                              } else {
                                driver.tabla.update_container($2, p, @1.begin.line, @1.begin.column, alcanceCampos);
                              }
                            } else {
                              driver.tabla.add_container($2, p, Compuesto, @1.begin.line, @1.begin.column, @1.begin.line, @1.begin.column, alcanceCampos);
                            }
                            $$ = new EmptyDef();
                          }

           | PARDO ID ";"   {
                            // FIXME Aqui falta revisar que pasa cuando el find_symbol si devuelva algo :s error o que?
                            Contenedor* c = driver.tabla.find_container($2);
                            if (!c) {
                              driver.tabla.add_container($2, Compuesto, @1.begin.line, @1.begin.column);
                            }
                            $$ = new EmptyDef();
                          }

           | GRIZZLI ID "{" { driver.tabla.enter_scope(); }
             campos "}" {
                          int alcanceCampos = driver.tabla.get_actual_scope();
                          driver.tabla.exit_scope();
                          GrizzliType* g = new GrizzliType($5, $2);
                          Contenedor* c = driver.tabla.find_container($2);
                            if (c) {
                              if (c->getDef()) {
                                driver.error(@1, @6, "Attempt to redefine the type " + $2 + ".");
                              } else {
                                driver.tabla.update_container($2, g, @1.begin.line, @1.begin.column, alcanceCampos);
                              }
                            } else {
                              driver.tabla.add_container($2, g, Compuesto, @1.begin.line, @1.begin.column, @1.begin.line, @1.begin.column, alcanceCampos);
                            }
                          $$ = new EmptyDef();
                        }

           | GRIZZLI ID ";"    {
                              // FIXME Aqui falta revisar que pasa cuando el find_symbol si devuelva algo :s error o que?
                              Contenedor* c = driver.tabla.find_container($2);
                              if (!c) {
                                driver.tabla.add_container($2, Compuesto, @1.begin.line, @1.begin.column);
                              }
                              $$ = new EmptyDef();
                            }
           ;

campos: campo ";"        { $$ = new std::vector<Type*>; $$->push_back($1); }
      | campos campo ";" { $$ = $1; $$->push_back($2); }
      ;

campo: tipo ID            { $$ = new CampoType($1,$2);
                            driver.tabla.add_symbol($2, $1, Campo, @2.begin.line, @2.begin.column, true);
                           }

      | defcueva ID        { $$ = $1;
                             driver.tabla.add_symbol($2, $1, Cueva, @2.begin.line, @2.begin.column, true);
                           }
      ;


tipo: PANDA       { $$ = new PandaType();                                   }
    | POLAR       { $$ = new PolarType();                                   }
    | KODIAK      { $$ = new KodiakType();                                  }
    | MALAYO      { $$ = new MalayoType();                                  }
    | HORMIGUERO  { $$ = new HormigueroType();                              }
    | EXTINTO     { $$ = new ExtintoType();                                 }
    | ID          { Contenedor* c = driver.tabla.find_container($1);
                    if (!c) {
                      driver.error(@1, "Type " + $1 + " is not defined.");
                      $$ = new ErrorType();
                    } else {
                      $$ = c->getTipo();
                    }
                  }
    ;

bloqueespecial: "{" instrucciones "}" { $$ = new Body($2);  }
              | instruccion ";"       { $$ = $1;            }
              ;

bloque: "{" { driver.tabla.enter_scope(); } instrucciones "}"     {
                                                                            $$ = new Body($3);
                                                                            driver.tabla.exit_scope();
                                                                          }
      | instruccion ";"                                                      { $$ = $1; }
      ;

instrucciones: instruccion                { $$ = new std::vector<Statement*>(); $$->push_back($1); }
             | instrucciones instruccion  { $$ = $1; $$->push_back($2);                            }
             | error ";"                  { $$ = new std::vector<Statement*>(); yyerrok;           }
             ;

%right ENTONCES SINO;
instruccion: defvariable                                                  { $$ = $1; }
           | defconstante                                                 { $$ = $1; }
           | lvalues"=" expresiones ";"                                  {
                                                                          if (!($1->size() == $3->size())) {
                                                                            driver.error(@1, @3, "The number of l-values and expressions is not the same.");
                                                                          }
                                                                          $$ = new Assign($1, $3);
                                                                         }
           | lvalues error expresiones ";"                                { $$ = new Empty(); yyerrok; }

           | LEER "(" ID ")" ";"                                          {
                                                                          Contenido* c = driver.tabla.find_symbol($3,Var);
                                                                          if (!c) {
                                                                            driver.error(@1, @4, "Trying to read variable " + $3 + " which is not defined.");
                                                                            $$ =  new Empty();
                                                                          }
                                                                          else if (!c->getMutabilidad()) {
                                                                            driver.error(@1, @4, "Trying to initialize variable " + $3 + ", which is not mutable.");
                                                                            $$ =  new Empty();
                                                                          } else {
                                                                            $$ = new Read($3);
                                                                          }
                                                                          }
           | ESCRIBIR "(" expresion ")" ";"                                { $$ = new Write($3); }
           | ID "(" expresiones ")" ";"                                    { Funcion* f = driver.tabla.get_function($1);
                                                                             if (!f) {
                                                                               driver.error(@1,@4,"Function " + $1 + " is not defined.");
                                                                               $$ = new Empty();
                                                                             } else {
                                                                               $$ = new Function($1, $3);
                                                                             }
                                                                           }
           | SI expresion ENTONCES bloque                                  { $$ = new If($2, $4);                 }
           | SI expresion ENTONCES bloque SINO bloque                       { $$ = new IfElse($2, $4, $6);         }

           | PARA ID EN "(" expresion ";" expresion ")"                     { driver.tabla.enter_scope();
                                                                              PolarType* p = new PolarType();
                                                                              driver.tabla.add_symbol($2, p, Var, @2.begin.line, @2.begin.column, @2.end.line, @2.end.column, false);
                                                                            }
             bloqueespecial                                                 {
                                                                              driver.tabla.exit_scope();
                                                                              $$ = new SimpleFor($2, $5, $7, $10);
                                                                            }
           | PARA ID EN "(" expresion ";" expresion ";" expresion ")"      { driver.tabla.enter_scope();
                                                                             PolarType* p = new PolarType();
                                                                             driver.tabla.add_symbol($2, p, Var, @2.begin.line, @2.begin.column, @2.end.line, @2.end.column, false);
                                                                           }
             bloqueespecial                                                { driver.tabla.exit_scope();
                                                                             $$ = new ComplexFor($2, $5, $9, $7, $12);
                                                                           }
           | PARA ID EN ID                                                 { Contenido* c = driver.tabla.find_symbol($4, Cueva);
                                                                             if (!c) {
                                                                               driver.error(@4,"Cueva " + $4 + " is not declared.");
                                                                             }
                                                                             CuevaType* cuevita = (CuevaType*) c->getTipo();
                                                                             Type* tipo = cuevita->getTipo();
                                                                             driver.tabla.enter_scope();
                                                                             driver.tabla.add_symbol($2, tipo, Cueva, @2.begin.line, @2.begin.column, @2.end.line, @2.end.column, false);
                                                                           }
            bloqueespecial                                                 { driver.tabla.exit_scope();
                                                                             $$ = new IdFor($2, $4, $6);
                                                                           }
           | iteracionindeterminada                                        { $$ = $1; }
           | ID "++" ";"                                                   { Contenido* c = driver.tabla.find_symbol($1,Var);
                                                                             if (c) {
                                                                               if (c->getMutabilidad()) {
                                                                                 $$ = new Increase($1);
                                                                               } else {
                                                                                 driver.error(@1, @2, "Attempt to increase variable " + $1 + ", which is not mutable.");
                                                                                 $$ = new Empty();
                                                                               }
                                                                             } else {
                                                                               driver.error(@1, @2, "Attempt to increase variable " + $1 + ", which is not declared.");
                                                                               $$ = new Empty();
                                                                             }
                                                                           }
           | ID "--" ";"                                                   { Contenido* c = driver.tabla.find_symbol($1,Var);
                                                                             if (c) {
                                                                               if (c->getMutabilidad()) {
                                                                                 $$ = new Decrement($1);
                                                                               } else {
                                                                                 driver.error(@1, @2, "Attempt to decrease variable " + $1 + ", which is not mutable.");
                                                                                 $$ = new Empty();
                                                                               }
                                                                             } else {
                                                                               driver.error(@1, @2, "Attempt to decrease variable " + $1 + ", which is not declared.");
                                                                               $$ = new Empty();
                                                                             }
                                                                           }
           | VOMITA     ";"                                                { $$ = new Return(); }
           | VOMITA ID  ";"                                                { Contenido* c = driver.tabla.find_symbol($2,Etiqueta);
                                                                             if (c) {
                                                                               $$ = new ReturnID($2);
                                                                             } else {
                                                                               driver.error(@1, @2, "Attempt to return to tag " + $2 + ", which is not declared.");
                                                                               $$ = new Empty();
                                                                             }
                                                                           }
           | FONDOBLANCO    ";"                                            { $$ = new Continue(); }
           | FONDOBLANCO ID ";"                                            { Contenido* c = driver.tabla.find_symbol($2,Etiqueta);
                                                                             if (c) {
                                                                               $$ = new ContinueID($2);
                                                                             } else {
                                                                               driver.error(@1, @2, "Attempt to continue to tag " + $2 + ", which is not declared.");
                                                                               $$ = new Empty();
                                                                             }
                                                                           }
           | ROLOEPEA    ";"                                               { $$ = new Break(); }
           | ROLOEPEA ID ";"                                               { Contenido* c = driver.tabla.find_symbol($2,Etiqueta);
                                                                             if (c) {
                                                                               $$ = new BreakID($2);
                                                                             } else {
                                                                               driver.error(@1, @2, "Attempt to break to tag " + $2 + ", which is not declared.");
                                                                               $$ = new Empty();
                                                                             }
                                                                           }
           ;

iteracionindeterminada: ID ":" MIENTRAS "(" expresion ")"   { Contenido* c = driver.tabla.find_symbol($1,Etiqueta);
                                                              TagType* t = new TagType();
                                                              if (!c) {
                                                                driver.tabla.add_symbol($1, t, Etiqueta, @1.begin.line, @1.begin.column, @1.end.line, @1.end.column, false);
                                                              } else {
                                                                driver.error(@1, "Tag " + $1 + " is already defined.");
                                                              }
                                                            }
                        bloque                              { $$ = new TagWhile($1, $5, $8); }

                      | MIENTRAS "(" expresion ")" bloque           { $$ = new While($3, $5); }
                      ;

lvalues: lvalue             { $$ = new std::vector<Expression*>(); $$->push_back($1); }
       | lvalues "," lvalue { $$ = $1; $$->push_back($3);                             }
       ;

lvalue: ID maybecueva              {
                                     Contenido* c;
                                     if (nullptr == $2) {
                                       c = driver.tabla.find_symbol($1, Var);
                                       $$ = new IDExpr($1);
                                     } else {
                                       c = driver.tabla.find_symbol($1, Cueva);
                                       $$ = new CuevaExpr($1, $2);
                                     }

                                     if (!c) {
                                       driver.error(@1, "Variable " + $1 + " is not defined.");
                                       ALCANCE_LVALUE = -1;
                                       $$ = new EmptyExpr();
                                     }
                                     else if (!c->getMutabilidad()) {
                                       driver.error(@1, "Variable " + $1 + " is not mutable.");
                                       ALCANCE_LVALUE = -1;
                                       $$ = new EmptyExpr();
                                     } else {
                                        if (!c->getTipo()->isSimple()) {
                                          Contenedor* tipo = driver.tabla.find_container(c->getTipo()->getName());
                                          ALCANCE_LVALUE = tipo->get_alcanceCampos();
                                        } else {
                                          if (nullptr == $2) {
                                            ALCANCE_LVALUE = c->getAlcance();
                                          } else {
                                            CuevaType* cueva = (CuevaType*) c->getTipo();
                                            Contenedor* tipo = driver.tabla.find_container(cueva->getTipo()->getName());
                                            if(tipo)
                                            {
                                              ALCANCE_LVALUE = tipo->get_alcanceCampos();
                                            }
                                          }
                                        }
                                     }
                                   }
      | lvalue "->" ID maybecueva {
                                    if (-1 != ALCANCE_LVALUE) {
                                     Contenido* c;
                                     if (nullptr == $4) {
                                       c = driver.tabla.find_scope($3, Campo, ALCANCE_LVALUE);
                                       $$ = new IDExpr($3);
                                     } else {
                                       c = driver.tabla.find_scope($3, Cueva, ALCANCE_LVALUE);
                                       $$ = new CuevaExpr($3, $4);
                                     }

                                     if (!c) {
                                       driver.error(@3, "Variable " + $3 + " is not in scope.");
                                       ALCANCE_LVALUE = -1;
                                       $$ = new EmptyExpr();
                                     }
                                     else if (!c->getMutabilidad()) {
                                       driver.error(@3, "Variable " + $3 + " is not mutable.");
                                       ALCANCE_LVALUE = -1;
                                       $$ = new EmptyExpr();
                                     } else {
                                        if (!c->getTipo()->isSimple()) {
                                          Contenedor* tipo = driver.tabla.find_container(c->getTipo()->getName());
                                          ALCANCE_LVALUE = tipo->get_alcanceCampos();
                                        } else {
                                          ALCANCE_LVALUE = c->getAlcance();
                                        }
                                     }
                                    } else {
                                      $$ = new EmptyExpr();
                                    }
                                  }
      | lvalue "."  ID maybecueva {
                                    if (-1 != ALCANCE_LVALUE) {
                                     Contenido* c;
                                     if (nullptr == $4) {
                                       c = driver.tabla.find_scope($3, Campo, ALCANCE_LVALUE);
                                       $$ = new IDExpr($3);
                                     } else {
                                       c = driver.tabla.find_scope($3, Cueva, ALCANCE_LVALUE);
                                       $$ = new CuevaExpr($3, $4);
                                     }

                                     if (!c) {
                                       driver.error(@3, "Variable " + $3 + " is not in scope.");
                                       ALCANCE_LVALUE = -1;
                                       $$ = new EmptyExpr();
                                     }
                                     else if (!c->getMutabilidad()) {
                                       driver.error(@3, "Variable " + $3 + " is not mutable.");
                                       ALCANCE_LVALUE = -1;
                                       $$ = new EmptyExpr();
                                     } else {
                                        if (!c->getTipo()->isSimple()) {
                                          Contenedor* tipo = driver.tabla.find_container(c->getTipo()->getName());
                                          ALCANCE_LVALUE = tipo->get_alcanceCampos();
                                        } else {
                                          ALCANCE_LVALUE = c->getAlcance();
                                        }
                                     }
                                    } else {
                                      $$ = new EmptyExpr();
                                    }
                                  }
      ;

maybecueva:             { $$ = nullptr; }
          | accesocueva { $$ = $1;      }
          ;

accesocueva:  "[" expresion "]"            { $$ = new std::vector<Expression*>(); $$->push_back($2); }
           | accesocueva "[" expresion "]" { $$ = $1; $$->push_back($3); }
           ;


expresiones: expresion                 { $$ = new std::vector<Expression*>(); $$->push_back($1); }
           | expresiones "," expresion { $$ = $1; $$->push_back($3); }
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

expresion: CONSTPOLAR                            { $$ = new ConstantExpr(std::string("polar")     , $1);      }
         | CONSTKODIAK                           { $$ = new ConstantExpr(std::string("kodiak")    , $1);      }
         | CONSTHORMIGUERO                       { $$ = new ConstantExpr(std::string("hormiguero"), $1);      }
         | CONSTMALAYO                           { $$ = new ConstantExpr(std::string("malayo")    , $1);      }
         | lvalue                                { $$ = $1;                                                   }
         | ID "(" expresiones ")"                { Funcion* f = driver.tabla.get_function($1);
                                                   if (!f) {
                                                     driver.error(@1,@4,"Function " + $1 + " is not defined.");
                                                     $$ = new EmptyExpr();
                                                   } else {
                                                     $$ = new FunctionExpr($1, $3);
                                                   }
                                                 }
         | funcionpredef                         { $$ = $1;                                                   }
         | BLANCO                                { $$ = new ConstantExpr(std::string("panda"), $1    );       }
         | NEGRO                                 { $$ = new ConstantExpr(std::string("panda"), $1    );       }
         | expresion "<"   expresion             { $$ = new BinaryExpr  (std::string("<"  )  , $1, $3);       }
         | expresion "=<"  expresion             { $$ = new BinaryExpr  (std::string("=<" )  , $1, $3);       }
         | expresion ">"   expresion             { $$ = new BinaryExpr  (std::string(">"  )  , $1, $3);       }
         | expresion ">="  expresion             { $$ = new BinaryExpr  (std::string(">=" )  , $1, $3);       }
         | expresion "=="  expresion             { $$ = new BinaryExpr  (std::string("==" )  , $1, $3);       }
         | expresion "=/=" expresion             { $$ = new BinaryExpr  (std::string("=/=")  , $1, $3);       }
         | expresion "|"   expresion             { $$ = new BinaryExpr  (std::string("|"  )  , $1, $3);       }
         | expresion "&"   expresion             { $$ = new BinaryExpr  (std::string("&"  )  , $1, $3);       }
         | "no" expresion                        { $$ = new UnaryExpr   (std::string("no" )  , $2    );       }
         | expresion "+"  expresion              { $$ = new BinaryExpr  (std::string("+"  )  , $1, $3);       }
         | expresion "-"  expresion              { $$ = new BinaryExpr  (std::string("-"  )  , $1, $3);       }
         | expresion "**" expresion              { $$ = new BinaryExpr  (std::string("**" )  , $1, $3);       }
         | expresion "*"  expresion              { $$ = new BinaryExpr  (std::string("*"  )  , $1, $3);       }
         | expresion "/"  expresion              { $$ = new BinaryExpr  (std::string("/"  )  , $1, $3);       }
         | expresion "%"  expresion              { $$ = new BinaryExpr  (std::string("%"  )  , $1, $3);       }
         | "-" expresion %prec UNARIO            { $$ = new UnaryExpr   (std::string("-"  )  , $2    );       }
         | "(" expresion ")"                     { $$ = $2;                                                   }
         | expresion "?" expresion ":" expresion { $$ = new SelectorExpr ($1                  , $3, $5);      }
         ;




funcionpredef: APANDA  "(" expresion ")" { $$ = new UnaryExpr($1, $3); }
             | AKODIAK "(" expresion ")" { $$ = new UnaryExpr($1, $3); }
             | AMALAYO "(" expresion ")" { $$ = new UnaryExpr($1, $3); }
             | APOLAR  "(" expresion ")" { $$ = new UnaryExpr($1, $3); }
             | LON     "(" expresion ")" { $$ = new UnaryExpr($1, $3); }
             ;

%%

void yy::bear_parser::error ( const location_type& l,
                              const std::string& m  )
{
  driver.error (l, m);
}

std::vector<std::string>* extraerIds(std::vector<elementoLista>* ids)
{
  std::vector<std::string>* l = new std::vector<std::string>();
  for(unsigned int i = 0; i < ids->size(); ++i)
  {
    l->push_back(ids->at(i).nombre);
  }
  return l;

}
