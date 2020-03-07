#ifndef __UTILS_H
#define __UTILS_H

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

#define true (1u)
#define false (0u)
typedef uint8_t  bool;

extern uint32_t amountOfComb;

int print_array_to_file (int *array, int numItem);
void print_array (int *alphabet, int sizeOfAlphabet, int k);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
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
int is_permutation(int *arr1,int *arr2, int sizeOfArr);
//function to check permutations
#endif /* __UTILS_H */
