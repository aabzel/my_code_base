#ifndef FIFO_CHAR_H
#define FIFO_CHAR_H

#include "custom_type.h"

typedef struct xFifo_array_t {
    uint16_t len;
    uint16_t capacity;
    uint16_t nextIndex;
    uint16_t lastIndex;
    char *array;
} Fifo_array_t;

bool fifo_init (Fifo_array_t* instance, int capacity, char *array);
bool fifo_push (Fifo_array_t* instance, char inChar);
bool fifo_pull (Fifo_array_t* instance, char *outChar);
bool fifo_peek (Fifo_array_t* instance, char *outChar);

#endif /* FIFO_CHAR_H */
