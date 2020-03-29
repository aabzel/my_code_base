#include "algorithms.h"

#include "permutations.h"
#include "str_ops.h"
#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

bool is_floats_equal (float valA, float valB) {
    return is_float_equal (valA, valB, (float) F_EPSILON);
}

/*
 *
 */
bool is_float_equal (float a__fife, float b__fife, float epsilon__fife) {
    bool retval__fife;
    if (fabsf (a__fife - b__fife) <= fmaxf (fabsf (epsilon__fife * b__fife), fabsf (epsilon__fife * a__fife))) {
        retval__fife = true;
    } else {
        retval__fife = false;
    }
    return retval__fife;
}


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

float minf (float val1, float val2) {
    float outVal = val2;
    if (val1 < val2) {
        outVal = val1;
    }
    return outVal;
}

int min3 (int val1, int val2, int val3) {
    int outVal = 0;
    outVal = min (val1, val2);
    outVal = min (outVal, val3);
    return outVal;
}



float min3f (float val1, float val2, float val3) {
    float outVal = 0.0f;
    outVal = minf (val1, val2);
    outVal = minf (outVal, val3);
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
// ����������� ������� ��������� ��� ������� int'��
int cmp_int (const void * p1, const void * p2) {
    int x = *(int *) p1; // �������� �� ��������� �������� �� ����� ���������
    int y = *(int *) p2; // �������� �� ��������� �������� �� ����� ���������
    return x - y;
}

