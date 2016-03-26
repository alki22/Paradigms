#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "word.h"
#include "bst.h"

char *strcat_(char *dest, const char *src, unsigned int offs);
/*
 * Concatenates the source string into the destiny string with the given offset.
 */

unsigned int count_lines(char *path);
/*
 * Returns the number of lines in the file
 */

void dict_trans_load(bst_t dict, char *path, int reverse);
/*
 * Loads the translation dictionary into the bst structure
 */

char ** dict_ignore_load(path);
/*
 * Loads the ignored words list into an array of strings
 */
