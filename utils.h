#ifndef __UTILS_H
#define __UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bin_heap_array.h"
#include "custom_type.h"
#include "linked_list.h"

#include <stdint.h>

#define NOT_NUM (-999999)
#define INT_MIN (-2147483648)
#define INT_MAX (2147483647)

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

extern char pemutationFile [100];
extern char kitFile [100];

void init_double_array (double * ptrArray, int size);
uint32_t reverseBits (uint32_t num);
uint8_t hamming_weight (uint32_t n);
unsigned int GrayToBinary32 (unsigned int num);
unsigned int GrayToBinary (unsigned int num);
uint32_t bin_to_gray (uint32_t num);
char * format_time_txt (void);
void init_file_name (void);
// cur date string
double calc_median_naiv (int * const inArr, int sizeOfArr);
char *generate_num_string (int n);
void print_array (int *alphabet, int sizeOfAlphabet, int k);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
void print_mem (uint8_t *memPtr, uint32_t sizeOfAlphabet);
double avrage_two (int val1, int val2);
uint32_t max_val (uint32_t amountofbit);
int* grayCode (int n, int* returnSize);
void print_bit_representation (float val);
char *uint32_to_bin_str (uint32_t const inVal32bit);
int **list_of_arr_to_arr_of_arr (list_node_t * const listOfArrays, int * const amountOfArrays, int** returnColumnSizes);
double calc_median (int * const inArr, int sizeOfArr);
long long summ_array (int const* const inArr, int sizeOfArr);
double avrage_two (int val1, int val2);
double* medianSlidingWindow (int* nums, int numsSize, int k, int* returnSize);
void print_array_double (double *alphabet, int sizeOfAlphabet);
bool is_odd (int val);
double calc_average (int const * const inArr, int sizeOfArr);
void print_bytes (uint32_t byte);
double* medianSlidingWindowArr (int* nums, int numsSize, int k, int* returnSize);

bool insert_val_to_2_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t * minBinHeap, int newVal, int oldVal, int sizeOfWind, int *curWinArr);

bool remove_old_val_from_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int oldVal);
bool insert_new_val_to_bin_heaps (BinaryHeap_t *maxBinHeap, BinaryHeap_t *minBinHeap, int newVal);

bool is_double_arr_equal (double *arr1, double *arr2, int arrSize);

#ifdef __cplusplus
}
#endif

#endif /* __UTILS_H */
