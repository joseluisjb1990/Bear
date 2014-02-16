Proyecto de CI4721 - Lenguajes de Programación II de Gabriela Limonta (10-10385) y José Luis Jiménez (10-10839) en el trimestre Enero - Marzo 2014 en la Universidad Simón Bolívar.

***

Bear
===================

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
Se escriben utilizando comillas simples ( \' \' ).

Por ejemplo: 'A','F','i', etc.


### 5. Hormiguero

El tipo de dato `hormiguero` representa a una cadena de caracteres.
Se escriben utilizando comillas dobles (\" \").

Por ejemplo: "Hola esto es un hormiguero!", "y esto tambien lo es", etc.


### 6. Cueva

El tipo de dato `cueva` representa arreglos multidimensionales con índices de base cero.
Para acceder a los contenidos en una posicion determinada de la cueva se utilizan los `'[]'`:


*Cueva unidimensional:

El acceso a una cueva unidimensional se hace de la siguiente manera:

    cueva[<número>]


*Cueva bidimensional:

El acceso a una cueva bidimensional se hace de la siguiente manera:

    cueva[<número>][<número>]

...

*Cueva n-dimensional:

El acceso a una cueva n-dimensional se hace de la siguiente manera:

    cueva[<número>][<número>]...[<número>]


### 7. Pardo

El tipo de dato `pardo` representa estructuras arbitrariamente anidadas.

Para acceder a un campo del pardo se utiliza el operador `->` seguido del nombre del campo al que se quiere acceder.


### 8. Grizzli

El tipo de dato `grizzli` representa uniones arbitrariamente anidadas.

Para acceder a un campo del pardo se utiliza el operador `.` seguido del nombre del campo al que se quiere acceder.

### 9. Extinto

El tipo de dato `extinto` representa al vacio (void).


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

        <condición> ? <expresión1> : <expresión2>

Si se cumple la `<condición>` se ejecuta la `<expresión1>`, en caso contrario se ejecuta la `<expresión2>`.


### Iteracion acotada

Existen dos tipos de iteración acotada.

1) Iteración acotada con salto

        para <variable> en ( <expresión1>, <expresión2>, <expresión3> ) hacer <instrucción>

Se ejecuta la `<instrucción>` desde `<expresión1>` hasta `<expresión3>` incrementando en `<expresión3>` la variable por cada iteración.

2) Iteración acotada con salto predefinido 1

        para <variable> en ( <expresión1>, <expresión2> ) hacer <instrucción>

Se ejecuta la `<instrucción>` desde `<expresión1>` hasta `<expresión2>` incrementando por defecto en una unidad la variable por cada iteración.
Esto es equivalente a hacer:

        para <variable> en ( <expresión1>, 1, <expresión2> ) hacer <instrucción>


(Falta ver si se puede hacer lo del paso para poder tener iteraciones que vayan de dos en dos, de tres en tres y asi...)


### Iteracion indeterminada

    mientras <condición> hacer <instrucción>

Se ejecuta la `<instrucción>` mientras la `<condición>` sea negro.


### Declaraciones

    <declaración1>;
    <declaración2>;
    ...
    <declaraciónN>;

donde cada `<declaración>` tiene la siguiente forma:

    <tipo> <identificador>

o

    <tipo> <identificadores>

Se pueden tener una o mas declaraciónes en el código.
Toda declaración va seguida de un `;` que funciona como terminador.
Se pueden declarar varias variables de un mismo tipo en una sola línea si se coloca una lista de identificadores separados por comas.

Por ejemplo:

    <tipo> foo;
    <tipo> bar, baz;

Se puede inicializar la variable al momento de declararla.
(falta profundizar en esto, como se inicializan?)

A continuación se presenta como se hacen las declaraciones para cada tipo diferente del lenguaje:

**1) Panda**

Las declaraciones para el tipo `panda` se hacen de la siguiente manera:

    panda <identificador>

**2) Polar**

Las declaraciones para el tipo `polar` se hacen de la siguiente manera:

    polar <identificador>

**3) Kodiak**

Las declaraciones para el tipo `kodiak` se hacen de la siguiente manera:

    kodiak <identificador>

**4) Malayo**

Las declaraciones para el tipo `malayo` se hacen de la siguiente manera:

    malayo <identificador>

**5) Hormiguero**

Las declaraciones para el tipo `hormiguero` se hacen de la siguiente manera:

    hormiguero <identificador> 

**6) Cueva**

La declaración de una cueva **unidimensional** se hace de la siguiente manera:

    cueva [<número>] de <tipo> <identificador>;

La declaración de una cueva **bidimensional** se hace de la siguiente manera:

    cueva [<número>] de cueva [<numero>] de <tipo> <identificador>;

La declaración de una cueva **n-dimensional** se hace de la siguiente manera:

    cueva [<número>] de cueva [<numero>] de cueva [<numero>] (...) de <tipo> <identificador>;


**7) Pardo**

La declaración de un `pardo` se hace de la siguiente manera:

    pardo <identificador> {
      <tipo> <identificador>;
      <tipo> <identificador>;
      ...
      <tipo> <identificador>
    } <identificador>

Los campos del `pardo` se encuentran separados por `;`.

**8) Grizzli**

La declaración de un `grizzli` se hace de la siguiente manera:

    grizzli <identificador> {
      <tipo> <identificador>;
      <tipo> <identificador>;
      ...
      <tipo> <identificador>
    } <identificador>

Los campos del `grizzli` se encuentran separados por `;`.

**9) Funciones**

Las declaraciones de funciones se hacen de la siguiente manera:

    <nombre_funcion>(<tipo1> <nombre1>, ... <tipoN> <nombreN>) => <tipo_retorno>
      <instrucción>


## Expresiones


### 1) Expresiones con pandas

Una expresión de `panda` está formada por las constantes `blanco` y `negro`, variables, llamadas a funciones y operaciones con pandas.
Se consideran los operadores `&`, `|` y `no` para las operaciones and, or y not respectivamente.
Se utiliza notación infija para el `&` y `|` y prefija para el `no`. La precedencia de los operadores (de mayor a menor) es la siguiente:

* `no`
  
* `&`
  
* `|`


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

Una expresion de `polar` está formada por números naturales (secuencias de dígitos del 0 al 9), llamadas a funciones, variables y operaciones con polares.
Se consideran como operadores aritméticos la suma (`+`), la resta (`-`), el incremento (`++`), el decremento (`--`) la división entera (`/`), la multiplicación (`*`), el módulo (`%`) y el inverso (`-` unario).
Los operadores binarios usan operacion infija, el inverso utiliza notación prefija y por último el incremento y decremento utilizan notación postfija.

La precedencia de los operadores (de mayor a menor) es la siguiente:

* `-` (unario)

* `++`, `--`

* `*`, `/`, `%`

* `+`, `-`

Ambos operandos de los operadores binarios deben ser del mismo tipo.
Si los operandos son de tipo `polar` el resultado también será de tipo `polar`.
El operando de `lon` debe ser de tipo `hormiguero` y retorna algo de tipo `polar`.
El operando de `++` y `--` debe ser una variable de tipo `polar`.


### 3) Expresiones con hormigueros

Una expresión de `hormiguero` está formada por una cadena de malayos denotada por comillas dobles (\" \") que puede contener cualquier caracter, llamadas a funciones, variables, y operaciones con hormigueros.



-------------------------------------------------------------------


*debemos explicar las expresiones con los demas tipos de datos???*


--------------------------------------------------------------------



## Reglas de alcance de variables

En Bear existe alcance estático.

## Funciones predefinidas

Bear provee las siguientes funciones predefinidas:

* `lon(x)` : toma un `hormiguero` o una `cueva` y devuelve un `polar` indicando la longitud del `hormiguero` o `cueva` según sea el caso.
* `concat(x,y)` : ambos argumentos son de tipo `hormiguero` y devuelve un nuevo elemento de tipo `hormiguero` que contiene la concatenación de los argumentos.


## Conversiones explicitas

Bear provee las siguientes funciones para convertir tipos:

* `a_kodiak(x)` : convierte la expresión x de tipo `polar` a un `kodiak`.

* `a_polar(x)` : convierte la expresión x de tipo `kodiak`, `hormiguero` o `malayo` a  un `polar`.

* `a_malayo(x)` : convierte la expresión x de tipo `polar` a un `malayo`.

* `a_hormiguero(x)` : convierte la expresión x de tipo `polar` a un `hormiguero`.


## Comentarios

Existen dos maneras de hacer comentarios en Bear.

1) Comentarios de una línea.

        <3 Este es un programa en el lenguaje Bear
        <3 definitivamente este es mi lenguaje favorito.
        <3 porque mira que lindos se ven estos comentarios
        <3 con muuuuuuuuchos corazones. Así puedo hacer
        <3 un código lleno de amor.

Toda línea que comience por `<3` es un comentario en el lenguaje Bear.

2) Comentarios por bloque.

        --<3 Este es un programa en el lenguaje Bear
             definitivamente este es mi lenguaje favorito.
             porque puedo poner mis comentarios llenos de amor
             hacia el código y cuando lo hago en bloques puedo
             incluso flechar a los lectores de mi codigo
             wow such comment very programmer <3->

Todo bloque de texto que comience en `--<3` y termine en `<3->` es un comentario en el lenguaje Bear.

En Bear los comentarios se realizan con corazones ya que comentar tu código es hacerlo con mucho amor.
Al no comentar demuestras poco amor hacia el código y hacia la futura persona que pueda leerlo :(.
