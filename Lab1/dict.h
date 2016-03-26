#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "word.h"
#include "bst.h"

unsigned int count_lines(char *path);
/*
 * Returns the number of lines in the file
 */

bst_t dict_trans_load(bst_t dict, char *path, int reverse);
/*
 * Loads the translation dictionary into the bst structure
 */

bst_t dict_trans_add(bst_t dict, word_t word1, word_t word2);
/*
 * Adds pair of words to specified dictionary
 */

struct dict_ignore dict_ignore_empty(void);
/*
 *
 */

struct dict_ignore dict_ignore_load(char *path, struct dict_ignore dict);
/*
 * Loads the ignored words list into an array of strings
 */

struct dict_ignore dict_ignore_add(struct dict_ignore dict, word_t word);
/*
 *
 */
