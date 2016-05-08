open Deck
open Printf

type player = { name : string; points : int; cards : deck; }

let playerNew (name : string) = {name = name; points = 0; cards = []}

let playerHand (player : player) =
    let cards = player.cards in
    let length = List.length cards in
    match cards with
    | [] ->
    | x :: xs ->    

let playerAdd (card : card) (player : player) =
    {player with cards = card :: player.cards}

let playerPlay (player : player) =
    printf "Que carta vas a jugar %s?" player.name;
    let input = read_int() in
    let playerDeck = player.cards in
    let (playerDeck, card) = deckGetSingleSpecificCard playerDeck input in
    if (fst card) = s then algo
    else begin
        let {player with cards = playerDeck} in
        (player, card))
    end