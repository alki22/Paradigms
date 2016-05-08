open Player
open Deck

let rec round (players : player list) (deck : deck) (table : (string * card) list) =
    match players with
    | [] -> calculate players table
    | x :: xs -> let (x, card) = playerPlay x

let play (players : player list) (deck : deck) =
    let (players, deck) = round players deck
