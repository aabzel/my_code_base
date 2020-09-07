#include "combinations_test.h"

#include "combinations.h"

bool test_combinations (void) {
	printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
	int nums[3] = {1,2,3};
	int returnSize=0;
	int* returnColumnSizes=NULL;
	subsets(nums, 3, &returnSize,  &returnColumnSizes);

    return true;
}
