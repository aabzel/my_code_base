#ifndef __ARRAYS_H
#define __ARRAYS_H

#include <stdint.h>
#include <string.h>

typedef struct xArray_t {
    int32_t *pArr;
    uint32_t arrSize;
} Array_t;

void* memdup (const void* mem, size_t sizeByte);
int *remove_int_from_arr (int *inArr, int arrSize, int delIndex);
int *add_val_to_end_array (int *inArr, int arrSize, int val);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
int *generate_num_array (int n);

#endif /* __ARRAYS_H */
