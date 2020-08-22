#include "arrays_test.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithms.h"
#include "array_type.h"
#include "arrays.h"
#include "str_ops.h"
#include "utils.h"

static bool test_concat_arrays (void) {
    bool res = false;
    int cmp_res;
    uint8_t cur_fin_array[16];
    uint8_t exp_fin_array[16] = {1, 2, 3, 4, 5, 6, 7, 8, 11, 22, 33, 44, 55, 66, 77, 88};
    uint8_t array1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t array2[8] = {11, 22, 33, 44, 55, 66, 77, 88};
    res = concatenate_array (cur_fin_array, 16, array1, 8, array2, 8);

    cmp_res = memcmp (cur_fin_array, exp_fin_array, 16);
    if (0 != cmp_res) {
        res = false;
    } else {
        res = true;
    }

    return res;
}

bool test_array (void) {
    bool res = test_concat_arrays ();
    return res;
}
