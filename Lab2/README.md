# Proyecto 2 : Readme

## ¿Qué hicimos?

En este proyecto se nos pidió programar un diccionario en *Java* que dados los archivos de input, diccionario de traducciones y diccionario de palabras a ignorar, y una flag booleana que nos indica si la traducción debe realizarse de español a inglés o viceversa.

## ¿Cómo hicimos esto?

Para cumplir nuestra tarea, estructuramos el proyecto de la siguiente manera:

* **Palabras**: para representar las palabras a traducir utilizamos dos tipos: *char[]* y *String*, dado que en *Java* el tipado no permite una equivalencia entre ellos, contrario a *C*, por ejemplo. El **char[]** se utiliza para aquellas operaciones que precisen recorrer la palabra carácter a carácter, mientras que el **String** es usado para el resto de las operaciones, ya que los diccionarios usan Strings.
* **Diccionario de palabras ignoradas**: fue implementado utilizando la estructura **ArrayList**, que a diferencia de la lista clásica utiliza almacenamiento dinámico de datos, lo que nos permite añadir, modificar y quitarle elementos.
* **Diccionario de traducciones**: se hizo mediante el uso de la estructura **TreeMap**, que consiste en un mapeo _<Clave, Valor>, que en este caso sería <Palabra, Traducción> Español-Inglés ó Inglés-Español según el valor de reverse, que también forma parte de la estructura. Este mapeo se caracteriza por preservar el orden de las claves (en este caso orden alfabético) mediante el uso de un *árbol binario de búsqueda* y garantizarnos búsqueda e inserción de elementos en el orden de O(log(n)).

## Sistema de dependencias

### Paquetes:

* **Translator**: compuesto por las clases DictIgnore y DictTrans. Utilizado por Translator.java. En este paquete están las funciones para el manejo de las estructuras previamente mencionadas.
* **Helpers**: compuesto por las clases Helpers y GetOpt. Utilizado por Translator.java. En este paquete encontramos funciones para el manejo de *Strings*, la funcion polishArray que elimina los caracteres sobrantes en el buffer que utilizamos para crear palabras desde el input (ver sección **Traductor** para mayor referencia) y GetOpt que es un port de la funcion de *GNU* en *C* para *Java*.

### Librerías estandar utilizadas:

* **java. io**
* **java.util**

## El traductor

* Hace un parseo mediante la función *getopt* de las flags con los que se corre el programa: 
 *-i* (archivo de entrada), *-g* (diccionario de palabras ignoradas), *-o* (archivo de salida), *-r* (la traducción es reversa).
* Se crean estructuras vacías para el *diccionario de traducciones* y el *diccionario de palabras ignoradas*.
* Se cargan esos diccionarios con los inputs dados: para el diccionario de traducciones hacemos una lectura de cada línea del input y separamos la línea usando **", "** como delimitador, esto nos retorna un arreglo de dos *Strings*, y el mapeo será determinado por el valor de reverse. *Array[0]* será key y *array[1]* para value si reverse es falso(traducción español-inglés) y viceversa para reverse verdadero(traducción inglés-español).
* Crea una instancia de *Translator*, que hace la traducción mediante *translate*, que crea un buffer de 100 caracteres en el que se guardan los caracteres del input, esto mediante un recorrido caracter a caracter de cada línea del input que terminará(formará una palabra) cuando un caracter no séa alfanumérico y la va a traducir mediante *translate_word* (si es un número se ahorra la búsqueda y no lo traduce), si no se encuentra la palabra, se dará al usuario la opción de ignorar esta vez o siempre (agregar al diccionario de palabras ignoradas) a la palabra o de traducirla esta vez o siempre (añadir al diccionario de traducciones) como la palabra ingresada a continuación. Esta traducción además respeta los signos de puntuación y de pregunta y los escribe en el output.
* Guarda los cambios en ambos diccionarios para su futuro uso.

## Reflexión

### ¿Qué cambió con respecto al proyecto anterior?

El principal cambio respecto al proyecto 1 fue el cambio de lenguaje y por ende de paradigma, pasamos de **C**, un lenguaje *imperativo*, a **Java**, un lenguaje *orientado a objetos*.

### Lo bueno:

* Nos tomó muchas menos lineas de código hacer el proyecto:

  | Count         | Java    | Java w/o GetOpt | C       |
  | ------------- | -------:| ---------------:| -------:|
  | Lines         | 634     | 352             | 1015    |
  | Words         | 2043    | 994             | 2742    |
  | Characters    | 19615   | 10870           | 24947   |

* El hecho de ser Java un lenguaje de un alto nivel de abstracción, nos facilitó encontrar y entender métodos para casi todas las tareas, ya sea en las librerías definidas en el lenguaje.
* Tuvimos que usar mucho el sitio de **Oracle** y **StackOverflow**, lo que al principio nos pareció "pesado", pero mostró ser una habilidad útil, considerando que estamos satisfechos con el laboratorio que logramos hacer.
* Nos percatamos de que Java, con su alto nivel de abstracción, y otras herramientas como el *Garbage Collector*, permite ser aprendido rapidamente (ya sabiendo C).

### Lo malo:

* La sintaxis puede ser confusa a veces para aquellos que venimos del **viejo y glorioso C**.
* El tipado nos obliga en ocasiones a realizar conversiones o casteos que en C serían innecesarios. El caso más puntual es el de **char[]** y **String**, que en este lenguaje no son equivalentes.

Pero igualmente la pasamos bien y aprendimos un nuevo lenguaje que en el mercado actual nos sirve para conseguir trabajo.

## Detalles

### Versión
1.0

### Compilación:

Para compilar los **.class** y un **.jar** hacemos `make`

### Ejecución:

Existen 2 casos:

##### Ejecutar los **.class**

Caso en el que uno se debe *parar* el el directorio **bin** y ejectuar `java Translator` y las respectivas opciones.

##### Ejectuar el **jar**

Nos volvemos a situar en **bin** y ejecutamos `jara -jar translator.jar` y las respectivas opciones.

### Herramientas usadas:
* Sublime Text 3.
* Editor de Markdown online **dillinger.io**.
* Google Hangouts.
