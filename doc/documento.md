# Bear


## Consideraciones Léxicas

Las siguientes son palabras reservadas del lenguaje, no pueden ser redefinidas ni utilizadas como identificadores (de variables, funciones, etc).

--------------   ----------   -------------   ----------   -------   ----------
`a_kodiak    `   `cueva   `   `fin        `   `leer    `   `no   `   `vomita  `
`a_malayo    `   `de      `   `fondoBlanco`   `lon     `   `oso  `   `roloePea`
`a_panda     `   `entonces`   `grizzli    `   `malayo  `   `panda`   `si      `
`a_polar     `   `escribir`   `hormiguero `   `mientras`   `pardo`   `sino    `
`blanco      `   `extinto `   `kodiak     `   `negro   `   `polar`
--------------   ----------   -------------   ----------   -------   -----------

Los identificadores son secuencias de caracteres alfanuméricos, el símbolo underscore (`_`), el símbolo de interrogación (`?`) y/o el símbolo de exclamación (`!`), y deben comenzar por una letra en minúscula o mayúscula.

Los identificadores son sensibles a mayúsculas; es decir, los nombres `foo`, `Foo`, `FOO` y `FoO` son todos identificadores diferentes.

Los números enteros solamente pueden escribirse en base decimal. Los números en base decimal son cualquier secuencia de dígitos entre 0 y 9.

Los números con parte fraccionaria de igual manera solo pueden ser escritos en base decimal.
Estos se constituyen por una secuencia no vacía de dígitos entre 0 y 9, seguida de un punto (`.`) y otra secuencia no vacía de dígitos entre 0 y 9.
También es posible agregar el exponente escribiendo "`e`" seguido de uno o mas dígitos entre 0 y 9.
Al mismo tiempo se puede especificar el signo del exponente agregando un `+` o `-` antes del exponente.
El exponente indica que el número antes del mismo se multiplica por diez (10) elevado al número indicado como exponente.

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


## Estructura de un programa

Todo programa escrito en Bear tiene la siguiente estructura:

    [definiciones] oso() => extinto <instrucción>

El punto de entrada del programa es la función principal `oso` que no toma parametros y tiene retorno `extinto`.
Anterior a la misma es posible hacer la declaración de constantes, variables y funciones que se desee.
Los corchetes (`[ ]`) indican que estas definiciones son opcionales.
Por último tenemos el cuerpo de nuestra función principal `oso` que puede ser una instrucción o un bloque de instrucciones.


## Reglas de alcance de variables

En Bear existe alcance estático.


## Tipos de datos

### Escalares:


**1. Panda**

El tipo de dato `panda` representa a los valores booleanos.
Puede tomar solamente dos valores: `negro`, correspondiente a los valores "verdaderos" y `blanco`, correpondiente a los valores "falsos".


**2. Polar**

El tipo de dato `polar` corresponde a los números enteros.
Son números enteros de 32 bits.


**3. Kodiak**

El tipo de dato `kodiak` corresonde a los números de punto flotante IEEE-754 de 32 bits.


**4. Malayo**

El tipo de dato `malayo` representa a un caracter ASCII.
Se escriben utilizando comillas simples ( `' '` ).

Por ejemplo: 'A','F','i', etc.


### Compuestos:

**1. Cueva**

El tipo de dato `cueva` representa arreglos multidimensionales con índices de base cero.
Representan una colección homogenea, el tipo de los elementos de una cueva puede ser cualquiera exceptuando `extinto`.
Para acceder a los contenidos en una posicion determinada de la cueva se utilizan los `'[ ]'`:


* Cueva unidimensional:

El acceso a una cueva unidimensional se hace de la siguiente manera:

    cueva[<número>]


* Cueva bidimensional:

El acceso a una cueva bidimensional se hace de la siguiente manera:

    cueva[<número>][<número>]

...

* Cueva n-dimensional:

El acceso a una cueva n-dimensional se hace de la siguiente manera:

    cueva[<número>][<número>]...[<número>]

El número de elementos en un arreglo no puede modificarse luego de ser declarado.

Las cuevas se indexan desde cero hasta una posición antes de su longitud.
El indice utilizado debe ser de tipo `polar`.

Si se intenta acceder a una posición fuera de los límites de la cueva hay una error a tiempo de ejecución.


**2. Pardo**

El tipo de dato `pardo` representa estructuras arbitrariamente anidadas.
Este mecanismo permite al usuario crear sus propios tipos de datos.
Representa una colección de campos de tipos heterogéneos.

La declaración de un pardo se hace de la siguiente manera:

    pardo <nombre> {
      <tipo> <identificador>;
      <tipo> <identificador>;
      ...
      <tipo> <identificador>;
    }

Las variables dentro de un pardo pueden ser de cualquier tipo exceptuando `extinto`, `hormiguero` o el mismo `pardo` que se esta definiendo para evitar una recursión infinita.

Para acceder a un campo del pardo se utiliza el operador `->` seguido del nombre del campo al que se quiere acceder.


**3. Grizzli**

El tipo de dato `grizzli` representa uniones arbitrariamente anidadas.
Este, junto con los pardos, son los únicos mecanismos que permiten al usuario crear sus propios tipos de datos.
(por ahora, hasta que decidamos si se va a hacer lo del discriminante oculto)
Las uniones en Bear son como las de C.
Es responsabilidad del usuario utilizar el grizzli en un contexto adecuado.

La declaración de un grizzli se hace de la siguiente manera:

    grizzli <nombre> {
      <tipo> <identificador>;
      <tipo> <identificador>;
      ...
      <tipo> <identificador>;
}

Debido a su semejanza física mucha gente suele confundir a los osos pardos y grizzli.
Dado que la declaración de un pardo y un grizzli en bear es semejante (solo varían en la palabra clave `pardo` y `grizzli`) podría ocurrir lo mismo que pasa con estos osos en la vida real.
Para evitar confusiones presentamos a continuación la diferencia entre ambos.
En un grizzli solamente uno de los campos definidos puede estar activo a la vez, en cambio en el pardo tenemos una colección de campos.

Para acceder a un campo del pardo se utiliza el operador `.` seguido del nombre del campo al que se quiere acceder.


### Especiales:

**1. Hormiguero**

El tipo de dato `hormiguero` representa a una secuencia de caracteres ASCII inmutable.
Al momento de declaración deben ser inicializados y su valor es constante durante la ejecución del programa.
Se escriben utilizando comillas dobles (`" "`).
(falta decir que tipo de caracter no pueden contener, por ahora se pueden escribir strings en lineas diferentes)


Por ejemplo: "Hola esto es un hormiguero!", "y esto tambien lo es", etc.

**2. Extinto**

El tipo de dato `extinto` representa al vacio.
Solo puede ser utilizado para indicar que una función no retorna algún valor.


## Variables

Las variables en Bear pueden declararse de cualquier tipo exceptuando el tipo `extinto`, incluyendo arreglos y tipos definidos por el usuario.

Las variables que se declaren fuera de algun alcance local tienen alcance global por defecto.
Las variables declaradas dentro del cuerpo de una función tienen alcance local, al igual que los parametros de una función se comportan como variables declaradas al inicio del cuerpo de la función con alcance local.

### Declaración de variables

La declaración de variables se hace de la siguiente manera:

    <tipo> <identificador>;                <3 declaración sin inicialización
    <tipo> <identificador> = <expresión>;  <3 declaración con inicialización

El tipo puede ser cualquier tipo escalar, `hormiguero`, o nombre de `pardo` o `grizzli` definido por el usuario.

Las variables de tipo `hormiguero` deben ser inicializadas siempre.

(que pasa si no se inicializan las variables? se ponen valores por defecto?)

El tipo de `<expresión>` y `<tipo>` deben coincidir.

Es posible además declarar mas de una variable en una misma línea e inicializarlas simultaneamente.
Esto se hace de la siguiente manera:

    panda foo, bar, baz;                 <3 lista de variables declaradas, sin inicializar
    polar qux, quux, corge = 42, 27, 32; <3 lista de variables declaradas e inicializadas

(que pasa si tengo listas de diferente longitud entre los identificadores y las expresiones. Se inicializan unas si y otras no ? que pasa si faltan variables y sobran expresiones? )

La declaración de una cueva se hace de la siguiente manera:

    cueva [<numero>] de <tipo> <identificador>;

El tipo del contenido de la cueva debe ser algún tipo escalar, nombre de `pardo` o `grizzli` definido por el usuario o incluso otra cueva, notese que esto nos permite construir cuevas multidimensionales.

Las cuevas no pueden ser inicializadas al momento de declaración. Tampoco se puede asignar directamente a ellas. La unica manera de introducir valores es accediendo a sus casillas individuales. Por ejemplo:

    a[1]    = 2;
    a[2][4] = 42;


## Funciones

La declaración de una función en Bear se hace de la siguiente manera:

    <nombre>(<tipo1> <nombre1>, ..., <tipoN> <nombreN>) => <tipo> {
      [declaraciones]
      <instrucciones>
      [vomita <expresión>]
    }

El tipo de la función solo puede ser de algún tipo escalar o `extinto`.

Opcionalmente se pueden declarar nuevas variables locales a la función.o

Para cualquier función que no tenga como tipo de retorno `extinto` es obligatorio tener la instrucción `vomita`.
Si el tipo de retorno es `extinto` entonces si aparece la instrucción `vomita` no puede estar acompañada de alguna expresión.

El pasaje de parámetros para los tipos escalares y hormigueros se hace por valor, para los tipos compuestos y los definidos por el usuario se hace por referencia.

(Permitimos un mecanismo para pasar tipos escalares por referencia?)

Las funciones admiten recursión.

Los parametros de tipo `cueva` se definen como sigue:

    extinto funcion(cueva[] de panda foo, cueva[] de cueva[42] de polar bar) {
    ...
    }

Para las cuevas unidimensionales no es necesario saber la primera dimensión; sin embargo, de dos dimensiones en adelante es necesario saberlas.

### Invocación de funciones

Se pueden utilizar las funciones en cualquier expresión a menos que sea una función declarada con tipo de retorno `extinto`. Por ejemplo:

    foo = 24 + f(12);

También es posible utilizar una función como una instrucción, cuando las mismas son declaradas con tipo de retorno `extinto`. Por ejemplo:

    foo(a,b,c);


## Asignación

    a0, a1, a2, ..., aN = e0, e1, e2, ..., eN

La asignación tiene el efecto de almacenar simultaneamente en las variables a0 .. aN el resultado de evaluar las expresiones e0 .. eN.
Los tipos de la variables y de las expresiones deben coincidir y en caso contrario se debe arrojar un error.

------------------------------------------------------------------
## Bloque
(Por ahora vamos a dejar esto de los bloques por aca hasta que decidamos si se van o se quedan.)

    {
    <instrucción1>;
    <instrucción2>;
    ...
    <instrucciónN>;
    }

Los bloques van encerrados entre llaves y contienen un conjunto de instrucciones a ejecutar.
(Aun no decidimos como manejar las declaraciones, si serán todas obligatorias al inicio o si se pueden hacer en cualquier lugar del programa.)
------------------------------------------------------------------

## Entrada

    leer(<variable>);

Lee el contenido de la entrada estándar y lo almacena en la variable <variable>.
Lo que se lee debe ser del tipo de la variable.
<variable> debe ser de alguno de los tipos escalares.


## Salida

    escribir(<variable>)

Escribe el contenido de variable en la salida estándar.
La `<variable>` debe ser de alguno de los tipos escalares.
También puede utilizarse directamente con alguna constante de tipo escalar.

Por ejemplo:

    escribir("Hola Mundo!");

    escribir('A');

    escribir(42);

    escribir(42.0);


## Estructuras de control

### Selector

Existen dos tipos de selectores en el lenguaje:

1) Condicional if-then:

        si <condición> entonces
          <instrucción>
        fin;

Si se cumple la `<condición>` se ejecuta la `<instrucción>`

2) Condicional if-then-else:

        si <condición> entonces <instrucción1>
                       sino     <instrucción2>
                       fin;

Si se cumple la `<condición>` se ejecuta la `<instrucción1>`, en caso contrario se ejecuta la `<instrucción2>`.

### Iteracion acotada

        para <variable> en ( <expresión1>, <expresión2>, <expresión3> ) hacer {
          <instrucción>
        }

Se ejecuta la `<instrucción>` desde `<expresión1>` hasta `<expresión3>` incrementando en `<expresión2>` la variable por cada iteración.

* La `<variable>` se declara automáticamente de tipo `polar` y solo es visible dentro del bloque de la iteración.

* La `<variable>` no puede ser modificada por el usuario.

* `<expresión1>`, `<expresión2>` y `<expresión3>` se evalúan una sola vez antes del primer ciclo.

* `<expresión2>` corresponde al aumento que se hace en cada iteración por lo que debe ser un número de tipo `polar` y positivo.

* Los límites de la iteración se revisan antes de comenzar la primera iteración, en caso de ser vacíos no se ejecuta ninguna iteración.

* `<expresión2>` es opcional, en caso de omitirla toma como valor por defecto el numero entero uno (1).


### Iteracion indeterminada

    mientras <condición> hacer {
      <instrucción>
    }

Se ejecuta la `<instrucción>` mientras la `<condición>` sea `negro`.
`<condición>` debe ser de tipo `panda`.
La `<condición>` se verifica al inicio de cada ciclo.

### Etiquetas, roloePea, fondoBlanco

Cualquier iteración indeterminada puede ser etiquetada. Por ejemplo:

    <etiqueta>: mientras <condición> hacer {
      <instrucción>
    }

Es posible anidar iteraciónes etiquetadas mientras los nombres de las etiquetas sean distintos.

Dentro de una iteración es posible utilizar la instrucción `roloePea` para finalizar la iteración.
Por defecto un `roloePea` rompe la iteración mas interna (cercana al `roloePea`).
Opcionalmente se puede hacer un `roloePea` con etiqueta, en este caso se rompe la iteración que tenga esa etiqueta. Por ejemplo:

    externa: mientras negro hacer {
      interna: mientras negro hacer {
        ...
        roloePea;         <3 rompe la iteración interna.
        ...
        roloePea externa; <3 rompe la iteración cuya etiqueta es externa.
      }
    }

El `fondoBlanco` funciona igual que el `roloePea`, con la diferencia de que en vez de finalizar la iteración, salta al siguiente ciclo.


## Incremento

    <variable>++

Es el equivalente de hacer <variable> = <variable> + 1.

## Decremento

    <variable>--

Es el equivalente de hacer <variable> = <variable> - 1.


## Expresiones



### 1) Expresiones con pandas

Una expresión de `panda` está formada por las constantes `blanco` y `negro`, variables, llamadas a funciones y operaciones con pandas.
Se consideran los operadores `&`, `|` y `no` para las operaciones and, or y not respectivamente.
Se utiliza notación infija para el `&` y `|` y prefija para el `no`. La precedencia de los operadores (de mayor a menor) es la siguiente:

* `no`
  
* `&`
  
* `|`


Los operandos de `&`, `|` y `no` deben ser de tipo `panda` al igual que su resultado.

Se tienen ademas operadores relacionales capaces de comparar polares, malayos y kodiaks
Los operadores disponibles son: igualdad (`==`), diferencia (`=/=`), mayor que (`>`), mayor o igual que (`>=`), menor que (`<`), menor o igual que (`=<`).
Ambos operadores deben ser del mismo tipo y el resultado será del tipo `panda`.

También se pueden comparar expresiones de tipo `panda` utilizando los operadores `==` y `=/=`.

Los operadores relacionales no son asociativos exceptuando los operadores `==` y `=/=` que asocian a la izquierda.

La precedencia de los operadores relacionales (de mayor a menor) es la siguiente:

* `>`, `>=`, `<`, `=<`

* `==`, `=/=`

Ademas es posible tener un selector que dada una `<condición>` de tipo `panda` si es `negro` corresponde entonces a la `<expresión1>` y si es `blanco` corresponde a la `<expresión2>`

        <condición> ? <expresión1> : <expresión2>

donde `<expresión1>` y `<expresión2>` son de tipo `panda`.


### 2) Expresiones con polares

Una expresion de `polar` está formada por números naturales (secuencias de dígitos del 0 al 9), llamadas a funciones, variables y operaciones con polares.
Se consideran como operadores aritméticos la suma (`+`), la resta (`-`), la división entera (`/`), la multiplicación (`*`), el módulo (`%`), la potenciación (`**`) y el inverso (`-` unario).
Los operadores binarios usan operacion infija y el inverso utiliza notación prefija.

La precedencia de los operadores (de mayor a menor) es la siguiente:

* `-` (unario)

* `**`

* `*`, `/`, `%`

* `+`, `-`

Ambos operandos de los operadores binarios deben ser del mismo tipo.
Si los operandos son de tipo `polar` el resultado también será de tipo `polar`.


### 3 Expresioens con kodiaks

Una expresion de `kodiak` está formada por números con partes decimales (anteriormente se explica la sintaxis para escribir los mismos), llamadas a funciones, variables y operaciones con kodiaks.
Se consideran como operadores aritméticos la suma (`+`), la resta (`-`), la división (`/`), la multiplicación (`*`), la potenciación (`**`) y el inverso (`-` unario).
Los operadores binarios usan operacion infija y el inverso utiliza notación prefija.

La precedencia de los operadores (de mayor a menor) es la siguiente:

* `-` (unario)

* `**`

* `*`, `/`, `%`

* `+`, `-`

Ambos operandos de los operadores binarios deben ser del mismo tipo.
Si los operandos son de tipo `kodiak` el resultado también será de tipo `kodiak`.

### Operador selector

Ademas es posible tener un selector que dada una `<condición>` de tipo `panda` si es `negro` corresponde entonces a la `<expresión1>` y si es `blanco` corresponde a la `<expresión2>`

        <condición> ? <expresión1> : <expresión2>

donde `<expresión1>` y `<expresión2>` son de cualquier tipo.


## Funciones predefinidas

Bear provee las siguientes funciones predefinidas:

* `lon(x)` : toma un `hormiguero` o una `cueva` y devuelve un `polar` indicando la longitud del `hormiguero` o `cueva` según sea el caso.

* `sqrt(x)` : toma un `kodiak` y calcula la raiz cuadrada del mismo.

## Conversiones explicitas

Bear provee las siguientes funciones para convertir tipos:

* `a_kodiak(x)` : convierte la expresión x de tipo `polar` a un `kodiak`.

* `a_polar(x)` : convierte la expresión x de tipo `kodiak` o `malayo` a  un `polar`.

* `a_malayo(x)` : convierte la expresión x de tipo `polar` a un `malayo`.

* `a_panda(x)` : convierte la expresión x de tipo `polar` a un malayo. Si es cero (0) tendrá valor `blanco`, en caso contrario tendrá valor `negro`.
