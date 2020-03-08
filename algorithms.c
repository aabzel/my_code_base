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


// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int (const void * p1, const void * p2) {
    int x = *(int *) p1; // добываем из указателя значение по этому указателю
    int y = *(int *) p2; // добываем из указателя значение по этому указателю
    return x - y;
}

