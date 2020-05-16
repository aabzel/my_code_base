#include "permutations.h"

#if 1==DEPLOY_PERMUTATIONS

#include "algorithms.h"
#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static int permutationNumber = 0;

bool print_permutations_ll (
    int *inCurrentArray,
    int inCurrSize,
    int *inIndexArrayRemain,
    int remainSize,
    int totalSize,
    int targetPermutIndex,
    int *outArray) {
    bool res = false;
    int *indexArrayTemp;
    int *indexArrayNew;
    if (remainSize < 0) {
        printf ("Error \n");
        return false;
    }
    if (inCurrSize < 0) {
        printf ("Error \n");
        return false;
    }
    if (NULL == inCurrentArray) {
        printf ("Error \n");
        return false;
    }
    if (NULL == inIndexArrayRemain) {
        printf ("Error \n");
        return false;
    }
    if (inCurrSize == totalSize) {
        permutationNumber++;
        //printf ("\n number %d", permutationNumber);
#if DEBUG_ARRAY
        print_curr_array (inCurrentArray, inCurrSize);
#endif
        if ((NULL != outArray) && (targetPermutIndex == permutationNumber)) {
            memcpy (outArray, inCurrentArray, inCurrSize * sizeof(int));
            return true;
        }
        res = true;

    }
    for (int i = 0; i < remainSize; i++) {
        indexArrayTemp = (int *) memdup ((void *) inIndexArrayRemain, remainSize * sizeof(int));
        if (indexArrayTemp) {
            int *currentArray = add_val_to_end_array (inCurrentArray, inCurrSize, indexArrayTemp [i]);
            if (currentArray) {
                indexArrayNew = remove_int_from_arr (indexArrayTemp, remainSize, i);
                if (indexArrayNew) {
                    print_permutations_ll (currentArray, inCurrSize + 1, indexArrayNew, remainSize - 1, totalSize, targetPermutIndex, outArray);
                    free (indexArrayNew);
                    res = true;
                }
            }
        }
    }
    return res;
}



bool get_i_permutation_of_n (int maxNumOfElement, int permutIndex, int *array) {
    bool res = false;
    permutationNumber = 0;
    if (permutIndex <= factorial (maxNumOfElement)) {
        int *indexArray;
        int *indexArrayNew;
        for (int i = 0; i < maxNumOfElement; i++) {
            indexArray = generate_num_array (maxNumOfElement);
            if (indexArray) {
                int *currentArray = add_val_to_end_array (NULL, 0, indexArray [i]);
                indexArrayNew = remove_int_from_arr (indexArray, maxNumOfElement, i);
                if (indexArrayNew) {
                    res = print_permutations_ll (currentArray, 1, indexArrayNew, maxNumOfElement - 1, maxNumOfElement, permutIndex, array);
                    free (indexArrayNew);
                }
            }
        }
    } else {
        printf ("there is no such permutation %d", permutIndex);
    }
    return res;
}


// given number N
// print all permutations for (1,2,..,N)
bool print_permutations (int N) {
    bool res = false;
    res = get_i_permutation_of_n (N, 0, NULL);
    return res;
}


list_node_t *permutllHead = NULL;

/* Function to print permutations of string
 This function takes three parameters:
 1. String
 2. Starting index of the string
 3. Ending index of the string. */
void permute_ll (char *string, int left, int right) {
    int index = 0;
    if (left == right) {
        printf ("%s\n", string);

    } else {
        for (index = left; index <= right; index++) {
            swap_char ((string + left), (string + index));
            permute_ll (string, left + 1, right);
            swap_char ((string + left), (string + index)); //backtrack
        }
    }
}

void permute (char *string) {
    int len = strlen (string);
    if (1 == len) {
        //printf ("%s\n", string);
    } else {
        if (1 < len) {
            permute_ll (string, 0, len - 1);
        }
    }
}

void permutation (int n) {
    if (0 < n) {
        char *numString = NULL;
        numString = generate_num_string (n);
        if (NULL != numString) {
            permute (numString);
            free (numString);
        }
    }
}

/*
 * inAlphabet array of elements to get values for the combinations
 * sizeOfAlphabet size of that array
 * k - amount of letters in result combination instance
 *
 * */
/* k - amount of letters*/
#if 0
void assemble_from_alph (int *inAlphabet, int sizeOfAlphabet, int k, int *curArr, int curArrSize) {
    if (0 == k) {
#if DEBUG_ASSEMBLE
        print_array_to_filename (kitFile, curArr, curArrSize);
        print_curr_array (curArr, curArrSize);
#endif
        linked_list_add_array (&permutllHead, curArr, curArrSize);
    }
    if (0 < k) {
        if (0 < sizeOfAlphabet) {
#if DEBUG_ASSEMBLE
            print_array (inAlphabet, sizeOfAlphabet, k);
#endif
            int *localAlphabet = malloc (sizeof(int) * sizeOfAlphabet);
            if (NULL == localAlphabet) {
                printf ("malloc for in alphabet error");
                return;
            }
            for (int numOrger = 0; numOrger < sizeOfAlphabet; numOrger++) {
                memcpy (localAlphabet, inAlphabet, sizeof(int) * sizeOfAlphabet);
                //printf ("\nw[%d]=%d", 2 - k, localAlphabet [numOrger]);
                int *currArray = add_val_to_end_array (curArr, curArrSize, localAlphabet [numOrger]);
                if (NULL != currArray) {
                    int *redusedAlphabet = NULL;
                    redusedAlphabet = remove_int_from_arr (localAlphabet, sizeOfAlphabet, numOrger);
                    if (redusedAlphabet) {
                        assemble_from_alph (redusedAlphabet, (sizeOfAlphabet - 1), (k - 1), currArray, curArrSize + 1);
                        free (redusedAlphabet);
                        free (currArray);
                    } else {
                        printf ("malloc for reduced alphabet error");
                        return;
                    }
                }
            }
#if DEBUG_COMBINE
            printf ("\n");
#endif
            free (localAlphabet);
        }

    }
}
#endif

#define DEBUG_IS_PERMUTATED 0
bool is_permutation (int *arr1, int *arr2, int sizeOfArr) {
    bool res = false;
#if DEBUG_IS_PERMUTATED
    printf ("\nArr1: ");
    print_curr_array (arr1, sizeOfArr);
    printf ("Arr2: ");
    print_curr_array (arr2, sizeOfArr);
#endif
    int amOfBytes = sizeof(int) * sizeOfArr;

    int *locArr1 = NULL;
    int *locArr2 = NULL;

    locArr1 = malloc (amOfBytes);
    if (locArr1) {
        memcpy (locArr1, arr1, amOfBytes);
        qsort (locArr1, sizeOfArr, sizeof(int), cmp_int);
    }

    locArr2 = malloc (amOfBytes);
    if (locArr2) {
        memcpy (locArr2, arr2, amOfBytes);
        qsort (locArr2, sizeOfArr, sizeof(int), cmp_int);
    }

    if (locArr1 && locArr2) {
        int ret = memcmp (locArr1, locArr2, amOfBytes);
        if (0 == ret) {
#if DEBUG_IS_PERMUTATED
            printf ("\nPermutated arrays!");
#endif
            res = true;
        }
        free (locArr1);
        free (locArr2);

    }
    return res;
}

#if 0
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize) {
#if DEBUG_PERMUT_ELEN_IN_LIST
    int static cnt = 0;
    printf ("\n%s() %d", __FUNCTION__,++cnt);
#endif
    bool res = false;
    list_node_t *curNode = pHead;
    if (curNode) {
        while (NULL != curNode) {
            if (arrSize == curNode->data.arrSize) {
                res = is_permutation (curNode->data.pArr, inArr, arrSize);
                if (true == res) {
#if DEBUG_PERMUT_ELEN_IN_LIST
                    printf ("\nList contained permutated array");
#endif
                    break;
                }
            } else {
#if DEBUG_IS_PERMUT
                printf ("\nsize of array unmatch inArrSize %d arrCurSize %d", arrSize, curNode->data.arrSize);
#endif
            }
            curNode = curNode->nextNode;
        }
    }
    return res;
}
#endif
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#if 0
int** permute_array (int* array, int numsSize, int* returnSize, int** returnColumnSizes) {
    int **arrayOfPtr;
    //clean list permutllHead
    assemble_from_alph (array, numsSize, numsSize, NULL, 0);
    //save_list_to_file (permutllHead, pemutationFile);
    arrayOfPtr = list_of_arr_to_arr_of_arr (permutllHead, returnSize, returnColumnSizes);
    return arrayOfPtr;
}
#endif

#if 0
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
#endif

#endif
