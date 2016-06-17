open Deck

type player = { name : string; points : int; cards : deck; played : card list }

(* Funciones *)
val player_new : string -> player
val player_give_card : player -> deck -> player * deck
val player_give_seven_cards : player -> deck -> player * deck
val player_order : player -> player -> int
val has_cards : player -> bool
val has_card : player -> card -> bool
val play_special : card -> player -> deck -> player * deck
val player_add_point : player -> player
val player_play : player -> deck -> player * deck

val player_print : player -> unit
val player_print_played : player -> unit
val player_print_position : player -> int -> unit