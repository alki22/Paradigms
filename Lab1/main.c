// Standard libraries included
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// User defined libraries included
#include "dict.h"

    isupper
    islower
    isalpha
    ispunct

int translator(char *path, bst_t dict_trans, char **dict_ignore) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Invalid file\n");
        return -1; // Error archivo invalido
    }

    word_t current;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (isalpha())
    }
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
    dict_trans_load(dict, dvalue, rflag);
    char **dict_ignore = dict_ignore_load(gvalue);
}

./translator -i texto.txt -d diccionario -g ignorados -o output.txt:
    