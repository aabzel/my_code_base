#include "fifo_char.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

static bool is_char_valid (char inChar);

bool fifo_init (Fifo_array_t* const instance, int capacity, char * const array) {
    bool res = false;
    if ((NULL != instance) && (0 < capacity)) {
        memset (array, 0x00, capacity);
        instance->len = 0;
        instance->nextIndex = 0;
        instance->capacity = capacity;
        instance->array = array;
        instance->initDone = true;
        res = true;
    } else {
        instance->initDone = false;
    }
    return res;
}

bool fifo_reset (Fifo_array_t* const instance) {
    bool res = false;
    if (instance && (0 < instance->capacity)) {
        memset (instance->array, 0x00, instance->capacity);
        instance->len = 0;
        instance->nextIndex = 0;
        res = true;
    }
    return res;
}

bool fifo_push (Fifo_array_t* instance, char inChar) {
    bool res = false;
    if (instance) {
        if (0 < instance->capacity && (true == instance->initDone)) {
            if ((instance->len < instance->capacity)) {
                if (is_char_valid (inChar)) {
                    int index = instance->nextIndex;
                    instance->array [index] = inChar;
                    instance->nextIndex++;
                    if (instance->capacity <= instance->nextIndex) {
                        instance->nextIndex = 0;
                    }
                    instance->len++;
                }
                res = true;
            }
        }
    }
    return res;
}

bool has_fifo_valid_data (Fifo_array_t* const instance) {
    bool res = false;
    if ((NULL != instance) && (0 < instance->capacity) && (0 < instance->len) && (true == instance->initDone)) {
        uint32_t i = 0;
        char ch = 0;
        for (i = 0; i < instance->capacity; i++) {
            ch = instance->array [i];
            if ((0x00 != ch) && (0x20 != ch)) {
                res = true;
                break;
            }
        }
    }
    return res;
}

bool fifo_pull (Fifo_array_t* instance, char *outChar) {
    bool res = false;
    if ((instance) && (true == instance->initDone)) {
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
    if (instance && (true == instance->initDone)) {
        if (0 < instance->capacity) {
            if (0 < instance->len) {
                *outChar = instance->array [instance->lastIndex];
                res = true;
            }
        }
    }
    return res;
}

bool fifo_push_array (Fifo_array_t* instance, char * const inArr, uint16_t arrLen) {
    bool res = true;
#if DEBUG_FIFO
    printf ("\n\r%s [%s] size %d\n\r", __FUNCTION__, inArr, arrLen);
#endif
    if (instance && (0 < arrLen) && (true == instance->initDone)) {
        uint16_t i;
        for (i = 0; i < arrLen; i++) {
            if (res == true) {
                res = fifo_push (instance, inArr [i]);
            }
        }
        printf ("\n\r%s filo len [%d]", __FUNCTION__, instance->len);
    }
    return res;
}

bool fifo_pull_array (Fifo_array_t* instance, char *outArr, uint16_t * const outLen) {
    bool res = true;
    (*outLen) = 0;
    char outChar = 0x00;
    while (1) {
        res = fifo_pull (instance, &outChar);
        if (true == res) {
            outArr [(*outLen)] = outChar;
            (*outLen)++;

        } else {
            break;
        }
    }
    return res;
}

static bool is_char_valid (char inChar) {
    bool res = true;
    if ((0x1B == inChar) || (0x5B == inChar)) { /*Escape [*/
        res = false;
    }
    return res;
}
