#ifndef SLIDING_WINDOW_MEDIAN_H
#define SLIDING_WINDOW_MEDIAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bin_heap_array.h"
#include "custom_type.h"

double *medianSlidingWindow (int *nums, int numsSize, int k, int *returnSize);
double *medianSlidingWindowArr (int *nums, int numsSize, int k, int *returnSize);
bool insert_val_to_2_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int newVal, int oldVal, int sizeOfWind,
                            int *curWinArr);
bool remove_old_val_from_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int oldVal);
bool insert_new_val_to_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int newVal);

#ifdef __cplusplus
}
#endif

#endif /* SLIDING_WINDOW_MEDIAN_H */
