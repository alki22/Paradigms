# Proyecto 3: OCaml - La Guerra Funcional

En este laboratorio se programó un juego de cartas: *La Guerra Funcional*. Se cuenta con un mazo de cartas españolas, y siete cartas especiales.

A continuación se explicará la implementación del laboratorio, como se enfrentaron los problemas, ejecución, etcétera.

## Implementación

El programa se compone de tres módulos:

* **Deck**: define las cartas, los mazos y todas las funciones sobre estos elementos.
* **Player**: define los jugadores, de manera individual.
* **Round**: implementa round, que es una colección de jugadores.

Estos módulos son utilizados por *main*.

A continuación explicaré cada módulo en detalle, y luego como todo esto se integra para crear *La Guerra Funcional*.

#### Módulos

##### Deck

Se definen tres tipos:

```ocaml
type suit = Espada | Copa | Oro | Basto |  ID | SWAP | MAX | MIN | TOP | PAR
type card = { suit : suit; value: int }
type deck = card list
```

El tipo `card` representa una carta, con su *palo* y su valor. Para las cartas especiales, se definió un palo para cada una, y un valor fijo de `-1`. Por ejemplo, la carta **SSWAP** se definiría de la siguiente manera:

```ocaml
let sswap = {suit = SWAP; value = -1};;

```

Al comienzo se optó por retirar las cartas de manera aleatoria. Esto fue cambiado ya que, al usar la carta *SMIN*, no era posible situar la carta al fondo del mazo general. Actualmente, el programa mezcla las cartas al comenzar, y luego funciona de manera ordinaria.

##### Player

Se define *player* como:

```ocaml
type player = { name : string; points : int; cards : deck; played : card list }
```

* **name**: el nombre del jugador.
* **points**: los puntos del jugador a traves de la partida.
* **cards**: la mano del jugador.
* **played**: la última carta jugada.

Se tienen funciones para determinar una gran variedad de cosas, si un jugador tiene cartas, si tiene una carta específica, darle un punto al jugador, aunque, la función principal es `player_play`.

La función `player_play` se encarga de presentar al jugador, y pedirle que juege cartas. Comienza pidiendonos una carta, luego cerciorándose de que efectivamente el jugador la posea.
Si esta carta es especial, iremos a una función que se encarga de realizar las tareas de cada carta especial, y a continuación pidiendole otra carta, que puede ser *especial* o *normal*.
Al jugar una carta normal esta se guarda en `player.played`.

##### Round

Una ronda esta definida como:

```ocaml
type round = player list
```

Como se dijo antes, una *round* es una colección de jugadores, y entonces las funciones relacionadas a jugadores como conjunto están en este módulo. 

Una de las tareas más importantes de este elemento es llamar a `player_play` por cada jugador, y luego de llamar a `decide_winner`, función que le entrega el punto al jugador que haya tirado la mayor carta, a traves de `player.played`.

Otras funciones que son muy visibles son `get_players` y `deck_deal_initial`. La primera nos pregunta los nombres de los jugadores y los crea, la segunda entrega las siete cartas iniciales al comienzo de la partida.

## Compilación y ejecución

Para compilar el laboratorio:

```bash
$ make
```

desde el directorio `grupo04/Lab3/`.

Y para correrlo (suponiendo que no nos movimos de directorio):

```bash
$ cd bin
$ ./la_guerra_funcional
``` 

## Comentarios

El proyecto fue muy interesante, aunque al principio haya presentado un desafío. Al final creo que el aprendizade de OCaml es útil, al menos para tener una noción básica. Y sin dudas de todo esto hay un gran aprendizaje, entre aprender el lenguaje, luchar con conceptos del paradigma funcional y con compiladores distintos.