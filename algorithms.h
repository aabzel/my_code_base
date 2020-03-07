#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

#define true (1u)
#define false (0u)
typedef uint8_t bool;

extern uint32_t amountOfComb;

void permutation (int n);
void permut_set (char *InSet);
void permute_ll (char *string, int left, int right);
void permute (char *string);
void swap (char * const x, char * const y);
char *removeCharFromString (char *str, uint32_t delIndex);
int *generate_num_array (int n);
char *generate_num_string (int n);
void print_combinations (char * const alphabet);
void combine_from_alph (int *inAlphabet, int sizeOfAlphabet, int k, int *curArr, int curArrSize);
void combine (int n, int k);
bool is_permutation (int *arr1, int *arr2, int sizeOfArr);
bool is_permutated_element_in_list (list_node_t *pHead, int *inArr, int arrSize);
bool assemble_combination_list (list_node_t *pPermutHead, list_node_t **pCombineHead);

//function to check permutations
#endif /* __ALGORITHMS_H */
