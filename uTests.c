#include "uTests.h"

#include "algorithms.h"
#include "amount_of_uio_states.h"
#include "arrays.h"
#include "bin_heap.h"
#include "bin_heap_array.h"
#include "bin_search_tree.h"
#include "bin_tree.h"
#include "bin_tree_draw.h"
#include "combinations.h"
#include "linked_list.h"
#include "min_path.h"
#include "min_path_diag_scale.h"
#include "parse_keepass.h"
#include "permutations.h"
#include "slidingWindowMax.h"
#include "slidingWindowMid.h"
#include "str_ops.h"
#include "test_avl_tree.h"
#include "test_fifo_char.h"
#include "test_lifo_char.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int unitTest (void) {
    bool res = false;

    res = test_lifo ();
    if (false == res) {
        return LIFO_CAHR_ERROR;
    }

    res = test_Valid_Parentheses ();
    if (false == res) {
        return VALID_PARENTHESES_ERROR;
    }

    res = test_calc_paratasis_nesting ();
    if (false == res) {
        return PARSE_NUM_PAR_NEST_ERROR;
    }
#if 1
    res = test_parse_num_operands ();
    if (false == res) {
        return PARSE_NUM_OPE_ERROR;
    }
#endif

    res = test_fifo_char ();
    if (false == res) {
        return FIFO_CAHR_ERROR;
    }
#if 0
    res = test_parseBoolExpr ();
    if (false == res) {
        return PARSE_BOOL_EXPRES_ERROR;
    }
#endif
    res = test_num_to_bin_str ();
    if (false == res) {
        return NUM_TO_BIN_STR_ERROR;
    }
    // int ret = 0;
#if TEST_ATOI
    res = test_myAtoi ();
    if (false == res) {
        return STR_TO_INT_ERROR;
    }
#endif

#if 0
    res = test_reverse ();
    if (false == res) {
        return REV_STR_ERROR;
    }
    res = test_detect_change ();
    if (false == res) {
        return DETECT_CHANGE_ERROR;
    }
#endif

#if DEPLOY_DIF_SUB_STR_ERROR
    res = test_lengthOfLongestSubstring ();
    if (false == res) {
        return DIF_SUB_STR_ERROR;
    }
#endif

#if DEPLOY_TEST_AVL_TREE
    res = test_avl_tree ();
    if (false == res) {
        return AVL_TREE_ERROR;
    }
#endif

#if 0
    ret = test_heap_api ();
    if (ret) {
        return ret;
    }

    res = test_delim_amount ();
    if (false == res) {
        return STRING_DELIM_ERROR;
    }

    res = test_string_clean ();
    if (false == res) {
        return STRING_CLEAN_ERROR;
    }
#endif

#if DEBUG_MAIL
    res = test_split ();
    if (false == res) {
        return STRING_SPLIT_ERROR;
    }
#endif

#if 0
    res = test_sliding_window_max ();
    if (false == res) {
        return SLIDING_WINDOW_MAX_ERROR;
    }

    res = test_is_bin_tree ();
    if (false == res) {
        return IS_BIN_SEARCH_TREE_ERROR;
    }
#endif

#if TEST_HEAP_DELET_ONE
    res = test_bin_heap_rand_add_and_del_one ();
    if (false == res) {
        return BIN_HEAP_DEL_ERROR;
    }
#endif

#if TEST_HEAP_DELET
    res = test_bin_heap_delete ();
    if (false == res) {
        return BIN_HEAP_DEL_ERROR;
    }
#endif

#if TEST_HEAP_SAME
    res = test_bin_heap_same_add ();
    if (false == res) {
        return BIN_HEAP_SAME_ERROR;
    }
#endif

#if TEST_HEAP_CON
    res = test_bin_heap_dec_add ();
    if (false == res) {
        return BIN_HEAP_ERROR;
    }
#endif

#if BIN_HEAP_RAND_ADD
    res = test_bin_heap_rand_add ();
    if (false == res) {
        return BIN_HEAP_RAND_ERROR;
    }
#endif

#if TEST_HEAP_MEM
    test_heap ();
#endif

#if 0
    res = test_algo ();
    if (false == res) {
        return ALGO_ERROR;
    }

    res = test_k_smallest ();
    if (false == res) {
        return K_SMALL_ERROR;
    }

    res = test_medianSlidingWindow ();
    if (false == res) {
        return MEDIAN_ERROR;
    }
#endif

#if 0
    res = test_valid_float_number ();
    if (false == res) {
        return IS_STR_FALSE_ERROR;
    }
#endif
#if TEST_KDBX
    res = try_to_open_kdbx_file ();
    if (false == res) {
        return TRY_OPEN_KEEPASS_ERROR;
    }
#endif

#if TEST_STR_STR
    res = test_stsstr ();
    if (false == res) {
        return STRCASESTR_ERROR;
    }
#endif

#if TEST_MIN_PATH
    res = test_min_path ();
    if (false == res) {
        return MIN_PATH_ERROR;
    }
#endif

#if TEST_MIN_PATH_DIAG
    res = test_min_path_diag ();
    if (false == res) {
        return MIN_PATH_DIAG_ERROR;
    }
#endif

#if TEST_MIN_DIAG_SCALE_SUMM
    res = test_min_diag_scale_summ ();
    if (false == res) {
        return MIN_PATH_DIAG_SCALE_ERROR;
    }
#endif

#if TEST_FIND_MIN_DIAG_SCALE_SUMM
    res = test_find_min_diag_scale_summ ();
    if (false == res) {
        return FIND_MIN_PATH_DIAG_SCALE_ERROR;
    }
    res = test_find_min_diag_scale_summ2 ();
    if (false == res) {
        return FIND_MIN_PATH_DIAG_SCALE2_ERROR;
    }
#endif

#if TEST_FLOAT
    res = test_float ();
#endif

#if TEST_UIO_COMB
    res = save_the_amount_of_uio ();
#endif

#if TEST_BIT_UTILS
    uint32_t n;
    n = reverseBits (0x00000001);
    if (0x80000000 != n) {
        return REV_BIT_ERROR;
    }
    n = reverseBits (0x0000000F);
    if (0xF0000000 != n) {
        return REV_BIT_ERROR;
    }

    uint8_t numSetBit = hamming_weight (56);
    if (3 != numSetBit) {
        return ONE_BIT_ERROR;
    }
    printf ("\n numSetBit:%d\n", numSetBit);

    test_heap ();

    char intStr[] = "ABCD";
    char *outStr = NULL;
    int *outArray;
    int cmpRes;

#endif

#if TEST_ARR_COMB
    res = test_array_combinations ();
    if (false == res) {
        return ARR_COMB_ERROR;
    }
#endif

#if TEST_YA_TASK
    res = test_ya_task ();
    if (false == res) {
        return CON_11_ERROR;
    }
#endif

#if TEST_UNIQ_DIAG_PATH_TASK
    res = test_uniq_path_diag ();
    if (false == res) {
        return UNIQ_PATH_DIAG_ERROR;
    } else {
        printf ("\ntest_uniq_path fine!\n");
    }
#endif

#if TEST_UNIQ_PATH_TASK
    res = test_uniq_path ();
    if (false == res) {
        return UNIQ_PATH_ERROR;
    } else {
        printf ("\ntest_uniq_path fine!\n");
    }
#endif

#if DEPLOY_REMAINED_TESTS
    res = test_parse_bin_tree_init_array ();
    if (false == res) {
        return BIN_ARR_PARSE_TREE_ERROR;
    }

    res = test_bin_tree_init_array ();
    if (false == res) {
        return BIN_ARR_TREE_ERROR;
    }

    res = test_bin_tree ();
    if (false == res) {
        return BIN_TREE_ERROR;
    }

    res = test_reverse_list ();
    if (false == res) {
        return LIST_REV_ERROR;
    }

    res = test_max_bit_val ();
    if (false == res) {
        return MAX_BIT_VAL_ERROR;
    } else {
        printf ("\ntest_max_bit_val fine!\n");
    }

    res = test_grey_conversation ();
    if (false == res) {
        return GRAY_ERROR;
    }

    int arr1[] = {1, 2};
    int arr2[] = {2, 1};
    res = is_permutation (arr1, arr2, 2);
    if (false == res) {
        return 11;
    }

    int arra1[] = {1, 2, 5};
    int arra2[] = {2, 1, 6};
    res = is_permutation (arra1, arra2, 3);
    if (true == res) {
        return 12;
    }

    outArray = generate_num_array (4);
    if (NULL != outArray) {
        if (0 != outArray[0]) {
            return 1;
        }
        if (1 != outArray[1]) {
            return 2;
        }
        if (2 != outArray[2]) {
            return 3;
        }
        if (3 != outArray[3]) {
            return 4;
        }
        free (outArray);
    }

    strcpy (intStr, "ABCD");
    outStr = removeCharFromString (intStr, 1);
#if DEBUG_UTEST
    printf ("in %s -%d out %s", intStr, 1, outStr);
#endif
    cmpRes = strcmp (outStr, "ACD");
    if (0 != cmpRes) {
        printf ("error intStr %s outStr %s", intStr, outStr);
        free (outStr);
        return 12;
    }

    strcpy (intStr, "ABCD");
    outStr = removeCharFromString (intStr, 0);
#if DEBUG_UTEST
    printf ("in %s -%d out %s", intStr, 0, outStr);
#endif
    cmpRes = strcmp (outStr, "BCD");
    free (outStr);
    if (0 != cmpRes) {
        printf ("error %s", outStr);
        return 22;
    }

    outStr = generate_num_string (4);
    if (NULL != outStr) {
        cmpRes = strcmp (outStr, "0123");
        free (outStr);
        if (0 != cmpRes) {
            return 33;
        }

    } else {
        return 35;
    }

    strcpy (intStr, "ABCD");
    outStr = removeCharFromString (intStr, 5);
#if DEBUG_UTEST
    printf ("in %s -%d out %s", intStr, 5, outStr);
    printf ("\n");
#endif
    free (outStr);

    res = test_linked_list ();
    if (false == res) {
        return LL_ERROR;
    }
#endif

    return FINE;
}

int test_heap_api (void) {
    bool res = false;

    res = test_bin_heap_par_ind_arr ();
    if (false == res) {
        return ARR_HEAP_ERROR;
    }

    res = test_min_bin_heap_delete_val ();
    if (false == res) {
        return ARR_MIN_BIN_HEAP_DELETE_VAL_ERROR;
    }

    res = test_bin_heap_delete_val ();
    if (false == res) {
        return ARR_HEAP_DELETE_VAL_ERROR;
    }

    res = test_max_bin_heap_insert ();
    if (false == res) {
        return ARR_MAX_HEAP_INSERT_ERROR;
    }

    res = test_min_bin_heap_insert ();
    if (false == res) {
        return ARR_MIN_HEAP_ERROR;
    }

    res = test_bin_heap_remove ();
    if (false == res) {
        return ARR_HEAP_GET_ERROR;
    }

    return FINE;
}

bool test_max_bit_val (void) {
    bool res = true;
    uint32_t maxVal = 0;
    maxVal = max_val (1);
    if (1 != maxVal) {
        res = false;
    }

    maxVal = max_val (2);
    if (3 != maxVal) {
        res = false;
    }
    maxVal = max_val (3);
    if (7 != maxVal) {
        res = false;
    }
    maxVal = max_val (4);
    if (15 != maxVal) {
        res = false;
    }

    res = false;
    int returnSize = 0;
    int *arr = grayCode (2, &returnSize);
    if (arr) {
        if (4 == returnSize) {
            if (0 == arr[0]) {
                if (3 == arr[2]) {
                    res = true;
                }
            }
        }
        free (arr);
    }

    return res;
}

bool test_grey_conversation (void) {
    bool res = true;
    if (0 != bin_to_gray (0)) {
        res = false;
    }
    if (1 != bin_to_gray (1)) {
        res = false;
    }
    if (3 != bin_to_gray (2)) {
        res = false;
    }
    if (2 != bin_to_gray (3)) {
        res = false;
    }
    return res;
}

bool test_linked_list (void) {
    bool res = true;
    list_node_t *llHead = NULL;
    int numOfElen = 0;
    int array1[] = {1, 2, 3, 4};
    int array2[] = {1, 2, 3, 4, 5, 6};
    res = linked_list_add_array (&llHead, array1, 4);
    if (true == res) {
        numOfElen = list_num_of_elements (llHead);
        if (1 != numOfElen) {
            printf ("List Num Error %d\n", numOfElen);
            res = false;
        }
    } else {
        printf ("List Add1 Error\n");
    }

    res = linked_list_add_array (&llHead, array2, 6);
    if (true == res) {
        numOfElen = list_num_of_elements (llHead);
        if (2 != numOfElen) {
            printf ("List Num Error %d\n", numOfElen);
            res = false;
        }
    } else {
        printf ("List Add2 Error\n");
    }
#if DEBUG_LL
    print_list (llHead);
#endif

    res = linked_list_deinit (llHead);
    if (false == res) {
        printf ("List Deinit Error\n");
    }

    return res;
}
#if 0
bool test_parse_bin_tree_init_array (void) {
    bool res = true;
    int array [] =
        { 1, 2, 3, 4, 5, NOT_NUM, 6, 7, NOT_NUM, NOT_NUM, NOT_NUM, NOT_NUM, 8 };
    int sizeOfArray = sizeof(array) / sizeof(array [0]);
    parse_bin_tree (array, sizeOfArray);

    return res;
}
#endif

#if 0
bool test_bin_tree_init_array (void) {
    bool res = false;
    TreeNode_t * root = NULL;

    int parentNode = 0;

    parentNode = get_parent_index (1, 100);
    if (0 != parentNode) {
        return false;
    }
    parentNode = get_parent_index (3, 100);
    if (1 != parentNode) {
        return false;
    }

    parentNode = get_parent_index (8, 100);
    if (3 != parentNode) {
        return false;
    }

    parentNode = get_parent_index (12, 100);
    if (5 != parentNode) {
        return false;
    }

    parentNode = get_parent_index (13, 100);
    if (6 != parentNode) {
        return false;
    }

    int array [8] =
        { 1, 2, 3, 4, 5, 6, 7, 8 };
    int sizeOfArray = sizeof(array) / sizeof(array [0]);
    assemble_tree_from_array (&root, array, sizeOfArray);
    res = print_tree_to_file (root, "array_tree.txt");
    return res;
}
#endif

bool test_bin_tree (void) {
    TreeNode_t *root = NULL;
    bool res = false;
    int sumOfLeaves = 0;
    create_binary_search_tree (&root, 10);
    if (NULL != root) {
        int depth = max_depth (root);
        printf ("\ndepth:%d\n", depth);
        sumOfLeaves = deepestLeavesSum (root);
        printf ("\n SumOfLeaves:%d\n", sumOfLeaves);
        res = print_tree_to_file (root, "rand_tree.txt");
    }
    return res;
}

bool test_reverse_list (void) {
    bool res = false;
    ListNode *head = NULL;
    ListNode *revhead = NULL;

    list_add_node_front (&head, 1);
    list_add_node_front (&head, 2);
    list_add_node_front (&head, 3);
    list_add_node_front (&head, 4);

    show_list (head);

    revhead = reverseList (head);

    show_list (revhead);

    reverse_rec (&revhead);

    show_list (revhead);

    if (NULL != revhead) {
        res = true;
    }

    return res;
}

bool test_uniq_path (void) {
    int numPath;

    numPath = uniquePaths (2, 2);
    if (2 != numPath) {
        return false;
    }
    printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
    numPath = uniquePaths (3, 2);
    if (3 != numPath) {
        return false;
    }

    numPath = uniquePaths (38, 10);
    if (1101716330 != numPath) {
        printf ("\n wrong numPath %d\n", numPath);
        return false;
    }

    numPath = uniquePaths (7, 3);
    if (28 != numPath) {
        printf ("\n wrong numPath %d\n", numPath);
        return false;
    }

    numPath = uniquePaths (51, 9);
    if (1916797311 != numPath) {
        printf ("\nnumPath 51 9  %d\n", numPath);
        return false;
    }

    return true;
}

bool test_uniq_path_diag (void) {
    bool res = false;
    int numPath;
    numPath = uniquePathDiag (2, 2);
    if (3 == numPath) {
        printf ("\n exp %d real %d", 3, numPath);
        res = true;
    }
    numPath = uniquePathDiag (2, 3);
    if (5 != numPath) {
        printf ("\n exp %d real %d", 5, numPath);
        return false;
    }

    numPath = uniquePathDiag (3, 2);
    if (5 != numPath) {
        printf ("\n exp %d real %d", 5, numPath);
        return false;
    }
    numPath = uniquePathDiag (3, 3);
    if (13 != numPath) {
        printf ("\n 3x3 exp %d real %d", 13, numPath);
        return false;
    }
    numPath = uniquePathDiag (3, 4);
    if (25 != numPath) {
        printf ("\n 3x4 exp %d real %d", 25, numPath);
        return false;
    }
    numPath = uniquePathDiag (6, 6);

    numPath = uniquePathDiag (7, 7);
    // printf ("\n 6x6 numPath = %d", numPath);

    return res;
}

bool test_ya_task (void) {
    bool res = false;
    int sizeOfArr = 0;
    int numOnes = 0;
    int arr[] = {0, 1, 1, 0, 1, 1, 0};
    sizeOfArr = sizeof (arr) / sizeof (arr[0]);

    numOnes = findMaxConsecutiveOnesFlip1 (arr, sizeOfArr);
    printf ("\n findMaxConsecutiveOnesFlip1: %d\n", numOnes);

    numOnes = findMaxConOnesDel1 (arr, sizeOfArr);
    printf ("\n findMaxConsecutiveOnesFlip1_: %d\n", numOnes);

    numOnes = findMaxConsecutiveOnes (arr, sizeOfArr);
    if (2 != numOnes) {
        return false;
    }

    res = is_single_zero (arr, sizeOfArr, 6);
    if (false == res) {
        printf ("\n unspot single zero 6");
        return false;
    }

    res = is_single_zero (arr, sizeOfArr, 0);
    if (false == res) {
        printf ("\n unspot single zero 0");
        return false;
    }

    res = is_single_zero (arr, sizeOfArr, 3);
    if (false == res) {
        printf ("\n unspot single zero 3");
        return false;
    }

    numOnes = count_max_amout_of_one_after_del (arr, sizeOfArr);
    if (4 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    numOnes = findMaxConOnesDel1 (arr, sizeOfArr);
    if (4 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    int arr2[] = {0, 1, 1, 1, 1, 1, 0};
    sizeOfArr = sizeof (arr2) / sizeof (arr2[0]);
    numOnes = count_max_amout_of_one_after_del (arr2, sizeOfArr);
    if (5 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    numOnes = findMaxConOnesDel1 (arr2, sizeOfArr);
    if (5 == numOnes) {
        res = true;
    } else {
        printf ("\n num of error ones %d", numOnes);
    }

    return res;
}

bool test_array_combinations (void) {
    bool res = false;
    int arr[] = {1, 2, 3};
    int arrSize = sizeof (arr) / sizeof (arr[0]);
    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **arrayOfArr = NULL;
    arrayOfArr = subsets (arr, arrSize, &returnSize, &returnColumnSizes);
    if (7 == returnSize) {
        res = true;
    }
    print_array_of_diff_arrays (arrayOfArr, returnSize, returnColumnSizes);

    return res;
}

void print_bytes (uint32_t byte) {
    float kByte = 4;
    float MByte = 4;
    float GByte = 4;
    kByte = (float)byte / 1024.0f;
    MByte = (float)kByte / 1024.0f;
    GByte = (float)MByte / 1024.0f;
    printf ("\nmax Available heap size [%u] byte [%f] k_Byte [%f] M_Byte [%f] G_Byte\n", byte, kByte, MByte, GByte);
}

bool test_heap (void) {
    uint32_t byte = 3;
    uint32_t mult = 10;
    uint32_t div = 2;
    while (1) {
        char *ptr = NULL;
        ptr = (char *)malloc (byte);
        if (ptr) {
            byte = (byte * mult) / div;
            // print_bytes (byte);
            free (ptr);
        } else {
            break;
        }
    } //[2327387742]
    print_bytes (byte);

    return true;
}

void test_combine (void) {
    // combine (4, 2);
}

bool test_algo (void) {
    int min3val;
    min3val = min3 (2, 3, 5);
    if (2 != min3val) {
        return false;
    }
    min3val = min3 (42, 33, 75);
    if (33 != min3val) {
        return false;
    }
    min3val = min3 (42, 533, 5);
    if (5 != min3val) {
        return false;
    }

    return true;
}

bool test_stsstr (void) {
    char text[100];
    char pattern[100];
    char *nullPtr = NULL;
    const char *resPtr;

    strcpy (text, "uArT_BaYpass tExt to uart");
    strcpy (pattern, "");
    resPtr = str_case_str (text, pattern);
    if (NULL == resPtr) {
        printf ("\nDid not spot\n");
        return false;
    }

    strcpy (text, "uArT_BaYpass tExt to uart");
    strcpy (pattern, "bAy");
    resPtr = str_case_str (text, pattern);
    if (NULL == resPtr) {
        printf ("\nDid not spot\n");
        return false;
    }
    printf ("\n[%s] [%s]\n", text, pattern);

    strcpy (pattern, "paTtern");
    resPtr = str_case_str (text, pattern);
    if (NULL != resPtr) {
        printf ("\nfalse spot\n");
        return false;
    }
    printf ("\n[%s] [%s]\n", text, pattern);

    resPtr = str_case_str (text, nullPtr);
    if (NULL != resPtr) {
        printf ("\nfalse spot pattern NULL\n");
        return false;
    }
    printf ("\n[%s] [%s]\n", text, pattern);

    resPtr = str_case_str (nullPtr, text);
    if (NULL != resPtr) {
        printf ("\nfalse spot text NULL\n");
        return false;
    }
    printf ("\n[%s] [%s]\n", text, pattern);
    return true;
}

bool test_float (void) {
    bool res = true;
    float val = 3.25f;
    print_bit_representation (val);
    print_bit_representation (0.15625f);

    return res;
}

bool test_min_path (void) {
    bool res = false;
    int grid[3][3] = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathSum ((int *)grid, numOfLine, numOfcolomn);
    if (7 == minSum) {
        res = true;
    } else {
        return false;
    }

    // save_array_as_dot ("map1.dot", (int *) grid, 3, 3);

    // minPath ((int *) grid, sizeOfGrid, gridColSize);
    int grid2[10][10];
    numOfLine = 10;
    numOfcolomn = 10;
    init_ramp_map ((int *)grid2, numOfLine, numOfcolomn);
    // init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    // minSum = minPathSum ((int *) grid2, 10, 10);
    // save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    minPath ((int *)grid2, numOfLine, numOfcolomn);

    return res;
}

bool test_min_path_diag_atmospher (void) {
    bool res = false;

    int grid5[5][5] = {
        {1, 1, 1, 999, 999}, {1, 1, 1, 999, 999}, {1, 1, 1, 999, 999}, {1, 1, 1, 999, 999}, {1, 1, 1, 999, 999}};
    res = minPathDiag ((int *)grid5, 5, 5);

    return res;
}

bool test_min_path_diag (void) {
    bool res = false;
    int grid[3][3] = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathDiagSum ((int *)grid, numOfLine, numOfcolomn);
    if (5 == minSum) {
        res = true;
    } else {
        return false;
    }
#define TEST_DIM 3
    int grid1[TEST_DIM][TEST_DIM];
    res = init_one_map ((int *)grid1, TEST_DIM, TEST_DIM);
    minSum = minPathDiagSum ((int *)grid1, TEST_DIM, TEST_DIM);
    if (TEST_DIM == minSum) {
        res = true;
    } else {
        return false;
    }

#define TEST_DIM2 8
    int grid2[TEST_DIM2][TEST_DIM2];
    // init_rod_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    // init_rand_array((int *) grid2, TEST_DIM2, TEST_DIM2);
    // init_box_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    init_ramp_map ((int *)grid2, TEST_DIM2, TEST_DIM2);
    minPathDiag ((int *)grid2, TEST_DIM2, TEST_DIM2);
    // int grid2 [10] [10];
    // numOfLine = 10;
    // numOfcolomn = 10;
    // init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    // init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    // minSum = minPathSum ((int *) grid2, 10, 10);
    // save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    // minPath ((int *) grid2, numOfLine, numOfcolomn);
#if TEST_3_3
    int grid3[3][3] = {{1, 93, 9}, {1, 95, 9}, {4, 2, 9}};
    minPathDiag ((int *)grid3, 3, 3);
#endif

    res = test_min_path_diag_atmospher ();
    if (false == res) {
        return false;
    }
    return res;
}

bool test_min_diag_scale_summ (void) {
    bool res = false;
    int grid[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    float totalSum = minPathDiagScaleSum ((int *)grid, 3, 3);
    if (is_floats_equal (totalSum, 2.828f)) {
        res = true;
    } else {
        printf ("\n totalSum %f \n", totalSum);
    }
    return res;
}

bool test_find_min_diag_scale_summ2 (void) {
    bool res = false;
#define TEST_ARR_DIM2 7
    int grid[TEST_ARR_DIM2][TEST_ARR_DIM2];
    init_ramp_map ((int *)grid, TEST_ARR_DIM2, TEST_ARR_DIM2);
    res = minPathDiagScale ((int *)grid, TEST_ARR_DIM2, TEST_ARR_DIM2);
    if (true == res) {
        res = true;
    }
    return res;
}

bool test_find_min_diag_scale_summ (void) {
    bool res = false;
    int grid[5][5] = {{1, 1, 100, 100, 100},
                      {1, 1, 100, 100, 100},
                      {1, 1, 100, 100, 100},
                      {1, 1, 100, 100, 100},
                      {1, 1, 100, 100, 100}};
    res = minPathDiagScale ((int *)grid, 5, 5);
    if (true == res) {
        res = true;
    }
    return res;
}

bool test_valid_float_number (void) {
    bool res;
    char string[100];

#if 1

    strcpy (string, " 4e3.");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "53K");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".1.");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "3. ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "0..");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "3.");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "078332e437");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".2e81");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "1  ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".  ");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, ".1");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "0");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "1 ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, "0e");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }
#endif

    strcpy (string, "1 4");
    res = isNumber (string);
    if (true == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    strcpy (string, " 0.1 ");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }
    strcpy (string, "2e10");
    res = isNumber (string);
    if (false == res) {
        printf ("\n error [%s]", string);
        return false;
    }

    return true;
}

bool test_k_smallest (void) {
    int numsSize;
    int val;
    int arr1[] = {1, 3, -1};
    numsSize = sizeof (arr1) / sizeof (arr1[0]);

    val = qselect (arr1, numsSize, 1);
    if (1 != val) {
        return false;
    }
    int arr2[] = {3, -1, -3};
    numsSize = sizeof (arr2) / sizeof (arr2[0]);
    val = qselect (arr2, numsSize, 1);
    if (-1 != val) {
        return false;
    }
    int arr3[] = {-1, -3, 5};
    numsSize = sizeof (arr3) / sizeof (arr2[0]);

    val = qselect (arr3, numsSize, 1);
    if (-1 != val) {
        return false;
    }

    return true;
}

bool test_medianSlidingWindow (void) {
    bool res = false;

    int arr100[] = {
        16807,     282475249, 622650073, 984943658, 144108930, 470211272, 101027544, 457850878, 458777923, 7237709,
        823564440, 115438165, 784484492, 74243042,  114807987, 137522503, 441282327, 16531729,  823378840, 143542612,
        896544303, 474833169, 264817709, 998097157, 817129560, 131570933, 197493099, 404280278, 893351816, 505795335,
        954899097, 636807826, 563613512, 101929267, 580723810, 704877633, 358580979, 624379149, 128236579, 784558821,
        530511967, 110010672, 551901393, 617819336, 399125485, 156091745, 356425228, 899894091, 585640194, 937186357,
        646035001, 25921153,  510616708, 590357944, 771515668, 357571490, 44788124,  927702196, 952509530, 130060903,
        942727722, 83454666,  108728549, 685118024, 118797801, 60806853,  571540977, 194847408, 35308228,  158374933,
        75260298,  824938981, 595028635, 962408013, 137623865, 997389814, 20739063,  107554536, 635339425, 654001669,
        777724115, 269220094, 34075629,  478446501, 864546517, 351934195, 581030105, 557810404, 146319451, 908194298,
        500782188, 657821123, 753799505, 102246882, 269406752, 816731566, 884936716, 807130337, 578354438, 892053144,
        153851501, 4844897,   616783871, 382955828, 330111137, 227619358, 723153177, 70982397,  147722294, 70477904,
        51621609,  606946231, 190959745, 912844175, 341853635, 808266298, 343098142, 456880399, 534827968, 280090412,
        195400260, 589673557, 6441594,   889688008, 57716395,  524325968, 14119113,  515204530, 388471006, 681910962,
        904797942, 400285365, 322842082, 463179852, 828530767, 832633821, 73185695,  316824712, 260973671, 815859901,
        267248590, 51724831,  194314738, 318153057, 111631616, 877819790, 304555640, 213110679, 541437335, 49077006,
        996497972, 63936098,  270649095, 428975319, 685583454, 351345223, 272112289, 398556760, 334948905, 724586126,
        532236123, 23129506,  836045813, 436476770, 60935238,  936329094, 915896220, 304987844, 34712366,  881140534,
        281725226, 901915394, 197941363, 348318738, 152607844, 784559590, 543436550, 290145159, 681808623, 977764947,
        750597385, 971307217, 737195272, 755539,    399399247, 462242385, 459413496, 951894885, 537140623, 848682420,
        12028144,  86531968,  289335735, 755699915, 623161625, 992663534, 43046042,  358796011, 943454679, 771024152,
        479575244, 507977295, 119878818, 49590396,  828087692, 621301815, 154112991, 104740033, 222122669, 889119397,
        238489553, 882410547, 944975825, 567121210, 866729662, 536830211, 719533808, 517273377, 592822761, 41000625,
        902737335, 127401868, 994977995, 140002776, 532062767, 49997439,  433829874, 464689331, 428540556, 968456301,
        859468872, 911300560, 168120094, 298918984, 967113755, 124639789, 462851407, 957828015, 678030193, 105222769,
        893015680, 944303455, 4016855,   732267506, 784170963, 454233502, 145586676, 329863108, 353963249, 323602331,
        1277844,   1887638,   660760808, 561939997, 685428651, 897054849, 465645203, 461495731, 440796531, 796198014,
        522395419, 779636775, 203042009, 175530180, 640687929, 351995223, 459244054, 458588260, 174076737, 834991545,
        44747317,  34837525,  837204200, 578134256, 486421564, 609960597, 668306648, 683337704, 907225550, 605925150,
        416541976, 24301412,  411938554, 111482797, 524102504, 760348381, 293034748, 855007065, 290659378, 379847699,
        778878209, 338725129, 121578553, 552265483, 501650447, 218264607, 471180773, 363045322, 494664305, 706755176,
        495170053, 616927224, 437784630, 360280366, 121205400, 284660444, 487495370, 684570285, 502883016, 252193898,
        637608155, 129841133, 189515557, 262696576, 707953178, 509658266, 307187357, 347221711, 42227878,  847320614,
        746474819, 195795737, 586983133, 678620591, 290623720, 135048762, 667306633, 262976197, 112576031, 925238588,
        555860589, 795054873, 843998877, 959637304, 21979358,  832861200, 599777254, 168068960, 794014915, 545293947,
        442645480, 452207730, 103669955, 564674546, 547837107, 28841238,  989340000, 18984926,  690545035, 988774857,
        110561113, 420250114, 862929593, 300601360, 118498354, 322968418, 439025357, 738342585, 163313729, 122721015,
        780776563, 32106102,  588860917, 380786643, 172819419, 971062967, 572547747, 83245269,  529855395, 812423303,
        490404473, 978719103, 754711748, 47424385,  345205658, 518163459, 520045406, 937673930, 250739824, 614285132,
        129300973, 493959603, 600246897, 618907920, 367603950, 9135231,   64488480,  171620203, 350213900, 939824520,
        681462533, 603481258, 937217003, 13618676,  255820950, 113423934, 143558780, 168279879, 836941832, 463482574,
        828433549, 346174542, 415306249, 523252771, 156766310, 601915879, 752200983, 798669970, 473392040, 666082723,
        20073650,  222902971, 118753229, 666190318, 473917746, 118710299, 151687230, 344185621, 554270776, 637850124,
        108668244, 26076958,  981747696, 116666771, 958829064, 322791560, 614056598, 790318751, 493869940, 240764503,
        462789551, 711192801, 123427205, 119315080, 164780418, 3559274,   838659649, 63040413,  810783320, 51519025,
        237322012, 586901783, 458854788, 151624117, 76424008,  263081550, 90265324,  404319195, 754451257, 318824511,
        304835690, 270438666, 187262410, 48760593,  766490553, 799809565, 92190960,  556228742, 540151403, 911254352,
        746007307, 928256141, 525244910, 633413200, 492192799, 970343127, 566120171, 429157787, 250334414, 450031625,
        244116641, 174619517, 13055348,  377901842, 287114315, 927515974, 177181445, 476211373, 805972220, 795739911,
        265509239, 90245054,  63641305,  172556929, 61382253,  652354189, 5815166,   537204356, 772359304, 651659860,
        73645898,  609005592, 442901720, 463866116, 625151580, 78098867,  495149352, 476026939, 208178698, 401494901,
        324160811, 797716616, 482756891, 501848671, 402331728, 356326671, 597951661, 343077045, 102303120, 421620240,
        268317158, 38299453,  39769627,  333685350, 962853711, 38535563,  274629594, 550207533, 66401727,  115307827,
        948398795, 114919531, 657737442, 140351516, 950885006, 98478515,  4466924,   706642601, 957627097, 596168661,
        440967103, 368034324, 799980108, 18044936,  72002281,  547517015, 151043710, 265963216, 130301905, 343775973,
        111767781, 225882720, 807270791, 791481169, 910297865, 702715827, 532329536, 238616728, 872357125, 628320384,
        796580167, 502789949, 835500476, 8416046,   300521576, 777568666, 158577467, 977260520, 862627384, 516341991,
        178425210, 905333258, 14428211,  622268744, 225419518, 464685718, 722321934, 132666825, 436280767, 854658689,
        523449818, 528073014, 566211825, 822102918, 173958028, 987333029, 500078034, 708006727, 55151240,  6933754,
        571486540, 427408396, 913090935, 401203083, 69048048,  287846865, 709087011, 31615252,  367553064, 301377876,
        137017237, 746232675, 628070245, 94482710,  773470415, 791728192, 560024710, 707454747, 722463037, 356701299,
        97368447,  88949715,  329241693, 647259579, 132567129, 115195164, 995333979, 473553501, 439295525, 191110289,
        502574958, 517114033, 62211800,  562165089, 528087670, 812535217, 430880846, 499521038, 936509543, 8240338,
        849385936, 98603321,  954597719, 73536496,  124791247, 67943788,  617428359, 270425987, 767145035, 707765235,
        498383912, 152185684, 924745989, 866683784, 120263734, 76422667,  826500519, 862972615, 669167045, 318665976,
        142326661, 373365825, 5182819,   1271631,   483422903, 751072698, 162936798, 230092639, 341914004, 29909503,
        763800679, 333748765, 88207391,  737904107, 236264924, 207314365, 114057121, 48114454,  205777106, 840127450,
        110051703, 448530832, 583071032, 499932141, 48961654,  412281977, 440942217, 742753900, 142357289, 302173465,
        978084747, 476003622, 816289879, 258459317, 359301516, 56564048,  484182762, 637121029, 532649039, 166052708,
        266605903, 987502657, 996510761, 924375752, 86561466,  785108621, 974044557, 292006996, 554426955, 115266930,
        54021494,  346645555, 96192221,  233429312, 586802293, 141231427, 500142232, 432477444, 209234791, 178402198,
        311549152, 434444856, 63273570,  227464303, 264627439, 947712914, 324735799, 78626766,  570591835, 67981921,
        110846043, 121122752, 688574086, 75289719,  526439150, 230168410, 822418623, 185044669, 282409605, 312349943,
        8437311,   657922431, 101977992, 45139816,  396138699, 496786971, 875180639, 45501370,  30325836,  525679891,
        147182857, 594094833, 300383328, 601518177, 510474410, 139217683, 14885176,  505523489, 887972091, 283070434,
        681484711, 976226904, 463491026, 763464891, 132610790, 494500522, 308559364, 931706890, 539924884, 399116813,
        10341441,  9907127,   591316179, 844185784, 598994537, 45329870,  88387561,  264032581, 894374165, 508545802,
        937357732, 231367332, 645347854, 214459759, 947609847, 739972377, 637940462, 626979010, 726943819, 710298150,
        119413377, 230900941, 42143836,  434826720, 245832299, 92396112,  856734759, 56219956,  788974390, 728536152,
        348330048, 342695014, 123959044, 320514918, 5240150,   817350101, 897741295, 910819821, 885295731, 398644501,
        662128245, 129154961, 748946057, 927703510, 974593928, 935350805, 653662173, 366782137, 229309669, 67439096,
        725004503, 121447421, 850318675, 595278518, 867224300, 260276489, 835740262, 743532054, 128868263, 18358643,
        902024889, 245245250, 608776735, 891469415, 726031364, 407052494, 595850963, 543867758, 887985652, 156485092,
        524957316, 887766714, 771761420, 192958060, 345807450, 895063368, 207078741, 448891847, 208199196, 746004787,
        885902501, 652188234, 364093128, 925270571, 886377448, 44687875,  242817253, 810641871, 821669329, 476562293,
        261433719, 164973471, 307738820, 25725764,  521681079, 511142630, 839594410, 95688080,  350266113, 462863342,
        951398138, 778248382, 845146044, 705698828, 920998393, 157863575, 70800980,  39109000,  967945596, 73005947,
        590767370, 3266087,   644506543, 313952733, 236262852, 172490261, 88376824,  876554400, 511982380, 68370778,
        789871857, 425373423, 278059498, 421567014, 728252845, 236261662, 945468509, 257726610, 929596849, 790709218,
        821019290, 288775055, 922285743, 319518555, 439236385, 137606534, 499086275, 864877321, 823811151, 759921226,
        703775251, 803694459, 20632783,  30316714,  372366437, 388337879, 384907698, 715914100, 810383137, 768094285,
        836445878, 717918284, 489470342, 311164915, 626045960, 432063067, 834735140, 675810707, 309543566, 293320728,
        12000562,  977466363, 820241969, 109242890, 739712623, 567222278, 624917313, 790245761, 267127010, 362834840,
        104576978, 983646000, 809207394, 334734507, 623187656, 430166551, 24761786,  706993431, 204554544, 619880739,
        892408776, 688507584, 105074252, 544374108, 808275514, 497991454, 998595019, 801783028, 107466671, 158592370,
        434756663, 215867947, 785684024, 907424543, 802916854, 629306008, 389114981, 767780552, 5986288,   265768163,
        792508359, 994411019, 348255379, 28195356,  871419461, 108408487, 955308353, 279743899, 606985788, 855794244,
        281369880, 224582466, 428738283, 789665274, 248300236, 414318909, 108898567, 40621834,  978847939, 418069684,
        78169651,  123289549, 598709266, 545747467, 268000110, 797619589, 792486327, 417097773, 568625581, 380889295,
        750607936, 148637874, 426245435, 694558231, 866566972, 949983028, 971319798, 594139070, 43874587,  251766297,
        893369089, 796102646, 67029090,  714958111, 129966612, 150957463, 756872112, 996923781, 423551951, 522329230};
    // int k=321;

    int arr5[] = {2147483647, 1, 2, 3, 4, 5, 6, 7, 2147483647};
    //  [2147483647, 1, 2, 3, 4, 5, 6, 7, 2147483647]
    int arr4[] = {2147483647, 2147483647};

    int arr3[] = {1, 2};

    int arr2[] = {1, 2, 3, 4, 2, 3, 1, 4, 2};

    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};

    int numsSize = 0;

    numsSize = sizeof (arr100) / sizeof (arr100[0]);
    res = check_array (arr100, numsSize, 321);
    if (false == res) {
        return res;
    }

    numsSize = sizeof (arr5) / sizeof (arr5[0]);
    res = check_array (arr5, numsSize, 2);
    if (false == res) {
        return res;
    }

    numsSize = sizeof (arr4) / sizeof (arr4[0]);
    res = check_array (arr4, numsSize, 2);
    if (false == res) {
        return res;
    }

    numsSize = sizeof (arr3) / sizeof (arr3[0]);
    res = check_array (arr3, numsSize, 1);
    if (false == res) {
        return res;
    }

    numsSize = sizeof (arr) / sizeof (arr[0]);
    res = check_array (arr, numsSize, 3);
    if (false == res) {
        return res;
    }

    numsSize = sizeof (arr2) / sizeof (arr2[0]);
    res = check_array (arr2, numsSize, 3);
    if (false == res) {
        return res;
    }

    return res;
}

bool check_array (int *arr, int numsSize, int k) {
    bool res;
    int returnSize = 0;
    double *prt;
    double *prtCorrect;

    prt = medianSlidingWindow (arr, numsSize, k, &returnSize);
    if (prt) {
        if (returnSize == (numsSize - k + 1)) {
        }
    }

    prtCorrect = medianSlidingWindowArr (arr, numsSize, k, &returnSize);
    if (prtCorrect) {
        if (returnSize == (numsSize - k + 1)) {
        }
    }
    res = is_double_arr_equal (prtCorrect, prt, returnSize);
    if (false == res) {
        printf ("\n Arrays are not equals \n");
        printf ("\n right ");
        print_array_double (prtCorrect, returnSize);
        printf ("\n calced ");
        print_array_double (prt, returnSize);
    }
    free (prt);
    free (prtCorrect);
    return res;
}

bool test_bin_heap_same_add (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned)time (&t));
    for (int a = 5; 0 < a; a -= 1) {
        if (true == res) {
            int b = 10;
            res = max_heap_insert (&binMaxHeapRoot, b);
            if (false == res) {
                printf ("\n max_heap_insert %d err", b);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n Notheap!");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_same.dot");

    return res;
}

bool test_bin_heap_rand_add (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned)time (&t));
    for (int a = 20; 0 < a; a -= 1) {
        if (true == res) {
            int b = rand () % 3;
            res = max_heap_insert (&binMaxHeapRoot, b);
            if (false == res) {
                printf ("\n max_heap_insert %d err", b);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n Notheap!");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_rand.dot");

    return res;
}

bool test_bin_heap_rand_add_and_del_one (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned)time (&t));
    for (int a = 10; 0 < a; a -= 1) {
        if (true == res) {
            int b = rand () % 100;
            res = max_heap_insert (&binMaxHeapRoot, b);
            if (false == res) {
                printf ("\n max_heap_insert %d err", b);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n Notheap!");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_rand.dot");
    get_max (&binMaxHeapRoot);

    print_tree_to_file (binMaxHeapRoot, "bin_heap_rand_after_del.dot");

    return res;
}

bool test_bin_heap_dec_add (void) {
    bool res = true;
    TreeNode_t *binMaxHeapRoot = NULL;
    for (int a = 10; 0 < a; a -= 2) {
        if (true == res) {
            res = max_heap_insert (&binMaxHeapRoot, a);
            if (false == res) {
                printf ("\n max_heap_insert %d err\n", a);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n tree is not heap!\n");
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_dec.dot");

    return res;
}

bool test_bin_heap_delete (void) {
    bool res = true;
    TreeNode_t *binMaxHeapRoot = NULL;
    for (int a = 10; 0 < a; a--) {
        if (true == res) {
            res = max_heap_insert (&binMaxHeapRoot, a);
            if (false == res) {
                printf ("\n max_heap_insert %d err\n", a);
            }
            res = is_max_heap (binMaxHeapRoot);
            if (false == res) {
                printf ("\n tree is not heap!\n");
            }
        }
    }

    int val = 0;
    for (int a = 10; 0 < a; a--) {
        if (true == res) {
            val = get_max (&binMaxHeapRoot);
            if (val != a) {
                res = false;
            }
        }
    }

    print_tree_to_file (binMaxHeapRoot, "bin_heap_del.dot");

    return res;
}

bool test_is_bin_tree (void) {
    bool res = false;

    TreeNode_t node1;
    TreeNode_t node2;

    node1.val = 1;
    node1.left = &node2;
    node1.right = NULL;

    node2.val = 1;
    node2.left = NULL;
    node2.right = NULL;

    res = is_bin_search_tree (&node1);
    if (true == res) {
        printf ("\n Error! 1\n");
        return false;
    }

    TreeNode_t node3;
    TreeNode_t node4;

    init_tree_node (&node3, 1, NULL, &node4);
    init_tree_node (&node4, 1, NULL, NULL);

    res = is_bin_search_tree (&node3);
    if (true == res) {
        printf ("\n Error! 2\n");
        return false;
    }

    TreeNode_t node11;
    TreeNode_t node22;
    TreeNode_t node33;
    TreeNode_t node44;
    TreeNode_t node55;

    init_tree_node (&node11, 10, &node22, &node33);
    init_tree_node (&node22, 5, NULL, NULL);
    init_tree_node (&node33, 15, &node44, &node55);
    init_tree_node (&node44, 6, NULL, NULL);
    init_tree_node (&node55, 20, NULL, NULL);

    print_tree_to_file (&node11, "not_BST.dot");
    res = is_bin_search_tree (&node11);
    if (true == res) {
        printf ("\n Error! 3\n");
        return false;
    }

    TreeNode_t nod0;
    TreeNode_t nod1;
    TreeNode_t nod2;
    TreeNode_t nod3;
    TreeNode_t nod4;
    TreeNode_t nod5;
    TreeNode_t nod6;
    TreeNode_t nod7;
    init_tree_node (&nod0, 3, &nod1, &nod2);
    init_tree_node (&nod1, 1, &nod3, &nod4);
    init_tree_node (&nod2, 5, &nod5, &nod6);
    init_tree_node (&nod3, 0, NULL, NULL);
    init_tree_node (&nod4, 2, NULL, &nod7);
    init_tree_node (&nod5, 4, NULL, NULL);
    init_tree_node (&nod6, 6, NULL, NULL);
    init_tree_node (&nod7, 3, NULL, NULL);
    print_tree_to_file (&nod0, "not_BST2.dot");

    res = is_bin_search_tree (&nod0);
    if (true == res) {
        printf ("\n Error! 4\n");
        return false;
    }

    TreeNode_t nd0;
    TreeNode_t nd1;
    init_tree_node (&nd0, -2147483648, NULL, &nd1);
    init_tree_node (&nd1, 2147483647, NULL, NULL);

    res = is_bin_search_tree (&nd0);
    if (false == res) {
        printf ("\n Error! 5\n");
        return false;
    }

    return true;
}

bool test_delim_amount (void) {

    char text[] = "Hello world";
    char pattern[] = "lo";
    int amountOfItem = 0;
    amountOfItem = count_amount_of_item (text, pattern);
    if (2 != amountOfItem) {
        printf ("\n-1\n");
        return false;
    }

    amountOfItem = count_amount_of_item (text, "He");
    if (1 != amountOfItem) {
        printf ("\n0\n");
        return false;
    }

    amountOfItem = count_amount_of_item (text, "ld");
    if (1 != amountOfItem) {
        printf ("\n1\n");
        return false;
    }
    amountOfItem = count_amount_of_item ("a b c d e", " ");
    if (5 != amountOfItem) {
        printf ("\n2\n");
        return false;
    }

    amountOfItem = count_amount_of_item ("1231567190", "1");
    if (3 != amountOfItem) {
        printf ("\n3\n");
        return false;
    }

    amountOfItem = count_amount_of_item ("qpeptypiop", "p");
    if (4 != amountOfItem) {
        printf ("\n4\n");
        return false;
    }

    return true;
}

bool test_split (void) {
    int amountOfval = 0;
    int resCmp = 0;

    char **ArrOfStrings;
    printf ("\n sizeof(char *) %ld \n", sizeof (char *));
    amountOfval = split ("Hello world", "wo", &ArrOfStrings);
    if (2 != amountOfval) {
        printf ("\n%s: %d\n", __FUNCTION__, amountOfval);
        return false;
    }

    if (NULL == ArrOfStrings) {
        printf ("\nNull pointer to array of pointer: %p\n", ArrOfStrings);
        return false;
    } else {
        printf ("\n (ArrOfStrings [0]): <%s> \n", ArrOfStrings[0]);
        printf ("\n (ArrOfStrings [1]): <%s> \n", ArrOfStrings[1]);

        // printf ("\n *ArrOfStrings+1: %llu\n",(long long unsigned int) *ArrOfStrings + ((char *)1));
    }

    resCmp = strncmp ((char *)ArrOfStrings[0], "Hello ", strlen ("Hello "));
    if (0 != resCmp) {
        printf ("\n%s: [%s]\n", __FUNCTION__, (char *)ArrOfStrings[0]);
        return false;
    }
    resCmp = strncmp ((char *)ArrOfStrings[1], "rld", strlen ("rld"));
    if (0 != resCmp) {
        printf ("\n%s: [%s]\n", __FUNCTION__, (char *)(ArrOfStrings[1]));
        return false;
    }

    return true;
}

bool test_bin_heap_par_ind_arr (void) {

    int parentIndex = 0;
    parentIndex = get_perent_index (0);
    if (-1 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    parentIndex = get_perent_index (1);
    if (0 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    parentIndex = get_perent_index (2);
    if (0 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_perent_index (3);
    if (1 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_perent_index (4);
    if (1 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_perent_index (6);
    if (2 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_right_child_index (3);
    if (8 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    parentIndex = get_left_child_index (2);
    if (5 != parentIndex) {
        printf ("\n parentIndex %d\n", parentIndex);
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    return true;
}

bool test_max_bin_heap_insert (void) {
    BinaryHeap_t binHeapObj;
    binHeapObj.length = 0;
    bool res = true;
    time_t t;
    srand ((unsigned)time (&t));

    res = bin_heap_init (&binHeapObj, 20);
    if (true == res) {
        for (int a = 0; a < 20; a++) {
            if (true == res) {
                int b = rand () % 50;
                res = heap_insert_val (&binHeapObj, true, b);
                if (false == res) {
                    printf ("\n [%s] %d heap_insert_val\n", __FUNCTION__, __COUNTER__);
                    return false;
                }
                res = is_bin_heap (&binHeapObj, true);
                if (false == res) {
                    printf ("\n [%s] %d is_bin_heap\n", __FUNCTION__, __COUNTER__);
                    return false;
                }
            }
        }

        res = is_bin_heap (&binHeapObj, true);
        if (false == res) {
            printf ("\n [%s] %d is_bin_heap\n", __FUNCTION__, __COUNTER__);
            return false;
        }
        res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array.dot");
    }

    return true;
}

bool test_min_bin_heap_insert (void) {
    BinaryHeap_t binHeapObj;
    binHeapObj.length = 0;
    bool res = true;
    time_t t;
    srand ((unsigned)time (&t));

    res = bin_heap_init (&binHeapObj, 20);

    for (int a = 0; a < 20; a++) {
        if (true == res) {
            int b = rand () % 50;
            res = heap_insert_val (&binHeapObj, false, b);
            if (false == res) {
                printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
                return false;
            }
            res = is_bin_heap (&binHeapObj, false);
            if (false == res) {
                printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
                return false;
            }
        }
    }

    res = is_bin_heap (&binHeapObj, false);
    if (false == res) {
        printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = draw_bin_heap_in_file (&binHeapObj, "min_bin_heap_array.dot");

    return true;
}

bool test_string_clean (void) {
    int cmpres;
    char *ptrString = NULL;
    ptrString = select_sub_string ("qwerty", "ui");
    if (NULL == ptrString) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    cmpres = strcmp (ptrString, "qwerty");
    if (0 != cmpres) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    free (ptrString);
    ptrString = NULL;

    ptrString = select_sub_string ("qweRTy", "RT");
    if (NULL == ptrString) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    cmpres = strcmp (ptrString, "qwe");
    if (0 != cmpres) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    free (ptrString);
    ptrString = NULL;

    ptrString = select_sub_string ("QWerty", "QW");
    if (NULL == ptrString) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }

    cmpres = strcmp (ptrString, "");
    if (0 != cmpres) {
        printf ("\n%s %d\n", __FUNCTION__, __COUNTER__);
        return false;
    }
    free (ptrString);
    ptrString = NULL;

    return true;
}

bool test_min_bin_heap_delete_val (void) {
    bool res = false;
    BinaryHeap_t minBinHeapObj;
    res = bin_heap_init (&minBinHeapObj, 20);
    if (res) {
        res = fill_up_heap_continuous_vals (&minBinHeapObj, 20, false);
        if (false == res) {
            printf ("\nUnable to fill up array\n");
        }
    }
    draw_bin_heap_in_file (&minBinHeapObj, "min_bin_heap_array1_20.dot");

    int valIndex;
    res = is_val_in_bin_heap (&minBinHeapObj, false, 10, 0, &valIndex);
    if (true == res) {
        res = bin_heap_remove_val (&minBinHeapObj, false, 10);
        if (true == res) {
            draw_bin_heap_in_file (&minBinHeapObj, "min_bin_heap_array1_20-10.dot");
            res = is_val_in_bin_heap (&minBinHeapObj, false, 10, 0, &valIndex);
            if (true == res) {
                printf ("\nphantom  val in the heap\n");
                res = false;
            } else {
                res = true;
            }
        } else {
            printf ("\nUnable to remove val\n");
        }
    } else {
        printf ("\nNo expected val 10\n");
    }
    bin_heap_deinit (&minBinHeapObj);

    return res;
}

bool test_bin_heap_delete_val (void) {
    bool res = false;
    BinaryHeap_t maxBinHeapObj;
    int valIndex;
    res = bin_heap_init (&maxBinHeapObj, 20);
    if (res) {
        res = fill_up_heap_continuous_vals (&maxBinHeapObj, 20, true);
        if (false == res) {
            printf ("\nUnable to fill up array\n");
        }
    }
    draw_bin_heap_in_file (&maxBinHeapObj, "bin_heap_array1_20.dot");

    res = is_val_in_bin_heap (&maxBinHeapObj, true, 10, 0, &valIndex);
    if (true == res) {
        res = bin_heap_remove_val (&maxBinHeapObj, true, 10);
        if (true == res) {
            draw_bin_heap_in_file (&maxBinHeapObj, "bin_heap_array1_20-10.dot");
            res = is_val_in_bin_heap (&maxBinHeapObj, true, 10, 0, &valIndex);
            if (true == res) {
                printf ("\nPhantom  val in the heap\n");
                res = false;
            } else {
                res = true;
            }
        } else {
            printf ("\nUnable to remove val\n");
        }
    } else {
        printf ("\nNo extected val 10\n");
    }
    bin_heap_deinit (&maxBinHeapObj);

    return res;
}

bool fill_up_heap_continuous_vals (BinaryHeap_t *binHeap, int maxVal, bool isMaxHeap) {
    bool res = true;
    if (binHeap) {
        for (int ind = 1; ind <= maxVal; ind++) {
            if (true == res) {
                res = heap_insert_val (binHeap, isMaxHeap, ind);
            }
        }
    }
    return res;
}

bool test_bin_heap_remove (void) {
    BinaryHeap_t binHeapObj;

    bool res = true;
    time_t t;
    srand ((unsigned)time (&t));

    res = bin_heap_init (&binHeapObj, 20);
    if (res) {
        for (int ind = 0; ind < 20; ind++) {
            if (true == res) {
                int b = rand () % 50;
                res = heap_insert_val (&binHeapObj, true, b);
                if (false == res) {
                    printf ("\n [%s] %d insert_val ind=%d\n", __FUNCTION__, __COUNTER__, ind);
                    return false;
                }
                res = is_bin_heap (&binHeapObj, true);
                if (false == res) {
                    res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array_error.dot");
                    printf ("\n [%s] %d is_max_bin_heap ind=%d\n", __FUNCTION__, __COUNTER__, ind);
                    return false;
                }
            }
        }
        res = draw_bin_heap_in_file (&binHeapObj, "rand_bin_heap_array.dot");

        printf ("\n");
        for (int a = 0; a < 20; a++) {
            int val = heap_pop (&binHeapObj, true);
            printf (" %d ", val);
            res = is_bin_heap (&binHeapObj, true);
            if (false == res) {
                res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array_error.dot");
                printf ("\n [%s] %d is_max_bin_heap a=%d\n", __FUNCTION__, __COUNTER__, a);
                return false;
            }
        }
        printf ("\n");
        res = is_bin_heap (&binHeapObj, true);
        if (false == res) {
            printf ("\n [%s] %d\n", __FUNCTION__, __COUNTER__);
            return false;
        }
        res = draw_bin_heap_in_file (&binHeapObj, "bin_heap_array.dot");
    }
    return res;
}

bool test_sliding_window_max (void) {
    bool res;
    int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int numsSize = 0;
    int returnSize;
    numsSize = sizeof (arr) / sizeof (arr[0]);
    int *resArr;
    resArr = maxSlidingWindow (arr, numsSize, 3, &returnSize);
    if (resArr) {
        res = true;
        print_curr_array (resArr, returnSize);
        free (resArr);
    }
    return res;
}

void assemble_tree_from_array (TreeNode_t **root, int *arr, int arraySize) {
    printf ("\n arraySize: %d\n", arraySize);
    for (int index = 0; index < arraySize; index++) {
        bst_insert (root, arr[index]);
    }
}

// Creates a binary search tree
void create_binary_search_tree (TreeNode_t **root, int how_many_elements) {
    int number = 0, counter = 0;
    time_t t;
    srand ((unsigned)time (&t));
    for (counter = 1; counter <= how_many_elements; counter++) {
        number = rand () / 100;
        bst_insert (root, number);
    }
    printf ("\nThe binary search tree is: \n");
    print_inorder_traversal (*root);
}
