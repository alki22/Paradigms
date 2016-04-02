// Copyright 2016 Collias, Tiraboschi

#ifndef LAB1_SRC_WORD_H_
#define LAB1_SRC_WORD_H_

// Standard libraries included
#include "stdbool.h"

typedef char *word_t;

int word_compare(word_t word, word_t other);
/* 
 * Compares two words, returns 0 if words are equal,
 * returns <0 if 'word' < 'other' (it's first letter),
 * and >0 if 'word' > 'other'.
 */

unsigned int word_length(word_t word);
/*
 * Returns the given word's length.
 */

word_t word_copy(word_t word);
/*
 * Allocates a new word into memory and copies the given one into it.
 */


word_t word_destroy(word_t word);
/*
 * Destroys the given word, free memory allocated and sets the word to NULL.
 */

#endif  // LAB1_SRC_WORD_H_

