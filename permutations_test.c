#include "permutations_test.h"

#include "arrays.h"
#include "permutations.h"

bool test_permutation (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
#if 0
	int nums[3] = {1,2,3};
	int return_size;
	int* returnColumnSizes;
	permute(nums, 3, &return_size,  &returnColumnSizes);
#endif

    int **resArray;
    int *returnColumnSizes = NULL;
    int return_size = 0;
    int in_array[3] = {1, 2, 3};
    resArray = permute (in_array, 3, &return_size, &returnColumnSizes);
    printf ("\n[d]return_size %d",  return_size);
    print_array_of_arrays (resArray, return_size, 3);
    return true;
}
