#ifndef __UTILS_H
#define __UTILS_H

#include <stdint.h>

#define DEBUR_LET_POS 1
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 1

#define true (1u)
#define false (0u)
typedef uint8_t  bool;

extern char pemutationFile [100];
extern char kitFile [100];

void init_file_name (void);
// cur date string
char *generate_num_string (int n);
void print_array (int *alphabet, int sizeOfAlphabet, int k);
void print_curr_array (int *alphabet, int sizeOfAlphabet);
#endif /* __UTILS_H */
