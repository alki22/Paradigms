// Copyright 2016 Collias, Tiraboschi

// Standard libraries included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// User defined libraries included
#include "dict.h"
#include "helpers.h"

word_t menu(dict_trans_t dict_trans, dict_ignore_t dict_ignore, word_t word) {
    printf("There is no translation for the word: %s\n"
           "Ignore (i) - Ignore All (h) - Translate as (t) - Always translate"
           " as (s)\n", word);

    char c;
    scanf("%c", &c);
    printf("%c\n", c);
    word_t result = NULL;
    switch (c) {
        case 'i':
            result = word_copy(word);
            break;
        case 'h':
            result = word_copy(word);
            dict_ignore_add(dict_ignore, word);
            break;
        case 't':
            printf("Translate %s as: ", word);
            result = malloc(100*sizeof(char));
            scanf("%s", result);
            break;
        case 's':
            printf("Translate %s as: ", word);
            result = malloc(100*sizeof(char));
            scanf("%s", result);
            dict_trans_add(dict_trans, word, result);
            break;
        default:
            printf("Invalid option");
            exit(EXIT_FAILURE);
    }
    while (c != '\n')
        scanf("%c", &c);
    return result;
}

word_t translate_word(dict_trans_t dict_trans, dict_ignore_t dict_ignore,
                      word_t word) {
    word_t translated = NULL;
    bool lowered = lower_first_letter(word);
    printf("word: %s, lowered: %d\n", word, lowered);
    translated = dict_trans_search(dict_trans, word);

    if (translated == NULL) {
        if (dict_ignore_search(dict_ignore, word)) {
            translated = word_copy(word);
        } else {
            translated = menu(dict_trans, dict_ignore, word);
        }
    } else {
        translated = word_copy(translated);
    }

    if (lowered) {
        upper_first_letter(translated);
    }
    return translated;
}

int translate(char *path, char *output, dict_trans_t dict_trans,
              dict_ignore_t dict_ignore) {
    FILE *fp_in = fopen(path, "r");
    FILE *fp_out = fopen(output, "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Invalid file on translate\n");
        exit(EXIT_FAILURE);
    }

    // Design choice
    char current[100];
    current[0] = '\0';
    word_t translated = NULL;
    unsigned int index = 0;
    char c;

    while ((c = fgetc(fp_in)) != EOF) {
        if (c == -62) {
            c = fgetc(fp_in);
        } else if (c == -61) {
            current[index] = c;
            ++index;
            c = fgetc(fp_in);
            current[index] = c;
            ++index;
            current[index] = '\0';
        } else if (isalnum(c)) {
            current[index] = c;
            ++index;
            current[index] = '\0';
        } else {
            if (index != 0) {
                printf("current: %s\n", current);
                translated = translate_word(dict_trans, dict_ignore, current);
                fprintf(fp_out, "%s", translated);
                printf("translated: %s\n", translated);
                translated = word_destroy(translated);
            }
            fprintf(fp_out, "%c", c);
            translated = NULL;
            empty_array(current, 100);
            index = 0;
        }
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}

int main(int argc, char *argv[]) {
    int rflag = 0;
    char *ivalue = NULL;
    char *dvalue = "dict_trans.txt";
    char *gvalue = "dict_ignore.txt";
    char *ovalue = "output.txt";

    char c;
    while ((c = getopt(argc, argv, "i:d:g:o:r")) != -1) {
        switch (c) {
            case 'i':
                ivalue = optarg;
                break;
            case 'd':
                dvalue = optarg;
                break;
            case 'g':
                gvalue = optarg;
                break;
            case 'o':
                ovalue = optarg;
                break;
            case 'r':
                rflag = 1;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n",
                             optopt);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort();
        }
    }

    if (ivalue == NULL) {
        fprintf(stderr, "Input file needed.\n");
        abort();
    }

    dict_trans_t dict_trans = dict_trans_empty(rflag);
    dict_ignore_t dict_ignore = dict_ignore_empty();

    dict_trans = dict_trans_load(dict_trans, dvalue);
    dict_ignore = dict_ignore_load(dict_ignore, gvalue);

    translate(ivalue, ovalue, dict_trans, dict_ignore);

    dict_trans_save(dict_trans, dvalue, rflag);
    dict_ignore_save(dict_ignore, gvalue);

    dict_trans_destroy(dict_trans);
    dict_ignore_destroy(dict_ignore);
    printf("Completado!\n");
    return 0;
}
