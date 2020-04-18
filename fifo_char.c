#include "fifo_char.h"

bool fifo_init (Fifo_array_t* instance, int capacity, char *array) {
    bool res = false;
    instance->len = 0;
    instance->nextIndex = 0;
    instance->capacity = capacity;
    instance->array = array;
    return res;
}

bool fifo_push (Fifo_array_t* instance, char inChar) {
    bool res = false;
    if (instance) {
        if (0 < instance->capacity) {
            if (instance->len < instance->capacity) {
                int index = instance->nextIndex;
                instance->array [index] = inChar;
                instance->nextIndex++;
                if (instance->capacity <= instance->nextIndex) {
                    instance->nextIndex = 0;
                }
                instance->len++;
                res = true;
            }
        }
    }
    return res;
}

bool fifo_pull (Fifo_array_t* instance, char *outChar) {
    bool res = false;
    if (instance) {
        if (0 < instance->len) {
            if (instance->len <= instance->capacity) {
                int index = instance->lastIndex;
                *outChar = instance->array [index];
                instance->array [index] = 0x00;
                instance->lastIndex++;
                if (instance->capacity <= instance->lastIndex) {
                    instance->lastIndex = 0;
                }
                instance->len--;
                res = true;
            }
        }
    }
    return res;
}

bool fifo_peek (Fifo_array_t* instance, char *outChar) {
    bool res = false;
    if (instance) {
        if (0 < instance->capacity) {
            if (0 < instance->len) {
                *outChar = instance->array [instance->lastIndex];
                res = true;
            }
        }
    }
    return res;
}
