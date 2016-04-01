#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
//Standard libraries included
#include "bst.h"
#include "pair.h"
#include "stack.h"
#include "word.h"
//User defined libraries included

struct _tree_node_t  {
    struct _pair_t *pair;
    struct _tree_node_t *left;
    struct _tree_node_t *right;
};

typedef struct _tree_node_t *bst_t;

bst_t bst_empty(void) {
    bst_t bst = NULL;
    return bst;
}

bst_t bst_destroy(bst_t bst) {
    stack_t stack = stack_empty();
    bst_t aux;
    while (!stack_is_empty(stack) || bst != NULL) {
        if (bst != NULL) {
            stack = stack_push(stack, bst);
            bst = bst->left;
        } else {
            bst = stack_top(stack);
            stack = stack_pop(stack);
            bst->pair = pair_destroy(bst->pair);
            aux = bst->right;
            free(bst);
            bst = aux;
        }
    }
    stack = stack_destroy(stack);
    return bst;
}

unsigned int bst_length(bst_t bst) {
    unsigned int length = 0;
    stack_t stack = stack_empty();
    bst_t aux = bst;
    while (!stack_is_empty(stack) || aux != NULL) {
        if (aux != NULL) {
            length++;
            if (aux->right != NULL) {
                stack = stack_push(stack, aux->right);
            }
            aux = aux->left;
        } else {
            aux = stack_top(stack);
            stack = stack_pop(stack);
        }
    }
    stack = stack_destroy(stack);
    return length;
}

bool bst_is_equal(bst_t bst, bst_t other) {
    stack_t stack_bst = stack_empty();
    stack_t stack_other = stack_empty();
    bool result = true;
    bst_t aux_bst, aux_other;
    aux_bst = bst;
    aux_other = other;
    if (bst_length(aux_bst) == bst_length(aux_other)) {
        while (!stack_is_empty(stack_bst) ||
               (aux_bst != NULL && aux_other != NULL)) {

            if (aux_bst != NULL && aux_other != NULL) {
                stack_bst = stack_push(stack_bst, aux_bst);
                stack_other = stack_push(stack_other, aux_other);
                aux_bst = aux_bst->left;
                aux_other = aux_other->left;
            } else {
                aux_bst = stack_top(stack_bst);
                aux_other = stack_top(stack_other);
                stack_bst = stack_pop(stack_bst);
                stack_other = stack_pop(stack_other);
                result = result &&
                         pair_is_equal(aux_bst->pair, aux_other->pair);
                aux_bst = aux_bst->right;
                aux_other = aux_other->right;
            }
        }
    } else
        result = false;
    stack_bst = stack_destroy(stack_bst);
    stack_other = stack_destroy(stack_other);
    return result;
}

word_t bst_search(bst_t bst, word_t word) {
    word_t result = NULL;
    bst_t tmp = bst;

    while (tmp != NULL && (word_compare(word, pair_fst(tmp->pair)) != 0)) {
        if (word_compare(word, pair_fst(tmp->pair)) < 0)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    if (tmp != NULL) result = pair_snd(tmp->pair);

    return result;
}

bst_t bst_add(bst_t bst, word_t word1, word_t word2) {
    unsigned int prev_length = bst_length(bst);

    bst_t add = calloc(1,sizeof(struct _tree_node_t));

    add->pair = pair_from_word(word1, word2);
    add->right = NULL;
    add->left = NULL;

    bst_t prevtmp = NULL;
    bst_t tmp = bst;

    if (bst != NULL) {
        while (tmp != NULL) {
            if (word_compare(word1, pair_fst(tmp->pair)) < 0) {
                prevtmp = tmp;
                tmp = tmp->left;
            } else {
                prevtmp = tmp;
                tmp = tmp->right;
            }
        }

        if (word_compare(word1, pair_fst(prevtmp->pair)) < 0) prevtmp->left = add;
        else prevtmp->right = add;

    } else bst = add;

    return bst;
}

pair_t max_pair(bst_t bst) {
    assert(bst != NULL);

    pair_t pair = NULL;
    bst_t tmp = bst;
    while (tmp->right != NULL) {
        tmp = tmp->right;
    }
    pair = pair_copy(tmp->pair);
    return pair;
}

bst_t bst_remove_max(bst_t bst) {
    if (bst != NULL) {
        bst_t tmp = bst;
        while (tmp->right != NULL) {
            tmp = tmp->right;
        }
        bst_t aux_left = bst->left;
        bst->pair = pair_destroy(bst->pair);
        free(bst);
        bst = aux_left;
    }
    return (bst);
}

bst_t bst_remove(bst_t bst, word_t word) {
    bool flag = false;
    unsigned int prev_length = bst_length(bst);
    bst_t prev_tmp = NULL;
    bst_t tmp = bst;

    while (tmp != NULL && !flag) {
        if (word_compare(word, pair_fst(tmp->pair)) < 0) {
            prev_tmp = tmp;
            tmp = tmp->left;
        } else if (word_compare(word, pair_fst(tmp->pair)) > 0) {
            prev_tmp = tmp;
            tmp = tmp->right;
        } else
            flag = true;
    }

    if (flag && prev_tmp != NULL) {
        if (tmp->left == NULL) {
            bst_t aux_right = tmp->right;
            tmp->pair = pair_destroy(tmp->pair);
            free(tmp);
            prev_tmp->right = aux_right;
        } else {
            pair_t pair = max_pair(tmp->left);
            tmp->pair = pair_destroy(tmp->pair);
            tmp->pair = pair;
            tmp->left = bst_remove_max(tmp->left);
        }
    } else {
        bst->pair = pair_destroy(bst->pair);
        free(bst);
        bst = NULL;
    }

    if (flag) {
        assert(prev_length - 1 == bst_length(bst));
    } else {
        assert(prev_length == bst_length(bst));
    }
    return (bst);
}

bst_t bst_copy(bst_t bst) {
    stack_t stack = stack_empty();
    bst_t copy = bst_empty();
    bst_t tmp = bst;
    while (!stack_is_empty(stack) || tmp != NULL) {
        if (tmp != NULL) {
            stack = stack_push(stack, tmp);
            tmp = tmp->left;
        } else {
            tmp = stack_top(stack);
            stack = stack_pop(stack);
            copy = bst_add(copy, pair_fst(tmp->pair),
                           pair_snd(tmp->pair));
            tmp = tmp->right;
        }
    }
    stack = stack_destroy(stack);
    return copy;
}

pair_t *bst_to_array(bst_t bst) {
    pair_t *result = malloc(bst_length(bst)*pair_size());
    stack_t stack = stack_empty();
    bst_t current = bst;
    unsigned int i = 0;
    while (!stack_is_empty(stack) || current != NULL) {
        if (current != NULL) {
            stack = stack_push(stack, current);
            current = current->left;
        } else {
            current = stack_top(stack);
            stack = stack_pop(stack);
            result[i] = pair_copy(current->pair);
            ++i;
            current = current->right;
        }
    }
    stack = stack_destroy(stack);
    return result;
}
