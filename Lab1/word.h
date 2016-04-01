#ifndef _WORD_H
#define _WORD_H

#include <stdbool.h>

typedef char *word_t;

int word_compare(word_t word, word_t other);
/* 
 * Compares two words, returns 0 if words are equal,
 * returns <0 if 'word' < 'other' (it's first letter),
 * and >0 if 'word' > 'other'.
 */

unsigned int word_length(word_t word);

word_t word_copy(word_t word);

word_t word_destroy(word_t word);

#endif
