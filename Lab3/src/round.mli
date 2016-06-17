open Player
open Deck

type round = player list

val empty_round : round

(* Funciones *)
val round_print : round -> unit
val round_print_message : round -> deck -> player -> unit
val print_positions : round -> unit

val player_num : round -> int
val round_add_point : player -> round -> round
val decide_winner : round -> round
val get_players : unit -> round
val deck_deal_initial : round -> deck -> round * deck
val play_round : round -> deck -> round * deck