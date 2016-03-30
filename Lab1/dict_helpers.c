#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Standard libraries included
#include "dict_helpers.h"

unsigned int count_lines(char *path) {
    FILE *fp = fopen(path,"r");
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

void swap(char **array, unsigned int i, unsigned int j) {
    if (i != j) {
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void insert(char **array, unsigned int i) {
    unsigned int j = i;
    while (j > 0) {
        if (strcmp(array[j], array[j-1]) < 0) {
            swap(array, j, j - 1);
            j--;
        } else
            break;
    }
}

void insertion_sort(char **array, unsigned int length) {
    for (unsigned int i = 1; i < length; i++)
        insert(array, i);
}

