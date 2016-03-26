#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//Standard libraries included
#include "word.h"
#include "bst.h"
//User defined libraries included

char *strcat(char *dest, const char *src, unsigned int offset) {
    size_t i,j;
    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = offset; src[j] != '\0'; j++)
        dest[i+j] = src[j];
    dest[i+j] = '\0';
    return dest;
}

unsigned int count_lines(char *path) {
    FILE *fp = fopen(filename,"r");
    int ch = 0;
    unsigned int lines = 0;

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

void dict_trans_load(bst_t dict, char *path, int reverse) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    word_t spa;
    word_t eng;
    unsigned int i;

    fp = fopen(path, "r");
    if (fp = NULL) {
        printf("Invalid file\n");
        return;
    }

    while (read = getline(&line, &len, fp)) != -1) {
        spa = NULL;
        eng = NULL;
        i = 0;
        for (; i < len; ++i) {
            char c = line[i];
            if (isalpha(c)) {
                strcat(spa, char *(c), 0);
            } else {
                strcat(eng, line, i+1);
                break;
            }
        }
        if (reverse)
            dict = bst_add(dict, eng, spa);
        else
            dict = bst_add(dict, spa, eng);
    }

    fclose(fp);

    if (line)
        free(line);
}

char ** dict_ignore_load(path) {
    unsigned int lines = count_lines(path);
    if (lines == 0) {
        printf("Invalid file\n");
        return NULL;
    }

    FILE *fp = fopen(path, "r");
    char *dict_ignore[lines];

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int i = 0;
    while (read = getline(&line, &len, fp)) != -1) {
        dict_ignore[i] = line;
        ++i;
    }

    return dict_ignore;
}
