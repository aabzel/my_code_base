#include "slidingWindowMid.h"

#include "arrays.h"
#include "algorithms.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
//https://medium.com/@nitishchandra/sliding-window-median-98a6710ab2a0
double* medianSlidingWindow (int* nums, int numsSize, int k, int* returnSize) {
// how many window position exest?
    printf ("\n Size of Array: %d \n", numsSize);
#if DEBUG_WINDOW
    print_curr_array (nums, numsSize);
#endif
    int size;
    double *ptrArray = NULL;
    if (0 < numsSize) {
        if (k <= numsSize) {
            size = numsSize - k + 1;
            ptrArray = (double *) malloc (sizeof(double) * size);
            if (ptrArray) {
                init_double_array (ptrArray, size);
                *returnSize = size;
                bool res = false;
                BinaryHeap_t minBinHeap;
                BinaryHeap_t maxBinHeap;
                res = bin_heap_init (&minBinHeap, k);
                if (true == res) {
                    res = bin_heap_init (&maxBinHeap, k);
                }

                if (true == res) {
                    /*minHeap.len > maxheap.len by one*/
                    /*load min heap*/
                    int i = 0;
                    for (i = 0; i < k; i++) {
                        res = heap_insert_val (&maxBinHeap, true, nums [i]);
                    }
                    /*load max heap     k=4: maxHeap:2
                     * k=5: maxHeap:2
                     * k=7: maxHeap:3
                     * */
                    for (i = 0; i < ((k / 2)); i++) {
                        int minVal;
                        minVal = heap_pop (&maxBinHeap, true);
                        res = heap_insert_val (&minBinHeap, false, minVal);
                    }
                    int j = k;
                    for (j = k; j < numsSize; j++) {
                        if (1 == k) {
                            ptrArray [j - k] = nums [j - k];
                        } else {
                            if (k & 1) {
                                ptrArray [j - k] = heap_peek (&maxBinHeap);
                            } else {
                                ptrArray [j - k] = (((double) heap_peek (&maxBinHeap)) + ((double) heap_peek (&minBinHeap))) / 2.0f;
                            }
                            res = insert_val_to_2_heaps (&maxBinHeap, &minBinHeap, nums [j], nums [j - k], k, &nums [j - k]);
                            if (false == res) {
                                bin_heap_deinit (&minBinHeap);
                                bin_heap_deinit (&maxBinHeap);
                                return ptrArray;
                            }
                        }
                    }
                    if (1 != k) {
                        if ((k & 1)) {
                            ptrArray [j - k] = heap_peek (&maxBinHeap);
                        } else {
                            ptrArray [j - k] = (((double) heap_peek (&maxBinHeap)) + ((double) heap_peek (&minBinHeap))) / 2.0f;
                        }
                    } else {
                        ptrArray [j - k] = nums [j - k];
                    }
                    bin_heap_deinit (&minBinHeap);
                    bin_heap_deinit (&maxBinHeap);
                }
            } else {
                printf ("\n Unable to malloc %u byte", (unsigned int) sizeof(double) * size);
            }
        }
    }
    return ptrArray;
}

double calc_median (int * const inArr, int sizeOfArr) {
    double median = 0.0;
    if (inArr) {
        int *localArr = memdup (inArr, sizeOfArr * sizeof(int));
        if (localArr) {
            if (is_odd (sizeOfArr)) {
                median = (double) qselect (localArr, sizeOfArr, sizeOfArr / 2);
            } else {
                int val1 = qselect (localArr, sizeOfArr, (sizeOfArr / 2) - 1);
                int val2 = qselect (localArr, sizeOfArr, sizeOfArr / 2);
                median = avrage_two (val1, val2);
            }
            free (localArr);
        } else {
            printf ("Unable to alloc %d byte", 4 * sizeOfArr);
        }
    }
    return median;
}

bool insert_val_to_2_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t * minBinHeap, int newVal, int oldVal, int sizeOfWind, int *curWinArr) {
    bool res = false;
    (void) curWinArr;
#if DEBUG_INSERT
    printf ("\n\n ");
    print_curr_array (curWinArr + 1, sizeOfWind);
    printf ("\n oldVal: [%d] newVal: [%d] ", oldVal, newVal);
    bin_heap_print (minBinHeap, false);
    bin_heap_print (maxBinHeap, true);
#endif

    res = remove_old_val_from_bin_heaps (maxBinHeap, minBinHeap, oldVal);
    if (false == res) {
        printf ("\n heaps remove error!\n");
        return res;
    }
    res = insert_new_val_to_bin_heaps (maxBinHeap, minBinHeap, newVal);
    if (false == res) {
        printf ("\n to heaps insert error!\n");
        return res;
    }
    if ((maxBinHeap->length + minBinHeap->length) != sizeOfWind) {
        printf ("\n Window error!\n");
        printf ("\n maxBinHeap->length %d \n", maxBinHeap->length);
        printf ("\n minBinHeap->length %d \n", minBinHeap->length);
        printf ("\n Window error!\n");
    } else {
        int emigratingValue;
        if (sizeOfWind & 1) {
            /*maxHeap.len- minHeap.len =1*/

            if (1 < (maxBinHeap->length - minBinHeap->length)) {
                emigratingValue = heap_pop (maxBinHeap, true);
                heap_insert_val (minBinHeap, false, emigratingValue);
            } else {
                if (-1 < (minBinHeap->length - maxBinHeap->length)) {
                    emigratingValue = heap_pop (minBinHeap, false);
                    heap_insert_val (maxBinHeap, true, emigratingValue);
                } else {
#if DEBUG
                            printf ("\n heap size invariant fine\n");
#endif
                }
            }
        } else {
            /*maxHeap.len- minHeap.len =0*/
            if (0 < (maxBinHeap->length - minBinHeap->length)) {
                emigratingValue = heap_pop (maxBinHeap, true);
                heap_insert_val (minBinHeap, false, emigratingValue);
            } else {
                if (0 < (minBinHeap->length - maxBinHeap->length)) {
                    emigratingValue = heap_pop (minBinHeap, false);
                    heap_insert_val (maxBinHeap, true, emigratingValue);
                } else {
                    printf ("\n heap size invariant fine\n");
                }
            }
        }
    }

#if DEBUG_INSERT
    printf ("\n heap_peek (maxBinHeap): [%d] heap_peek (minBinHeap): [%d] ", heap_peek (maxBinHeap), heap_peek (minBinHeap));
#endif
    return res;
}

bool remove_old_val_from_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int oldVal) {
    bool res = false;

    if (!is_empty_heap (maxBinHeap)) {
        if (oldVal < heap_peek (maxBinHeap)) {
            res = bin_heap_remove_val (maxBinHeap, true, oldVal);
            // transfer val from min to max heap
            return res;
        }
    }

    if (!is_empty_heap (minBinHeap)) {
        if (heap_peek (minBinHeap) < oldVal) {
            res = bin_heap_remove_val (minBinHeap, false, oldVal);
            // transfer val from max to min heap
            return res;
        }
    }

    //if (!is_empty_heap (maxBinHeap) && !is_empty_heap (minBinHeap)) {
    if ((oldVal != heap_peek (maxBinHeap)) && (oldVal == heap_peek (minBinHeap))) {
        heap_pop (minBinHeap, false);
        return true;
    } else if ((oldVal == heap_peek (maxBinHeap)) && (oldVal != heap_peek (minBinHeap))) {
        int val = heap_pop (maxBinHeap, true);
        if (val != oldVal) {
            printf ("\nunidentified error\n");
        }
        return true;
    } else if ((oldVal == heap_peek (maxBinHeap)) && (oldVal == heap_peek (minBinHeap))) {
        if (minBinHeap->length < maxBinHeap->length) {
            heap_pop (maxBinHeap, true);
        } else {
            heap_pop (minBinHeap, false);
        }
        return true;
    }
    //}

    return false;
}

// newVal:1  heap_peek (maxBinHeap) 3
bool insert_new_val_to_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int newVal) {
#if DEBUG_INSERT
    printf ("\n newVal [%d] ", newVal);
    printf ("\n heap_peek (maxBinHeap) [%d] ", heap_peek (maxBinHeap));
    printf (" heap_peek (minBinHeap) [%d] ", heap_peek (minBinHeap));
#endif
    bool res = false;

    if (!is_empty_heap (minBinHeap) && !is_empty_heap (maxBinHeap)) {
        if (heap_peek (minBinHeap) <= newVal) {
            res = heap_insert_val (minBinHeap, false, newVal);
        } else if (newVal <= heap_peek (maxBinHeap)) {
            res = heap_insert_val (maxBinHeap, true, newVal);
        } else {
            /*heap_peek(maxBinHeap)<newVal<heap_peek(minBinHeap)*/
            if (maxBinHeap->length < minBinHeap->length) {
                res = heap_insert_val (maxBinHeap, true, newVal);
            } else {
                res = heap_insert_val (minBinHeap, false, newVal);
            }
        }
    } else if (is_empty_heap (minBinHeap) && !is_empty_heap (maxBinHeap)) {
        res = heap_insert_val (maxBinHeap, true, newVal);
    } else if (is_empty_heap (maxBinHeap) && !is_empty_heap (minBinHeap)) {
        res = heap_insert_val (minBinHeap, false, newVal);
    } else {
        printf ("incredible error");
    }

    return res;
}

/* Given an unsorted list of numbers, how do we find the median element? */
/*How to find the kth(N/2) largest element in an unsorted array of length n in O(n)?*/

/*O(logN)*/
double calc_median_naiv (int * const inArr, int sizeOfArr) {
    double median = 0.0;
    if (inArr) {
        int *localArr = memdup (inArr, sizeOfArr * sizeof(int));
        if (localArr) {
            qsort (localArr, sizeOfArr, sizeof(int), cmp_int);
            if (is_odd (sizeOfArr)) {
                median = localArr [((int) sizeOfArr / 2)];
            } else {
                median = avrage_two (localArr [sizeOfArr / 2 - 1], localArr [sizeOfArr / 2]);
                //median = calc_average (&localArr [sizeOfArr / 2 - 1], 2);
            }
            free (localArr);
        } else {
            printf ("Unable to alloc %d byte", 4 * sizeOfArr);
        }
    }
    return median;
}

double* medianSlidingWindowArr (int* nums, int numsSize, int k, int* returnSize) {
// how many window position exest?
    int size = numsSize - k + 1;
    double *ptrArray = (double *) malloc (sizeof(double) * size);
    if (ptrArray) {
        *returnSize = size;
        for (int j = 0; j < size; j++) {
            ptrArray [j] = calc_median (&nums [j], k);
        }
    } else {
        printf ("Unable to malloc %u byte", (unsigned int) sizeof(double) * size);
    }
    return ptrArray;
}

