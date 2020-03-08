#include "algorithms.h"

#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

list_node_t *combinationListHead = NULL;
list_node_t *permutllHead = NULL;
uint32_t amountOfComb = 0u;

/* Function to print permutations of string
 This function takes three parameters:
 1. String
 2. Starting index of the string
 3. Ending index of the string. */
void permute_ll (char *string, int left, int right) {
    int index = 0;
    if (left == right) {
        printf ("%s\n", string);
        amountOfComb++;
    } else {
        for (index = left; index <= right; index++) {
            swap ((string + left), (string + index));
            permute_ll (string, left + 1, right);
            swap ((string + left), (string + index)); //backtrack
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
/* Function to swap values at two pointers */
void swap (char * const x, char * const y) {
    if (x != y) {
        char temp;
        temp = *x;
        *x = *y;
        *y = temp;
    } else {
        //printf ("The same element\n");
    }

}

char *removeCharFromString (char *str, uint32_t delIndex) {
    size_t alphabetLength = strlen (str);
    char *tempArray = malloc (alphabetLength);
    if (tempArray) {
        strcpy (tempArray, str);
        uint32_t index = 0;
        if (delIndex < (alphabetLength + 1)) {
            for (index = delIndex; index < (alphabetLength - 1); index++) {
                tempArray [index] = tempArray [index + 1];
            }
        }
        tempArray [alphabetLength - 1] = '\0';
        return tempArray;
    } else {
        printf ("Malloc error");
    }

    return NULL;
}

void print_combinations (char * const alphabet) {
    size_t alphabetLength = strlen (alphabet);
    static int cnt = 0;
    cnt++;
    if (1 == cnt) {
        amountOfComb = 0;
        for (int32_t i = 0; i < alphabetLength; i++) {
            printf ("%c\n", alphabet [i]);
            amountOfComb++;
        }
    }
#if 1==DEBUG_ARG
    printf ("\n inAlphabet: [%s] len: [%u] \n", alphabet, alphabetLength);
#endif
    if (0 < alphabetLength) {
        char *sepMem = malloc (alphabetLength);
        if (sepMem) {
            strcpy (sepMem, alphabet);
            permute (sepMem);
            free (sepMem);
        }
        for (uint32_t firstLet = 0; firstLet < alphabetLength; firstLet++) {
            char *remainAlphabet = NULL;
            remainAlphabet = removeCharFromString (alphabet, firstLet);
#if DEBUG_REMAIN_ALPH==1
            //printf ("initAlpm[%s]->remainAlp[%s]", alphabet, remainAlphabet);
#endif // DEBUG_REMAIN_ALPH
            print_combinations (remainAlphabet);
            free (remainAlphabet);
        }
    }
    if (0 == alphabetLength) {
        return;
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

void combine (int n, int k) {
    int *numArray = generate_num_array (n);
    if (numArray) {
        amountOfComb = 0;
        combine_from_alph (numArray, n, k, NULL, 0);
        free (numArray);

        printf ("permutation list:");
#if PRINT_PERMUTATIONS
        print_list (permutllHead);
#endif
        save_list_to_file (permutllHead, pemutationFile);
        printf ("\n");

        combinationListHead = NULL;
        assemble_combination_list (permutllHead, &combinationListHead);

#if PRINT_COMBINATIONS
        printf ("compination list:");
        print_list (combinationListHead);
#endif
        save_list_to_file (combinationListHead, kitFile);
    } else {
        printf ("malloc for init alphabet array error");
    }
}

bool assemble_combination_list (list_node_t *pPermutHead, list_node_t **pCombineHead) {
#if DEBUG_ASSEMBLE_COMB
    int cnt = 0;
    printf ("%s()", __FUNCTION__);
#endif
    list_node_t *curNode = pPermutHead;
    bool res = false;
    if (curNode) {
        while (curNode) {
#if DEBUG_ASSEMBLE_COMB
            printf ("\nElement %d", ++cnt);
#endif
            if (curNode) {
                res = is_permutated_element_in_list (*pCombineHead, curNode->data.pArr, curNode->data.arrSize);
                if (false == res) {
#if DEBUG_ASSEMBLE_COMB
                    printf ("\nAdd array to final list\n");
                    print_curr_array (curNode->data.pArr, curNode->data.arrSize);
#endif

                    res = linked_list_add_array (pCombineHead, curNode->data.pArr, curNode->data.arrSize);
                    if (false == res) {
                        printf ("\nError in add array!\n");
                    }
                }
            }
            curNode = curNode->nextNode;
        }
    } else {
        printf ("\nEmpty permut list\n");
    }
#if DEBUG_ASSEMBLE_COMB
    printf ("\nList of combinations: \n");
#endif
#if DEBUG_ASSEMBLE_COMB
    printf ("%s() done", __FUNCTION__);
#endif
    return res;
}

/* k - amount of letters*/
void combine_from_alph (int *inAlphabet, int sizeOfAlphabet, int k, int *curArr, int curArrSize) {
    if (0 == k) {
        amountOfComb++;
        //print_array_to_file (curArr, curArrSize);
#if DEBUG_COMBINE
        print_curr_array (curArr, curArrSize);
#endif
        linked_list_add_array (&permutllHead, curArr, curArrSize);
    }
    if (0 < k) {
        if (0 < sizeOfAlphabet) {
#if DEBUG_COMBINE
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
                        combine_from_alph (redusedAlphabet, (sizeOfAlphabet - 1), (k - 1), currArray, curArrSize + 1);
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

// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int (const void * p1, const void * p2) {
    int x = *(int *) p1; // добываем из указателя значение по этому указателю
    int y = *(int *) p2; // добываем из указателя значение по этому указателю
    return x - y;
}

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
                printf ("\nsize unmatch inArrSize %d arrCurSize %d", arrSize, curNode->data.arrSize);
            }
            curNode = curNode->nextNode;
        }
    }
    return res;
}
