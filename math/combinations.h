#ifndef __COMBINATIONS_H
#define __COMBINATIONS_H

#ifdef COMBINATIONS
#include "linked_list.h"
#include "linked_list_array.h"
#include "utils.h"

#include <stdint.h>

#define DEBUG_COMBINE 1
#define PRINT_COMBINATIONS 0
#define SAVE_COMBINATIONS 0

extern list_array_node_t *combinationListHead;

int **subsets (int *nums, int numsSize, int *returnSize, int **returnColumnSizes);
void test_combine (void);
void print_combinations (char *const alphabet);
void combine (int n, int k);
bool assemble_combination_list (list_array_node_t *pPermutHead, list_array_node_t **pCombineHead);
// int** combine(int n, int k, int* returnSize, int** returnColumnSizes);
#endif

#endif /* __COMBINATIONS_H */
