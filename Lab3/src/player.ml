open Deck
open Printf

type player = { name : string; points : int; cards : string list; }

let playerNew (name : string) = {name = name; points = 0; cards = [] }

let playerHand (player : player) = player.cards

let playerAdd (card : string) (player : player) =
    {player with cards = card :: player.cards}


let playerPlay (player : player) (card : string) =
    let list = player.cards in
    match list with
    | [] -> begin printf "La carta no pertenece al mazo" player
    | x :: xs ->
    | 


let pedro = new_player "pedro"
let pedro = add "C11" pedro
let pedro = add "C12" pedro
