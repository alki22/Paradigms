// Standard libraries included
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User defined libraries included
#include "helpers.h"

#define BUFFER_SIZE 128

char *readline(FILE * file) {
    bool done = false;
    char *result = NULL, *read_from = NULL;
    char *alloc_result = NULL, *fgets_result = NULL;
    unsigned int size = BUFFER_SIZE;
    size_t result_len = 0;

    /* char *fgets(char *s, int size, FILE *stream);

       fgets() reads in at most one less than size characters from stream and
       stores them into the buffer pointed to by s. Reading stops after an EOF
       or a newline. If a newline is read, it is stored into the buffer. A
       terminating null byte ('\0') is stored after the last character in the
       buffer. */

    while (!done) {
        /* need to use 2 pointers to avoid leaking resources from 'result' */
        alloc_result = realloc(result, size * sizeof(char));
        if (alloc_result == NULL) {
            /* realloc failed, yet we need to free the memory from 'result' */
            free(result);
            result = NULL;
            done = true;
        } else {
            /* point 'result' to the newly allocated memory */
            result = alloc_result;

            /* point 'read_from' to the unused memory space */
            read_from = result + result_len;

            /* read from 'file' up to 'size - result_len' */
            fgets_result = fgets(read_from, size - result_len, file);
            if (fgets_result == NULL) {
                free(result);
                result = NULL;
                done = true;
            } else {
                /* check if the user entered a newline */
                result_len = strlen(result);
                assert(result_len < size);
                if (feof(file)) {
                    done = true;
                } else if (result[result_len - 1] == '\n') {
                    /* Remove trailing '\n' */
                    result[result_len - 1] = '\0';
                    assert(strlen(result) == result_len - 1);
                    done = true;
                }
            }
        }
        size = size * 2;
    }

    /* will return NULL if something went wrong */
    assert(result == NULL || result[strlen(result)] != '\n');
    return (result);
}

void empty_array(char array[], unsigned int length) {
    unsigned int i;
    for (i = 0; i < length; ++i)
        array[i] = '\0';
}

char *first_letter_upper(char *word) {
    char *result = calloc(3,sizeof(char));
    if (word[0] == -61) {
        result[0] = -61;
        switch (word[1]) {
            // Á
            case -127:
                result[1] = -95;
                break;
            // É
            case -119:
                result[1] = -87;
                break;
            // Í
            case -115:
                result[1] = -83;
                break;
            // Ó
            case -109:
                result[1] = -77;
                break;
            // Ú
            case -102:
                result[1] = -70;
                break;
            // Ñ
            case -111:
                word[1] = -79;
                break;
            default:
                printf("Error\n");
                exit(EXIT_FAILURE);
        }
    }
    else if (isupper(word[0])) {

        result[0] = tolower(word[0]);
    }
    return result;
}

bool lower_first_letter(char *word) {
    bool result;
    char *fl = first_letter_upper(word);
    if (strlen(fl) > 0) {
        unsigned int i, len = (unsigned int)strlen(fl);
        for (i = 0; i < len; ++i) {
            word[i] = fl[i];
        }
        result = true;
    }
    else
        result = false;
    return result;
}

void upper_first_letter(char *word) {
    if (word[0] == -61) {
        switch (word[1]) {
            // Á
            case -95:
                word[1] = -127;
                break;
            // É
            case -87:
                word[1] = -119;
                break;
            // Í
            case -83:
                word[1] = -115;
                break;
            // Ó
            case -77:
                word[1] = -109;
                break;
            // Ú
            case -70:
                word[1] = -102;
                break;
            // Ñ
            case -79:
                word[1] = -111;
                break;
            default:
                printf("Error\n");
                exit(EXIT_FAILURE);
        }
    }
    else {
        word[0] = toupper(word[0]);
    }
}

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
    unsigned int i;
    for (i = 1; i < length; i++)
        insert(array, i);
}

