open Player
open Deck

let rec round (players : player list) (deck : deck) (table : (string * card) list) =
    match players with
    | [] -> calculate players table
    | x :: xs -> let (x, card) = playerPlay x

let rec playAux (players : player list) (table : (player * card) list) =
    match players with
    | [] -> table
    | x :: xs ->    let r = playerPlay x in
                    let table = r :: table in
                    playAux xs table

let play (players : player list) =
    let table = playAux players [] in
    let winner = maxPlayer table in
