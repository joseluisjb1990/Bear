%{

%}

DIGIT    [0-9]
ID       [a-zA-Z][a-zA-Z0-9\?!_]*
CHAR     [a-zA-Z0-9]

%option noyywrap

%%

"<3".* { printf("Comentario : %s \n" , yytext); }  /* eat up one-line comments */

'[a-zA-Z0-9]?'    { printf("Caracter: %s\n", yytext); }

{DIGIT}+    {
            printf( "An integer: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }

{DIGIT}+","{DIGIT}*        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }

'(\\.|[^\\\"])?'   { printf("Un caracter %s \n", yytext); }

oso|panda|negro|blanco|polar|kodiak|hormiguero|cueva|de|pardo|grizzli|malayo|extinto|leer|escribir|si|entonces|fin|sino|no|lon|a_kodiak|a_polar|a_malayo|a_hormiguero|roloePea|fondoBlanco|vomita|mientras {
            printf( "A keyword: %s\n", yytext );
            }

{ID}        printf( "An identifier: %s\n", yytext );

\"(\\.|[^\\\"])*\"  printf( "Un string: %s \n", yytext);

"["        printf("Abre corchete\n");
"]"        printf("Cierra corchete\n");
"("        printf("Abre parentesis\n");
")"        printf("Cierra parentesis\n");
"{"        printf("Abre llaves\n");
"}"        printf("Cierra llaves\n");
"=>"       printf("Flecha doble\n");
"="        printf("Asignacion\n");
"."        printf("Punto\n");
";"        printf("Punto y coma\n");
":"        printf("Dos puntos\n");
"->"       printf("Flecha simple\n");
","        printf("Coma\n");
"?"        printf("Signo de interrogacion\n");

"+"|"-"|"*"|"/"|"%"|"++"|"&"|"|"|"<"|">"|"=<"|">="|"=="|"=/="   printf( "An operator: %s\n", yytext );

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    }
