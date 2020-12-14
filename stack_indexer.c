#include "stack_indexer.h"

#include <stdlib.h>

bool stack_indexer_init (StackIndexer_t *stack_indexer, uint32_t capacity) {
    bool res = false;
    if (stack_indexer) {
        stack_indexer->capacity = capacity;
        stack_indexer->pos = 0; // index for next insert
        res = true;
    }
    return res;
}

bool stack_indexer_push (StackIndexer_t *stack_indexer) {
    bool res = false;
    if (stack_indexer) {
        if (stack_indexer->pos < stack_indexer->capacity) {
            stack_indexer->pos++;
            res = true;
        }
    }
    return res;
}

bool stack_indexer_pop (StackIndexer_t *stack_indexer) {
    bool res = false;
    if (stack_indexer) {
        if (0 < stack_indexer->pos) {
            stack_indexer->pos--;
            res = true;
        } else {
            printf ("\n Error stack_indexer_pop");
        }
    }
    return res;
}

bool stack_indexer_is_correct (StackIndexer_t *stack_indexer) {
    bool res = false;
    if (stack_indexer) {
        if ((stack_indexer->pos) < (stack_indexer->capacity)) {
            res = true;
        }
    }
    return res;
}

bool stack_indexer_is_full (StackIndexer_t *stack_indexer) {
    bool res = false;
    if (stack_indexer) {
        if (stack_indexer->pos == (stack_indexer->capacity - 1)) {
            res = true;
        }
    }
    return res;
}

bool stack_indexer_reset (StackIndexer_t *stack_indexer) {
    bool res = false;
    if (stack_indexer) {
        stack_indexer->capacity = 0;
        stack_indexer->pos = 0;
        res = true;
    }
    return res;
}
