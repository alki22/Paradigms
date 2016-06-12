type card = { suit : suit; value: int }
type deck = card list

val deck_full : deck

val deal_hand : deck -> deck ->  deck * deck

val deck_draw : deck -> int -> deck * deck

val deck_draw_single : deck -> card * deck

(* Concatena dos decks *)
val combineDecks : deck -> deck -> deck

val maxCard : card -> card -> card

val getPairCards : deck -> deck
