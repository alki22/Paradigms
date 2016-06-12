type card = { suit : suit; value: int }
type deck = card list

val deck_full : deck

val deal_hand : deck -> deck ->  deck * deck

val deck_draw : deck -> int -> deck * deck

val deck_draw_single : deck -> card * deck

val max_card : card -> card -> card

val get_even_cards : deck -> deck
