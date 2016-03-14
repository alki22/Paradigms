#ifndef _PAIR_H
#define _PAIR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pair.h"
#include "word.h"

struct _pair_t
{
	word_t fst;
	word_t snd;
};

typedef struct _pair_t *pair_t;

pair_t pair_from_word(word_t fst, word_t spa) {
	pair_t pair = NULL;
	pair = calloc(1, sizeof(struct _pair_t));
	pair->fst = fst;
	pair->spa = spa;
	return pair;
}
	
pair_t pair_destroy(pair_t pair)
{
	free(pair);
	pair = NULL;
	return pair;
}

word_t pair_fst(pair_t pair)
{
	return pair->fst;
}

word_t pair_snd(pair_t pair)
{
	return pair->spa;
}

bool pair_is_equal(pair_t pair, pair_t other)
{
	bool result = true;
	result = (word_compare(pair->fst, other->fst) == 0);
	result = result && (word_compare(pair->spa, other->spa) == 0);
	return result;
}

#endif
