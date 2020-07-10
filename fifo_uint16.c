#include "fifo_uint16.h"

#include <string.h>
#include <stdint.h>

bool fifo_uint16_init (Fifo_uint16_array_t* const instance, uint16_t capacity, uint16_t * const inArray) {
    bool res = false;
    if ((NULL != instance) && (0u < capacity)) {
        (void) memset (inArray, 0x00, 2 * capacity);
        fifo_index_init (&(instance->fifoState), capacity);
        instance->array = inArray;
        instance->initDone = true;
        res = true;
    } else {
        instance->initDone = false;
    }
    return res;
}

bool fifo_uint16_reset (Fifo_uint16_array_t* const instance) {
    bool res = false;
    if ((NULL != instance) && (0u < instance->fifoState.size) && (true == instance->initDone)) {
        (void) memset (instance->array, 0x00, 2 * instance->fifoState.size);
        instance->fifoState.count = 0u;
        instance->fifoState.start = 0u;
        instance->fifoState.end = 0u;
        res = true;
    }
    return res;
}

bool fifo_uint16_push (Fifo_uint16_array_t* instance, uint16_t inChar) {
    bool res = false;
    if (NULL != instance) {

        if ((0u < instance->fifoState.size) && (true == instance->initDone)) {
            if ((instance->fifoState.count < instance->fifoState.size)) {
                instance->array [instance->fifoState.end] = inChar;
                (void) fifo_index_add (&(instance->fifoState));
                res = true;
            }
        }
    }
    return res;
}

bool has_fifo_uint16__valid_data (Fifo_uint16_array_t* const instance) {
    bool res = false;
    if ((NULL != instance) && (true == instance->initDone)) {
        if (0u < instance->fifoState.size) {
            if (0u < instance->fifoState.count) {
                uint32_t i = 0u;
                uint16_t value =  0;
                for (i = 0u; i < instance->fifoState.size; i++) {
                    value = instance->array [i];
                    if ( 0U != value) {
                        res = true;
                        break;
                    }
                }
            }
        }
    }
    return res;
}

bool fifo_uint16_pull (Fifo_uint16_array_t* instance, uint16_t * const outChar) {
    bool res = false;
    if ((NULL != instance) && (true == instance->initDone)) {
        if (0u < instance->fifoState.count) {
            if (instance->fifoState.count <= instance->fifoState.size) {
                *outChar = instance->array [instance->fifoState.start];
                instance->array [instance->fifoState.start] = (char) 0x00;
                (void) fifo_index_get (&(instance->fifoState));
                res = true;
            }
        }
    }
    return res;
}

bool fifo_uint16_peek (Fifo_uint16_array_t* instance, uint16_t * const outChar) {
    bool res = false;
    if ((NULL != instance) && (true == instance->initDone)) {
        if (0u < instance->fifoState.size) {
            if (0u < instance->fifoState.count) {
                *outChar = instance->array [instance->fifoState.start];
                res = true;
            }
        }
    }
    return res;
}

bool fifo_uint16_push_array (Fifo_uint16_array_t* instance, uint16_t * const inArr, uint16_t arrLen) {
    bool res = true;
#if DEBUG_FIFO_CHAR
    rx_printf ("\n\r%s [%s] size %d\n\r", __FUNCTION__, inArr, arrLen);
#endif
    if ((NULL != instance) && (0u < arrLen) && (true == instance->initDone)) {
        uint16_t i;
        for (i = 0u; i < arrLen; i++) {
            if (res == true) {
                res = fifo_uint16_push (instance, inArr [i]);
            }
        }
#if DEBUG_FIFO_CHAR
        rx_printf ("\n\r%s filo len [%d]", __FUNCTION__, instance->fifoState.size);
#endif
    }
    return res;
}

bool fifo_uint16_pull_array (Fifo_uint16_array_t* instance, uint16_t * const outArr, uint16_t * const outLen) {
    bool res = true;
    if ((NULL != outArr) && (NULL != outLen) && (true == instance->initDone)) {
        bool runLoop = true;
        (*outLen) = 0u;
        while (true == runLoop) {
            if (0u < instance->fifoState.count) {
                uint16_t outVal = 0U;
                res = fifo_uint16_pull (instance, &outVal);
                if (true == res) {
                    outArr [(*outLen)] = outVal;
                    (*outLen)++;
                } else {
                    runLoop = false;
                }
            } else {
                runLoop = false;
                res = true;
            }
        }
    } else {
        res = false;
    }
    return res;
}

bool fifo_uint16_peek_array (Fifo_uint16_array_t* instance, uint16_t *outArr, uint16_t * const outLen) {
    bool res = false;
    if (NULL != instance) {
        if ((NULL != outArr) && (NULL != outLen)) {
            (*outLen) = 0u;
            if (true == fifo_index_valid (&(instance->fifoState))) {
                if (true == instance->initDone) {
                    if (0u < instance->fifoState.count) {
                        uint16_t i = 0u;
                        uint16_t run = instance->fifoState.start;
                        for (i = 0; i < instance->fifoState.count; i++) {
                            outArr [i] = instance->array [run];
                            if (run < instance->fifoState.size) {
                                run++;
                            } else {
                                run = 0;
                            }
                        }
                        (*outLen) = instance->fifoState.count;
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}

