#ifndef _PAIR_H
#define _PAIR_H

#include <stdbool.h>
#include "index.h"
#include "data.h"


typedef struct _pair_t *pair_t;

pair_t pair_from_word(char *spa, char *eng);
/*
 * Build a new pair from the word.
 *
 * Do NOT free index and data after creating the pair, but only through
 * pair_destroy.
 */

pair_t pair_destroy(pair_t pair);
/*
 * Free the memory allocated by the given 'pair'. Set 'pair' to NULL.
 */

index_t pair_spa(pair_t pair);
/*
 * Return a reference to the first pair element.
 */

data_t pair_eng(pair_t pair);
/*
 * Return a reference to the second pair element.
 */

bool pair_is_equal(pair_t pair, pair_t other);
/*
 * Return whether 'pair' is equal to 'other'.
 */

#endif
