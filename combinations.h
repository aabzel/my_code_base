#ifndef __COMBINATIONS_H
#define __COMBINATIONS_H


#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUG_COMBINE 1
#define PRINT_COMBINATIONS 0
#define SAVE_COMBINATIONS 0

extern list_node_t *combinationListHead;

int **subsets (int *nums, int numsSize, int *returnSize, int **returnColumnSizes);
void test_combine (void);
void print_combinations (char *const alphabet);
void combine (int n, int k);
bool assemble_combination_list (list_node_t *pPermutHead, list_node_t **pCombineHead);
// int** combine(int n, int k, int* returnSize, int** returnColumnSizes);


#endif /* __COMBINATIONS_H */
