#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Standard libraries included
#include "bst.h"
#include "dict.h"
#include "dict_helpers.h"
#include "helpers.h"
#include "word.h"
// User defined libraries included

struct _dict_trans_t {
    struct _tree_node_t *tree;
    unsigned int length;
    bool reverse;
};

struct _dict_ignore_t {
    word_t *array;
    unsigned int length;
};

//typedef struct _dict_trans_t *dict_trans_t;
//typedef struct _dict_ignore_t *dict_ignore_t;

dict_trans_t dict_trans_empty(bool reverse) {
    dict_trans_t dict = malloc(1*sizeof(struct _dict_trans_t));
    dict->tree = NULL;
    dict->length = 0;
    dict->reverse = reverse;
    return dict;
}

dict_trans_t dict_trans_add(dict_trans_t dict, word_t word1, word_t word2) {
    dict->tree = bst_add(dict->tree, word1, word2);
    ++dict->length;
    return dict;
}

dict_trans_t dict_trans_load(dict_trans_t dict, char *path) {
    FILE *fp;
    char *line = NULL;

    word_t spa;
    word_t eng;
    unsigned int i, j;

    fp = fopen(path, "r");
    if (fp = NULL) {
        printf("Invalid file\n");
        exit(EXIT_FAILURE);
    }
    printf("dict.c: linea 54\n");
    while (true) {
        printf("dict.c: linea 56\n");
        line = readline(fp);
        printf("dict.c: linea 58\n");
        spa = malloc(strlen(line)-1*sizeof(char));
        eng = malloc(strlen(line)-1*sizeof(char));
        i = 0;
        j = 0;
        for (; i < strlen(line); ++i) {
            printf("dict.c: linea 62\n");
            char c = line[i];
            printf("dict.c: linea 64, c = %c\n", c);
            if (isalpha(c)) {
                spa[strlen(spa)] = c;
            } else {
                for(i = i+1; i < strlen(line); ++i) {
                    eng[j] = line[i];
                    ++j;
                }
                break;
            }
        }
        if (dict->reverse)
            dict = dict_trans_add(dict, eng, spa); // podriamos cargar en un array
        else
            dict = dict_trans_add(dict, spa, eng);

        free(spa);
        free(eng);
    }

    fclose(fp);

    if (line)
        free(line);

    dict->length = bst_length(dict->tree);
    return dict;
}

word_t dict_trans_search(dict_trans_t dict, word_t word) {
    return bst_search(dict->tree, word);
}

dict_trans_t dict_trans_destroy(dict_trans_t dict) {
    dict->tree = bst_destroy(dict->tree);
    free(dict);
    dict = NULL;
    return dict;
}

void dict_trans_save(dict_trans_t dict, char *path) {
    // falta pensar que pasa cuando reverse = 1
    FILE *fp;
    unsigned int i;

    pair_t *array = bst_to_array(dict->tree);

    fp = fopen(path, "w");
    if (fp == NULL) {
        printf("Invalid file\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < dict->length; ++i) {
        fprintf(fp, "%s", pair_fst(array[i]));
        fprintf(fp, ",");
        fprintf(fp, "%s\n", pair_snd(array[i]));
    }

    fclose(fp);
}

dict_ignore_t dict_ignore_empty(void) {
    dict_ignore_t dict = malloc(1*sizeof(struct _dict_ignore_t));
    dict->array = NULL;
    dict->length = 0;
    return dict;
}

dict_ignore_t dict_ignore_add(dict_ignore_t dict, word_t word) {
    dict->length++;
    word_t *new = malloc(dict->length*sizeof(char *));
    unsigned int i;
    for(i = 0; i < dict->length - 1; ++i)
        new[i] = dict->array[i];
    new[i] = word;

    free(dict->array);
    dict->array = new;
    ++dict->length;
    return dict;
}

dict_ignore_t dict_ignore_load(char *path, dict_ignore_t dict) {
    unsigned int lines = count_lines(path);
    if (lines == 0) {
        printf("Invalid file\n");
        return NULL;
    }

    FILE *fp = fopen(path, "r");

    dict->array = (char **)malloc(lines*sizeof(char*));
    dict->length = lines;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        dict->array[i] = line;
        ++i;
    }

    return dict;
}


void dict_ignore_sort(dict_ignore_t dict) {
    insertion_sort(dict->array, dict->length);
}

bool dict_ignore_search(dict_ignore_t dict, word_t word) {
    dict_ignore_sort(dict);
    unsigned int i;
    for (i = 0; i < dict->length; ++i) {
        if (!strcmp(word, dict->array[i]))
            return 1;
    }
    return 0;
}

dict_ignore_t dict_ignore_destroy(dict_ignore_t dict) {
    free(dict->array);
    dict->array = NULL;
    free(dict);
    dict = NULL;
    return dict;
}

void dict_ignore_save(char *path, dict_ignore_t dict) {
    // Pre: dictionary is sorted alphabetically
    FILE *fp;
    unsigned int i;

    fp = fopen(path, "w");
    if (fp == NULL) {
        printf("Invalid file\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < dict->length; ++i) {
        fprintf(fp, "%s\n", dict->array[i]);
    }

    fclose(fp);
}
