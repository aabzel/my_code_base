#ifndef __UTILS_H
#define __UTILS_H

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

#define true (1u)
#define false (0u)
typedef uint8_t bool;

extern char pemutationFile [100];
extern char kitFile [100];

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

#endif /* __UTILS_H */
