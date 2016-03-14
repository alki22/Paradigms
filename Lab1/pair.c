#ifndef _PAIR_H
#define _PAIR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "pair.h"

struct _pair_t
{
	char *spa;
	char *eng;
};

typedef struct _pair_t *pair_t;

pair_t pair_from_word(char *spa, char *eng) {
	pair_t pair = NULL;
	pair = calloc(1, sizeof(struct _pair_t));
	pair->spa = spa;
	pair->eng = eng;
	return pair;
}
	
pair_t pair_destroy(pair_t pair)
{
	free(pair);
	pair = NULL;
	return pair;
}

char *pair_fst(pair_t pair)
{
	return pair->spa;
}

char *pair_snd(pair_t pair)
{
	return pair->eng;
}

bool pair_is_equal(pair_t pair, pair_t other)
{
	bool result = true;
	result = (strcmp(pair->spa, other->spa) == 0);
	result = result && (strcmp(pair->eng, other->eng) == 0);
	return result;
}

#endif
