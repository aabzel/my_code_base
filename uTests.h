#ifndef __UTESTS_H
#define __UTESTS_H

#include <stdint.h>

#include "bin_search_tree.h"
#include "utils.h"

#define DEPLOY_DIF_SUB_STR_ERROR 0
#define TEST_STR_STR 0
#define TEST_UNIQ_DIAG_PATH_TASK 0
#define TEST_MIN_PATH_DIAG 0
#define TEST_MIN_DIAG_SCALE_SUMM 0
#define TEST_UNIQ_PATH_TASK 0
#define TEST_UIO_COMB 0
#define TEST_YA_TASK 0
#define TEST_HEAP_CON 0
#define TEST_HEAP_SAME 0
#define BIN_HEAP_RAND_ADD 0
#define DEPLOY_TEST_AVL_TREE 0
#define TEST_BIT_UTILS 1

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
    BIN_HEAP_RAND_ERROR = 30,
    BIN_HEAP_SAME_ERROR = 31,
    BIN_HEAP_DEL_ERROR = 32,
    IS_BIN_SEARCH_TREE_ERROR = 33,
    STRING_DELIM_ERROR = 34,
    STRING_CLEAN_ERROR = 35,
    STRING_SPLIT_ERROR = 36,
    ARR_HEAP_ERROR = 37,
    BIN_HEAP_INSERT_ERROR = 38,
    ARR_HEAP_GET_ERROR = 39,
    ARR_MIN_HEAP_ERROR = 40,
    ARR_HEAP_DELETE_VAL_ERROR = 41,
    ARR_MAX_HEAP_INSERT_ERROR = 42,
    ARR_MIN_BIN_HEAP_DELETE_VAL_ERROR = 43,
    SLIDING_WINDOW_MAX_ERROR = 45,
    AVL_TREE_ERROR = 46,
    DIF_SUB_STR_ERROR = 47,
    REV_STR_ERROR = 48,
    DETECT_CHANGE_ERROR = 49,
    FIFO_CAHR_ERROR = 50,
    STR_TO_INT_ERROR = 51,
    NUM_TO_BIN_STR_ERROR = 52,
    PARSE_BOOL_EXPRES_ERROR = 53,
    LIFO_CAHR_ERROR = 54,
    VALID_PARENTHESES_ERROR = 55,
    PARSE_NUM_OPE_ERROR = 56,
    PARSE_NUM_PAR_NEST_ERROR = 57,
    EXTRACT_OPE_ERROR = 58,
    PARSE_NOT_ERROR = 59,
    PARSE_AND_ERROR = 60,
    SINGLE_NUMBER_ERROR = 61,
    EXTRACT_MK_FILE_ERROR = 62,
    CHAR_REP_ERROR = 63,
    LIST_SORT_ERROR = 64,
    NUM_OF_ARGS_ERROR = 65,
    MAX_ENVELOPES_TEST_ERROR = 66,
    GENERATE_BIT_MASK_ERROR = 67,
    EXTRACT_BITS_ERROR = 68,
    FLOAR_TO_SAMPLE_ERROR = 69,
    SUB_STR_REPL_ERROR = 70,
    SUB_STR_CNT_ERROR = 71,
    CLEAN_TEXT_ERROR = 72,
    PARSE_UINT8_ERROR = 73,
    PARSE_UINT16_ERROR = 74,
    PARSE_UINT32_ERROR = 75,
    PARSE_VI_ERROR = 76,
    PARSE_MAC_ERROR = 77,
    PARSE_IP_ERROR = 79,
    PARSE_SERIAL_ERROR = 80,
    PARSE_HEX_ERROR = 81,
    PARSE_EXTRACT_SUB_ERROR = 82,
    SHA256_ERROR = 83,
    AES_ERROR = 84,
    ARRAY_ERROR = 85,
    EXTRACT_C_FILE_ERROR = 86,
    BIN_GAP_ERROR = 87,
    COMPARE_VERSION_ERROR = 88,
    BIN_PERIOD_ERROR = 89,
    ALGORITM_ERROR = 90,
    PERMUT_ERROR = 91,
    COMBINE_ERROR = 92,
    CONVERT_ERROR = 93,
    PARSE_PHY_ADDR_ERROR = 94,
    PARSE_PHY_REG_VALS_ERROR = 95,
    STR_OPS_ERROR = 96,
    TEST_MK_2_DOT_ERROR = 97,
    GENERATE_REG_PARSER_ERROR = 98,
    BIT_UTILS_ERROR = 99,
    ALGOTITHMS_ERROR = 100,
    AURIGA_TASK_ERROR = 101,
    STATIC_LOCAL_ERROR = 102,
    MATRIX_ACCSESS_ERROR = 103,
    BIN_UTILS_ERROR = 104,
    STACK_ERROR = 105,
    IS_MAP_ERROR = 106,
    DECODE_WAYS_ERROR = 107,
    MALLOC_SIZE_ERROR = 108,
    ENCODE_STRING_ERROR = 109,
    TEST_STACK_ERROR = 110,
    TEXT_ADDR_ERROR = 111,

    NUM_ERROR = 120
} utError_t;

int unit_test (void);

// bool test_sliding_window_max (void);
// bool test_max_bin_heap_insert (void);
// int test_heap_api (void);
bool test_split (void);
bool test_string_clean (void);
bool test_is_bin_tree (void);
bool test_bin_heap_rand_add_and_del_one (void);
// bool test_bin_heap (void);
// bool test_bin_heap_same_add (void);
// bool test_bin_heap_rand_add (void);
// bool test_bin_heap_dec_add (void);
// bool test_heap (void);
// int qselect (int *v, int len, int k);

bool test_valid_float_number (void);
bool test_stsstr (void);
// bool test_bin_heap_par_ind_arr (void);
bool test_array_combinations (void);
bool test_ya_task (void);
// bool test_uniq_path (void);
// bool test_uniq_path_diag (void);
// bool test_parse_bin_tree_init_array (void);
// bool test_bin_tree_init_array (void);
// bool test_bin_tree (void);
bool test_max_bit_val (void);
bool test_linked_list (void);
bool test_grey_conversation (void);
bool test_reverse_list (void);
bool test_float (void);

bool test_min_diag_scale_summ (void);
bool test_min_path_diag (void);
bool test_min_path (void);
// bool test_medianSlidingWindow (void);
// bool test_min_path_diag_atmospher (void);
bool test_find_min_diag_scale_summ (void);
bool test_find_min_diag_scale_summ2 (void);
bool test_delim_amount (void);
bool check_array (int *arr, int numsSize, int k);

void print_matrix_ji (void);
void print_matrix_ij (void);
bool test_print_matrix (void);

// bool test_bin_heap_delete (void);
// bool test_min_bin_heap_insert (void);
// bool test_bin_heap_insert (void);
// bool test_min_bin_heap_delete_val (void);
// bool test_bin_heap_remove (void);
// bool test_bin_heap_delete_val (void);
bool fill_up_heap_continuous_vals (BinaryHeap_t *binHeap, int maxVal, bool isMaxHeap);

void assemble_tree_from_array (TreeNode_t **root, int *arr, int arraySize);
void create_binary_search_tree (TreeNode_t **root, int how_many_elements);

#define EXPECT_EQ_STR(strL, strR)                                                                                      \
    do {                                                                                                               \
        if (0 != strcmp (strL, strR)) {                                                                                \
            printf ("\n%s:Line: %d %d in \nstrL: [%s] \nstrR: [%s] ", __FUNCTION__, __LINE__, __COUNTER__, strL,       \
                    strR);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_NE(val1, val2)                                                                                          \
    do {                                                                                                               \
        if (val1 == val2) {                                                                                            \
            printf ("\n%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                      \
            printf ("   val1: 0x%x val2: 0x%x  ", (int)val1, (int)val2);                                               \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_EQ(val1, val2)                                                                                          \
    do {                                                                                                               \
        if (val1 != val2) {                                                                                            \
            printf ("\n%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                      \
            printf ("   val1: 0x%x val2: 0x%x  ", (int)val1, (int)val2);                                               \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_HEX_EQ(val1, val2)                                                                                      \
    do {                                                                                                               \
        if (val1 != val2) {                                                                                            \
            printf ("\n%s:Line: %d %d in val1: %x val2: %x ", __FUNCTION__, __LINE__, __COUNTER__, (int)val1,          \
                    (int)val2);                                                                                        \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_TRUE(val)                                                                                               \
    do {                                                                                                               \
        if (true != ((bool)val)) {                                                                                     \
            printf ("\n%s:Line: %d in val %d ", __FUNCTION__, __LINE__, (int)val);                                     \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_FALSE(val)                                                                                              \
    do {                                                                                                               \
        if (false != val) {                                                                                            \
            printf ("\n%s:Line: %d val %d ", __FUNCTION__, __LINE__, (int)val);                                        \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#endif /* __UTESTS_H */
