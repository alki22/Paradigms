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

let rec round (players : player list) =
    let table = playAux players [] in
    let table = processWinner table in (* give point *)
    (* Refrescamos players *)
    let players = refreshPlayers table
    (* Vemos si alguién ya terminó *)
    let players