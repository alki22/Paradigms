open Player
open Deck

type round = player list

let empty_round = ([]:round)

(* Conseguimos los jugadores *)
(* Usamos List.rev para que se respete el orden en que entraron los jugadores *)
let get_players () =
  let init_message =
    "Ingrese el nombre del jugador o EXIT para comenzar el juego:" in
  let rec get_players_rec plays n =
    print_endline init_message;
    let input = read_line () in
    let is_exit = (input = "EXIT") in
    if not is_exit then begin
      let np = player_new input in
      let n = n-1 in
      if n > 0 then
        get_players_rec (np :: plays) n
      else
        (List.rev (np :: plays))
    else
      ((List.rev plays):round)
  in
  get_players_rec empty_round 5

let deal_round (players:round) (deck:deck) =
  let deal_round' players deck new_players =
    match players with
    | [] -> (players, deck)
    | x :: xs -> let x, deck = player_give_seven_cards x deck in
                 deal_round' xs deck (x :: new_players)

  let players, deck = deal_round' players deck [] in
  let players = List.rev players in
  (players, deck)

let play_round (players:round) (deck:deck) =
  let play_round' players deck num =
    match players with
    | [] -> 
    | x :: xs ->
      if has_cards x then begin
        player_play x deck
      end