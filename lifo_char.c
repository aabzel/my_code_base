#include "lifo_char.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool init_lifo_index (Lifo_index_t *const lifoIndex, uint16_t desCapacity) {
    bool res = false;
    if (NULL != lifoIndex) {
        lifoIndex->len = 0u;
        lifoIndex->capacity = desCapacity;
        res = true;
    }
    return res;
}

bool lifo_index_valid (const Lifo_index_t *const lifoIndex) {
    bool res = false;
    if (NULL != lifoIndex) {
        if (0 < lifoIndex->capacity) {
            if (lifoIndex->len < lifoIndex->capacity) {
                res = true;
            }
        }
    }
    return res;
}

bool lifo_init (Lifo_array_t *const instance, uint16_t capacity, char *const array) {
    bool res = false;
    if (NULL != instance) {
        instance->initDone = false;
        if (NULL != array) {
            memset (array, 0x00, capacity);
            init_lifo_index (&(instance->lifoStat), capacity);
            instance->array = array;
            instance->initDone = true;
        }
    }
    return res;
}

bool lifo_reset (Lifo_array_t *const instance) {
    bool res = false;
    if (instance && (0 < instance->lifoStat.capacity)) {
        memset (instance->array, 0x00, instance->lifoStat.capacity);
        instance->lifoStat.len = 0u;
        res = true;
    }
    return res;
}

bool lifo_push (Lifo_array_t *instance, char inChar) {
    bool res = false;
    if (instance) {
        if ((0u < instance->lifoStat.capacity) && (true == instance->initDone)) {
            if ((instance->lifoStat.len < instance->lifoStat.capacity)) {
                instance->array[instance->lifoStat.len] = inChar;
                instance->lifoStat.len++;
                res = true;
            }
        }
    }
    return res;
}

bool lifo_pull (Lifo_array_t *instance, char *outChar) {
    bool res = false;
    if ((instance) && (true == instance->initDone)) {
        if (0 < instance->lifoStat.len) {
            if (instance->lifoStat.len <= instance->lifoStat.capacity) {
                *outChar = instance->array[instance->lifoStat.len - 1];
                instance->array[instance->lifoStat.len - 1] = 0x00;
                instance->lifoStat.len--;
                res = true;
            }
        }
    }
    return res;
}

bool lifo_peek (Lifo_array_t *const instance, char *const outChar) {
    bool res = false;
    if (instance && (true == instance->initDone)) {
        if (0 < instance->lifoStat.capacity) {
            if (0 < instance->lifoStat.len) {
                *outChar = instance->array[(instance->lifoStat.len - 1)];
                res = true;
            }
        }
    }
    return res;
}

bool lifo_push_array (Lifo_array_t *instance, char *const inArr, uint16_t arrLen) {
    bool res = true;
    if (instance && (0 < arrLen) && (true == instance->initDone)) {
        uint16_t i;
        for (i = 0; i < arrLen; i++) {
            if (res == true) {
                res = lifo_push (instance, inArr[i]);
            }
        }
    } else {
        res = false;
    }
    return res;
}

bool lifo_pull_array (Lifo_array_t *instance, char *const outArr, uint16_t *const outLen) {
    bool res = true;
    if ((NULL != outArr) && (NULL != outLen) && (true == instance->initDone)) {
        bool runLoop = true;
        (*outLen) = 0u;
        while (true == runLoop) {
            if (0u < instance->lifoStat.len) {
                char outChar = (char)0;
                res = lifo_pull (instance, &outChar);
                if (true == res) {
                    outArr[(*outLen)] = outChar;
                    (*outLen)++;
                } else {
                    runLoop = false;
                }
            } else {
                outArr[(*outLen)] = '\0';
                runLoop = false;
                res = true;
            }
        }
    } else {
        res = false;
    }
    return res;
}

bool lifo_peek_array (Lifo_array_t *instance, char *outArr, uint16_t *const outLen) {
    bool res = false;
    if (NULL != instance) {
        if ((NULL != outArr) && (NULL != outLen)) {
            (*outLen) = 0u;
            if (true == instance->initDone) {
                if (0u < instance->lifoStat.len) {
                    int32_t i = 0u;
                    uint16_t run = instance->lifoStat.len - 1;
                    for (i = 0; i < instance->lifoStat.len; i++) {
                        outArr[i] = instance->array[run];
                        run--;
                    }
                    (*outLen) = instance->lifoStat.len;
                    outArr[i] = '\0';
                    res = true;
                }
            }
        }
    }
    return res;
}
