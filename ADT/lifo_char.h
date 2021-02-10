#ifndef LIFO_CHAR_H
#define LIFO_CHAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct xLifo_index_t {
    uint16_t len;
    uint16_t capacity;
} Lifo_index_t;

typedef struct xLifo_array_t {
    Lifo_index_t lifoStat;
    char *array;
    bool initDone;
} Lifo_array_t;

bool init_lifo_index (Lifo_index_t *const lifoIndex, uint16_t desCapacity);
bool lifo_index_valid (const Lifo_index_t *const lifoIndex);

bool lifo_init (Lifo_array_t *const instance, uint16_t capacity, char *const array);
bool lifo_reset (Lifo_array_t *const instance);
bool lifo_push (Lifo_array_t *const instance, char inChar);
bool lifo_pull (Lifo_array_t *const instance, char *const outChar);
bool lifo_peek (Lifo_array_t *const instance, char *const outChar);
bool has_lifo_valid_data (Lifo_array_t *const instance);

bool lifo_push_array (Lifo_array_t *const instance, char *const inArr, uint16_t arrLen);
bool lifo_pull_array (Lifo_array_t *const instance, char *const outArr, uint16_t *const outLen);
bool lifo_peek_array (Lifo_array_t *const instance, char *const outArr, uint16_t *const outLen);

#ifdef __cplusplus
}
#endif

#endif /* LIFO_CHAR_H */
