type card = string * int
type deck = card list

val deckFull : deck

val deckGetSingleSpecificCard : deck -> int -> deck * card

(* Retirar solo un elemento del mazo, retorna la carata y el mazo sin la carta *)
val deckGetSingleCard : deck -> deck * card

(* Retirar N cartas del mazo, retorna las cartas en una lista y el mazo sin esas cartas *)
val deckGetMultipleCards : deck -> int -> deck * deck

(* Concatena dos decks *)
val combineDecks : deck -> deck -> deck

val maxCard : card -> card -> card