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

//static int curPermutationNumber = 0;
/*inCurrentArray will be freed in here*/
/*inIndexArrayRemain will be freed outside */
bool print_permutations_ll (int *inCurrentArray, int inCurrSize, int *inIndexArrayRemain, int remainSize, int totalSize, // amount of item in permutation
    int targetPermutIndex,
    int startIndex,
    int endIndex,
    int *outArray) {

#if DEBUG_CURR_ARRAY
    printf ("\n cur array: ");
    print_curr_array (inCurrentArray, inCurrSize);
    printf ("\n");
#endif
    bool res = false;
    int *indexArrayTemp;
    int *indexArrayNew;
    if (remainSize < 0) {
        printf ("%s Error %d\n", __FUNCTION__, 3);
        return false;
    }
    int range = endIndex - startIndex + 1;
#if PRINT_PERMUTATIONS_LL
    if (2 == range) {
        printf ("%s Debug range %d\n", __FUNCTION__, range);
    }
#endif
    if (false == is_in_range (targetPermutIndex, startIndex, endIndex)) {
        free (inCurrentArray);
        return false;
    } else {
#if DEBUG_IND_RANGE
        printf (" -> [%d<=%d<=%d] range %d", startIndex, targetPermutIndex, endIndex, range);
#endif
    }
    if (0 == remainSize) {
        //printf ("remainSize 0 \n");
        //free(inIndexArrayRemain);
    }
    if (inCurrSize < 0) {
        printf ("%s Error %d\n", __FUNCTION__, 1);
        return false;
    }
    if ((NULL == inCurrentArray)) {
        printf ("%s Error %d\n", __FUNCTION__, 2);
        return false;
    }

    if (inCurrSize == totalSize) {
#if DEBUG_ARRAY
        printf ("\n number %d", curPermutationNumber);
        print_curr_array (inCurrentArray, inCurrSize);
#endif

        if ((NULL != outArray) && (targetPermutIndex == startIndex)) {
            //printf ("\n ");
            memcpy (outArray, inCurrentArray, inCurrSize * sizeof(int));
            free (inCurrentArray);
            free (inIndexArrayRemain);
            return true;
        }
    }
    int stepInd = 0;

    if (0 < remainSize) {
        if (remainSize <= range) {
            //is divided?
            if (0 == (range % remainSize)) {
                if ((1 == range) && (range == remainSize)) {
                    stepInd = 0;
                } else {
                    stepInd = range / remainSize;
                }
            } else {
#if DEBUG_PRINT_PERMUTATIONS_LL
                printf ("\n remainSize %d range %d startInd %d endInd %d target %d", remainSize, range, startIndex, endIndex, targetPermutIndex);
#endif
                return false;
            }
        } else {
#if DEBUG_PRINT_PERMUTATIONS_LL
            printf ("\n remainSize %d range %d", remainSize, range);
#endif
            return false;
        }
    } else {
        return true;
    }
#if DEBUG_PRINT_PERMUTATIONS_LL
    printf ("\n range %d remainSize %d stepInd %d", range, remainSize, stepInd);
#endif

    for (int i = 0; i < remainSize; i++) {
        indexArrayTemp = (int *) memdup ((void *) inIndexArrayRemain, remainSize * sizeof(int));
        if (indexArrayTemp) {
            int *currentArray = add_val_to_end_array (inCurrentArray, inCurrSize, indexArrayTemp [i]);
            if (currentArray) {
#if DEBUG_PRINT_PERMUTATIONS_LL
                printf ("\n");
                print_curr_array (currentArray, inCurrSize + 1);
                printf ("\n");
#endif
                indexArrayNew = remove_int_from_arr (indexArrayTemp, remainSize, i);
                //indexArrayNew will be freed in print_permutations_ll
                int startInd = startIndex;
                int endInd = startIndex;
                if (0 < stepInd) {
                    startInd = startIndex + (i * stepInd);        //0
                    endInd = startIndex + (i * stepInd) + stepInd - 1;        //
                }
                if (true == is_in_range (targetPermutIndex, startInd, endInd)) {
                    res = print_permutations_ll (
                        currentArray,
                        inCurrSize + 1,
                        indexArrayNew,
                        remainSize - 1,
                        totalSize,
                        targetPermutIndex,
                        startInd,
                        endInd,
                        outArray);
                } else {
                    free (currentArray);
                }

                if (indexArrayNew) {
                    free (indexArrayNew);
                }
                if (true == res) {
                    return true;
                }
            }
        }
    }
    free (inCurrentArray);
    return res;
}
//4: 1....24     6    (1 7 13 19)
//5: 1....120    24   (1 25 49 73 97 )
bool get_i_permutation_of_n (int maxNumOfElement, uint32_t permutIndex, int *array) {
    bool res = false;
    if(1==maxNumOfElement){
        (*array)=0;
        return true;
    }
    uint32_t amountOfpermutations = factorial (maxNumOfElement);
    int indexStep = amountOfpermutations / maxNumOfElement;        //24/4 = 6
    if (permutIndex < amountOfpermutations) {
        int *indexArray;
        int *indexArrayNew;
        for (int i = 0; i < maxNumOfElement; i++) {
            indexArray = generate_num_array_malloc (maxNumOfElement);
            if (indexArray) {
                int *currentArray = add_val_to_end_array (NULL, 0, indexArray [i]);
                //indexArray will be freed in remove_int_from_arr
                indexArrayNew = remove_int_from_arr (indexArray, maxNumOfElement, i);
                if (indexArrayNew) {
                    //currentArray will be freed in print_permutations_ll
                    int indexStart = i * indexStep;        //0
                    int indexEnd = i * indexStep + indexStep - 1;        //5
                    if (true == is_in_range (permutIndex, indexStart, indexEnd)) {
                        res = print_permutations_ll (
                            currentArray,
                            1,
                            indexArrayNew,
                            maxNumOfElement - 1,
                            maxNumOfElement,
                            permutIndex,
                            indexStart,
                            indexEnd,
                            array);

                    }

                    free (indexArrayNew);
                    if (true == res) {
                        return true;
                    }
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
