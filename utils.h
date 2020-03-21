#ifndef __UTILS_H
#define __UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"
#include "linked_list.h"

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

extern char pemutationFile [100];
extern char kitFile [100];

uint32_t reverseBits (uint32_t num);
uint8_t hamming_weight (uint32_t n);
unsigned int GrayToBinary32 (unsigned int num);
unsigned int GrayToBinary (unsigned int num);
uint32_t bin_to_gray (uint32_t num);
char * format_time_txt (void);
void init_file_name (void);
// cur date string
char *generate_num_string (int n);
void print_array (int *alphabet, int sizeOfAlphabet, int k);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
void test_heap (void);
uint32_t max_val (uint32_t amountofbit);
int* grayCode (int n, int* returnSize);
char *uint32_to_bin_str (uint32_t const inVal32bit);
int **list_of_arr_to_arr_of_arr (list_node_t * const listOfArrays, int * const amountOfArrays, int** returnColumnSizes);

#ifdef __cplusplus
}
#endif

#endif /* __UTILS_H */
