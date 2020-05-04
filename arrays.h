#ifndef __ARRAY_H
#define __ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

int* singleNumber (int* nums, int numsSize, int* const returnSize) ;

bool is_single_zero (int * const arr, int sizeOfArr, int indexToArr);
int findMaxConsecutiveOnes (int* nums, int numsSize);
int findMaxConsecutiveOnesFlip1 (int* nums, int length);
int findMaxConOnesDel1 (int * const array, int length);
void print_array_to_file_pointer (FILE * filePointer, int *array, int size);
void print_array_to_filename (char *filename, int *array, int size);
int count_max_amout_of_one_after_del (int *arr, int sizeOfArr);
void* memdup (const void* mem, size_t sizeByte);
int *remove_int_from_arr (int *inArr, int arrSize, int delIndex);
int *add_val_to_end_array (int *inArr, int arrSize, int val);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
int *generate_num_array (int n);
void print_array_of_diff_arrays (int **arrOfArr, int amountOfLine, int *colSizes);
void print_array_of_arrays (int **arrOfArr, int amountOfLine, int amountOfCol);
bool test_single_number (void) ;

#ifdef __cplusplus
}
#endif

#endif /* __ARRAYS_H */
