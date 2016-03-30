#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "word.h"
#include "bst.h"

unsigned int count_lines(char *path);
/*
 * Returns the number of lines in the file
 */

struct dict_trans *dict_trans_empty(void);
/*
 * Create empty "translation dictionary"
 */

struct dict_trans *dict_trans_add(struct dict_trans *dict, word_t word1, word_t word2);
/*
 * Adds pair of words to specified dictionary
 */

struct dict_trans *dict_trans_load(struct dict_trans *dict, char *path, int reverse);
/*
 * Loads the translation dictionary into the bst structure
 */

struct dict_ignore *dict_ignore_empty(void);
/*
 * Create empty "ignore dictionary"
 */

struct dict_ignore *dict_ignore_add(struct dict_ignore *dict, word_t word);
/*
 * Adds word to specified dictionary
 */

struct dict_ignore *dict_ignore_load(char *path, struct dict_ignore dict);
/*
 * Loads the ignored words list into an array of strings
 */
