// Standard libraries included
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// User defined libraries included
#include <stdbool.h>
#include <string.h>
#include "word.h"

typedef char *word_t;

int word_compare(word_t word, word_t other) {
	return strcmp(word, other);
}

unsigned int word_length(word_t word) {
	return strlen(word);
}

word_t word_copy(word_t word) {
	unsigned int i, length = word_length(word);

	word_t copy = malloc(length + 1);
	copy[length] = '\0';
	for (i = 0; i < length; ++i) {
		copy[i] = word[i];
	}
	assert(word_compare(word, copy) == 0);
	return copy;
}

word_t word_destroy(word_t word) {
	free(word);
	return NULL;
}
