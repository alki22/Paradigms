open Deck

type player = { name : string; points : int; cards : deck; }

(* Crea un nuevo jugador con un nombre *)
val player_new : string -> player

(* Se le da una carta al jugador *)
val player_give_card : player -> deck -> player * deck

(* Se le dan siete cartas al jugador*)
val player_give_seven_cards : player -> deck -> player * deck