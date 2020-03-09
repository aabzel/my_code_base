#ifndef __PERMUTATIONS_H
#define __PERMUTATIONS_H

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

extern list_node_t *permutllHead;

void test_permut (void);
int** permute_array(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
void permutation (int n);
void permut_set (char *InSet);
void permute_ll (char *string, int left, int right);
void permute (char *string);
int *generate_num_array (int n);
char *generate_num_string (int n);
void combine_from_alph (int *inAlphabet, int sizeOfAlphabet, int k, int *curArr, int curArrSize);
bool is_permutation (int *arr1, int *arr2, int sizeOfArr);
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize);

//function to check permutations
#endif /* __PERMUTATIONS_H */
