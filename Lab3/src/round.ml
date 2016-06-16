open Player
open Deck

type round = player list

let empty_round = ([]:round)

let round_add_point (player:player) (players:round) =
  let round_add_point' player players after =
    match players with
    | [] -> List.rev after
    | p :: ps ->  match player = p with
                  | true -> let player = player_add_point player in
                            (List.rev after) @ (player :: ps)
                  | false ->  let after = p :: after in
                              round_add_point' player ps after
  in
  round_add_point' player players []

let decide_winner (players:round) =
  let decide_winner' x ys after =
    match ys with
    | [] -> x
    | y :: ys ->  let cardx = List.nth x.played 0 in
                  let cardy = List.nth y.played 0 in
                  let card1, card2, b = sort_card cardx cardy in
                  match b with
                  | true -> (* cardx > cardy *) decide_winner' x ys
                  | false -> (* cardx < cardy *) decide_winner' y ys
  in
  match players with
  | x :: xs -> let winner = decide_winner' x xs in
               round_add_point winner players


(* Generamos los jugadores *)
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

let deck_deal (players:round) (deck:deck) =
  let deal_round' players deck new_players =
    match players with
    | [] -> (players, deck)
    | x :: xs -> let x, deck = player_give_seven_cards x deck in
                 deal_round' xs deck (x :: new_players)

  let players, deck = deal_round' players deck [] in
  let players = List.rev players in
  (players, deck)

let play_round (players:round) (deck:deck) =
  let rec play_round' players deck players_after =
    match players with
    | [] -> (List.rev players, deck)
    | x :: xs ->  if has_cards x then begin
                    print_round_message round deck x
                    let x, deck = player_play x deck in
                    let players_after = x :: player_after in
                    play_round' xs deck players_after
                  end
  in
  let players, deck = play_round' players deck [] in
  let players = decide_winner players in
  (players, deck)


(** Funciones para printear **)

let print_round (round:round) =
  print_endline "Ronda:";
  let rec print_round_rec (r:round) = 
    match r with
    | [] -> ()
    | x :: xs ->  print_player_played x;
                  print_round_rec xs
  in
  print_round_rec round;

let print_round_message (round:round) (deck:deck) (player:player) =
  print_newline ();
  print_string "Mazo: ";
  print_int (deck_size deck);
  print_endline " cartas";
  print_round round;
  player_print player;
  print_string "Que carta vas a jugar ";
  print_string player.name;
  print_endline "?";