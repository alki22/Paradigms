open Random
open List

type card = string
type deck = card list

let deckFull = ["B1";"B2";"B3";"B4";"B5";"B6";"B7";"B8";"B9";"B10";"B11";"B12";
                "C1";"C2";"C3";"C4";"C5";"C6";"C7";"C8";"C9";"C10";"C11";"C12";
                "E1";"E2";"E3";"E4";"E5";"E6";"E7";"E8";"E9";"E10";"E11";"E12";
                "O1";"O2";"O3";"O4";"O5";"O6";"O7";"O8";"O9";"O10";"O11";"O12";
                "SID";"SSWAP";"SMAX";"SMIN";"STOP";"SPAR"]

(* l -> lista, s -> donde voy guardando la nueva lista, k -> posicion a borrar *)
let rec listDeleteElemAux l s k =
    match l with
    | [] -> []
    | x :: xs -> if k == 0 then
                    s @ xs
                else
                    listDeleteElemAux xs (s @ [x]) (k - 1)

let listDeleteElem l k =
    listDeleteElemAux l [] k

(* c -> lista de cartas, k -> posicion de la carta *)
let rec deckGetCardAux c k =
    match c with
    | [] -> ""
    | x :: xs -> if k == 0 then
                    x
                else
                    deckGetCardAux xs (k - 1)

let deckGetCard c =
    let l = List.length c in
    if (l == 0) then
        None
    else
        let r = Random.int l in
        let x = deckGetCardAux c r in (* Esta carta va a algún lado *)
        Some (x,listDeleteElem c r)