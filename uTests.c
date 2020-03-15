#include "uTests.h"

#include "algorithms.h"
#include "arrays.h"
#include "bin_tree.h"
#include "bin_search_tree.h"
#include "permutations.h"
#include "str_ops.h"
#include "linked_list.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int unitTest (void) {

    test_heap ();

    char intStr [] = "ABCD";
    char *outStr = NULL;
    int *outArray;
    int cmpRes;
    bool res;

    res = test_uniq_path ();
    if (false == res) {
        return UNIQ_PATH_ERROR;
    }else{
        printf ("\ntest_uniq_path fine!\n");
    }

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

bool test_parse_bin_tree_init_array (void) {
    bool res = true;
    int array [] =
        { 1, 2, 3, 4, 5, NOT_NUM, 6, 7, NOT_NUM, NOT_NUM, NOT_NUM, NOT_NUM, 8 };
    int sizeOfArray = sizeof(array) / sizeof(array [0]);
    parse_bin_tree (array, sizeOfArray);

    return res;
}

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
    printf ("\n%s %d\n", __FUNCTION__,__COUNTER__);
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
    if(1916797311!=numPath ){
        printf ("\nnumPath 51 9  %d\n", numPath);
        return false;
    }



    return true;
}
