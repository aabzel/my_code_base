#include "algorithms.h"
#include "combinations.h"
#include "linked_list.h"
#include "permutations.h"
#include "utils.h"
#include "uTests.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main (int argc, char **argv) {
#if 1
    init_file_name ();
    int ret = unitTest ();
    if (0 != ret) {
        printf ("Unit Test Error: %d\n", ret);
    } else {
        test_combine ();
    }
#endif

    //permute (alphabet);

#if 0
    int ret = test_case ();
    if (ALLOC_FREE_OK != ret) {
        printf ("errorCode: [%s] \n\n", to_name_str (ret));
    } else {
        printf ("\n uTestOk!\n");
    }
#endif
    printf ("Done!\n\n");
//    getchar ();
    return 0;
}


void test_permut (void) {
    int** resArray;
    int* returnColumnSizes = NULL;
    int returnSize = 0;
    int inArray [4] =
        { 1, 2, 3, 4 };
    int numsSize = sizeof(inArray) / sizeof(inArray [0]);
    resArray = permute_array (inArray, numsSize, &returnSize, &returnColumnSizes);
    print_array_of_arrays (resArray, returnSize, numsSize);
}

