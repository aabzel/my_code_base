#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUG_LET_POS 0
#define DEBUG_ARG 0

#define F_EPSILON 0.0005f

bool swap_int (int * const x, int * const y);

int qselect (int *v, int len, int k);
bool is_power_of_two (int x);

short compare (int Data1, int Data2);
int max (int val1, int val2);
int min (int val1, int val2);
int min3 (int val1, int val2, int val3);

void swap_char (char * const x, char * const y);
int partition (int *arr, int l, int r);
int qselect (int *v, int len, int k);
float minf (float val1, float val2);
float min3f (float val1, float val2, float val3);
bool is_floats_equal (float valA, float valB);
bool is_float_equal (float a__fife, float b__fife, float epsilon__fife);

int cmp_int (const void * p1, const void * p2);
void swap (char * const x, char * const y);
int *generate_num_array (int n);
char *generate_num_string (int n);

#endif /* __ALGORITHMS_H */
