#include "slidingWindowMax.h"

#include "arrays.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *maxSlidingWindow (int *nums, int numsSize, int k, int *returnSize) {
// how many window position exest?
#if DEBUG_MAXSLIDINGWINDOW
    printf ("\n Size of Array: %d \n", numsSize);
    print_curr_array (nums, numsSize);
#endif
    int size;
    int *ptrArray = NULL;
    if ((0 < numsSize) && (k <= numsSize)) {
        size = numsSize - k + 1;
        ptrArray = (int *)malloc (sizeof (int) * size);
        if (ptrArray) {
            memset (ptrArray, 0x00, sizeof (int) * size);
            *returnSize = size;
            bool res = false;
            BinaryHeap_t maxBinHeap;
            res = bin_heap_init (&maxBinHeap, k);
            if (false == res) {
                printf ("\n bin_heap_init error");
                return ptrArray;
            }
            int i = 0;
            for (i = 0; i < k; i++) {
                res = heap_insert_val (&maxBinHeap, true, nums[i]);
            }
            for (i = k; i < numsSize; i++) {
                ptrArray[i - k] = heap_peek (&maxBinHeap);
                res = update_max_heap (&maxBinHeap, nums[i], nums[i - k], k);
                if (false == res) {
                    printf ("\n Unable update_max_heap");
                    return ptrArray;
                }
            }
            ptrArray[i - k] = heap_peek (&maxBinHeap);
            bin_heap_deinit (&maxBinHeap);

        } else {
            printf ("\n Unable to malloc %u byte", (unsigned int)sizeof (int) * size);
        }
    }
    return ptrArray;
}

bool update_max_heap (BinaryHeap_t *maxBinHeap, int newVal, int oldVal, int sizeOfWind) {
    bool res = true;
#if DEBUG_HEAP_MAX_UPDATE
    printf ("\n oldVal: [%d] newVal: [%d] ", oldVal, newVal);
    printf ("\n old heap ");
    bin_heap_print (maxBinHeap, true);
#endif
    if (maxBinHeap->length != sizeOfWind) {
        printf ("\n size error window %d bin heap %d", sizeOfWind, maxBinHeap->length);
        res = false;
        return res;
    }

    res = bin_heap_remove_val (maxBinHeap, true, oldVal);
    if (false == res) {
        printf ("\n Unable bin_heap_remove_val");
        return res;
    }
    res &= heap_insert_val (maxBinHeap, true, newVal);
    if (false == res) {
        printf ("\n Unable heap_insert_val");
        return res;
    }
#if DEBUG_HEAP_MAX_UPDATE
    printf ("\n New heap ");
    bin_heap_print (maxBinHeap, true);
#endif
    if (maxBinHeap->length != sizeOfWind) {
        printf ("\n size error window %d bin heap %d", sizeOfWind, maxBinHeap->length);
        res = false;
        return res;
    }

    return res;
}
