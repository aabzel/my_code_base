#include "algorithms.h"

#include "arrays.h"
#include "float_utils.h"
#include "linked_list.h"
#include "permutations.h"
#include "str_ops.h"
#include "utils.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t average_quick (uint32_t a, uint32_t b) {
    uint32_t res;
    res = (a | b) - ((a ^ b) >> 1);
    return res;
}

uint32_t average_slow (uint32_t a, uint32_t b) {
    uint32_t res;
    uint64_t temp = a + b;
    temp = temp >> 1;
    res = (uint32_t)temp;
    return res;
}

int sum_digits (int val) {
    int t, sum = 0, remainder;
    t = val;
    while (t != 0) {
        remainder = t % 10;
        sum = sum + remainder;
        t = t / 10;
    }
    return sum;
}

void print_permut_terms (int *in_current_array, int in_curr_arr_size, int pos, int *alf, int alf_size, int total_num,
                         int sum, int *syllables) {
    if (in_curr_arr_size == total_num) {
        int arr_sum = sum_arr ((uint32_t *)in_current_array, in_curr_arr_size);
        if (sum == arr_sum) {
            printf ("\n");
            print_curr_array (in_current_array, in_curr_arr_size);
            memcpy (syllables, in_current_array, sizeof (int) * in_curr_arr_size);
        }
        free (in_current_array);
        in_current_array = NULL;
    }

    if (pos < total_num) {
        for (int i = 0; i < alf_size; i++) {
            int *currentArray = add_val_to_end_array (in_current_array, in_curr_arr_size, alf[i]);
            if (NULL != currentArray) {
                print_permut_terms (currentArray, in_curr_arr_size + 1, pos + 1, alf, alf_size, total_num, sum,
                                    syllables);
            } else {
                printf ("\nUnable to alloc memory");
            }
        }
    }
}

void print_terms (int total_num, int *alf, int alf_size, int sum, int *syllables) {
    printf ("\n");
    print_permut_terms (NULL, 0, 0, alf, alf_size, total_num, sum, syllables);
}

bool is_in_range (int val, int lowBound, int upBound) {
    bool res = false;
    if (lowBound <= upBound) {
        if (lowBound <= val) {
            if (val <= upBound) {
                res = true;
            }
        }
    } else {
        printf ("\n%s %d %d %d\n", __FUNCTION__, val, lowBound, upBound);
    }
    return res;
}

uint32_t factorial (uint32_t n) {
    uint32_t factor = 1;
    uint32_t i = 0;
    if (0 < n) {
        for (i = n; 0 < i; i--) {
            factor *= i;
        }
    } else {
        factor = 1;
    }
    return factor;
}

#if 0
bool is_floats_equal (float valA, float valB) {
    return is_float_equal (valA, valB, (float) F_EPSILON);
}
#endif

/*
 *
 */
bool is_float_equal (float a__fife, float b__fife, float epsilon__fife) {
    bool retval__fife;
    if (fabsf (a__fife - b__fife) <= fmaxf (fabsf (epsilon__fife * b__fife), fabsf (epsilon__fife * a__fife))) {
        retval__fife = true;
    } else {
        retval__fife = false;
    }
    return retval__fife;
}

int max_int (int val1, int val2) {
    int outVal = val1;
    if (val1 < val2) {
        outVal = val2;
    }
    return outVal;
}

int min_int (int val1, int val2) {
    int outVal = val2;
    if (val1 < val2) {
        outVal = val1;
    }
    return outVal;
}

float minf (float val1, float val2) {
    float outVal = val2;
    if (val1 < val2) {
        outVal = val1;
    }
    return outVal;
}

int min3 (int val1, int val2, int val3) {
    int outVal = 0;
    outVal = min_int (val1, val2);
    outVal = min_int (outVal, val3);
    return outVal;
}

int qselect (int *v, int len, int k) {
#define SWAP(a, b)                                                                                                     \
    {                                                                                                                  \
        tmp = v[a];                                                                                                    \
        v[a] = v[b];                                                                                                   \
        v[b] = tmp;                                                                                                    \
    }
    int i, st, tmp;

    for (st = i = 0; i < len - 1; i++) {
        if (v[i] > v[len - 1])
            continue;
        SWAP (i, st);
        st++;
    }

    SWAP (len - 1, st);

    return k == st ? v[st] : st > k ? qselect (v, st, k) : qselect (v + st, len - st, k - st);
}

float min3f (float val1, float val2, float val3) {
    float outVal = 0.0f;
    outVal = minf (val1, val2);
    outVal = minf (outVal, val3);
    return outVal;
}

/* Function to swap values at two pointers */
void swap_char (char *const x, char *const y) {
    if ((x != y) && (*x != *y)) {
        char temp;
        temp = *x;
        *x = *y;
        *y = temp;
    } else {
        // printf ("The same element\n");
    }
}

bool swap_int (int *const x, int *const y) {
    bool res = false;
    if (x != y) {
        int temp;
        temp = *x;
        *x = *y;
        *y = temp;
        res = true;
    }
    return res;
}
#if 0
bool is_power_of_two (int x) { return ((0 < x) && (0 == (x & (x - 1)))); }
#endif

typedef struct xPox_t {
    int x;
    int y;
} xPox_t;

#define USE_PRINT_LT 0

// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int (const void *p1, const void *p2) {
    int x = *(int *)p1; // добываем из указателя значение по этому указателю
    int y = *(int *)p2; // добываем из указателя значение по этому указателю
    return x - y;
}

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition (int *arr, int l, int r) {
    int x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap_int (&arr[i], &arr[j]);
            i++;
        }
    }
    swap_int (&arr[i], &arr[r]);
    return i;
}

short compare (int leftVal, int rightVal) {
    if (rightVal < leftVal)
        return 1;
    else if (leftVal < rightVal)
        return -1;
    return 0;
}

int update_max (int curMax, int newVal) {
    int newMax = 0;
    if (curMax < newVal) {
        newMax = newVal;
    } else {
        newMax = curMax;
    }
    return newMax;
}
