#ifndef __COMBINATIONS_H
#define __COMBINATIONS_H

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

extern list_node_t *combinationListHead;

void test_combine (void);
void print_combinations (char * const alphabet);
void combine (int n, int k);
bool assemble_combination_list (list_node_t *pPermutHead, list_node_t **pCombineHead);
//int** combine(int n, int k, int* returnSize, int** returnColumnSizes);

#endif /* __COMBINATIONS_H */
