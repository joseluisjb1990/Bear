# Bear

## Palabras reservadas

Las siguientes son palabras reservadas del lenguaje, no pueden ser redefinidas ni utilizadas como identificadores.

--------------   ----------   -------------   ----------   -------   ----------
`a_hormiguero`   `cueva   `   `fin        `   `leer    `   `no   `   `vomita  `
`a_kodiak    `   `de      `   `fondoBlanco`   `lon     `   `oso  `   `roloePea`
`a_malayo    `   `entonces`   `grizzli    `   `malayo  `   `panda`   `si      `
`a_polar     `   `escribir`   `hormiguero `   `mientras`   `pardo`   `sino    `
`blanco      `   `extinto `   `kodiak     `   `negro   `   `polar`
--------------   ----------   -------------   ----------   -------   -----------


## Estructura de un programa

Todo programa escrito en Bear tiene la siguiente estructura:

    oso <instrucción>

(aca falta completar con como es la estructura con eso de las funciones que no sabemos que hacer)


## Tipos de datos


### 1. Panda

El tipo de dato `panda` representa a los booleanos. Puede ser Negro (true) o Blanco (false).


### 2. Polar

El tipo de dato `polar` representa a los números enteros. Son números enteros de 32 bits.


### 3. Kodiak

El tipo de dato `kodiak` representa a los números de punto flotante de 32 bits.


### 4. Malayo

El tipo de dato `malayo` representa a un caracter ASCII.
Se escriben utilizando comillas simples ( ' ' ).

Por ejemplo: 'A','F','i', etc.


### 5. Hormiguero

El tipo de dato `hormiguero` representa a una cadena de caracteres.
Se escriben utilizando comillas dobles ("").

Por ejemplo: "Hola esto es un hormiguero!", "y esto tambien lo es", etc.


### 6. Cueva

El tipo de dato `cueva` representa arreglos multidimensionales con índices de base cero.
Para acceder a los contenidos en una posicion determinada de la cueva se utilizan los '[]':


*Cueva unidimensional:

La declaración de una cueva unidimensional se hace de la siguiente manera:

    cueva <identificador> [<número>] de <tipo>;


El acceso a una cueva unidimensional se hace de la siguiente manera:

    cueva[<número>]


*Cueva bidimensional:

La declaración de una cueva bidimensional se hace de la siguiente manera:

    cueva <identificador> [<número>] de cueva [<numero>] de <tipo>;

El acceso a una cueva bidimensional se hace de la siguiente manera:

    cueva[<número>][<número>]

...

*Cueva n-dimensional:

La declaración de una cueva n-dimensional se hace de la siguiente manera:

    cueva <identificador> [<número>] de cueva [<numero>] de cueva [<numero>] (...) de <tipo>;

El acceso a una cueva n-dimensional se hace de la siguiente manera:

    cueva[<número>][<número>]...[<número>]


### 7. Pardo

El tipo de dato `pardo` representa estructuras arbitrariamente anidadas.

La declaración de un pardo se hace de la siguiente manera:

    pardo <identificador> {
      <tipo> <identificador>;
      <tipo> <identificador>;
      ...
      <tipo> <identificador>;
    }

Para acceder a un campo del pardo se utiliza el operador `->` seguido del nombre del campo al que se quiere acceder.


### 8. Grizzli

El tipo de dato `grizzli` representa uniones arbitrariamente anidadas.

La declaración de un grizzli se hace de la siguiente manera:

    grizzli <identificador> {
      <tipo> <identificador>;
      <tipo> <identificador>;
      ...
      <tipo> <identificador>;
    }

Para acceder a un campo del pardo se utiliza el operador `.` seguido del nombre del campo al que se quiere acceder.


## Instrucciones

A continuación se presentan las diferentes instrucciones que posee el lenguaje Bear.


### Asignación

    <variable> = <expresión>

La asignación tiene el efecto de almacenar en la variable <variable> el valor de <expresión>.
El tipo de la variable y de la expresión debe coincidir y en caso contrario se debe arrojar un error.


### Bloque

    {
    <instrucción1>;
    <instrucción2>;
    ...
    <instrucciónN>;
    }

Los bloques van encerrados entre llaves y contienen un conjunto de instrucciones a ejecutar.
(Aun no decidimos como manejar las declaraciones, si serán todas obligatorias al inicio o si se pueden hacer en cualquier lugar del programa.)


### Entrada

    leer(<variable>);

Lee el contenido de la entrada estándar y lo almacena en la variable <variable>.
Lo que se lee debe ser del tipo de la variable.
<variable> debe ser de alguno de los tipos primitivos.


### Salida

    escribir(<variable>)

Escribe el contenido de variable en la salida estándar.
La `<variable>` debe ser de alguno de los tipos primitivos.
También puede utilizarse directamente con alguna constante de tipo primitivo.

Por ejemplo:

    escribir("Hola Mundo!");

    escribir('A');

    escribir(42);

    escribir(42.0);


### Selector

Existen tres tipos de selectores en el lenguaje:

1) Condicional if-then-else:

        si <condición> entonces <instrucción1>
                       sino     <instrucción2>
                       fin;

Si se cumple la `<condición>` se ejecuta la `<instrucción1>`, en caso contrario se ejecuta la `<instrucción2>`.


2) Condicional if-then:

        si <condición> entonces
          <instrucción>
        fin;

Si se cumple la `<condición>` se ejecuta la `<instrucción>`


3) Condicional if-then-else simplificado:

        <condición> ? <instrucción1> : <instrucción2>

Si se cumple la `<condición>` se ejecuta la `<instrucción1>`, en caso contrario se ejecuta la `<instrucción2>`.
Las instrucciones 1 y 2 deben ser instrucciones simples; es decir, no pueden ser bloques que contengan mas instrucciones.


### Iteracion acotada

        para <variable> en <<número1>, <número2>> <instrucción>

Se ejecuta la `<instrucción>` desde el `<número1>` hasta el `<número2>` incrementando en una unidad la variable por cada iteración.
(Falta ver si se puede hacer lo del paso para poder tener iteraciones que vayan de dos en dos, de tres en tres y asi...)


### Iteracion indeterminada

    mientras <condición> <instrucción>

Se ejecuta la `<instrucción>` mientras la `<condición>` sea negro.


### Declaraciones

    <tipo1> <identificador1>;
    <tipo2> <identificador2>;
    ...
    <tipoN> <identificadorN>;

Las declaraciones se hacen indicando el tipo de la variable y luego el nombre de la misma. Se pueden declarar varias variables de un mismo tipo en una sola línea.

Por ejemplo:

    panda jose, gaby;

Se puede inicializar la variable al momento de declararla.

Las declaraciones de funciones se hacen de la siguiente manera:

    <nombre_funcion>(<tipo1> <nombre1>, ... <tipoN> <nombreN>) => <tipo_retorno>
      <instrucción>


## Expresiones


### 1) Expresiones con pandas

Una expresión de `panda` está formada por las constantes `blanco` y `negro`, variables, llamadas a funciones y operadores booleanos.
Se consideran los operadores `&`, `|` y `no` para las operaciones and, or y not respectivamente.
Se utiliza notación infija para el `&` y `|` y prefija para el `no`. La precedencia de los operadores (de mayor a menor) es la siguiente:

*`no`

*`&`

*`|`


Los operandos de `&`, `|` y `no` deben ser de tipo `panda` al igual que su resultado.

Se tienen ademas operadores relacionales capaces de comparar polares y kodiaks.
Los operadores disponibles son: igualdad (`==`), diferencia (`=/=`), mayor que (`>`), mayor o igual que (`>=`), menor que (`<`), menor o igual que (`=<`).
Ambos operadores deben ser del mismo tipo y el resultado será del tipo `panda`.

También se pueden comparar expresiones de tipo `panda` utilizando los operadores `==` y `=/=`.

Los operadores relacionales no son asociativos exceptuando los operadores `==` y `=/=` que asocian a la izquierda.

La precedencia de los operadores relacionales (de mayor a menor) es la siguiente:

* `>`, `>=`, `<`, `=<`

* `==`, `=/=`


### 2) Expresiones con polares

Una expresion de `polar` está formada por números naturales (secuencias de dígitos del 0 al 9), llamadas a funciones, variables y operadores aritméticos.
Se consideran como operadores aritméticos la suma (`+`), la resta (`-`), el incremento (`++`), el decremento (`--`) la división entera (`/`), la multiplicación (`*`), el módulo (`%`) y el inverso (`-` unario).
Se considera también como operador la longitud de un `hormiguero` o `cueva` (`lon`).
Los operadores binarios usan operacion infija, el inverso y `lon` utilizan notación prefija y por último el incremento y decremento utilizan notación postfija.

La precedencia de los operadores (de mayor a menor) es la siguiente:

* `-` (unario)

* `lon`, `++`, `--`

* `*`, `/`, `%`

* `+`, `-`

Ambos operandos de los operadores binarios deben ser del mismo tipo.
Si los operandos son de tipo `polar` el resultado también será de tipo `polar`.
El operando de `lon` debe ser de tipo `hormiguero` y retorna algo de tipo `polar`.
El operando de `++` y `--` debe ser una variable de tipo `polar`.


### 3) Expresiones con hormigueros

Una expresión de `hormiguero` está formada por una cadena de malayos denotada por "" que puede contener cualquier caracter, llamadas a funciones, variables, y operadores de hormigueros.
Se consideran como operadores de hormigueros la concatenación (`++`) y la longitud (`lon`).
La concatenación utiliza notación infija y la longitud utiliza notación prefija.

La precedencia de los operadores (de mayor a menor) es la siguiente:

* `lon`

* `++`

Los operandos de `++` deben ser ambos de tipo `hormiguero` y su resultado es de tipo `hormiguero` también.







*debemos explicar las expresiones con los demas tipos de datos???*
donde ponemos las funciones en este documento??






## Reglas de alcance de variables


## Conversiones explicitas

Bear provee las siguientes funciones para convertir tipos:

* `a_kodiak(x)` : convierte la expresión x de tipo `polar` a un `kodiak`.

* `a_polar(x)` : convierte la expresión x de tipo `kodiak`, `hormiguero` o `malayo` a  un `polar`.

* `a_malayo(x)` : convierte la expresión x de tipo `polar` a un `malayo`.

* `a_hormiguero(x)` : convierte la expresión x de tipo `polar` a un `hormiguero`.


## Comentarios

    <3 Este es un programa en el lenguaje Bear
    <3 definitivamente este es mi lenguaje favorito.
    <3 porque mira que lindos se ven estos comentarios
    <3 con muuuuuuuuchos corazones. Así puedo hacer
    <3 un código lleno de amor.

Toda línea que comience por `<3` es un comentario en el lenguaje Bear.
Solo hay comentarios de una línea, no existen comentarios por bloques.
