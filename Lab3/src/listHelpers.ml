let rec elemInList list elem =
    match list with 
    | [] -> false
    | (x :: xs) ->  let b = (elem = x) in
                    if b then true else elemInList xs elem