#ifndef STACK_NUM_H
#define STACK_NUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stack_indexer.h"

typedef struct xStack_t {
    StackIndexer_t index;
    int *data_ptr;
    bool is_init;
} numStack_t;

bool stack_init (numStack_t **stack_instance, int des_capacity);
bool stack_realloc (numStack_t *stack_instance, int new_des_capacity);

bool stack_push (numStack_t *stack_instance, int data);
bool stack_pop (numStack_t *stack_instance, int *out_data);
bool stack_peek (numStack_t *stack_instance, int *out_data);
void stack_free (numStack_t *stack_instance);
void stack_debug (numStack_t *stack_instance);
#ifdef __cplusplus
}
#endif

#endif /*STACK_NUM_H*/
