open Deck
open Player
open Pervasives
open Printf

exception NotEnoughPlayers

let addPlayer =
    let name = read_line() in
    if name = "EXIT" then (0,"EXIT")
    else (1,name)

let rec getPlayers (s : player list) =
    let got = addPLayer() in
    match got with
    | (0,_) -> s
    | (1,name) ->   let s = (playerNew name) :: s in
                    getPlayers s

let dealPlayer (player : player) (deck : deck) =
    let s = deckGetMultipleCards d 7 in
    ((fst s),{player with cards = (snd s) @ player.cards})

let dealAllPlayers (players : player list) (deck : deck) (s : player list) =
    match players with
    | [] -> (s, deck)
    | x :: xs ->    let m = dealPlayer x d in
                    let s = s @ [snd m] in
                    dealAllPlayers xs (fst m) s
                    

let _ =
    (* Definimos a los jugadores *)
    let players = getPlayers [] in
    if List.length players < 2 then
        raise NotEnoughPlayers
    else
        (* Repartimos las cartas *)
        let (players, deck) = dealAllPlayers players deckFull in
        (* JUGAMOS *)
        play players deck
