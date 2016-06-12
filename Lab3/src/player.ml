open Deck
open Printf

type player = { name : string; points : int; cards : deck; played : card list }

let player_new (name : string) = {name = name; points = 0; cards = []; played = [] }

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

let has_cards (player:player) =
  List.lenght player.cards <> 0

let has_card (player:player) (card:card) =
  let cards = List.filter (fun x -> x = card) player.cards in
  let len = List.lenght cards in
  match len with
  | 0 -> false
  | _ -> true

let play_special (card:card) (player:player) (deck:deck) =
  match card.suit with 
  | ID -> (player, deck)
  | SWAP -> let player_cards = player.cards in
            let player = { name = player.name;
                          points = player.points;
                          cards = deck;
                          played = player.played } in
            let deck = player_cards in
            (player, deck)
  | MAX -> let max, deck = deck_max deck
  | MIN -> let player_cards, deck = 
  | TOP ->
  | PAR ->


(* Pre: tiene al menos una carta*)
let rec player_play (player:player) (deck:deck) =
  let input = read_line () in
  let card = string_to_card input in
  let b = has_card player card in
  match b with
  | false -> player_play player deck
  | true -> let player_cards = List.filter (fun x -> x <> card) player.cards in
            let extracted_card, deck = deck_draw_single deck
            let player_cards = extracted_card :: player_cards
            let player = { name = player.name;
                          points = player.points;
                          cards = player_cards;
                          played = card :: player.played } in
            match is_normal card with
            | true -> (player, deck)
            | false ->  let player, deck = play_special card player deck in
                        player_play player deck
  


(** Funciones para printear **)

let player_print (player:player) =
  print_string player.name;
  print_char '(';
  print_int player.points;
  print_char ')';
  print_string ": ";
  print_deck player.cards

let player_print_played (player:player) =
  match player.played with
  | deck_empty -> ()
  | _ ->  print_string player.name;
          print_string "  ";
          print_deck player.played)