#ifndef FIFO_CHAR_H
#define FIFO_CHAR_H

#include "custom_type.h"

typedef struct xFifo_array_t {
    uint16_t len;
    uint16_t capacity;
    uint16_t nextIndex;
    uint16_t lastIndex;
    char *array;
    bool initDone;
} Fifo_array_t;

bool fifo_reset (Fifo_array_t* const instance);
bool fifo_init (Fifo_array_t* const instance, int capacity, char * const array);
bool fifo_push (Fifo_array_t* instance, char inChar);
bool fifo_pull (Fifo_array_t* instance, char *outChar);
bool fifo_peek (Fifo_array_t* instance, char *outChar);
bool has_fifo_valid_data (Fifo_array_t* const instance);

bool fifo_push_array (Fifo_array_t* instance, char *const inArr, uint16_t arrLen);
bool fifo_pull_array (Fifo_array_t* instance, char *outArr, uint16_t *outLen);
bool fifo_peek_array (Fifo_array_t* instance, char *outArr, uint16_t *outLen);

#endif /* FIFO_CHAR_H */
