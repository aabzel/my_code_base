#ifndef STACK_STR_H
#define STACK_STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stack_indexer.h"

typedef struct xStrStack_t {
    StackIndexer_t index;
    char **data_ptr;
    bool is_init;
} strStack_t;


bool stack_str_init (strStack_t **stack_instance, int des_capacity);
bool stack_str_realloc (strStack_t *stack_instance, int new_des_capacity);

bool stack_str_push (strStack_t *stack_instance, char *in_str);
bool stack_str_pop (strStack_t *stack_instance, char *out_str);
bool stack_str_peek (strStack_t *stack_instance, char *out_str);
void stack_str_free (strStack_t *stack_instance);

bool stack_str_debug (strStack_t *stack_instance);

#ifdef __cplusplus
}
#endif

#endif /*STACK_STR_H*/
