type suit = Espada | Copa | Oro | Basto |  ID | SWAP | MAX | MIN | TOP | PAR
type card = { suit : suit; value: int }
type deck = card list

val deck_empty : deck
val deck_full : deck

(* Funciones *)
val deck_draw_single : deck -> card * deck
val deck_draw : deck -> int -> deck * deck
val deal_hand : deck -> deck ->  deck * deck
val deck_size : deck -> int

val sort_card : card -> card -> card * card * bool
val max_card : card -> card -> card
val min_card : card -> card -> card
val deck_get : deck -> (card -> card -> card) -> card * deck
val is_normal : card -> bool
val get_even_cards : deck -> deck * deck
val string_to_card : string -> deck

val print_deck : deck -> unit