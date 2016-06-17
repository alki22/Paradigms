open Player
open Deck

type round = player list

val empty_round : round

val round_print : round -> unit
val round_print_message : round -> deck -> player -> unit
val print_positions : round -> unit

val player_num : round -> int
val decide_winner : round -> round
val get_players : unit -> round
val deck_deal_initial : round -> deck -> round * deck
val play_round : round -> deck -> round * deck