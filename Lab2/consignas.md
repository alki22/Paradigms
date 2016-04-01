#Laboratorio 2: Programación Orientada a Objetos en Java.

En este laboratorio implementaremos un traductor de documentos  español-ingles en **Java**.


## Traductor Español-Inglés
El traductor es un programa de línea de comando que utiliza un diccionario español/inglés el cual se carga en memoria cuando el programa se inicia. Además cuenta con un diccionario de palabras ignoradas que contiene aquellas palabras que el usuario decide no traducir de un idioma al otro.

Dado un documento de entrada, el traductor procesa el mismo palabra por palabra, buscando para cada una la traducción correspondiente. Si encuentra una palabra para la cual no hay una traducción especificada, consulta al usuario sobre que hacer con la misma. En este caso, el usuario puede elegir ignorarla solo esta vez, ignorarla siempre, proveer una traducción para usar solo una vez, o proveer una traducción definitiva para dicha palabra.
Al finalizar el procesamiento del documento, el traductor genera un nuevo documento con el texto traducido.

###Requerimientos Funcionales

A continuación se especifican en detalle las distintas funcionalidades que deberá implementar el traductor.


1. El traductor deberá aceptar los siguientes argumentos:

		
		-i FILE | --input=FILE      : Documento de entrada. (Requerido)
		-d FILE | --dictionary=FILE : Diccionario de traducción.
		-g FILE | --ignored=FILE    : Diccionario de palabras ignoradas.
		-o FILE | --output=FILE     : Archivo de salida.
		-r      | --reverse  		 : Dirección de la traducción.
	 
	
	
	
2. Generar un archivo de salida que respete los signos de puntuación del archivo original. Ejemplo: si en el archivo de entrada tenemos `Hola, chau.`, en el archivo de salida debemos obtener `Hello, bye.`.
 
3. Ante una palabra para la cual no hay definida una traducción, mostrar el siguiente mensaje:

	
		No hay traducción para la palabra: XXXXXXXX
	
		Ignorar (i) - Ignorar Siempre (h) - Traducir como (t) - Traducir siempre como (s) 
	

4. Si el usuario decide **Ignorar** entonces todas las occurencias de la palabra en el documento se ignoran pero no se actualiza el diccionario de palabras ignoradas.

5. Si el usuario decide **Ignorar Siempre**, entonces todas las ocurrencias de la palabra en el documento son ignoradas y se actualiza el diccionario de palabras ignoradas.

6. Si el usuario decide **Traducir como** o **Traducir siempre como** el sistema le permite ingresar la traducción correspondiente de la siguiente  forma:

		Traducir XXXXXXXX como: YYYYYYYYY
	
	En el primero de los casos, **Traducir como**, la traducción se utiliza para todas las ocurrencias de dicha palabra en el documento pero no actualiza el diccionario. Mientras que en el segundo caso, **Traducir siempre como**, ademas de utilizar dicha traducción para todas las ocurrencias de la palabra en el documento, también agrega la traducción al diccionario. 

6. Si una palabra tiene una traducción disponible, el sistema no propone ninguna acción.

7. Si una palabra esta en el diccionario de palabras ignoradas, el sistema no propone ninguna acción.

8. Si el parámetro `--reverse` está presente cuando se ejecuta el traductor, entonces en el mismo se comporta como un traductor inglés-español.

9. El diccionario español-inglés tiene el siguiente formato:
	
	
		palabra-español,palabra-inglés
		palabra-español,palabra-inglés
		...
		palabra-español,palabra-inglés
	
##Consignas

1. Implementar el sistema utilizando una arquitectura que sea lo más desacoplada posible y que favorezca la reutilización de código. Para ello deberán:
	* Diseñar la jerarquía de clases.
	* Definir claramente las interfaces. 

3. El proyecto debe respetar la siguiente estructura de carpetas:

		bin/
		src/
		README.md
		makefile
	
	También pueden seguir la estructura propuesta por [Maven](https://maven.apache.org/guides/introduction/introduction-to-the-standard-directory-layout.html).

4. Deberán crear un `makefile` 	que permita compilar el programa usando el comando `make`. El binario resultante debe alojarse en la carpeta `bin`.

5. El código deberá respetar un coding-style. Se recomienda leer el [style guide](https://google.github.io/styleguide/javaguide.html) de Google y usar la herramienta [checkstyle](http://checkstyle.sourceforge.net/). 

5. Deberán completar el archivo README explicando: las decisiones de diseño que tomaron, las dependencias que se tienen, de donde instalarlas y como hacerlo, como compilar, como ejecutar, etc.

6. Todas las simplificaciones y las suposiciones que se hicieron durante el Lab-1, siguen siendo válidas.

## Características de la presentación

* Fecha de entrega: hasta el 15/04/2016 a las 23:59:59.999
* Deberán crear un tag indicando el release para corregir.

		git tag -a entrega -m "Entrega lab-2"
		git push origin entrega

* Si no está el tag no se corrige. Tampoco se consideran commits posteriores al tag.

## Recomendaciones
* Tómense el tiempo necesario para pensar la arquitectura del programa y diseñar los clases antes de empezar a codificar.
* Diseñen pensando en reutilizar el código o las abstracciones cuando sea posible.
* Documenten los métodos y que no son intuitivos.
* No abusen de los comentarios en el código.
* Si la definición de una funcionalidad es ambigua, busquen clarificaciones antes de codificar basados en supuestos. Esto es responsabilidad de Uds.
