open Deck
type player = { hand : deck; name : string; score : int }

let playerDraw { hand = h; name = n; _ } d =
	let (c,d) = deckGetCard d in
		c :: hand
