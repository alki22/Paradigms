type card
type deck

(* Retirar solo un elemento del mazo, retorna la carata y el mazo sin la carta *)
val deckGetSingleCard : deck -> card * deck

(* Retirar N cartas del mazo, retorna las cartas en una lista y el mazo sin esas cartas *)
val deckGetMultipleCards : deck -> int -> deck * deck