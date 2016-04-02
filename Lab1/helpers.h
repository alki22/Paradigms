#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include <stdlib.h>

char *readline(FILE * file);

void empty_array(char array[], unsigned int length);

bool lower_first_letter(char *word);

void upper_first_letter(char *word);
#endif
