#include "test_algorithms.h"

#include "algorithms.h"
#include "bit_utils.h"
#include "uTests.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool test_bit_utils (void) {
    EXPECT_EQ (MASK_0_BITS, calc_16_mask (0));
    EXPECT_EQ (MASK_1_BITS, calc_16_mask (1));
    EXPECT_EQ (MASK_2_BITS, calc_16_mask (2));
    EXPECT_EQ (MASK_3_BITS, calc_16_mask (3));
    EXPECT_EQ (MASK_4_BITS, calc_16_mask (4));
    EXPECT_EQ (MASK_5_BITS, calc_16_mask (5));
    EXPECT_EQ (MASK_6_BITS, calc_16_mask (6));
    EXPECT_EQ (MASK_7_BITS, calc_16_mask (7));
    EXPECT_EQ (MASK_8_BITS, calc_16_mask (8));
    EXPECT_EQ (MASK_9_BITS, calc_16_mask (9));
    EXPECT_EQ (MASK_10_BITS, calc_16_mask (10));
    EXPECT_EQ (MASK_11_BITS, calc_16_mask (11));
    EXPECT_EQ (MASK_12_BITS, calc_16_mask (12));
    EXPECT_EQ (MASK_13_BITS, calc_16_mask (13));
    EXPECT_EQ (MASK_14_BITS, calc_16_mask (14));
    EXPECT_EQ (MASK_15_BITS, calc_16_mask (15));
    EXPECT_EQ (MASK_16_BITS, calc_16_mask (16));
    return true;
}

static bool test_k_smallest (void) {
    int numsSize;
    int val;
    int arr1[] = {1, 3, -1};
    numsSize = sizeof (arr1) / sizeof (arr1[0]);

    val = qselect (arr1, numsSize, 1);
    if (1 != val) {
        return false;
    }
    int arr2[] = {3, -1, -3};
    numsSize = sizeof (arr2) / sizeof (arr2[0]);
    val = qselect (arr2, numsSize, 1);
    if (-1 != val) {
        return false;
    }
    int arr3[] = {-1, -3, 5};
    numsSize = sizeof (arr3) / sizeof (arr2[0]);

    val = qselect (arr3, numsSize, 1);
    if (-1 != val) {
        return false;
    }

    return true;
}

static bool test_algo (void) {
    int min3val;
    min3val = min3 (2, 3, 5);
    if (2 != min3val) {
        return false;
    }
    min3val = min3 (42, 33, 75);
    if (33 != min3val) {
        return false;
    }
    min3val = min3 (42, 533, 5);
    if (5 != min3val) {
        return false;
    }

    return true;
}

static bool test_sum_digits () {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_EQ (2, sum_digits (11));
    return true;
}

static bool test_avarage (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    uint32_t average_q, average_s;
    for (uint32_t a = 0; a <= 0xFFFFFFF0; a += 103) {
        for (uint32_t b = 0; b <= 0xFFFFFFF0; b += 101) {
            average_q = average_quick (a, b);
            average_s = average_slow (a, b);
            if (average_q != average_s) {
                printf ("\n[!] a:%u b:%u()", a, b);
                printf ("\n[!] aq:%u as:%u()", average_q, average_s);
            }
            EXPECT_EQ (average_q, average_s);
        }
    }
    return true;
}

static bool test_two_sum (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    int return_size = 0;
    int nums1[] = {3, 3};
    int *result;

    int nums2[] = {3, 2, 4};
    return_size = 0;
    result = twoSum (nums2, 3, 6, &return_size);
    EXPECT_NE (NULL, result);
    print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (1, result[0]);
    EXPECT_EQ (2, result[1]);
    free(result);

    result = twoSum (nums1, 2, 6, &return_size);
    EXPECT_NE (NULL, result);
    print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (0, result[0]);
    EXPECT_EQ (1, result[1]);
    free(result);


    int nums3[] = {2, 7, 11, 15};
    return_size = 0;
    result = twoSum (nums3, 4, 9, &return_size);
    EXPECT_NE (NULL, result);
    print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (0, result[0]);
    EXPECT_EQ (1, result[1]);
    free(result);

    return true;
}

bool test_algorithms (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_TRUE (test_two_sum ());
    // EXPECT_TRUE (test_avarage());
    EXPECT_TRUE (test_k_smallest ());
    EXPECT_TRUE (test_algo ());
    EXPECT_TRUE (test_sum_digits ());
    EXPECT_TRUE (test_bit_utils ());
    return true;
}
