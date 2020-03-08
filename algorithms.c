#include "algorithms.h"

#include "permutations.h"
#include "str_ops.h"
#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

list_node_t *combinationListHead = NULL;


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


void print_combinations (char * const alphabet) {
    size_t alphabetLength = strlen (alphabet);
    static int cnt = 0;
    cnt++;
    if (1 == cnt) {

        for (int32_t i = 0; i < alphabetLength; i++) {
            printf ("%c\n", alphabet [i]);

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

void combine (int n, int k) {
    int *numArray = generate_num_array (n);
    if (numArray) {

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


// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int (const void * p1, const void * p2) {
    int x = *(int *) p1; // добываем из указателя значение по этому указателю
    int y = *(int *) p2; // добываем из указателя значение по этому указателю
    return x - y;
}

