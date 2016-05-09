open Deck
open Printf

type player = { name : string; points : int; cards : deck; thrown : card list }

let playerNew (name : string) = {name = name; points = 0; cards = []; thrown = [] }

let playerAdd (card : card) (player : player) =
    {player with cards = card :: player.cards}

let playerGive (player : player) (card : card) =
    if (elemInList player.deck card) then
        {player with cards = deckCardDelete player.cards card}
    else
    


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