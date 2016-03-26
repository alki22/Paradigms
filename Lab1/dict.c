#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Standard libraries included
#include "word.h"
#include "bst.h"
//User defined libraries included

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
