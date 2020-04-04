#ifndef __UTESTS_H
#define __UTESTS_H

#include <stdint.h>

#include "utils.h"

#define TEST_STR_STR 0
#define TEST_UNIQ_DIAG_PATH_TASK 0
#define TEST_MIN_PATH_DIAG 0
#define TEST_MIN_DIAG_SCALE_SUMM 0
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
    STRCASESTR_ERROR = 21,
    MIN_PATH_DIAG_SCALE_ERROR = 22,
    FIND_MIN_PATH_DIAG_SCALE_ERROR = 23,
    FIND_MIN_PATH_DIAG_SCALE2_ERROR = 24,
    TRY_OPEN_KEEPASS_ERROR = 25,
    IS_STR_FALSE_ERROR = 26,
    MEDIAN_ERROR = 27,
    K_SMALL_ERROR = 28,
    BIN_HEAP_ERROR = 29,
    NUM_ERROR
} error_t;

int unitTest (void);

bool test_bin_heap (void);
bool test_heap (void);
int qselect (int *v, int len, int k);
bool test_k_smallest (void);
bool test_valid_float_number (void);
bool test_stsstr (void);
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
bool test_min_diag_scale_summ (void);
bool test_min_path_diag (void);
bool test_min_path (void);
bool test_medianSlidingWindow (void);
bool test_min_path_diag_atmospher (void);
bool test_find_min_diag_scale_summ (void);
bool test_find_min_diag_scale_summ2 (void);

#endif /* __UTESTS_H */
