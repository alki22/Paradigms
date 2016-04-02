// Standard libraries included
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// User defined libraries included
#include "pair.h"
#include "word.h"

// Pair structure definition
struct _pair_t
{
	word_t fst;
	word_t snd;
};

typedef struct _pair_t *pair_t;

pair_t pair_from_word(word_t fst, word_t snd) {
	pair_t pair = (struct _pair_t *)calloc(1, sizeof(struct _pair_t));
	pair->fst = word_copy(fst);
	pair->snd = word_copy(snd);
	return pair;
}
	
pair_t pair_destroy(pair_t pair)
{
	pair->fst = word_destroy(pair->fst);
	pair->snd = word_destroy(pair->snd);
	free(pair);
	return NULL;
}

word_t pair_fst(pair_t pair)
{
	return pair->fst;
}

word_t pair_snd(pair_t pair)
{
	return pair->snd;
}

pair_t pair_copy(pair_t pair) {
	pair_t copy = malloc(1*sizeof(struct _pair_t));
	copy->fst = word_copy(pair->fst);
	copy->snd = word_copy(pair->snd);
	return copy;
}

bool pair_is_equal(pair_t pair, pair_t other) {
	bool result = true;
	result = (word_compare(pair->fst, other->fst) == 0);
	result = result && (word_compare(pair->snd, other->snd) == 0);
	return result;
}

unsigned int pair_size(void) {
	return sizeof(struct _pair_t);
}
