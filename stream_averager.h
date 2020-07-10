#ifndef STREAM_AVERAGER_H
#define STREAM_AVERAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"
#include "fifo_uint16.h"

typedef struct xAaverager_t {
    Fifo_uint16_array_t fifou16;
    uint64_t curSumm;
}averager_t;

bool init_averager (averager_t * const instance, uint16_t capacity, uint16_t * const inArray);
bool deinit_averager (averager_t * const instance);
bool put_averager (averager_t * const instance, uint16_t newVal, uint16_t * const outAverageVal);
bool get_averager (averager_t * const instance,uint16_t * const outAverageVal);

#ifdef __cplusplus
}
#endif

#endif /* STREAM_AVERAGER_H */
