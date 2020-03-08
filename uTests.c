#include "uTests.h"

#include "algorithms.h"
#include "arrays.h"
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
            printf ("List Num Error %d\n",numOfElen);
            res = false;
        }
    } else {
        printf ("List Add1 Error\n");
    }

    res = linked_list_add_array (&llHead, array2, 6);
    if (true == res) {
        numOfElen = list_num_of_elements (llHead);
        if (2 != numOfElen) {
            printf ("List Num Error %d\n",numOfElen);
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
