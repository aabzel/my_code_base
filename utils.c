#include "utils.h"

#include "algorithms.h"
#include "arrays.h"
#include "bin_heap_array.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

char pemutationFile [100];
char kitFile [100];

void init_file_name (void) {
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf (
        pemutationFile,
        "permutation_%d_%d_%d_%d_%d_%d.txt",
        timeinfo->tm_mday,
        timeinfo->tm_mon + 1,
        timeinfo->tm_year + 1900,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);

    sprintf (
        kitFile,
        "kit_%d_%d_%d_%d_%d_%d.txt",
        timeinfo->tm_mday,
        timeinfo->tm_mon + 1,
        timeinfo->tm_year + 1900,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);

}

char *generate_num_string (int n) {
    char *charStr = NULL;
    charStr = malloc (n + 1);
    for (int i = 0; i < n; i++) {
        charStr [i] = (i) + '0';
    }
    charStr [n] = '\0';
    return charStr;
}

void print_array (int *alphabet, int sizeOfAlphabet, int k) {
    printf ("\nAlphabet size: [%d] lettesRemained [%d] ", sizeOfAlphabet, k);
    printf ("{");
    for (int i = 0; i < sizeOfAlphabet; i++) {
        printf ("%d", alphabet [i]);
    }
    printf ("}");
    printf ("\n");
}

void init_double_array (double * ptrArray, int size) {
    for (int i = 0; i < size; i++) {
        ptrArray [i] = 0.0;
    }
}

void print_array_double (double *alphabet, int sizeOfAlphabet) {

    printf ("\n{ ");
    for (int i = 0; i < sizeOfAlphabet; i++) {
        printf ("%.3f, ", alphabet [i]);
    }
    printf (" }");
    printf ("\n");
}

// Store the formatted string of time in the output
char * format_time_txt (void) {
    static char output [1000];
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    sprintf (
        output,
        "[%d %d %d %d:%d:%d].txt",
        timeinfo->tm_mday,
        timeinfo->tm_mon + 1,
        timeinfo->tm_year + 1900,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);
    return output;
}

/*
 * This function converts an unsigned binary
 * number to reflected binary Gray code.
 *
 * The operator >> is shift right. The operator ^ is exclusive or.
 */
uint32_t bin_to_gray (uint32_t num) {
    return num ^ (num >> 1);
}

/*
 * This function converts a reflected binary
 * Gray code number to a binary number.
 * Each Gray code bit is exclusive-ored with all
 * more significant bits.
 */
unsigned int GrayToBinary (unsigned int num) {
    unsigned int mask = num >> 1;
    while (mask != 0) {
        num = num ^ mask;
        mask = mask >> 1;
    }
    return num;
}

/*
 * A more efficient version for Gray codes 32 bits or fewer
 * through the use of SWAR (SIMD within a register) techniques.
 * It implements a parallel prefix XOR function.  The assignment
 * statements can be in any order.
 *
 * This function can be adapted for longer Gray codes by adding steps.
 * A 4-bit variant changes a binary number (abcd)2 to (abcd)2 ^ (00ab)2,
 * then to (abcd)2 ^ (00ab)2 ^ (0abc)2 ^ (000a)2.
 */
unsigned int GrayToBinary32 (unsigned int num) {
    num = num ^ (num >> 16);
    num = num ^ (num >> 8);
    num = num ^ (num >> 4);
    num = num ^ (num >> 2);
    num = num ^ (num >> 1);
    return num;
}

uint32_t max_val (uint32_t amountofbit) {
    uint32_t val = 0u;
    for (uint32_t i = 0; i < amountofbit; i++) {
        val |= (1 << i);
    }
    return val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode (int n, int* returnSize) {
    uint32_t maxVal = 0u;
    maxVal = max_val (n);
    int *outArr = NULL;
    *returnSize = maxVal + 1;
    outArr = malloc ((maxVal + 1) * sizeof(int));
    if (outArr) {
        for (uint32_t binVal = 0; binVal <= maxVal; binVal++) {
            outArr [binVal] = bin_to_gray (binVal);
        }
    }
    return outArr;
}

uint32_t reverseBits (uint32_t num) {
    uint32_t numOfbit = 4 * 8u;
    uint32_t reverseNum = 0u;
    uint32_t i;
    uint32_t temp;

    for (i = 0u; i < numOfbit; i++) {
        temp = (num & (1 << i));
        if (temp) {
            reverseNum |= (1 << ((numOfbit - 1) - i));
        }
    }
    return reverseNum;
}

uint8_t hamming_weight (uint32_t n) {
    uint8_t sum = 0;
    while (n != 0) {
        printf ("\nn      :%s", uint32_to_bin_str (n));
        printf ("\n n-1   :%s", uint32_to_bin_str (n - 1));
        printf ("\nn&(n-1):%s", uint32_to_bin_str (n & (n - 1)));
        printf ("\n");
        sum++;
        n &= (n - 1);
    }
    return sum;
}

char *uint32_to_bin_str (uint32_t const inVal32bit) {
    static char outBitStr [33] = "";
    int8_t rBit = 0;
    uint8_t cell = 0u;
    uint32_t mask = 0u;
    for (rBit = 31; 0 <= rBit; rBit--) {
        cell = (((uint8_t) 31u) - ((uint8_t) rBit));
        if (cell < sizeof(outBitStr)) {
            mask = (uint32_t) (((uint32_t) 1u) << ((uint32_t) rBit));
            if (0u != (inVal32bit & mask)) {
                outBitStr [cell] = '1';
            } else {
                outBitStr [cell] = '0';
            }
        }
    }
    return outBitStr;
}

int **list_of_arr_to_arr_of_arr (list_node_t * const listOfArrays, int * const amountOfArrays, int** returnColumnSizes) {
    int numElem = list_num_of_elements (listOfArrays);
    int **arrayOfPtr;
    arrayOfPtr = NULL;
    if (0 < numElem) {
        *amountOfArrays = numElem;
        arrayOfPtr = (int **) malloc (numElem * sizeof(int));
        int* columnSizes = malloc (numElem * sizeof(int));
        for (int i = 0; i < numElem; i++) {
            list_node_t *curNode = get_node_by_index (listOfArrays, i);
            if (NULL != curNode) {
                columnSizes [i] = curNode->data.arrSize;
                arrayOfPtr [i] = curNode->data.pArr;
            } else {
                printf ("\n lack of element with ind %d in the list listOfArrays", i);
            }
        }
        *returnColumnSizes = columnSizes;
    }

    return arrayOfPtr;

}

void print_bit_representation (float val) {
    union union_type {
        uint32_t vali;
        float val;
    };
    union union_type cnvt;
    cnvt.val = val;
    printf ("size of %d", (int) sizeof(float));
    printf ("\n %f %d \n%s\n", cnvt.val, cnvt.vali, uint32_to_bin_str (cnvt.vali));
}

void print_mem (uint8_t *memPtr, uint32_t sizeOfAlphabet) {
    printf ("\n");
    uint32_t i;
    for (i = 0; i < sizeOfAlphabet; i++) {
        printf ("%02X", memPtr [i]);
    }
    printf ("\n");
}

long long summ_array (int const* const inArr, int sizeOfArr) {
    long long int sum = 0;
    if (inArr) {
        for (int i = 0; i < sizeOfArr; i++) {
            sum += inArr [i];
        }
    }
    return sum;
}

double avrage_two (int val1, int val2) {
    double avagage = (double) (((double) (((double) val1) + ((double) val2)) / 2.0));
    return avagage;
}

bool is_odd (int val) {
    bool res = false;
    if (val & 1) {
        res = true;
    }
    return res;
}

double calc_average (int const * const inArr, int sizeOfArr) {
    double median = 0.0;
    if (inArr) {
        if (0 < sizeOfArr) {
            double sum = (double) summ_array (inArr, sizeOfArr);
            median = sum / sizeOfArr;
        }
    }
    return median;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
//https://medium.com/@nitishchandra/sliding-window-median-98a6710ab2a0
double* medianSlidingWindow (int* nums, int numsSize, int k, int* returnSize) {
// how many window position exest?

    print_curr_array (nums, numsSize);
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
                        if (k & 1) {
                            ptrArray [j - k] = heap_peek (&maxBinHeap);
                        } else {
                            ptrArray [j - k] = (heap_peek (&maxBinHeap) + heap_peek (&minBinHeap)) / 2.0f;
                        }
                        res = insert_val_to_2_heaps (&maxBinHeap, &minBinHeap, nums [j], nums [j - k], k, &nums [j - k]);
                    }
                    if (k & 1) {
                        ptrArray [j - k] = heap_peek (&maxBinHeap);
                    } else {
                        ptrArray [j - k] = (heap_peek (&maxBinHeap) + heap_peek (&minBinHeap)) / 2.0f;
                    }
                }
            } else {
                printf ("Unable to malloc %u byte", (unsigned int) sizeof(double) * size);
            }
        }
    }
    return ptrArray;
}

#define DEBUG_INSERT 1
bool insert_val_to_2_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t * minBinHeap, int newVal, int oldVal, int sizeOfWind, int *curWinArr) {
    bool res = false;
#if DEBUG_INSERT
    printf ("\n\n ");
    print_curr_array (curWinArr + 1, sizeOfWind);
    printf ("\n oldVal: [%d] newVal: [%d] ", oldVal, newVal);
#endif
    if (0 < maxBinHeap->length && 0 < minBinHeap->length) {
        if (heap_peek (maxBinHeap) <= heap_peek (minBinHeap) || 1) {
            res = remove_old_val_from_bin_heaps (maxBinHeap, minBinHeap, oldVal);
            if (false == res) {
                printf ("\n heaps remove error!\n");
            }
            res = insert_new_val_to_bin_heaps (maxBinHeap, minBinHeap, newVal);
            if (false == res) {
                printf ("\n to heaps insert error!\n");
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
        } else {
            printf ("\nError in heap pair: ");
            printf ("\n heap_peek (maxBinHeap) %d ", heap_peek (maxBinHeap));
            printf ("\n heap_peek (minBinHeap) %d \n", heap_peek (minBinHeap));

        }
    } else {
        printf ("\nError in heap lenght\n");
        printf ("\n maxBinHeap->length %d ", maxBinHeap->length);
        printf ("   minBinHeap->length %d\n", minBinHeap->length);

    }
    printf ("\n heap_peek (maxBinHeap): [%d] heap_peek (minBinHeap): [%d] ", heap_peek (maxBinHeap), heap_peek (minBinHeap));

    return res;
}

bool remove_old_val_from_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int oldVal) {
    bool res = false;
    if (oldVal < heap_peek (maxBinHeap)) {
        res = bin_heap_remove_val (maxBinHeap, true, oldVal);
        // transfer val from min to max heap
        return res;
    }

    if (heap_peek (minBinHeap) < oldVal) {
        res = bin_heap_remove_val (minBinHeap, false, oldVal);
        // transfer val from max to min heap
        return res;
    }

    if ((oldVal != heap_peek (maxBinHeap)) && (oldVal == heap_peek (minBinHeap))) {
        heap_pop (minBinHeap, false);
        return true;
    } else if ((oldVal == heap_peek (maxBinHeap)) && (oldVal != heap_peek (minBinHeap))) {
        heap_pop (maxBinHeap, true);
        return true;
    } else if ((oldVal == heap_peek (maxBinHeap)) && (oldVal == heap_peek (minBinHeap))) {
        if (minBinHeap->length < maxBinHeap->length) {
            heap_pop (maxBinHeap, true);
        } else {
            heap_pop (minBinHeap, false);
        }
        return true;
    }
    return false;
}

// newVal:1  heap_peek (maxBinHeap) 3
bool insert_new_val_to_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int newVal) {
    printf ("\n newVal [%d] ", newVal);
    printf ("\n heap_peek (maxBinHeap) [%d] ", heap_peek (maxBinHeap));
    printf (" heap_peek (minBinHeap) [%d] ", heap_peek (minBinHeap));
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
        res = heap_insert_val (minBinHeap, true, newVal);
    } else {
        printf ("incredible error");
    }

    return res;
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

bool is_double_arr_equal (double *arr1, double *arr2, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        if (!is_floats_equal (arr1 [i], arr2 [i])) {
            return false;
        }
    }
    return true;
}

