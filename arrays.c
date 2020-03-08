#include "arrays.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void* memdup (const void* mem, size_t sizeByte) {
    void* out = NULL;
    if (0 < sizeByte) {
        if (mem) {
            out = malloc (sizeByte);
            if (NULL != out) {
                memcpy (out, mem, sizeByte);
            }
        }else{
            printf ("NUll Array pointer!");
        }
    } else {
        printf ("NUll Array!");
    }

    return out;
}

int *add_val_to_end_array (int *inArr, int arrSize, int val) {
    int *newArr = NULL;
    newArr = malloc (sizeof(int) * (arrSize + 1));
    if (newArr) {
        memcpy (newArr, inArr, sizeof(int) * arrSize);
        newArr [arrSize] = val;
    } else {
        printf ("Unable to accoc");
    }
    return newArr;
}

int *remove_int_from_arr (int *inArr, int arrSize, int delIndex) {
    int *newArr = NULL;
    if (delIndex < arrSize) {
        newArr = malloc (sizeof(int) * arrSize);
        memcpy (newArr, inArr, sizeof(int) * arrSize);
        int index = 0;
        for (index = delIndex; index < (arrSize - 1); index++) {
            newArr [index] = newArr [index + 1];
        }
    } else {
        printf ("arrSize: %d delIndex: %d", arrSize, delIndex);
    }
    return newArr;
}

int *generate_num_array (int n) {
    int *outArray = NULL;
    outArray = malloc (sizeof(int) * (n));
    for (int i = 0; i < n; i++) {
        outArray [i] = (i );
    }

    return outArray;
}

void print_curr_array (int *alphabet, int sizeOfAlphabet) {
    for (int i = 0; i < sizeOfAlphabet; i++) {
        printf ("[%d]", alphabet [i]);
    }
    printf ("\n");
}

