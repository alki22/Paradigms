// Standard libraries included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// User defined libraries included
#include "dict.h"
#include "helpers.h"

word_t menu(dict_trans_t dict_trans, dict_ignore_t dict_ignore, word_t current) {
    printf("No hay traducción para la palabra: %s\n\n"
           "\tIgnorar (i) - Ignorar Todas (h) - Traducir como (t) - Traducir siempre como (s)",
           current);

    char c;
    char *result;
    scanf("%c", &c);
    switch (c) {
        case 'i':
            result = current;
        case 'h':
            result = current;
            dict_ignore_add(dict_ignore, current);
        case 't':
            printf("Traducir %s como: ", current);
            scanf("%s", result);
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

word_t translate_word(dict_trans_t dict_trans, dict_ignore_t dict_ignore, word_t word) {
    word_t translated;
    translated = dict_trans_search(dict_trans, word);
    if (translated == NULL) {
        if (!dict_ignore_search(dict_ignore, word)) {
            translated = menu(dict_trans, dict_ignore, word);
        } else {
            translated = word;
        }
    }
}

int translate(char *path, char *output, dict_trans_t dict_trans, dict_ignore_t dict_ignore) {
    FILE *fp_in = fopen(path, "r");
    FILE *fp_out = fopen(output, "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Invalid file\n");
        exit(EXIT_FAILURE);
    }

    word_t word, word_p, trans;
    char *line, *line_iso;
    size_t len;
    while (true) {
        line = readline(fp_in);
        if (line == NULL)
            break;
        
        len = strlen(line);
        line_iso = malloc(len*sizeof(char));
        utf8_to_latin9(line_iso, line, len);
        word = strtok(line_iso, " ");
        
        while (word != NULL) {
            word_t current = malloc(strlen(word)*sizeof(char));
            unsigned int i, j = 0, took_letter = 0;
            
            for (i = 0; i < strlen(word); ++i) {
                if (isalnum(word[i])) {
                    current[j] = word[i];
                    ++j;
                    current[j] = '\0';
                } else if (!took_letter) {
                    fprintf(fp_out, "%c", word[i]);
                } else {
                    trans = translate_word(dict_trans, dict_ignore, current);
                    fprintf(fp_out, "%s%c", trans, word[i]);
                }
            }


            word = strtok(NULL, " ");
            free(line_iso);
        }
    }
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}

int main(int argc, char *argv[]) {
    int dflag = 0;
    int gflag = 0;
    int oflag = 0;
    int rflag = 0;
    char *ivalue = NULL;
    char *dvalue = NULL;
    char *gvalue = NULL;
    char *ovalue = NULL;

    printf("linea 112\n");
    char c;
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
    printf("linea 146\ndvalue: %s\n", dvalue);
    // Tenemos ya todo lo que necesitamos para empezar.
    // En caso de tener diccionarios deberiamos cargarlos.
    dict_trans_t dict_trans = dict_trans_empty(rflag);
    printf("linea 150\n");
    dict_trans = dict_trans_load(dict_trans, dvalue);
    printf("linea 152\n");
    dict_ignore_t dict_ignore = dict_ignore_empty();
    dict_ignore = dict_ignore_load(gvalue, dict_ignore);

    printf("linea 156\n");
    // Hay que hacer unos chequeos con los argumentos de entrada
    translate(ivalue, ovalue, dict_trans, dict_ignore);
    return 0;
}
