(* Chequea si un elemento pertenece a la lista *)
val elemInList : 'a list -> 'a -> bool

(* Devuelve una copia de la lista dada sin el k-ésimo elemento *)
val listDeleteElem : 'a list -> int -> 'a list