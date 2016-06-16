open Deck
open Player
open Round

let rec game_rec (players:round) (general:deck) =
  let new_ps, new_gen = play_round players general in
  if player_num new_ps > 1 then game_rec new_ps new_gen
  else print_positions new_ps

let _ =
  let players = get_players () in
  (* let general = shuffle full_deck in *)
  let players, aux_deck = deck_deal players deck_full in
  let new_gen, rest_gen = take 5 aux_gen in
  game_rec players new_gen
