#include "russian_doll_envelopes_test.h"

#include "algorithms.h"
#include "arrays.h"
#include "permutations.h"
#include "russian_doll_envelopes.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//[7,8]]

bool maxEnvelopes_test9 (void) {
    int amount;
    bool res = true;

    amount = factorial (9);
    if (362880 != amount) {
        return false;
    }

    int arr [8];
    res = get_i_permutation_of_n (9, 1, arr);
    if (false == res) {
        return false;
    }

    int envelopesColSize = 0;
    int invelop1_9 [2] =
        { 1, 2 };
    int invelop2_9 [2] =
        { 2, 3 };
    int invelop3_9 [2] =
        { 3, 4 };
    int invelop4_9 [2] =
        { 3, 5 };
    int invelop5_9 [2] =
        { 4, 5 };
    int invelop6_9 [2] =
        { 5, 5 };
    int invelop7_9 [2] =
        { 5, 6 };
    int invelop8_9 [2] =
        { 6, 7 };

    int invelop9_9 [2] =
        { 7, 8 };
    int *listOfEnvelop9 [9];

    listOfEnvelop9 [0] = invelop1_9;
    listOfEnvelop9 [1] = invelop2_9;
    listOfEnvelop9 [2] = invelop3_9;
    listOfEnvelop9 [3] = invelop4_9;
    listOfEnvelop9 [4] = invelop5_9;
    listOfEnvelop9 [5] = invelop6_9;
    listOfEnvelop9 [6] = invelop7_9;
    listOfEnvelop9 [7] = invelop8_9;
    listOfEnvelop9 [8] = invelop9_9;
    amount = maxEnvelopes (listOfEnvelop9, 9, &envelopesColSize);
    if (7 != amount) {
        printf ("\n nesting %d ", amount);
        return false;
    }
    return res;
}

bool maxEnvelopes_test8 (void) {
    int amount;
    bool res = true;

    amount = factorial (8);
    if (40320 != amount) {
        return false;
    }

    int arr [8];
    res = get_i_permutation_of_n (8, 1, arr);
    if (false == res) {
        return false;
    }

    int envelopesColSize = 0;
    int invelop1_8 [2] =
        { 1, 2 };
    int invelop2_8 [2] =
        { 2, 3 };
    int invelop3_8 [2] =
        { 3, 4 };
    int invelop4_8 [2] =
        { 4, 5 };
    int invelop5_8 [2] =
        { 5, 6 };
    int invelop6_8 [2] =
        { 5, 5 };
    int invelop7_8 [2] =
        { 6, 7 };
    int invelop8_8 [2] =
        { 7, 8 };
    int *listOfEnvelop8 [8];

    listOfEnvelop8 [0] = invelop1_8;
    listOfEnvelop8 [1] = invelop2_8;
    listOfEnvelop8 [2] = invelop3_8;
    listOfEnvelop8 [3] = invelop4_8;
    listOfEnvelop8 [4] = invelop5_8;
    listOfEnvelop8 [5] = invelop6_8;
    listOfEnvelop8 [6] = invelop7_8;
    listOfEnvelop8 [7] = invelop8_8;
    amount = maxEnvelopes (listOfEnvelop8, 8, &envelopesColSize);
    if (7 != amount) {
        printf ("\n nesting %d ", amount);
        return false;
    }
    return res;
}

//[[1,2],[2,3],[3,4],[3,5],[4,5],[5,5],[5,6],[6,7],[7,8]]
//[[1,2],[2,3],[3,4],[4,5],[5,6],[5,5],[6,7],[7,8]]

//[  [5,5]   [7,8]>[6,7]>[5,6]>[4,5]>[3,4]>[2,3]>[1,2]]
bool maxEnvelopes_test1 (void) {
    int amount;
    bool res = true;

    amount = factorial (1);
    if (1 != amount) {
        return false;
    }

    int arr [1];
    res = get_i_permutation_of_n (1, 0, arr);
    if (false == res) {
        return false;
    }

    int envelopesColSize = 0;
    int invelop1_1 [2] =
        { 1, 1 };

    int *listOfEnvelop1 [1];

    listOfEnvelop1 [0] = invelop1_1;

    amount = maxEnvelopes (listOfEnvelop1, 1, &envelopesColSize);
    if (1 != amount) {
        printf ("\n nesting %d ", amount);
        return false;
    }
    return res;
}

bool maxEnvelopes_test4 (void) {
    int amount;
    bool res = true;
    int envelopesColSize = 0;
    amount = factorial (4);
    if (24 != amount) {
        return false;
    }

    int arr [4];
    res = get_i_permutation_of_n (4, 1, arr);
    if (false == res) {
        return false;
    }

    //print_permutations (4);
    //w h
    int invelop0 [2] =
        { 5, 4 };
    int invelop1 [2] =
        { 6, 4 };
    int invelop2 [2] =
        { 6, 7 };
    int invelop3 [2] =
        { 2, 3 };
    int *listOfEnvelop [4];
    listOfEnvelop [0] = invelop0;
    listOfEnvelop [1] = invelop1;
    listOfEnvelop [2] = invelop2;
    listOfEnvelop [3] = invelop3;
    amount = maxEnvelopes (listOfEnvelop, 4, &envelopesColSize);
    if (3 != amount) {
        printf ("\n nesting %d ", amount);
        return false;
    }
    return res;
}

bool maxEnvelopes_test (void) {
    bool res = true;

    res = test_permutation_i (4, 1);
    if (false == res) {
        printf ("\n 2nd permutation of 4 error");
        return false;
    }
    res = test_i_permutation (4);
    if (false == res) {
        printf ("\n permutation of 4 error");
        return false;
    }
    res = test_i_permutation (5);
    if (false == res) {
        printf ("\n permutation of 5 error");
        return false;
    }
    res = test_i_permutation (6);
    if (false == res) {
        printf ("\n permutation of 6 error");
        return false;
    }
    res = test_i_permutation (7);
    if (false == res) {
        printf ("\n permutation of 7 error");
        return false;
    }
    res = test_i_permutation (8);
    if (false == res) {
        printf ("\n permutation of 8 error");
        return false;
    }

    res = maxEnvelopes_test1 ();
    if (false == res) {
        return false;
    }

    res = maxEnvelopes_test4 ();
    if (false == res) {
        return false;
    }

    res = maxEnvelopes_test6 ();
    if (false == res) {
        return false;
    }

    res = maxEnvelopes_test8 ();
    if (false == res) {
        return false;
    }

    res = maxEnvelopes_test9 ();
    if (false == res) {
        return false;
    }

    int amount;
    amount = factorial (0);
    if (1 != amount) {
        return false;
    }
    if (1 != amount) {
        return false;
    }
    amount = factorial (4);
    if (24 != amount) {
        return false;
    }

    return true;
}

bool maxEnvelopes_test6 (void) {
    int amount;
    bool res = true;

    res = maxEnvelopes_test8 ();
    if (false == res) {
        return false;
    }

    amount = factorial (0);
    if (1 != amount) {
        return false;
    }
    if (1 != amount) {
        return false;
    }
    amount = factorial (4);
    if (24 != amount) {
        return false;
    }

    int envelopesColSize = 0;
    int invelop1_6 [2] =
        { 4, 5 };
    int invelop2_6 [2] =
        { 4, 6 };
    int invelop3_6 [2] =
        { 6, 7 };
    int invelop4_6 [2] =
        { 2, 3 };
    int invelop5_6 [2] =
        { 1, 1 };
    int invelop6_6 [2] =
        { 1, 1 };
    int *listOfEnvelop6 [6];
    //[[4,5],[4,6],[6,7],[2,3],[1,1],[1,1]]
    //[,[4,6]>   [6,7]>[4,5]>[2,3]>[1,1]   [1,1]]
    listOfEnvelop6 [0] = invelop1_6;
    listOfEnvelop6 [1] = invelop2_6;
    listOfEnvelop6 [2] = invelop3_6;
    listOfEnvelop6 [3] = invelop4_6;
    listOfEnvelop6 [4] = invelop5_6;
    listOfEnvelop6 [5] = invelop6_6;
    amount = maxEnvelopes (listOfEnvelop6, 6, &envelopesColSize);
    if (4 != amount) {
        printf ("\n nesting %d ", amount);
        return false;
    }

    return res;
}

bool test_i_permutation (int N) {
    bool res = false;

    if (0 < N) {
        int amountOfCombinations;
        amountOfCombinations = factorial (N);

        // how many ways to list envelops
        //printf ("\n Progress %d\n", amountOfCombinations);
        int spotPermutCnt = 0;
        for (int i = 0; i < amountOfCombinations; i++) {
            int *arraOfIndex = malloc (sizeof(int) * N);
            if (arraOfIndex) {
                memset (arraOfIndex, 0, sizeof(int) * N);
                bool res = false;
                res = get_i_permutation_of_n (N, i, arraOfIndex);
                if (true == res) {
                    spotPermutCnt++;
                    //printf ("\n i: %d/%d ", i, amountOfCombinations);
                    res = is_correct_permutation (arraOfIndex, N, N);
                    if (false == res) {
                        print_curr_array (arraOfIndex, N);
                        free (arraOfIndex);
                        printf ("\n i: incorrect permutation  %d/%d", i, amountOfCombinations);
                        return false;
                    } else {
                        uint64_t summ = sum_arr ((uint32_t *) arraOfIndex, (uint32_t) N);
                        if (!(0 < summ)) {
                            res = false;
                            print_curr_array (arraOfIndex, N);
                        }
                        res = true;
                    }
                } else {
                    res = false;
                    free (arraOfIndex);
                    printf ("\n i: undetermined permutation %d/%d ", i, amountOfCombinations);
                    return false;
                }
                free (arraOfIndex);
            }

        }
        if (spotPermutCnt != amountOfCombinations) {
            res = false;
            printf ("\n%s not all permutation checked ! %d/%d\n", __FUNCTION__, spotPermutCnt, amountOfCombinations);
        } else {
            res = true;
        }

    }

    return res;
}

bool test_permutation_i (int N, int i) {
    bool res = false;
    if (0 < N) {
        // how many ways to list envelops
#if DEBUG_TEST_PERMUTATION_I
        int amountOfCombinations;
        amountOfCombinations = factorial (N);
        printf ("\n amount of permutations %d\n", amountOfCombinations);
#endif
        int *arraOfIndex = malloc (sizeof(int) * N);
        if (arraOfIndex) {
            memset (arraOfIndex, 0, sizeof(int) * N);
            res = get_i_permutation_of_n (N, i, arraOfIndex);
            if (true == res) {
#if DEBUG_TEST_PERMUTATION_I
                printf ("\n i: %d/%d ", i, amountOfCombinations);
#endif
                res = is_correct_permutation (arraOfIndex, N, N);
                if (false == res) {
                    print_curr_array (arraOfIndex, N);
                    free (arraOfIndex);
#if DEBUG_TEST_PERMUTATION_I
                    printf ("\n i: incorrect permutation  %d/%d", i, amountOfCombinations);
#endif
                    return false;
                } else {
                    uint64_t summ = sum_arr ((uint32_t *) arraOfIndex, (uint32_t) N);
                    if (!(0 < summ)) {
                        res = false;
                        print_curr_array (arraOfIndex, N);
                    }
                    res = true;
                }
            } else {
                res = false;
                free (arraOfIndex);
#if DEBUG_TEST_PERMUTATION_I
                printf ("\n i: undetermined permutation %d/%d ", i, amountOfCombinations);
#endif
                return false;
            }
            free (arraOfIndex);
        } else {
            printf ("\n  malloc error %d ", N);
        }
    }

    return res;
}

