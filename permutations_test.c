#include "permutation_test.h"

void test_permut (void) {
    int **resArray;
    int *returnColumnSizes = NULL;
    int returnSize = 0;
    int inArray[4] = {1, 2, 3, 4};
    int numsSize = sizeof (inArray) / sizeof (inArray[0]);
    resArray = permute_array (inArray, numsSize, &returnSize, &returnColumnSizes);
    print_array_of_arrays (resArray, returnSize, numsSize);
}

#endif
