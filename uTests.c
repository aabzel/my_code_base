#include "uTests.h"

#include "bin_heap_array.h"
#include "algorithms.h"
#include "arrays.h"
#include "bin_tree.h"
#include "bin_tree_draw.h"
#include "bin_heap.h"
#include "bin_search_tree.h"
#include "combinations.h"
#include "min_path.h"
#include "permutations.h"
#include "bin_heap.h"
#include "str_ops.h"

#include "linked_list.h"
#include "utils.h"
#include "amount_of_uio_states.h"
#include "min_path_diag_scale.h"
#include "parse_keepass.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

int unitTest (void) {
    bool res = false;
    int ret = 0;

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

    res = test_split ();
    if (false == res) {
        return STRING_SPLIT_ERROR;
    }

    res = test_is_bin_tree ();
    if (false == res) {
        return IS_BIN_SEARCH_TREE_ERROR;
    }
#if TEST_HEAP_DELET_ONE
    res= test_bin_heap_rand_add_and_del_one();
    if (false == res) {
         return BIN_HEAP_DEL_ERROR;
     }
#endif

#if TEST_HEAP_DELET
    res = test_bin_heap_delete();
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

    res = test_valid_float_number ();
    if (false == res) {
        return IS_STR_FALSE_ERROR;
    }
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

    char intStr [] = "ABCD";
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

    int arr1 [] =
        { 1, 2 };
    int arr2 [] =
        { 2, 1 };
    res = is_permutation (arr1, arr2, 2);
    if (false == res) {
        return 11;
    }

    int arra1 [] =
        { 1, 2, 5 };
    int arra2 [] =
        { 2, 1, 6 };
    res = is_permutation (arra1, arra2, 3);
    if (true == res) {
        return 12;
    }

    outArray = generate_num_array (4);
    if (NULL != outArray) {
        if (0 != outArray [0]) {
            return 1;
        }
        if (1 != outArray [1]) {
            return 2;
        }
        if (2 != outArray [2]) {
            return 3;
        }
        if (3 != outArray [3]) {
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
    int* arr = grayCode (2, &returnSize);
    if (arr) {
        if (4 == returnSize) {
            if (0 == arr [0]) {
                if (3 == arr [2]) {
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
    int array1 [] =
        { 1, 2, 3, 4 };
    int array2 [] =
        { 1, 2, 3, 4, 5, 6 };
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

bool test_bin_tree (void) {
    TreeNode_t * root = NULL;
    bool res = false;
    int sumOfLeaves = 0;
    create_binary_search_tree (&root, 10);
    if (NULL != root) {
        int depth = max_depth (root);
        printf ("\ndepth:%d\n", depth);
        print2D (root);
        sumOfLeaves = deepestLeavesSum (root);
        printf ("\n SumOfLeaves:%d\n", sumOfLeaves);
        res = print_tree_to_file (root, "rand_tree.txt");
    }
    return res;
}

bool test_reverse_list (void) {
    bool res = false;
    ListNode* head = NULL;
    ListNode* revhead = NULL;

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
    //printf ("\n 6x6 numPath = %d", numPath);

    return res;
}

bool test_ya_task (void) {
    bool res = false;
    int sizeOfArr = 0;
    int numOnes = 0;
    int arr [] =
        { 0, 1, 1, 0, 1, 1, 0 };
    sizeOfArr = sizeof(arr) / sizeof(arr [0]);

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

    int arr2 [] =
        { 0, 1, 1, 1, 1, 1, 0 };
    sizeOfArr = sizeof(arr2) / sizeof(arr2 [0]);
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
    int arr [] =
        { 1, 2, 3 };
    int arrSize = sizeof(arr) / sizeof(arr [0]);
    int returnSize = 0;
    int* returnColumnSizes = NULL;
    int** arrayOfArr = NULL;
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
    kByte = (float) byte / 1024.0f;
    MByte = (float) kByte / 1024.0f;
    GByte = (float) MByte / 1024.0f;
    printf ("\nmax Available heap size [%u] byte [%f] k_Byte [%f] M_Byte [%f] G_Byte\n", byte, kByte, MByte, GByte);
}

bool test_heap (void) {
    uint32_t byte = 3;
    uint32_t mult = 10;
    uint32_t div = 2;
    while (1) {
        char *ptr = NULL;
        ptr = (char *) malloc (byte);
        if (ptr) {
            byte = (byte * mult) / div;
            //print_bytes (byte);
            free (ptr);
        } else {
            break;
        }
    } //[2327387742]
    print_bytes (byte);

    return true;
}

void test_combine (void) {
    //combine (4, 2);
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
    char text [100];
    char pattern [100];
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
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathSum ((int *) grid, numOfLine, numOfcolomn);
    if (7 == minSum) {
        res = true;
    } else {
        return false;
    }

    //save_array_as_dot ("map1.dot", (int *) grid, 3, 3);

    //minPath ((int *) grid, sizeOfGrid, gridColSize);
    int grid2 [10] [10];
    numOfLine = 10;
    numOfcolomn = 10;
    init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    //init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    //minSum = minPathSum ((int *) grid2, 10, 10);
    //save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    minPath ((int *) grid2, numOfLine, numOfcolomn);

    return res;
}

bool test_min_path_diag_atmospher (void) {
    bool res = false;

    int grid5 [5] [5] =
        {
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 },
            { 1, 1, 1, 999, 999 } };
    res = minPathDiag ((int *) grid5, 5, 5);

    return res;
}

bool test_min_path_diag (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathDiagSum ((int *) grid, numOfLine, numOfcolomn);
    if (5 == minSum) {
        res = true;
    } else {
        return false;
    }
#define TEST_DIM 3
    int grid1 [TEST_DIM] [TEST_DIM];
    res = init_one_map ((int *) grid1, TEST_DIM, TEST_DIM);
    minSum = minPathDiagSum ((int *) grid1, TEST_DIM, TEST_DIM);
    if (TEST_DIM == minSum) {
        res = true;
    } else {
        return false;
    }

#define TEST_DIM2 8
    int grid2 [TEST_DIM2] [TEST_DIM2];
    //init_rod_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    //init_rand_array((int *) grid2, TEST_DIM2, TEST_DIM2);
    //init_box_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    init_ramp_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    minPathDiag ((int *) grid2, TEST_DIM2, TEST_DIM2);
    //int grid2 [10] [10];
    //numOfLine = 10;
    //numOfcolomn = 10;
    //init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    //init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    //minSum = minPathSum ((int *) grid2, 10, 10);
    //save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    //minPath ((int *) grid2, numOfLine, numOfcolomn);
#if TEST_3_3
    int grid3 [3] [3] =
        {
            { 1, 93, 9 },
            { 1, 95, 9 },
            { 4, 2, 9 } };
    minPathDiag ((int *) grid3, 3, 3);
#endif

    res = test_min_path_diag_atmospher ();
    if (false == res) {
        return false;
    }
    return res;
}

bool test_min_diag_scale_summ (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 1, 1 },
            { 1, 1, 1 },
            { 1, 1, 1 } };
    float totalSum = minPathDiagScaleSum ((int*) grid, 3, 3);
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
    int grid [TEST_ARR_DIM2] [TEST_ARR_DIM2];
    init_ramp_map ((int*) grid, TEST_ARR_DIM2, TEST_ARR_DIM2);
    res = minPathDiagScale ((int*) grid, TEST_ARR_DIM2, TEST_ARR_DIM2);
    if (true == res) {
        res = true;
    }
    return res;
}

bool test_find_min_diag_scale_summ (void) {
    bool res = false;
    int grid [5] [5] =
        {
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 },
            { 1, 1, 100, 100, 100 } };
    res = minPathDiagScale ((int*) grid, 5, 5);
    if (true == res) {
        res = true;
    }
    return res;
}

bool test_valid_float_number (void) {
    bool res;
    char string [100];

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
    int arr1 [] =
        { 1, 3, -1 };
    numsSize = sizeof(arr1) / sizeof(arr1 [0]);

    val = qselect (arr1, numsSize, 1);
    if (1 != val) {
        return false;
    }
    int arr2 [] =
        { 3, -1, -3 };
    numsSize = sizeof(arr2) / sizeof(arr2 [0]);
    val = qselect (arr2, numsSize, 1);
    if (-1 != val) {
        return false;
    }
    int arr3 [] =
        { -1, -3, 5 };
    numsSize = sizeof(arr3) / sizeof(arr2 [0]);

    val = qselect (arr3, numsSize, 1);
    if (-1 != val) {
        return false;
    }

    return true;
}

bool test_medianSlidingWindow (void) {
    bool res = false;
    double* prt;
    double* prtCorrect;

    int arr2 [] =
        { 1, 2, 3, 4, 2, 3, 1, 4, 2 };

    int arr [] =
        { 1, 3, -1, -3, 5, 3, 6, 7 };
    int numsSize = sizeof(arr) / sizeof(arr [0]);
    int returnSize = 0;
    int k = 3;
    prt = medianSlidingWindow (arr, numsSize, k, &returnSize);
    if (prt) {
        printf ("\n mem Alloced! %d ", returnSize);
        if (returnSize == (numsSize - k + 1)) {
            print_array_double (prt, returnSize);
            res = true;
        }
    }

    prtCorrect = medianSlidingWindowArr (arr, numsSize, k, &returnSize);
    if (prtCorrect) {
        printf ("\n mem Alloced! %d ", returnSize);
        if (returnSize == (numsSize - k + 1)) {
            print_array_double (prtCorrect, returnSize);
            res = true;
        }
    }
    res = is_double_arr_equal (prtCorrect, prt, returnSize);
    if (false == res) {
        printf ("\n Arrays are not equals \n");
    }
    free (prt);
    free (prtCorrect);

     numsSize = sizeof(arr2) / sizeof(arr2 [0]);
    prt = medianSlidingWindow (arr2, numsSize, k, &returnSize);
    if (prt) {
        printf ("\n mem Alloced! %d ", returnSize);
        if (returnSize == (numsSize - k + 1)) {
            print_array_double (prt, returnSize);
            res = true;
        }
    }

    prtCorrect = medianSlidingWindowArr (arr2, numsSize, k, &returnSize);
    if (prtCorrect) {
        printf ("\n mem Alloced! %d ", returnSize);
        if (returnSize == (numsSize - k + 1)) {
            print_array_double (prtCorrect, returnSize);
            res = true;
        }
    }
    res = is_double_arr_equal (prtCorrect, prt, returnSize);
    if (false == res) {
        printf ("\n Arrays are not equals \n");
    }
    free (prt);
    free (prtCorrect);

    return res;
}
bool test_bin_heap_same_add (void) {
    bool res = true;
    time_t t;
    TreeNode_t *binMaxHeapRoot = NULL;
    srand ((unsigned) time (&t));
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
    srand ((unsigned) time (&t));
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
    srand ((unsigned) time (&t));
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

    char text [] = "Hello world";
    char pattern [] = "lo";
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
    printf ("\n sizeof(char *) %ld \n", sizeof(char *));
    amountOfval = split ("Hello world", "wo", &ArrOfStrings);
    if (2 != amountOfval) {
        printf ("\n%s: %d\n", __FUNCTION__, amountOfval);
        return false;
    }

    if (NULL == ArrOfStrings) {
        printf ("\nNull pointer to array of pointer: %p\n", ArrOfStrings);
        return false;
    } else {
        printf ("\n (ArrOfStrings [0]): <%s> \n", ArrOfStrings [0]);
        printf ("\n (ArrOfStrings [1]): <%s> \n", ArrOfStrings [1]);

        //printf ("\n *ArrOfStrings+1: %llu\n",(long long unsigned int) *ArrOfStrings + ((char *)1));
    }

    resCmp = strncmp ((char *) ArrOfStrings [0], "Hello ", strlen ("Hello "));
    if (0 != resCmp) {
        printf ("\n%s: [%s]\n", __FUNCTION__, (char *) ArrOfStrings [0]);
        return false;
    }
    resCmp = strncmp ((char *) ArrOfStrings [1], "rld", strlen ("rld"));
    if (0 != resCmp) {
        printf ("\n%s: [%s]\n", __FUNCTION__, (char *) (ArrOfStrings [1]));
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
    srand ((unsigned) time (&t));

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
    srand ((unsigned) time (&t));

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

    res = is_val_in_bin_heap (&minBinHeapObj, false, 10, 0);
    if (true == res) {
        res = bin_heap_remove_val (&minBinHeapObj, false, 10);
        if (true == res) {
            draw_bin_heap_in_file (&minBinHeapObj, "min_bin_heap_array1_20-10.dot");
            res = is_val_in_bin_heap (&minBinHeapObj, false, 10, 0);
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
    res = bin_heap_init (&maxBinHeapObj, 20);
    if (res) {
        res = fill_up_heap_continuous_vals (&maxBinHeapObj, 20, true);
        if (false == res) {
            printf ("\nUnable to fill up array\n");
        }
    }
    draw_bin_heap_in_file (&maxBinHeapObj, "bin_heap_array1_20.dot");

    res = is_val_in_bin_heap (&maxBinHeapObj, true, 10, 0);
    if (true == res) {
        res = bin_heap_remove_val (&maxBinHeapObj, true, 10);
        if (true == res) {
            draw_bin_heap_in_file (&maxBinHeapObj, "bin_heap_array1_20-10.dot");
            res = is_val_in_bin_heap (&maxBinHeapObj, true, 10, 0);
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
    srand ((unsigned) time (&t));

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
