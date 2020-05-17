#ifndef __PERMUTATIONS_H
#define __PERMUTATIONS_H

#define DEPLOY_PERMUTATIONS 1

#if 1==DEPLOY_PERMUTATIONS

#include "linked_list.h"
#include "utils.h"
#include "custom_type.h"

#include <stdint.h>

#define DEBUG_ARG 0
#define DEBUG_IND_RANGE 1
#define DEBUG_CURR_ARRAY 1


extern list_node_t *permutllHead;

// given number N
// print all permutations for (1,2,..,N)
void test_permut (void);
int** permute_array(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
void permut_set (char *InSet);
void permute_ll (char *string, int left, int right);
void permute (char *string);
int *generate_num_array (int n);
char *generate_num_string (int n);
//void assemble_from_alph (int *inAlphabet, int sizeOfAlphabet, int k, int *curArr, int curArrSize);
bool get_i_permutation_of_n (int maxNumOfElement, int permutIndex, int *array);

bool print_permutations_ll (
    int *inCurrentArray,
    int inCurrSize,
    int *inIndexArrayRemain,
    int remainSize,
    int totalSize,
    int targetPermutIndex,
    int startIndex,
    int endIndex,
    int *outArray);

bool is_permutation (int *arr1, int *arr2, int sizeOfArr);
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize);
void permutation (int n);
bool print_permutations (int N);

#endif

//function to check permutations
#endif /* __PERMUTATIONS_H */
