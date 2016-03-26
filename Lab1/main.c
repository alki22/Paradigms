// Standard libraries included
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

// User defined libraries included
#include "dict.h"

word_t menu(bst_t dict_trans, char **dict_ignore, word_t current) {
    printf("No hay traducción para la palabra: %s\n\nIgnorar (i) -
           Ignorar Todas (h) - Traducir como (t) - Traducir siempre como (s)",
           current);

    char c;
    scanf("%c", c);
    switch (c) {
        case 'i':
            result = current;
        case 'h':
            result = current;
            dict_ignore_add(current); // To implement
        case 't':
            printf("Traducir %s como: ", current);
            scanf("I%s", result);
        case 's':
            printf("Traducir %s como: ", current);
            scanf("%s", result);
            dict_trans_add(dict_trans, current, result);
        default:
            printf("Invalid option");
            exit(EXIT_FAILURE);
    }
    return result;
}

int translator(char *path, char *output, bst_t dict_trans, char **dict_ignore) {
    FILE *fp_in = fopen(path, "r");
    FILE *fp_out = fopen(output, "w");

    if (fp == NULL) {
        printf("Invalid file\n");
        return -1; // Error archivo invalido
    }

    // Design choice
    word_t current[100]; // Fijarse si neceitamos hacer ralloc
    word_t translated = NULL;
    unsigned int curr_elem;

    char c;
    while ((c = fgetc(fp_in)) != EOF) {
        curr_elem = 0;
        if (isalpha(c)) {
            current[++curr_elem] = c;
            current[curr_elem] = '\0';
        } else {
            translated = bst_search(dict_trans, current);
            if (translated == NULL) {
                // Menu para ver que hacemos
            } else {
                fprintf(fp_out, translated);
            }

            if (c != '¿') {
                char str[2];
                str[0] = c;
                str[1] = '\0'
                fprintf(fp_out, str);
            }

        }
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
    dict_trans = dict_trans_load(dict, dvalue, rflag);
    char **dict_ignore = dict_ignore_load(gvalue);
}
