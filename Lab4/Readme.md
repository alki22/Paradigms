# Proyecto 4 : Readme
![image of Feed](https://d3rnbxvnd0hlox.cloudfront.net/images/channels/4/icons/large.png)
## ¿Qué hicimos?
Hicimos un **newsfeed**: una página web donde se muestran utilizando el protocolo **rss** las noticias de las fuentes que se agreguen una vez el usuario haya iniciado sesión. Utilizamos para programarlo el *framework* (conjunto de métodos y reglas de uso) **Flask** de **Python**. El usuario puede iniciar sesión utilizando su cuenta de *Google*, *Github* ó *Facebook* y la página se va a referir de ahí en más al usuario por el nombre que utilice en su cuenta. Para llevar el registro de los usuarios y sus suscripciones se utiliza una base de datos **SQLite** y **peewee** para "traducir" los objetos *User* y *Feed* descriptos en *models.py* en entradas de la base de datos.
## Decisiones de diseño:
### Clases utilizadas:
* Para la implementación de los tokens de acceso a aplicaciones remotas utilizamos objetos del tipo **OAuth**, que registran dichos inicios de sesión a través de su método **remote_app()** y una serie de parámetros para conseguir la información del usuario y extraer de esta su nombre.
* Para implementar la sesión propiamente dicha utilizamos objetos del tipo **session** y el método **get()** que nos permite a través del token generado previamente iniciar la sesión.
### Librerías usadas:
* Todas las librerías presentes en el archivo requirements.txt del repositorio (no se utilizó ninguna librería externa).
## Funcionamiento:
* Al ingresar la *URL* de la página, el programa determina si ya nos registramos y dejamos abierta una sesión, en ese caso nos redirige a la sección de feeds(página principal). Caso contrario, nos redirige a la pantalla de inicio de sesión.
* En la **pantalla de inicio de sesión** se nos pide autenticarnos con nuestra cuenta de *Google*, *Github* o *Facebook*. En caso de que no otorguemos el permiso requerido u ocurra algún error, se nos redirigira a esta pantalla con un mensaje de error. Si todo marcha bien, el servidor checkea si el usuario existe en la base de datos, si existe, entonces se selecciona a ese usuario, si no existe, se crea una entrada en la base de datos para este usuario y se selecciona a este. Luego se redirige a la página principal.
* En la **página principal** se muestra una lista de los feeds a los que se suscribió el usuario, donde al clickear cualquiera de estos se despliega una lista de las noticias más recientes del mismo. También se muestra también un botón que nos redirige a la página donde se añaden feeds, donde puede añadirse cualquier feed a la lista, siempre y cuando no esté repetido.
## Problemática en el desarrollo:
### Ahora viene lo bueno...
* Al principio el equipo de desarrollo no entendió un **#$%&** la gramática ni el funcionamiento del código. Nos dejamos llevar bastante por los templates que nos parecieron ilegibles al principio (Pero luego gracias a tener un parcial de redes el lunes pudimos comprender un poco mejor) y el susto de no haber trabajado nunca con *scripting* ó *bases de datos* en lo que va de la carrera.
* Una vez superados nuestros temores iniciales, el primer problema que enfrentamos en el desarrollo fue la implementación de **tokens de acceso**, ya que consultando repositorios en **Github** nos encontrabamos con que habían muchas maneras distintas de implementar algo parecido, pero no fue hasta que vimos las implementaciones de **Miguel Grinberg** y **mitsuhiko** que nos dimos cuenta que se podían hacer todas las cosas de la misma manera prácticamente.
* En cuanto a **bugs** del programa (y no de nuestra cabeza), sólo nos enfrentamos a dos, salvo que alguien encuentre otros...(guiño guiño):
![image of Guiño guiño](https://t3.kn3.net/taringa/1/4/2/5/6/0/creogame/00B.jpg)
    * Primero, un problema de redirección cuando se inicia sesión con *Google*, ya que no tuvimos en cuenta que la credencial que otorga pide explícitamente las *URLs* a las que va a redireccionar. Además al solicitar el token de acceso, la implementación con la que nos guiamos utilizaba parámetros distintos, y luego nos dimos cuenta que se pueden utilizar uniformemente los parámetros y lo único que cambia entre plataformas es la conformación de la información del usuario.
    * Segundo, descubrimos un error que tuvimos en la función que almacena los feeds que no nos permitía añadir el mismo feed con usuarios diferentes, este fue corregido con el commit [1456953](https://bitbucket.org/paradigmas-programacion-famaf/grupo04/commits/14569539668f7ebc42bb5ce13c07e9b068679fb3).
## Detalles:
### Versión
1.0
### Ejecución:
```
$ python runserver.py
```
### Visualización:
En el navegador ingresar la URL **localhost:5000/**.
### Herramientas usadas:
* Sublime Text 3.
* Editor de Markdown online **dillinger.io**.
* Google Hangouts.
### Agradecimientos:
* A [**Miguel Grinberg**](https://github.com/miguelgrinberg)
* A [**mitsuhiko**](https://github.com/mitsuhiko)
* A la catedra por su apoyo incondicional y por haber pospuesto la entrega.
