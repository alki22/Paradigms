#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Standard libraries included
#include "word.h"
#include "bst.h"
//User defined libraries included

struct dict_trans {
    bst_t tree;
    unsigned int length;
};

struct dict_ignore {
    word_t *array;
    unsigned int length;
};

unsigned int count_lines(char *path) {
    FILE *fp = fopen(filename,"r");
    int ch = 0;
    unsigned int *lines = 0;

    if (fp == NULL)
        return 0;

    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(fp);

    return lines;
}

struct dict_trans dict_trans_empty(void) {
    struct dict_trans dict = malloc(1*sizeof(struct dict_trans));
    dict->tree = NULL;
    dict->length = 0;
    return dict;
}

bst_t dict_trans_load(bst_t dict, char *path, int reverse) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    word_t spa;
    word_t eng;
    unsigned int i, j;

    fp = fopen(path, "r");
    if (fp = NULL) {
        printf("Invalid file\n");
        return;
    }

    while (read = getline(&line, &len, fp)) != -1) {
        spa = malloc(len-1*sizeof(char));
        eng = malloc(len-1*sizeof(char));
        i = 0;
        j = 0;
        for (; i < len; ++i) {
            char c = line[i];
            if (isalpha(c)) {
                spa[strlen(spa)] = c;
            } else {
                for(i = i+1; i < len; ++i) {
                    eng[j] = line[i];
                    ++j;
                }
                break;
            }
        }
        if (reverse)
            dict = bst_add(dict, eng, spa);
        else
            dict = bst_add(dict, spa, eng);

        free(spa);
        free(eng);
    }

    fclose(fp);

    if (line)
        free(line);
}


bst_t dict_trans_add(bst_t dict, word_t word1, word_t word2) {
    dict = bst_add(dict, word1, word2);
    return dict;
}

struct dict_ignore dict_ignore_empty(void) {
    struct dict_ignore dict = malloc(1*sizeof(struct dict_ignore));
    dict->array = NULL;
    dict->length = 0;
    return dict;
}

struct dict_ignore dict_ignore_load(char *path, struct dict_ignore dict) {
    unsigned int lines = count_lines(path);
    if (lines == 0) {
        printf("Invalid file\n");
        return NULL;
    }

    FILE *fp = fopen(path, "r");

    dict->array = malloc(lines*sizeof(char*);
    dict->length = lines;

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int i = 0;
    while (read = getline(&line, &len, fp)) != -1) {
        dict->array[i] = line;
        ++i;
    }

    return dict;
}

struct dict_ignore dict_ignore_add(struct dict_ignore dict, word_t word) {
    dict->length++;
    word_t * new = malloc(dict->length*sizeof(char *));
    unsigned int i;
    for(i = 0; i < dict->length - 1; ++i)
        new[i] = dict->array[i];
    new[i] = word;

    free(dict->array);
    dict->array = new;
    return dict;
}
