#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include <stdlib.h>

char *readline(FILE * file);

size_t utf8_to_latin9(char *const output, const char *const input, const size_t length);

#endif
