open Deck
open Printf

type player = { name : string; points : int; cards : deck; played : card list }

let player_new (name : string) = {name = name; points = 0; cards = []; played = [] }

let player_give_card (p:player) (deck:deck) =
  if deck_size deck > 0 then begin
    let card, deck = deck_draw_single deck in
    ({ name = p.name; points = p.points; cards = card :: p.cards; played = p.played},
      deck)
  end
  else
    (p, deck)

(* Repartimos 7 cartas del mazo principal al jugador *)
let player_give_seven_cards (p:player) (deck:deck) =
  let hand, deck = deal_hand p.cards deck in
    ({ name = p.name; points = p.points; cards = hand; played= p.played},
    deck)

let player_order (p:player) (q:player) =
  if p.points = q.points then 0 
  else if p.points > q.points then 1
  else -1

let has_cards (player:player) =
  List.length player.cards > 0

let has_card (player:player) (card:card) =
  let cards = List.filter (fun x -> x = card) player.cards in
  let len = List.length cards in
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
  | MAX ->  if deck_size deck > 0 then begin
              let max, deck = deck_get deck max_card in
              let player = { name = player.name;
                            points = player.points;
                            cards = max :: player.cards;
                            played = player.played } in
              (player, deck)
            end
            else
              (player, deck)
  | MIN ->  let normal, special = List.partition (fun x -> x.value > 0) player.cards in
            let min, normal = deck_get normal min_card in
            let player_cards = normal @ special in
            let deck = deck @ [min] in
            let player = { name = player.name;
                          points = player.points;
                          cards = player_cards;
                          played = player.played } in
            (player, deck)
  | TOP ->  if deck_size deck > 0 then begin
              let card, deck = deck_draw_single deck in
              let player = { name = player.name;
                            points = player.points;
                            cards = card :: player.cards;
                            played = player.played } in
              (player, deck)
            end
            else
              (player, deck)
  | PAR ->  let even, rest = get_even_cards deck in
            let deck = rest in
            let player = { name = player.name;
                          points = player.points;
                          cards = even @ player.cards;
                          played = player.played } in
            (player, deck)
  | _ -> failwith "Not expected suit"

let player_add_point (player:player) =
  { name = player.name;
   points = player.points + 1;
   cards = player.cards;
   played = player.played }

let player_print (player:player) =
  print_string player.name;
  print_char '(';
  print_int player.points;
  print_char ')';
  print_string ": ";
  print_deck player.cards

(* Pre: tiene al menos una carta*)
let rec player_play (player:player) (deck:deck) =
  let input = read_line () in
  let card = string_to_card input in
  if List.length card > 0 then begin
    let card = List.hd card in
    match has_card player card with
    | false ->  print_string "No tiene esa carta!\n";
                player_play player deck
    | true -> (let player_cards = List.filter (fun x -> x <> card) player.cards in
              if is_normal card then begin
                if deck_size deck > 0 then begin
                  let extracted_card, deck = deck_draw_single deck in
                  let player_cards = extracted_card :: player_cards in
                  let player = { name = player.name;
                                points = player.points;
                                cards = player_cards;
                                played = [card] } in
                  (player, deck)
                end
                else begin
                  let player = { name = player.name;
                                points = player.points;
                                cards = player_cards;
                                played = [card] } in
                  (player, deck)
                end
              end
              else begin
                let player = { name = player.name;
                              points = player.points;
                              cards = player_cards;
                              played = [card] } in
                let player, deck = play_special card player deck in
                if deck_size deck > 0 then begin
                  let extracted_card, deck = deck_draw_single deck in
                  let player_cards = extracted_card :: player.cards in
                  let player = { name = player.name;
                                points = player.points;
                                cards = player_cards;
                                played = [card] } in
                  player_print player;
                  player_play player deck
                end
                else begin
                  let player = { name = player.name;
                                points = player.points;
                                cards = player.cards;
                                played = [card] } in
                  player_print player;
                  player_play player deck
                end
              end)
  end
  else
    player_play player deck


let player_print_played (player:player) =
  match player.played with
  | [] -> ()
  | _ ->  print_string player.name;
          print_string "  ";
          print_deck player.played

let player_print_position (p:player) (a:int) =
  print_int a;
  print_string "   ";
  print_string p.name;
  print_string "   ";
  print_int p.points;
  print_newline()
