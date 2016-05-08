open ListHelpers
open List
open Random

type card = string * int
type deck = card list

let deckFull = [("B",1);("B",2);("B",3);("B",4);("B",5);("B",6);("B",7);("B",8);("B",9);("B",10);("B",11);("B",12);
                ("C",1);("C",2);("C",3);("C",4);("C",5);("C",6);("C",7);("C",8);("C",9);("C",10);("C",11);("C",12);
                ("E",1);("E",2);("E",3);("E",4);("E",5);("E",6);("E",7);("E",8);("E",9);("E",10);("E",11);("E",12);
                ("O",1);("O",2);("O",3);("O",4);("O",5);("O",6);("O",7);("O",8);("O",9);("O",10);("O",11);("O",12);
                ("SID",0);("SSWAP",0);("SMAX",0);("SMIN",0);("STOP",0);("SPAR",0)]

(* Devuelve la K-ésima carta del mazo dado *)
let rec deckGetSingleCardAux (c : deck) (k : int) =
    match c with
    | [] -> failwith "ERROR: Not enough cards."
    | x :: xs -> if k == 0 then
                    x
                else
                    deckGetSingleCardAux xs (k - 1)

(* Dada una lista devuelve una tupla conformada por una carta aleatoria y la lista sin dicha carta *)
let deckGetSingleCard (d : deck) =
    let l = List.length d in
    if (l == 0) then
        failwith "ERROR: Not enough cards."
    else
        let r = Random.int l in
        let x = deckGetSingleCardAux d r in
        (listDeleteElem d r, x)

(* Dada una lista devuelve una tupla conformada por una carta aleatoria y la lista sin dicha carta *)
let deckGetSingleSpecificCard (d : deck) (k : int) =
    let l = List.length d in
    if (l == 0) then
        failwith "ERROR: Not enough cards."
    else
        let x = deckGetSingleCardAux d k in
        (listDeleteElem d k, x) 

(* Pre: hay suficientes cartas *)
let rec deckGetMultipleCardsAux (deck : deck) (n : int) (s : deck) =
    if n = 0 then (deck,s)
    else begin
        let c = (deckGetSingleCard deck) in
        let s = (snd c) :: s in
        deckGetMultipleCardsAux (fst c) (n - 1) s
    end

(* Conseguimos n cartas del mazo d, devolviendo una tupla con el mazo y las cartas retiradas *)
let deckGetMultipleCards (deck : deck) (n : int) =
    let l = List.length deck in
    if l < n then failwith "ERROR: Not enough cards."
    else deckGetMultipleCardsAux deck n []

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