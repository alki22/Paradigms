open List
open Random

type suit = Espada | Copa | Oro | Basto |  ID | SWAP | MAX | MIN | TOP | PAR

type card = { suit : suit; value: int }
type deck = card list

let id = {value = -1; suit = ID}
let swap = {value = -1; suit = SWAP}
let max = {value = -1; suit = MAX}
let min = {value = -1; suit = MIN}
let top = {value = -1; suit = TOP}
let par = {value = -1; suit = PAR}

let specials = [id; swap; max; min; top; par]

let values = [1; 2; 3; 4; 5; 6; 7; 8; 9; 10; 11; 12]
let normal_suits = [Espada; Copa; Oro; Basto]

let deck_empty = ([]:deck)

let deck_full =
  let make_value_cards num =
  List.map (fun suit -> {value = num; suit = suit}) normal_suits in
  specials @ (List.concat (List.map make_value_cards values))

(* Repartir las cartas iniciales *)
let deal_hand (hand:deck) (deck:deck) =
  match deck with
  | [] -> invalid_arg "Empty deck"
  | xs -> let took, left = deck_draw xs 7 in
      (hand @ took, left)
    
(* Toma n cartas del mazo principal *)
let deck_draw (deck:deck) (num:int) =
  let rec deck_draw' acc deck num = 
    match num with
    | 0 -> (acc, deck)
    | _ ->  let c = deck_draw_single (deck:deck) in
            let acc = (fst c) :: acc in
            deck_draw' acc (snd c) (num - 1)
  in
  deck_draw' [] deck num

(* Toma una carta del mazo dado *)
(* Debería levantar excepción *)
let deck_draw_single (deck:deck) =
  let l = List.length deck in
  match l with
  | 0 ->  raise EMPTY_DECK
  | _ ->  let r = Random.int l in
          let card = List.nth deck r in
          (card, List.filter (fun x -> x <> card) deck)

let deck_size (deck:deck) =
  List.length deck

(* Ordena las cartas, la primera es la mayor, la segunda la menor *)
let sort_card (card1:card) (card2:card) =
  if (snd card1) > (snd card2) then (card1, card2, true)
  else if (snd card1) < (snd card2) then (card2, card1, false)
  else
    begin
    if (fst card1) = "E" then (card1, card2, true)
    else if (fst card2) = "E" then (card2, card1, false)
    else if (fst card1) = "B" then (card1, card2, true)
    else if (fst card2) = "B" then (card2, card1, false)
    else if (fst card1) = "O" then (card1, card2, true)
    else (card2, card1, false)

(* Devuelve la máxima carta *)
let max_card (card1:card) (card2:card) =
  let card1, card2, b = sort_card card1, card2 in
  card1

(* Devuelve la mínima carta *)
let min_card (card1:card) (card2:card) =
  let card1, card2, b = sort_card card1, card2 in
  card2

(* Devuelve la máxima carta del mazo, y el mazo sin la carta *)
let deck_get (deck:deck) f =
  match deck with
  | [] -> 
  | x :: xs ->  let deck_get' xs x =
                  match xs with
                  | [] -> x
                  | y :: ys ->  let card = f x y in
                                deck_get' ys card
                in
                let card = deck_get' xs x in
                (card, List.filter (fun x -> x <> card) deck)

let is_normal (card:card) =
  List.exists (fun s -> s = card.suit) normal_suits

(* Separa las cartas pares, de las impares, del mazo *)    
let get_even_cards (deck:deck) =
  let even = List.filter (fun x -> ((snd x) mod 2) = 0) deck in
  let odd = List.filter (fun x -> ((snd x) mod 2) = 0) deck in
  (even, odd)

(* Dado un string, parseamos una carta *)
let string_to_card c =
  let len = (String.length c - 1)  in
  let possible_int = (String.sub c 1 len)
  in
  try
  match String.get c 0 with
    'E' -> {value = int_of_string possible_int; suit = Espada}
  | 'C' -> {value = int_of_string possible_int; suit = Copa}
  | 'O' -> {value = int_of_string possible_int; suit = Oro}
  | 'B' -> {value = int_of_string possible_int; suit = Basto}
  | 'S' -> (match String.sub c 1 2 with
              "ID" -> {value = -1; suit = ID}
            | "SW" -> {value = -1; suit = SWAP}
            | "MA" -> {value = -1; suit = MAX}
            | "MI" -> {value = -1; suit = MIN}
            | "TO" -> {value = -1; suit = TOP}
            | "PA" -> {value = -1; suit = PAR}
            | _ -> invalid_arg "No such card.")
  | _ -> invalid_arg "No such card."
  with Failure "int_of_string" -> (print_endline "No es una carta valida!"; [])

(** Funciones que printean **)

let rec print_deck (target:deck) =
  match target with
  | [] -> print_newline ()
  | [x] ->  print_card x;
            print_newline ()
  | x :: xs -> print_card x;
               print_char ' ';
               print_deck xs