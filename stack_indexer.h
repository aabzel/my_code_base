#ifndef STACK_INDEXER_H
#define STACK_INDEXER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct xStackIndexer_t {
    uint32_t capacity;
    int32_t pos; // index for next insert
} StackIndexer_t;

bool stack_indexer_init (StackIndexer_t *StackIndexer, uint32_t capacity);
bool stack_indexer_pop (StackIndexer_t *StackIndexer);
bool stack_indexer_is_correct (StackIndexer_t *StackIndexer);
bool stack_indexer_is_full (StackIndexer_t *StackIndexer);
bool stack_indexer_reset (StackIndexer_t *StackIndexer);

#ifdef __cplusplus
}
#endif

#endif /*STACK_INDEXER_H*/
