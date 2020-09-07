#include "permutations_test.h"

#include "permutations.h"

bool test_permutation (void) {
	printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
#if	0
	int nums[3] = {1,2,3};
	int return_size;
	int* returnColumnSizes;
	permute(nums, 3, &return_size,  &returnColumnSizes);
#endif

    int **resArray;
    int *returnColumnSizes = NULL;
    int return_size = 0;
    int in_array[3] = {1, 2, 3};
    int nums_size = sizeof (in_array) / sizeof (in_array[0]);
    resArray = permute_array (in_array, nums_size, &return_size, &returnColumnSizes);
    print_array_of_arrays (resArray, return_size, nums_size);
    return true;
}


