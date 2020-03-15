#ifndef __UTESTS_H
#define __UTESTS_H

#include <stdint.h>

#include "utils.h"

typedef enum {
    FINE = 0,
    LIST_REV_ERROR = 5,
    BIN_TREE_ERROR = 6,
    BIN_ARR_TREE_ERROR = 7,
    BIN_ARR_PARSE_TREE_ERROR = 8,
    MAX_BIT_VAL_ERROR = 66,
    UNIQ_PATH_ERROR=9,
    GRAY_ERROR = 88,
    LL_ERROR = 99,
    NUM_ERROR
} error_t;

int unitTest (void);

bool test_uniq_path(void);
bool test_parse_bin_tree_init_array (void);
bool test_bin_tree_init_array (void);
bool test_bin_tree (void);
bool test_max_bit_val (void);
bool test_linked_list (void);
bool test_grey_conversation (void);
bool test_reverse_list (void);

#endif /* __UTESTS_H */
