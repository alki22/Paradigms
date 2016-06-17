open Player
open Deck

type round = player list

let empty_round = ([]:round)

(** Funciones para printear **)

let round_print (round:round) =
  print_endline "Ronda:";
  let rec round_print' (r:round) = 
    match r with
    | [] -> ()
    | x :: xs ->  player_print_played x;
                  round_print' xs
  in
  round_print' round

let round_print_message (round:round) (deck:deck) (player:player) =
  print_newline ();
  print_string "Mazo: ";
  print_int (deck_size deck);
  print_endline " cartas";
  round_print (List.rev round);
  player_print player;
  print_string "Que carta vas a jugar ";
  print_string player.name;
  print_endline "?"

(* Imprime todas las posiciones de una ronda *)
let print_positions (players:round) =
  print_string "\nGAME OVER. Posiciones:";
  print_newline();
  let rec print_all_position (players:round) (a:int) =
    match players with
    [] -> ()
    | x::xs -> player_print_position x a;
               print_all_position xs (a+1)     
  in
  let sort_players (players:round) = List.rev (List.sort player_order players) in
  print_all_position (sort_players players) 1

(** Funciones generales **)

let player_num (players:round) =
  let with_cards = List.filter has_cards players in
  List.length with_cards

let round_add_point (player:player) (players:round) =
  let rec round_add_point' player players after =
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
  let rec decide_winner' p ps =
    (match ps with
    | [] -> p
    | y :: ys ->  let cardp = List.nth p.played 0 in
                  let cardy = List.nth y.played 0 in
                  let card1, card2, b = sort_card cardp cardy in
                  match b with
                  | true -> (* cardp > cardy *) decide_winner' p ys
                  | false -> (* cardp < cardy *) decide_winner' y ys)
  in
  match players with
  | [] -> failwith "No players!"
  | [x] -> round_add_point x [x]
  | x :: xs ->  let winner = decide_winner' x xs in
                print_string "El jugador ";
                print_string winner.name;
                print_endline " gano la ronda.";
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
    end
    else
      ((List.rev plays):round)
  in
  get_players_rec empty_round 5



let deck_deal_initial (players:round) (deck:deck) =
  let rec deal_round' players after deck =
    (match players with
    | [] -> (List.rev after, deck)
    | x :: xs -> let x, deck = player_give_seven_cards x deck in
                 deal_round' xs (x :: after) deck)
  in
  let players, deck = deal_round' players [] deck in
  (players, deck)

let play_round (players:round) (deck:deck) =
  let rec play_round' ps ps_after deck =
    (match ps with
    | [] -> (List.rev ps_after, deck)
    | x :: xs ->  if has_cards x then
                    round_print_message ps_after deck x;
                    let x, deck = player_play x deck in
                    let ps_after = x :: ps_after in
                    play_round' xs ps_after deck)
  in
  let players, deck = play_round' players [] deck in
  let players = decide_winner players in
  (players, deck)
