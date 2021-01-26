#ifndef FIFO_UINT16_H
#define FIFO_UINT16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fifo_index.h"
#include <stdint.h>

typedef struct xFifo_uint16_array_t {
    fifo_index_info_t fifoState;
    uint16_t *array;
    bool initDone;
} Fifo_uint16_array_t;

bool fifo_uint16_reset (Fifo_uint16_array_t *const instance);
bool fifo_uint16_init (Fifo_uint16_array_t *const instance, uint16_t capacity, uint16_t *const inArray);
bool fifo_uint16_push (Fifo_uint16_array_t *const instance, uint16_t inChar);
bool fifo_uint16_pull (Fifo_uint16_array_t *const instance, uint16_t *const outChar);
bool fifo_uint16_peek (Fifo_uint16_array_t *const instance, uint16_t *const outChar);

bool fifo_uint16_push_array (Fifo_uint16_array_t *const instance, uint16_t *const inArr, uint16_t arrLen);
bool fifo_uint16_pull_array (Fifo_uint16_array_t *const instance, uint16_t *const outArr, uint16_t *const outLen);
bool fifo_uint16_peek_array (Fifo_uint16_array_t *const instance, uint16_t *const outArr, uint16_t *const outLen);

bool has_fifo_uint16__valid_data (Fifo_uint16_array_t *const instance);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_UINT16_H */
