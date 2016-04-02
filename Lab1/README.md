# Proyecto 1: README
## ¿Qué hicimos?
En este proyecto se nos pidió programar un diccionario que dados los archivos de input, output, diccionario de traducciones y diccionario de palabras ignoradas (que no deben ser traducidas), y una flag booleana que nos indica si la traducción debe realizarse de español a inglés o viceversa.


## ¿Cómo lo hicimos?

### Estructuras utilizadas:
Para llevar a cabo el proyecto utilizamos las siguientes estructuras:

* Una estructura **palabra**, que no es otra cosa que un typedef del tipo *string*

* Una estructura de **pares**, compuesta por dos palabras, en la que almacenamos una palabra en español y su correspondiente traducción.

* Una estructura de **árbol binario de búsqueda**, que se completa de forma iterativa (para lo que nos fue necesario añadir la estructura de **pila**), y que se completa de diferentes maneras según sea el orden que pide la traducción.

* Una para el **diccionario de traducciones**, compuesto por un puntero a un árbol de búsqueda binario, un *entero sin signo* que marca la longitud de este árbol y un *bool* "reverse" que nos indica si debemos cambiar el sentido de la traducción.

* Por último una para el **diccionario de palabras ignoradas**, que consiste de un *arreglo de palabras* (que se ordena alfabéticamente en cada ejecución) y un *entero sin signo* que nos indica su longitud.

Para cada una de las cuales, se entrega una librería de funciones específicas.


### Librerías estandar utilizadas:
* stdio.h
* stdlib.h
* string.h
* unistd.h
* ctype.h
* stdbool.h


### Funcion principal:
 Al correr el programa, este hace lo siguiente:
* Hace un parseo mediante la función **getopt** de los flags con los que se corre el programa:
      * -i (archivo de entrada).
      * -d (archivo diccionario).
      * -g (diccionario de palabras ignoradas). 
      * -o (archivo de salida).
      * -r (la traducción es reversa)

* Se crea una estructura de diccionario de traducciones  y una de diccionario de palabras ignoradas vacías.

* Se las carga con los pares indicados en los archivos correspondientes a estas estructuras. Mediante **strtok** se "corta" a las traducciones del diccionario quitando las comas y formando dos palabras, una la española y la otra su traducción en inglés y luego formando el par correspondiente para ser insertado en el árbol, mientras que para el arreglo que representa el diccionario de palabras ignoradas sólo se inserta la palabra en el idioma del que se está traduciendo.

* Efectúa la traducción mediante la función **translate**, que abre los archivos de entrada y salida mediante un parseo con **fget** que elimina los signos de pregunta y admiración de apertura, determina cuáles caracteres son especiales (como letras acentuadas y ñ) en el archivo de entrada (lo que se debe traducir), efectua la traducción mediante **word_translate**, escribe la misma en el archivo de salida y cierra estos dos archivos.

* Guarda los diccionarios generados con todos sus cambios (palabras agregadas durante la ejecución del programa) en los sus archivos correspondientes.

* Y por último destruye las estructuras generadas y devuelve los recursos que se solicitaron para generar las mismas para luego concluir su ejecución.


## Compilación y ejecución:
* Para compilar el programa debemos ejecutar en consola:
    ```sh
    $ make
    ```
* Para ejecutarlo:
    ```sh
    $ bin/translator (flags respectivos)
    ```


## Herramientas usadas:
* Sublime text editor.
* Editor de texto markdown *dillinger.io*.
* GNU gdb.
* Valgrind.
* Google Hangouts.
