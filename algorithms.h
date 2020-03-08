#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

extern list_node_t *combinationListHead;


int cmp_int (const void * p1, const void * p2);
void swap (char * const x, char * const y);

int *generate_num_array (int n);
char *generate_num_string (int n);
void print_combinations (char * const alphabet);
void combine (int n, int k);
bool assemble_combination_list (list_node_t *pPermutHead, list_node_t **pCombineHead);


#endif /* __ALGORITHMS_H */
