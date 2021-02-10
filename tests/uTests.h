#ifndef __UTESTS_H
#define __UTESTS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#include <iostream>
#endif

#if 0
#include "bin_search_tree.h"
#include "utils.h"
#endif

bool unit_test (void);

size_t basename_start (const char *filename);
#define BASENAME() ((__FILE__ ":") + basename_start (__FILE__))

#ifdef __cplusplus
bool u_tests (void);
#endif

// bool test_sliding_window_max (void);
// bool test_max_bin_heap_insert (void);
// int test_heap_api (void);
bool test_split (void);
bool test_string_clean (void);
#if 0
bool test_is_bin_tree (void);
bool test_bin_heap_rand_add_and_del_one (void);
#endif

bool test_valid_float_number (void);
bool test_stsstr (void);
bool test_array_combinations (void);
bool test_ya_task (void);
bool test_max_bit_val (void);
bool test_linked_list (void);
bool test_grey_conversation (void);
bool test_reverse_list (void);
bool test_float (void);

bool test_min_diag_scale_summ (void);
bool test_min_path_diag (void);
bool test_min_path (void);
bool test_find_min_diag_scale_summ (void);
bool test_find_min_diag_scale_summ2 (void);
bool test_delim_amount (void);
bool check_array (int *arr, int numsSize, int k);

void print_matrix_ji (void);
void print_matrix_ij (void);
bool test_print_matrix (void);

#define EXPECT_EQ_STR_LEN(strL, strR, len)                                                                             \
    do {                                                                                                               \
        if (0 != strncmp (strL, strR, len)) {                                                                          \
            printf ("\n%s:Line: %d %d in \nstrL: [%s] \nstrR: [%s] ", __FUNCTION__, __LINE__, __COUNTER__, strL,       \
                    strR);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#ifdef __cplusplus
#define EXPECT_EQ_STR_CPP(strLc, strRc)                                                                                \
    do {                                                                                                               \
        string strL (strLc);                                                                                           \
        string strR (strRc);                                                                                           \
        if (0 != strL.compare (strR)) {                                                                                \
            cout << "[e] " << __FUNCTION__ << "() Line " << __LINE__ << " [" << strL << "] != [" << strR << "] "       \
                 << endl;                                                                                              \
            return false;                                                                                              \
        } else {                                                                                                       \
            /* cout << "OK!" << endl;*/                                                                                \
        }                                                                                                              \
    } while (0);

#define EXPECT_VEC_EQ(veca, vecb)                                                                                      \
    do {                                                                                                               \
        vector<int> vect_a = veca;                                                                                     \
        vector<int> vect_b = vecb;                                                                                     \
        if (vect_a != vect_b) {                                                                                        \
            cout << "[e] " << __FUNCTION__ << "() Line " << __LINE__ << "Different vectors" << endl;                   \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);
#endif

#define EXPECT_EQ_STR(strL, strR)                                                                                      \
    do {                                                                                                               \
        if (0 != strcmp (strL, strR)) {                                                                                \
            printf ("\n%s:Line: %d %d in \nstrL: [%s] \nstrR: [%s] ", __FUNCTION__, __LINE__, __COUNTER__, strL,       \
                    strR);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

#define EXPECT_EQ_MEM(memL, memR, len)                                                                                 \
    do {                                                                                                               \
        if (0 != memcmp (memL, memR, len)) {                                                                           \
            printf ("\n%s:Line: %d diffenent memory", __FUNCTION__, __LINE__);                                         \
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

#define EXPECT_NULL(val)                                                                                               \
    do {                                                                                                               \
        if (0 != val) {                                                                                                \
            printf ("\n%s():Line: %d in  val: %u ", __FUNCTION__, __LINE__, val);                                      \
            return val;                                                                                                \
        }                                                                                                              \
    } while (0);

#define EXPECT_EQ(vala, valb)                                                                                          \
    do {                                                                                                               \
        int val1 = vala;                                                                                               \
        int val2 = valb;                                                                                               \
        if (val1 != val2) {                                                                                            \
            printf ("\n%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                      \
            /*printf ("   val1: 0x%x val2: 0x%x  ", (int)val1, (int)val2);*/                                           \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
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

#define EXPECT_TRUE(val_in)                                                                                            \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
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
