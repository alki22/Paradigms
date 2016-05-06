open Deck
open Player
open Pervasives
open Printf

let players = []

let addPlayer =
    let name = read_line() in
    if name = "EXIT" then (0,"EXIT")
    else (1,name)

let rec getPlayers (s : list player) =
    let got = addPLayer() in
    match got with
    | (0,_) -> s
    | (1,name) -> 