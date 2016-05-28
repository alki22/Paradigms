# Proyecto 4: README

![image of Feed](https://d3rnbxvnd0hlox.cloudfront.net/images/channels/4/icons/large.png)

## ¿Qué hicimos?

Se realizó un **newsfeed**: una página web donde se muestran, utilizando el protocolo **rss y atom**, noticias de las fuentes que se agreguen, una vez el usuario haya iniciado sesión. Esta hecho en base al *micro-framework* (conjunto de métodos y reglas de uso) **Flask** de Python. El usuario puede iniciar sesión utilizando su cuenta de Google, Github o Facebook, a traves de *OAuth*. Para llevar el registro de los usuarios y sus suscripciones se el **ORM**, **peewee**, con una base de datos **SQLite**.

### Flask

Flask es un *micro-framework* que permite generar [sitios web dinámicos][dynamic_web_page]. Se caracteriza por lo simple que es, siendo que este proyecto se programó en **309 lineas de código python**.

También se utilizaron otras librerías para potenciar a Flask:

* [feedparser]: nos permite parsear *rss* y *atom*,
* [Flask-OAuthlib]: se hace cargo de *OAuth*,
* [peewee]: con la tarea de *traducir* los objetos *User* y *Feed*, descriptos en *models.py*, en entradas de la base de datos,
* [Flask-login]: lleva registro del usuario logueado en el sitio.

## Diseño del laboratorio

### Librerías usadas

Solo las librerías presentes en el archivo requirements.txt del repositorio.

### Funcionamiento

Para ingresar al servidor el usuario se debe dirigir a `localhost:5000`:

Al ingresar, el programa determina si ya se ha registrado el usuario y si se dejó abierta una sesión, en ese caso se lo redirige a `localhost:5000/index`. Caso contrario, nos redirige a la pantalla de inicio de sesión, `localhost:5000/login`.

En la **pantalla de inicio de sesión** se pide autenticación con alguna cuenta de *Google*, *Github* o *Facebook*. En caso de que no se le otorgue el permiso requerido u ocurra algún error, seguiremos en `localhost:5000/login`.

Si todo marcha bien, el servidor se encarga de comprobar la existencia del usuario en la base de datos:

* si existe, entonces se selecciona a ese usuario,
* si no existe, se crea una entrada en la base de datos para este usuario y se loguea (con *Flask-login*).

Luego se redirige a la página principal.

En la **página principal** se tienen varios elementos:

* una lista de los feeds a los que se ha suscrito el usuario: si se clickea en el título de cualquiera de estos, se despliega una lista de las noticias del mismo;

* un botón para añadir más feeds, redirecciona a `localhost:5000/new_feed`;

* un botón para borrar algún feed registrado;

* y un botón para desloguearnos, redirecciona a `localhost:5000/log_out`.

Los feeds no pueden repetirse en un mismo usuario, esto se da por el modelo de la base de datos.

Los tokens fueron definidos sin clases ya que nos parecía un esfuerzo innecesario.

### Problemas a la hora del desarrollo

Fue extraño adaptarse a Flask, al nunca haber tenido experiencia con frameworks. Muchas partes de Flask no son visibles al desarrollador y eso puede generar una dificultad. Con tiempo se pudo entender que estaba sucediendo.

El primer problema que se enfrentó fue manejar la base de datos. Se desconocía el funcionamiento, principalmente de que tarea realizaba un *ORM*, en este caso *peewee*. Terminó siendo una de las tareas más interesantes, y también de las más fáciles.

Luego, la implementación de **tokens de acceso** también fue problemática, ya que consultando en internet se podían ver muchas maneras distintas de hacerlo, pero fue hasta que se estudiaron las implementaciones de **Miguel Grinberg** y **mitsuhiko**. Se llegó a la realización de que se podia realizar esta tarea de forma sistemática.

En cuanto a **bugs** del programa, sólo nos enfrentamos a dos:

1. un problema de redirección cuando se inicia sesión con *Google*, ya que no tuvimos en cuenta que la credencial que otorga pide explícitamente las *URLs* a las que va a redireccionar, que sean fijas. Además al solicitar el token de acceso, la implementación con la que nos guiamos utilizaba parámetros distintos, y luego nos dimos cuenta que se pueden utilizar uniformemente los parámetros y lo único que cambia entre plataformas es la conformación de la información del usuario;
2. descubrimos un error que tuvimos en la función que almacena los feeds que no nos permitía añadir el mismo feed con usuarios diferentes, este fue corregido con el commit [1456953][commit].

## Detalles

### Ejecución

```sh
$ python runserver.py
```
### Visualización

En el navegador ingresar la URL `localhost:5000`.

### Herramientas usadas

* [Google Hangouts]
* [Grip]
* [Sublime Text 3]
* [PyCharm]

### Agradecimientos

* A [**Miguel Grinberg**](https://github.com/miguelgrinberg) (que nos salvó las papas)
* A [**mitsuhiko**](https://github.com/mitsuhiko) (no tanto como Miguel)
* A la catedra por su ayuda y por haber pospuesto la entrega.

## Opinión

Hablando desde nuestra persona, nosotros pensamos que el proyecto fue el más interesante que hemos hecho. Aprendimos a usar Flask, pero también a lidiar con problemas de todos los días, leer documentación, buscar.

Este lab, también, estuvo muy bien organizado, los recursos provistos eran de gran ayuda. Capaz al principio parecía grande, pero con un poco de perspectica, ahora, nos parece un buen proyecto, y el tamaño apropiado (como dije arriba, 309 lineas de código Python)


[dynamic_web_page]: https://en.wikipedia.org/wiki/Dynamic_web_page

[feedparser]: https://pythonhosted.org/feedparser/
[Flask-OAuthlib]: https://flask-oauthlib.readthedocs.io/en/latest/
[peewee]: http://docs.peewee-orm.com/en/latest/
[Flask-login]:https://flask-login.readthedocs.org/en/latest/

[commit]: https://bitbucket.org/paradigmas-programacion-famaf/grupo04/commits/14569539668f7ebc42bb5ce13c07e9b068679fb3

[Google Hangouts]: https://hangouts.google.com/
[Grip]: https://github.com/joeyespo/grip
[Sublime Text 3]: https://www.sublimetext.com/
[PyCharm]: https://www.jetbrains.com/pycharm/