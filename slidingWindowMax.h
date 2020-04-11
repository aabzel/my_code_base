#ifndef SLIDING_WINDOW_MAXIMUM_H
#define SLIDING_WINDOW_MAXIMUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bin_heap_array.h"
#include "custom_type.h"

#define DEBUG_MAXSLIDINGWINDOW 0
#define DEBUG_HEAP_MAX_UPDATE 0

int* maxSlidingWindow (int* nums, int numsSize, int k, int* returnSize);
bool update_max_heap (BinaryHeap_t *maxBinHeap, int newVal, int oldVal, int sizeOfWind) ;
 
#ifdef __cplusplus
}
#endif

#endif /* SLIDING_WINDOW_MAXIMUM_H */
