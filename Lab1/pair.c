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

pair_t pair_from_word(word_t fst, word_t snd) {
	pair_t pair = (struct _pair_t *)calloc(1, sizeof(struct _pair_t));
	pair->fst = fst;
	pair->snd = snd;
	return pair;
}
	
pair_t pair_destroy(pair_t pair)
{
	free(pair);
	pair = NULL;
	return pair;
}

pair_t pair_copy(pair_t pair) {
	pair_t copy = (struct _pair_t *)calloc(1, sizeof(struct _pair_t));
	copy->fst = pair->fst;
	copy->snd = pair->snd;
	return copy;
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
	pair_t copy = NULL;
	copy = calloc(1, sizeof(struct _pair_t));
	copy->fst = pair->fst;
	copy->snd = pair->snd;
	return copy;
}

bool pair_is_equal(pair_t pair, pair_t other) {
	bool result = true;
	result = (word_compare(pair->fst, other->fst) == 0);
	result = result && (word_compare(pair->snd, other->snd) == 0);
	return result;
}
