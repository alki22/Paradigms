// Copyright 2016 Collias, Tiraboschi

#ifndef LAB1_SRC_PAIR_H_
#define LAB1_SRC_PAIR_H_

// Standard libraries included
#include <stdbool.h>

// User defined libraries included
#include "word.h"

typedef struct _pair_t *pair_t;

pair_t pair_from_word(word_t spa, word_t eng);
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

pair_t pair_copy(pair_t pair);
/*
 * Copy the pair given.
 */

word_t pair_fst(pair_t pair);
/*
 * Return a reference to the first pair element.
 */

word_t pair_snd(pair_t pair);
/*
 * Return a reference to the second pair element.
 */

bool pair_is_equal(pair_t pair, pair_t other);
/*
 * Return whether 'pair' is equal to 'other'.
 */

unsigned int pair_size(void);

#endif  // LAB1_SRC_PAIR_H_
