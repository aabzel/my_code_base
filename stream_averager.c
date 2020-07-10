#include "stream_averager.h"

#include <string.h>

bool init_averager (averager_t * const instance, uint16_t capacity, uint16_t * const inArray) {
    bool res = false;
    if (NULL != instance) {
        instance->curSumm = 0U;
        res = fifo_uint16_init (&(instance->fifou16), capacity, inArray);
    }
    return res;
}
bool deinit_averager (averager_t * const instance) {
    bool res = false;
    if (NULL != instance) {
        instance->curSumm = 0u;
        res = fifo_uint16_reset (&(instance->fifou16));
    }
    return res;
}

bool put_averager (averager_t * const instance, uint16_t newVal, uint16_t * const outAverageVal) {
    bool res = false;
    uint16_t averageVal = 0U;
    uint16_t oldVal = 0U;
    if (NULL != instance) {
        instance->curSumm += newVal;
        if (instance->fifou16.fifoState.count < instance->fifou16.fifoState.size) {
            res = fifo_uint16_push (&(instance->fifou16), newVal);
        } else {
            res = fifo_uint16_pull (&(instance->fifou16), &oldVal);
            if (true == res) {
                instance->curSumm -= oldVal;
                res = fifo_uint16_push (&(instance->fifou16), newVal);
            }
        }
        averageVal = instance->curSumm / instance->fifou16.fifoState.count;
        if (NULL != outAverageVal) {
            (*outAverageVal) = averageVal;
        }
    }
    return res;
}

bool get_averager (averager_t * const instance, uint16_t * const outAverageVal) {
    bool res = false;
    if (NULL != instance) {
        if (NULL != outAverageVal) {
            (*outAverageVal) = instance->curSumm / instance->fifou16.fifoState.count;
        }

    }
    return res;
}

