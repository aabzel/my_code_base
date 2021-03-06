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
    int *result;

    int nums4[] = {3, 2, 3};
    return_size = 0;
    result = twoSum (nums4, 3, 6, &return_size);
    EXPECT_NE (NULL, result);
    // print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (0, result[0]);
    EXPECT_EQ (2, result[1]);
    free (result);

    int nums2[] = {3, 2, 4};
    return_size = 0;
    result = twoSum (nums2, 3, 6, &return_size);
    EXPECT_NE (NULL, result);
    //   print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (1, result[0]);
    EXPECT_EQ (2, result[1]);
    free (result);

    int nums1[] = {3, 3};
    result = twoSum (nums1, 2, 6, &return_size);
    EXPECT_NE (NULL, result);
    // print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (0, result[0]);
    EXPECT_EQ (1, result[1]);
    free (result);

    int nums3[] = {2, 7, 11, 15};
    return_size = 0;
    result = twoSum (nums3, 4, 9, &return_size);
    EXPECT_NE (NULL, result);
    //    print_array_int (result, 2);
    EXPECT_EQ (2, return_size);
    EXPECT_EQ (0, result[0]);
    EXPECT_EQ (1, result[1]);
    free (result);

    return true;
}

static bool test_tree_sum (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_EQ (0, numRollsToTarget (0, 5, 0));
    EXPECT_EQ (1, numRollsToTarget (1, 5, 5));
    EXPECT_EQ (1, numRollsToTarget (2, 5, 10));
    EXPECT_EQ (6, numRollsToTarget (2, 6, 7));
    EXPECT_EQ (1, numRollsToTarget (1, 6, 3));
    EXPECT_EQ (0, numRollsToTarget (1, 2, 3));
    EXPECT_EQ (222616187, numRollsToTarget (30, 30, 500));

    return true;
}

static bool test_swap (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    for (int a = (INT_MAX - 2); 0 < a; a -= INT_MAX / 1000) {
        for (int b = (INT_MAX - 1); 0 < b; b -= INT_MAX / 1000) {
            int x1 = a;
            int y1 = b;
            int x2 = a;
            int y2 = b;
            // printf ("\n[d] a %d b %d", a,b);
            EXPECT_TRUE (swap_int (&x1, &y1));
            EXPECT_TRUE (swap_int2 (&x2, &y2));
            EXPECT_EQ (x1, x2);
            EXPECT_EQ (y1, y2);
        }
    }
    return true;
}

bool test_algorithms (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_TRUE (test_swap ());
    EXPECT_TRUE (test_tree_sum ());
    EXPECT_TRUE (test_two_sum ());
    // EXPECT_TRUE (test_avarage());
    EXPECT_TRUE (test_k_smallest ());
    EXPECT_TRUE (test_algo ());
    EXPECT_TRUE (test_sum_digits ());
    return true;
}
