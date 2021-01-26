#include "permutations_test.h"

#include "arrays.h"
#include "permutations.h"
#include "uTests.h"

static bool test_permutation3 (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);

    int **resArray;
    int *returnColumnSizes = NULL;
    int return_size = 0;
    int in_array[3] = {1, 2, 3};
    resArray = permute (in_array, 3, &return_size, &returnColumnSizes);
    printf ("\n[d]return_size %d", return_size);
    print_array_of_arrays (resArray, return_size, 3);
    return true;
}

static bool test_permutation4 (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);

    int **resArray;
    int *returnColumnSizes = NULL;
    int return_size = 0;
    int in_array[4] = {1, 2, 3, 4};
    resArray = permute (in_array, 4, &return_size, &returnColumnSizes);
    printf ("\n[d]return_size %d", return_size);
    print_array_of_arrays (resArray, return_size, 4);
    return true;
}

static bool test_generate_permutation (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    int exp_arr0[2] = {0, 0};
    int exp_arr1[2] = {0, 1};
    int exp_arr29[2] = {5, 5};
    int *arr = NULL;
    int cmp = 0;
    arr = generate_perm_arr (2, 6, 0);
    EXPECT_EQ (0, memcmp (arr, exp_arr0, 2 * sizeof (int)));
    free (arr);

    arr = generate_perm_arr (2, 6, 1);
    EXPECT_EQ (0, memcmp (arr, exp_arr1, 2 * sizeof (int)));
    free (arr);

    arr = generate_perm_arr (2, 6, 35);
    print_curr_array (arr, 2);
    EXPECT_EQ (0, memcmp (arr, exp_arr29, 2 * sizeof (int)));
    free (arr);

    return true;
}

bool test_permutation (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    EXPECT_TRUE (test_generate_permutation ());
    EXPECT_TRUE (test_permutation3 ());
    EXPECT_TRUE (test_permutation4 ());
    return true;
}
