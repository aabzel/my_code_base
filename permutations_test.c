#include "permutations_test.h"

#include "arrays.h"
#include "permutations.h"

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

bool test_permutation (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    test_permutation3 ();
    test_permutation4 ();
    return true;
}
