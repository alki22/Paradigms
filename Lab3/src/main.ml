open Deck
open Player
open Round
open Printf

let rec game_rec (players:round) (deck:deck) =
  let players, deck = play_round players deck in
  if player_num players > 1 then game_rec players deck
  else print_positions players

let _ =
  Random.self_init();
  let deck = deck_shuffle deck_full in
  let players = get_players () in
  let players, deck = deck_deal_initial players deck in
  print_string "\nLas cartas fueron repartidas!\n";
  game_rec players deck
