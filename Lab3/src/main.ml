open Deck
open Player
open Pervasives
open Printf
open Round

exception NotEnoughPlayers

let readPlayer () =
    let name = read_line() in
    if name = "EXIT" then (0,"EXIT")
    else (1,name)

let rec getPlayers (s : player list) =
    let player = readPlayer() in
    match player with
    | (0,_) -> s
    | (1,name) ->   let s = (playerNew name) :: s in
                    getPlayers s 
    | (_,_) -> failwith "ERROR: Added player has an issue"

let dealPlayer (deck : deck) (player : player) =
    let s = deckGetMultipleCards deck 7 in
    let concat = combineDecks (snd s) player.cards in
    ((fst s),{player with cards = concat})

let rec dealAllPlayers (deck : deck) (players : player list) (mapped : player list) =
    match players with
    | [] -> (deck, mapped)
    | x :: xs ->    let s = dealPlayer deck x in
                    let mapped = mapped @ [snd s] in
                    dealAllPlayers (fst s) xs mapped
                    

let _ =
    (* Definimos a los jugadores *)
    let players = getPlayers [] in
    if List.length players < 2 then
        raise NotEnoughPlayers
    else
        (* Repartimos las cartas *)
        let tmp = dealAllPlayers deckFull players [] in
        let players = snd tmp in
        let deck = fst tmp in
        (* JUGAMOS *)
        round players
