#ifndef _STACK_H
#define _STACK_H

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bst.h"

typedef struct _stack_t *stack_t;

stack_t stack_empty(void);
/*
 * Return a newly created, empty stack.
 *
 * The caller must call stack_destroy when done using the resulting stack,
 * so the resources allocated by this call are freed.
 *
 * POST: the result is a valid stack pointer, and stack_length(result) is 0.
 */

bool stack_is_empty(stack_t stack);
/*
 * Return a if the stack is empty or not.
 */

bst_t stack_top(stack_t stack);


stack_t stack_push(stack_t stack, bst_t bst);
/*
 * Return the given 'stack' with the ('index', 'data') added to the top.
 *
 * The given 'index' and 'data' are inserted in the stack,
 * so they can not be destroyed by the caller.
 *
 * PRE: all 'stack', 'index' and 'data' are valid instances.
 *
 * POST: the length of the result is the same as the length of 'stack'
 * plus one. The elements of the result are the same as the ones in 'stack'
 * with the new pair ('index', 'data') added at the end of the stack.
 */

stack_t stack_pop(stack_t stack);
/*
 * Return the given 'stack' with the top (index, <data>) pair
 * occurrence removed.
 *
 * Please note that 'index' may not be in the stack (thus an unchanged
 * stack is returned).
 *
 * PRE: 'stack' and 'index' are valid instances.
 *
 * POST: the length of the result is the same as the length of 'stack'
 * minus one if 'index' existed in 'stack'. The elements of the result is
 * the same as the one in 'stack' with the entry for 'index' removed.
 */

stack_t stack_destroy(stack_t stack);
/*
 * Free the resources allocated for the given 'stack', and set it to NULL.
 */

#endif
