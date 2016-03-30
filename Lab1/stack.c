#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "bst.h"

struct _stack_t {
    bst_t bst;
    struct _stack_t *next;
};


stack_t stack_empty(void) {
	stack_t result = NULL;
	assert(result == NULL);	
	return result;
}

bool stack_is_empty(stack_t stack) {
    return stack == NULL;
}

bst_t stack_top(stack_t stack) {
    assert(stack != NULL);
    
    return stack->bst;
}

stack_t stack_push(stack_t stack, bst_t bst) {
	stack_t current;
	
	current = calloc(1,sizeof(struct _stack_t));
	current->bst = bst;
	current->next = stack;
	stack = current;
	current = NULL;
	
	return stack;
}

stack_t stack_pop(stack_t stack) {
	
	stack_t current = stack;
	stack = stack->next;
	
	free(current);
	
	return stack;
}

stack_t stack_destroy(stack_t stack) {
    while (stack != NULL) {
        stack = stack_pop(stack);
    }
    
    return stack;
}
