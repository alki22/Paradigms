#ifndef _HELPERS_H
#define _HELPERS_H

// Standard libraries included
#include <stdio.h>
#include <stdlib.h>

char *readline(FILE * file);
/*
 * Makes a line-by-line read of the given file.
 */
 
void empty_array(char array[], unsigned int length);
/*
 * Empties the given array, frees it's alocated resources and sets it to NULL.
 */
 
bool lower_first_letter(char *word);
/*
 * Returns if the word's first letter is a lower.
 */
 
void upper_first_letter(char *word);
/*
 * Turns the word's first letter into an upper.
 */

unsigned int count_lines(char *path);
/*
 * Returns the number of lines of the file.
 */

void insertion_sort(char **array, unsigned int length);
/*
 * Sorts the given array.
 */
 
#endif
