type player

(* Crea un nuevo jugador con un nombre *)
val playerNew : string -> player

(* Devuelve la mano del jugador en un mazo *)
val playerHand : player -> deck

(* Se le da una carta al jugador *)
val playerAdd : card -> player -> player
