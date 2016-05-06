open Deck
open Player
open Pervasives
open Printf

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

let _ =
    (* Definimos a los jugadores *)
    let players = getPlayers [] in
    if List.length players < 2 then raise NotEnoughPlayers
    (* Repartimos las cartas *)
    
