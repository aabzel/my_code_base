#include "combinations.h"

#include "algorithms.h"
#include "arrays.h"
#include "linked_list.h"
#include "linked_list_array.h"
#include "permutations.h"
#include "str_ops.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_array_node_t *combinationListHead = NULL;

void print_combinations (char *const alphabet) {
    int32_t alphabetLength = strlen (alphabet);
    static int cnt = 0;
    cnt++;
    if (1 == cnt) {

        for (int32_t i = 0; i < alphabetLength; i++) {
            printf ("%c\n", alphabet[i]);
        }
    }
#if 1 == DEBUG_ARG
    printf ("\n inAlphabet: [%s] len: [%u] \n", alphabet, alphabetLength);
#endif
    if (0 < alphabetLength) {
        char *sepMem = malloc (alphabetLength);
        if (sepMem) {
            strcpy (sepMem, alphabet);
            permute_str (sepMem);
            free (sepMem);
        }
        for (int32_t firstLet = 0; firstLet < alphabetLength; firstLet++) {
            char *remainAlphabet = NULL;
            remainAlphabet = removeCharFromString (alphabet, firstLet);
#if DEBUG_REMAIN_ALPH == 1
            // printf ("initAlpm[%s]->remainAlp[%s]", alphabet, remainAlphabet);
#endif // DEBUG_REMAIN_ALPH
            print_combinations (remainAlphabet);
            free (remainAlphabet);
        }
    }
    if (0 == alphabetLength) {
        return;
    }
}

void combine (int n, int k) {
    int *numArray = generate_num_array_malloc (n);
    if (numArray) {
        assemble_from_alph (numArray, n, k, NULL, 0);
        free (numArray);

        printf ("permutation list:");
#if PRINT_PERMUTATIONS
        print_list (permutllHead);
#endif
#ifdef SAVE_PERM_LIST_TO_FILE
        save_list_to_file (permutllHead, pemutationFile);
        printf ("\n");
#endif
        combinationListHead = NULL;
        assemble_combination_list (permutllHead, &combinationListHead);

#if PRINT_COMBINATIONS
        printf ("compination list:");
        print_list (combinationListHead);
#endif
#ifdef SAVE_PERM_LIST_TO_FILE
        save_list_to_file (combinationListHead, kitFile);
#endif
    } else {
        printf ("malloc for init alphabet array error");
    }
}

bool assemble_combination_list (list_array_node_t *pPermutHead, list_array_node_t **pCombineHead) {
#if DEBUG_ASSEMBLE_COMB
    int cnt = 0;
    printf ("%s()", __FUNCTION__);
#endif
    list_array_node_t *curNode = pPermutHead;
    bool res = false;
    if (curNode) {
#ifdef SAVE_IN_LIST
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
#endif
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **subsets (int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    int amOfelem = 0u;
    int **arrOfArrys;
    for (amOfelem = 1u; amOfelem <= numsSize; amOfelem++) {
        assemble_from_alph (nums, numsSize, amOfelem, NULL, 0u);
    }
    // combinationListHead = NULL;
    // assemble_combination_list (permutllHead, &combinationListHead);
#if PRINT_COMBINATIONS
    printf ("compination list:");
    print_list (combinationListHead);
    *returnSize = list_num_of_elements (combinationListHead);
    *returnColumnSizes = NULL;
#endif
#if SAVE_COMBINATIONS
    save_list_to_file (combinationListHead, kitFile);
#endif
#ifdef SAVE_PERM_LIST_TO_FILE
    arrOfArrys = list_of_arr_to_arr_of_arr (combinationListHead, returnSize, returnColumnSizes);
#endif
    return arrOfArrys;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
//}
