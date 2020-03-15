#ifndef __ALGORITHMS_H
#define __ALGORITHMS_H

#include "linked_list.h"
#include "utils.h"

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

int uniquePaths (int xMax, int yMax);
int unique_paths (int m, int n);
int max (int val1, int val2);
int cmp_int (const void * p1, const void * p2);
void swap (char * const x, char * const y);

int *generate_num_array (int n);
char *generate_num_string (int n);

#endif /* __ALGORITHMS_H */
