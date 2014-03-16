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

# undef yywrap
# define yywrap() 1

// The location of the current token.
static yy::location loc;
%}
%option noyywrap nounput batch debug noinput

%x comentario

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

"<3".*   { loc.step(); };

"--<3"   {  loc.step(); BEGIN(comentario); }

<comentario>{
  "<3->"   { loc.step(); BEGIN(INITIAL);                                                             }
  [^<\n]+  { loc.step();                                                                             }
  "<"      { loc.step();                                                                             }
  \n       { loc.lines(1); loc.step();                                                               }
  <<EOF>>  { driver.error(loc, "Comentario sin terminar :("); return yy::bear_parser::make_END(loc); }
}

{DIGIT}+  { return yy::bear_parser::make_CONSTPOLAR(yytext, loc); }

{DIGIT}+\.{DIGIT}*  { return yy::bear_parser::make_CONSTKODIAK(yytext, loc); }

{DIGIT}+(\.{DIGIT})?e-?{DIGIT}+  { return yy::bear_parser::make_CONSTKODIAK(yytext, loc);}

'.'|'\\n'   { return yy::bear_parser::make_CONSTMALAYO(yytext, loc);}

\"([^\"\n])*\"  { return yy::bear_parser::make_CONSTHORMIGUERO(yytext, loc); }
\"([^\"\n])*    { driver.error(loc, "String incompleto");                    }

blanco      { return yy::bear_parser::make_BLANCO(yytext, loc);      }
negro       { return yy::bear_parser::make_NEGRO(yytext, loc);       }
no          { return yy::bear_parser::make_NO(loc);                  }
oso         { return yy::bear_parser::make_OSO(loc);                 }
extinto     { return yy::bear_parser::make_EXTINTO(yytext, loc);     }
const       { return yy::bear_parser::make_CONST(yytext, loc);       }
cueva       { return yy::bear_parser::make_CUEVA(yytext, loc);       }
de          { return yy::bear_parser::make_DE(yytext, loc);          }
pardo       { return yy::bear_parser::make_PARDO(yytext, loc);       }
grizzli     { return yy::bear_parser::make_GRIZZLI(yytext, loc);     }
leer        { return yy::bear_parser::make_LEER(yytext, loc);        }
escribir    { return yy::bear_parser::make_ESCRIBIR(yytext, loc);    }
si          { return yy::bear_parser::make_SI(yytext, loc);          }
entonces    { return yy::bear_parser::make_ENTONCES(yytext, loc);    }
sino        { return yy::bear_parser::make_SINO(yytext, loc);        }
para        { return yy::bear_parser::make_PARA(yytext, loc);        }
en          { return yy::bear_parser::make_EN(yytext, loc);          }
vomita      { return yy::bear_parser::make_VOMITA(yytext, loc);      }
fondoBlanco { return yy::bear_parser::make_FONDOBLANCO(yytext, loc); }
roloePea    { return yy::bear_parser::make_ROLOEPEA(yytext, loc);    }
a_panda     { return yy::bear_parser::make_APANDA(yytext, loc);      }
a_malayo    { return yy::bear_parser::make_AMALAYO(yytext, loc);     }
a_polar     { return yy::bear_parser::make_APOLAR(yytext, loc);      }
a_kodiak    { return yy::bear_parser::make_AKODIAK(yytext, loc);     }
lon         { return yy::bear_parser::make_LON(yytext, loc);         }
mientras    { return yy::bear_parser::make_MIENTRAS(yytext, loc);    }

{ID}   { return yy::bear_parser::make_ID(yytext, loc); }

[\n]  { loc.lines(1); loc.step (); }

[ \t]+ { loc.step (); }


"("   { return yy::bear_parser::make_ABREPARENTESIS(loc);   }
")"   { return yy::bear_parser::make_CIERRAPARENTESIS(loc); }
"{"   { return yy::bear_parser::make_ABRELLAVE(loc);        }
"]"   { return yy::bear_parser::make_CIERRACORCHETE(loc);   }
"["   { return yy::bear_parser::make_ABRECORCHETE(loc);     }
"}"   { return yy::bear_parser::make_CIERRALLAVE(loc);      }
":"   { return yy::bear_parser::make_DOSPUNTOS(loc);        }
"?"   { return yy::bear_parser::make_INTERROGACION(loc);    }
"+"   { return yy::bear_parser::make_SUMA(loc);             }
"++"  { return yy::bear_parser::make_INCREMENTO(loc);       }
"-"   { return yy::bear_parser::make_MENOS(loc);            }
"--"  { return yy::bear_parser::make_DECREMENTO(loc);       }
"*"   { return yy::bear_parser::make_MULTIPLICACION(loc);   }
"**"  { return yy::bear_parser::make_POTENCIA(loc);         }
"/"   { return yy::bear_parser::make_DIVISION(loc);         }
"%"   { return yy::bear_parser::make_MODULO(loc);           }
"&"   { return yy::bear_parser::make_AND(loc);              }
"|"   { return yy::bear_parser::make_OR(loc);               }
"<"   { return yy::bear_parser::make_MENOR(loc);            }
">"   { return yy::bear_parser::make_MAYOR(loc);            }
"=<"  { return yy::bear_parser::make_MENORIGUAL(loc);       }
">="  { return yy::bear_parser::make_MAYORIGUAL(loc);       }
"=="  { return yy::bear_parser::make_IGUALDAD(loc);         }
"=/=" { return yy::bear_parser::make_DIFERENCIA(loc);       }
";"   { return yy::bear_parser::make_PUNTOCOMA(loc);        }
","   { return yy::bear_parser::make_COMA(loc);             }
"="   { return yy::bear_parser::make_ASIGNACION(loc);       }
"=>"  { return yy::bear_parser::make_FLECHARETORNO(loc);    }
"->"  { return yy::bear_parser::make_FLECHA(loc);           }
"."   { return yy::bear_parser::make_PUNTO(loc);            }
"^"   { return yy::bear_parser::make_TECHO(loc);            }


<<EOF>>    return yy::bear_parser::make_END(loc);

.  driver.error(loc, "Caracter inesperado");

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
