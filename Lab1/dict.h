#ifndef _DICT_H
#define _DICT_H

// Standard libraries included
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// User defined libraries included
#include "word.h"
#include "bst.h"
#include "dict_helpers.h"

typedef struct _dict_trans_t *dict_trans_t;
typedef struct _dict_ignore_t *dict_ignore_t;

dict_trans_t dict_trans_empty(bool reverse);
/*
 * Create empty "translation dictionary".
 */

dict_trans_t dict_trans_add(dict_trans_t dict, word_t word1, word_t word2);
/*
 * Adds pair of words to specified dictionary.
 */

dict_trans_t dict_trans_load(dict_trans_t dict, char *path);
/*
 * Loads the translation dictionary into the bst structure.
 */

word_t dict_trans_search(dict_trans_t dict, word_t word);
/*
 * Searchs for the given word in the translations dictionary.
 */
dict_trans_t dict_trans_destroy(dict_trans_t dict);
/*
 * Free the translations dictionary and sets it to NULL.
 */
void dict_trans_save(dict_trans_t dict, char *path);
/*
 * Saves the dictionary into the dictionary file in the given path.
 */

dict_ignore_t dict_ignore_empty(void);
/*
 * Creates an empty "ignore dictionary".
 */

dict_ignore_t dict_ignore_add(dict_ignore_t dict, word_t word);
/*
 * Adds word to specified dictionary.
 */

dict_ignore_t dict_ignore_load(dict_ignore_t dict, char *path);
/*
 * Loads the ignored words list into an array of strings
 */

void dict_ignore_sort(dict_ignore_t dict);
/*
 * Sorts the ignored words dictionary in alphabetical order.
 */
 
bool dict_ignore_search(dict_ignore_t dict, word_t word);
/*
 * Returns if the given word is in the ignored words dictionary.
 */

dict_ignore_t dict_ignore_destroy(dict_ignore_t dict);
/*
 * Free the ignored words dictionary and sets it to NULL.
 */

void dict_ignore_save(dict_ignore_t dict, char *path);
/*
 * Writes the new ignored words dictionary into the dictionary file in the given path.
 */

#endif
