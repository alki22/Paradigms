let rec elemInList list elem =
    match list with 
    | [] -> false
    | (x :: xs) ->  let b = (elem = x) in
                    if b then true else elemInList xs elem

(* l -> lista, s -> donde voy guardando la nueva lista, k -> posicion a borrar *)
let rec listDeleteElemAux l s k =
    match l with
    | [] -> []
    | x :: xs -> if k == 0 then
                    s @ xs
                else
                    listDeleteElemAux xs (s @ [x]) (k - 1)

(* Devuelve una copia de la lista dada sin el K-ésimo elemento *)
let listDeleteElem l k =
    listDeleteElemAux l [] k