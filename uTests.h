#ifndef __UTESTS_H
#define __UTESTS_H

#include <stdint.h>

#include "utils.h"

#define TEST_UNIQ_DIAG_PATH_TASK 0
#define TEST_MIN_PATH_DIAG 1
#define TEST_UNIQ_PATH_TASK 0
#define TEST_UIO_COMB 0
#define TEST_YA_TASK 0

typedef enum {
    FINE = 0,
    LIST_REV_ERROR = 5,
    BIN_TREE_ERROR = 6,
    BIN_ARR_TREE_ERROR = 7,
    BIN_ARR_PARSE_TREE_ERROR = 8,
    UNIQ_PATH_ERROR = 9,
    CON_11_ERROR = 10,
    ONE_BIT_ERROR = 11,
    REV_BIT_ERROR = 12,
    MIN_PATH_ERROR = 13,
    UNIQ_PATH_DIAG_ERROR = 14,
    ARR_COMB_ERROR = 15,
    GRAY_ERROR = 16,
    MAX_BIT_VAL_ERROR = 17,
    LL_ERROR = 18,
    ALGO_ERROR = 19,
    MIN_PATH_DIAG_ERROR = 20,
    NUM_ERROR
} error_t;

int unitTest (void);

bool test_array_combinations (void);
bool test_ya_task (void);
bool test_uniq_path (void);
bool test_uniq_path_diag (void);
bool test_parse_bin_tree_init_array (void);
bool test_bin_tree_init_array (void);
bool test_bin_tree (void);
bool test_max_bit_val (void);
bool test_linked_list (void);
bool test_grey_conversation (void);
bool test_reverse_list (void);
bool test_float (void);
bool test_algo (void);

#endif /* __UTESTS_H */
