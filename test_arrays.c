#include "test_arrays.h"

#include "arrays.h"

static bool test_arrays_del (void) {
    printf ("\n %s() ", __FUNCTION__);

    int orig_array3[3] = {55, 66, 77};
    int exp_array3[2] = {55, 66};
    int *new_array;
    new_array = remove_int_from_arr (orig_array3, 3, 2);

    int cmp_res = 0;
    cmp_res = memcmp (exp_array3, orig_array3, 2);
    if (0 != cmp_res) {
        printf ("\n Error delete element from array: last");
        return false;
    }

    int orig_array1[3] = {1, 2, 3};
    int exp_array1[3] = {1, 3};
    new_array = remove_int_from_arr (orig_array1, 3, 1);

    cmp_res = 0;
    cmp_res = memcmp (exp_array1, orig_array1, 2);
    if (0 != cmp_res) {
        printf ("\n Error delete element from array: middle");
        return false;
    }

    int orig_array_z[1] = {2};
    new_array = remove_int_from_arr (orig_array_z, 1, 0);
    if (NULL != new_array) {
        printf ("\n Error delete element from array: single");
        return false;
    }

    int orig_array_0[3] = {11, 22, 33};
    int exp_array_0[3] = {22, 33};
    new_array = remove_int_from_arr (orig_array_0, 3, 0);

    cmp_res = 0;
    cmp_res = memcmp (exp_array_0, orig_array_0, 2);
    if (0 != cmp_res) {
        printf ("\n Error delete element from array: first");
        return false;
    }

    return true;
}

static bool test_concat_arrays (void) {
    printf ("\n %s() ", __FUNCTION__);
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
    printf ("\n %s() ", __FUNCTION__);
    bool res = test_concat_arrays ();
    if (false == res) {
        return false;
    }

    res = test_arrays_del ();
    if (false == res) {
        return false;
    }

    return res;
}
