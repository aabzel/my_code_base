#ifndef EVALUATE_CACHE_H
#define EVALUATE_CACHE_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

// https://stackoverflow.com/questions/21299488/cache-size-estimation-on-your-system

// 32kByte Cache
// 76800 stall
// 256 kByte L2
// 8 Mbyte L3
// 16G RAM

// probably not be very accurate on Windows/Linux because services and other
// processes can mess with caches during runtime.

#define K_BYTE (1024)
#define M_BYTE (1024UL * 1024UL)
#define G_BYTE (1024UL * 1024UL * 1024UL)

#define MEM_SIZE_BYTE (G_BYTE)
#define SIZE_STEP (8 * K_BYTE)
//#define SIZE_STEP (10)

bool evaluate_cache (uint64_t byte_max);

double measure_byte_assess_time_slow_dyn (uint64_t byte);
double measure_byte_assess_time_fast_dyn (uint64_t byte);

#endif /*EVALUATE_CACHE_H*/
