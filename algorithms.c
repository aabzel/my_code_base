#include "algorithms.h"

#include "permutations.h"
#include "str_ops.h"
#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int max (int val1, int val2) {
    int outVal = val1;
    if (val1 < val2) {
        outVal = val2;
    }
    return outVal;
}

int min (int val1, int val2) {
    int outVal = val2;
    if (val1 < val2) {
        outVal = val1;
    }
    return outVal;
}

/* Function to swap values at two pointers */
void swap (char * const x, char * const y) {
    if (x != y) {
        char temp;
        temp = *x;
        *x = *y;
        *y = temp;
    } else {
        //printf ("The same element\n");
    }

}

typedef struct xPox_t {
    int x;
    int y;
} xPox_t;

#define USE_PRINT_LT 0







// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int (const void * p1, const void * p2) {
    int x = *(int *) p1; // добываем из указателя значение по этому указателю
    int y = *(int *) p2; // добываем из указателя значение по этому указателю
    return x - y;
}

