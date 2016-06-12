open Deck
open Printf

type player = { name : string; points : int; cards : deck; played : card list }

let player_new (name : string) = {name = name; points = 0; cards = []; thrown = [] }

let player_give_card (p:player) (deck:deck) =
  try
    let card, deck = deck_draw_single deck in
    ({ name = p.name; points = p.points; cards = hand; played = p.played},
    deck)

  with EMPTY_DECK -> (print_string "No hay mas cartas";
                     (p, deck))

(* Repartimos 7 cartas del mazo principal al jugador *)
let player_give_seven_cards (p:player) (deck:deck) =
  let hand, new_deck = deal_hand p.cards deck in
    (* Tupla de player y deck *)
    ({ name = p.name; points = p.points; cards = hand; played= p.played},
    new_main)

(* Pre: tiene al menos una carta*)
let player_play (player : player) =
    printf "Que carta vas a jugar %s?" player.name;
    let input = read_int() in
    let card = string_to_card input in
    let playerDeck = player.cards in
    let (playerDeck, card) = deckGetSingleSpecificCard playerDeck input in
    if (fst card) = s then algo
    else begin
        let {player with cards = playerDeck} in
        (player, card))
    end
