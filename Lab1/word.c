#include <stdlib.h>
#include <stdio.h>
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
	word_t copy = (char *)malloc(length*sizeof(char *));
	for (i = 0; i < length; ++i) {
		copy[i] = word[i];
	}
	return copy;
}