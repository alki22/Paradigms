#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bst.h"
#include "word.h"

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

void dict__trans_load(bst_t dict, char *path, int reverse) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    word_t spa;
    word_t eng;
    unsigned int i;

    fp = fopen(path, "r");
    if (fp = NULL) {
        printf("Archivo invalido\n");
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
        printf("Archivo invalido");
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

int main(argc, char *argv[]) {
    int dflag = 0;
    int gflag = 0;
    int oflag = 0;
    int rflag = 0;
    char *ivalue = NULL;
    char *dvalue = NULL;
    char *gvalue = NULL;
    char *ovalue = NULL;

    while ((c = getopt(argc, argv, "i:d:g:o:r")) != -1) {
        switch (c) {
            case 'i':
                ivalue = optarg;
                break;
            case 'd':
                dflag = 1;
                dvalue = optarg;
                break;
            case 'g':
                gflag = 1;
                gvalue = optarg;
                break;
            case 'o':
                oflag = 1;
                ovalue = optarg;
                break;
            case 'r':
                rflag = 1;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort ();
        }
    }
    // Tenemos ya todo lo que necesitamos para empezar.
    // En caso de tener diccionarios deberiamos cargarlos.
    dict_trans = bst_empty();
    dict_trans_load(dict, dvalue);
    char **dict_ignore = dict_ignore_load(gvalue);
}
