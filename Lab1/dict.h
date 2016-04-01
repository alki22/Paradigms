#ifndef _DICT_H
#define _DICT_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// Standard libraries included
#include "word.h"
#include "bst.h"
#include "dict_helpers.h"
// User defined libraries included

typedef struct _dict_trans_t *dict_trans_t;
typedef struct _dict_ignore_t *dict_ignore_t;

dict_trans_t dict_trans_empty(bool reverse);
/*
 * Create empty "translation dictionary"
 */

dict_trans_t dict_trans_add(dict_trans_t dict, word_t word1, word_t word2);
/*
 * Adds pair of words to specified dictionary
 */

dict_trans_t dict_trans_load(dict_trans_t dict, char *path);
/*
 * Loads the translation dictionary into the bst structure
 */

word_t dict_trans_search(dict_trans_t dict, word_t word);

dict_trans_t dict_trans_destroy(dict_trans_t dict);

void dict_trans_save(dict_trans_t dict, char *path);

dict_ignore_t dict_ignore_empty(void);
/*
 * Create empty "ignore dictionary"
 */

dict_ignore_t dict_ignore_add(dict_ignore_t dict, word_t word);
/*
 * Adds word to specified dictionary
 */

dict_ignore_t dict_ignore_load(dict_ignore_t dict, char *path);
/*
 * Loads the ignored words list into an array of strings
 */

void dict_ignore_sort(dict_ignore_t dict);

bool dict_ignore_search(dict_ignore_t dict, word_t word);

dict_ignore_t dict_ignore_destroy(dict_ignore_t dict);

void dict_ignore_save(dict_ignore_t dict, char *path);

#endif
