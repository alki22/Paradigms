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
    if num = 0 then (acc, deck)
    else begin
      let c = deck_draw_single (deck:deck) in
      let acc = (fst c) :: acc in
      deck_draw' acc (snd c) (num - 1)
    end
  in
  deck_draw' [] deck num

(* Toma una carta del mazo dado *)
(* Debería levantar excepción *)
let deck_draw_single (deck:deck) =
  let l = List.length deck in
  if l = 0 then
    raise EMPTY_DECK
  let r = Random.int l in
  let card = List.nth deck r in
  (card, List.filter (fun x -> x <> card) deck)

let deck_size (deck:deck) =
  List.length deck

(* Combinamos dos mazos *)
let rec combineDecks (deck1 : deck) (deck2: deck) =
  match deck1 with
  | [] -> deck2
  | x :: xs -> combineDecks xs (x :: deck2)

(* Devuelve la máxima carta *)
let maxCard (card1 : card) (card2 : card) =
  if (snd card1) > (snd card2) then card1
  else if (snd card1) < (snd card2) then card2
  else
    begin
    if (fst card1) = "E" then card1
    else if (fst card2) = "E" then card2
    else if (fst card1) = "B" then card1
    else if (fst card2) = "B" then card2
    else if (fst card1) = "O" then card1
    else card2

(* Devuelve todas las cartas pares del mazo *)    
let getPairCards (deck:deck) = 
    List.filter (fun x -> ((snd x) mod 2) = 0) deck

(* Saca la carta de arriba del mazo *)
let getTopCard (deck_deck) = 
    deck_draw_single(deck)



