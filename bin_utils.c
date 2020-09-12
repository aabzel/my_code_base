#include "bin_utils.h"

#include "algorithms.h"

#define SKIP_ZER 0
#define CNT_ZER 1

int proc_bit (int bit, int *cur_state, int *cnt) {
    int cur_gap = 0;
    if (SKIP_ZER == *cur_state) {
        if (0 == bit) {
            (*cur_state) = SKIP_ZER;
        }
        if (1 == bit) {
            printf ("count 0\n");
            (*cur_state) = CNT_ZER;
            (*cnt) = 0;
        }
    }
    if (CNT_ZER == *cur_state) {
        if (0 == bit) {
            printf ("0");
            (*cnt)++;
        }
        if (1 == bit) {
            printf ("cnt %u\n", *cnt);
            cur_gap = *cnt;
            (*cnt) = 0;
        }
    }
    return cur_gap;
}

int binary_gap (int N) {
    int i = 0;
    printf ("\n N %u\n", N);
    int max_gap = 0;
    int cur_cnt = 0;
    int cur_bit;
    int count_zero_mode = 0;
    for (i = 0; i < 32; i++) {
        cur_bit = N & (1 << i);
        if (0 < cur_bit) {
            printf ("cnt mode on i=%u\n", i);
            count_zero_mode = 1;
        }
        if (1 == count_zero_mode) {

            if (0 == cur_bit) {
                cur_cnt++;
                printf ("+0 i=%u cnt %u\n", i, cur_cnt);
            } else {
                max_gap = max_int (max_gap, cur_cnt);
                cur_cnt = 0;
            }
        }
    }
    // write your code in C99 (gcc 6.2.0)
    return max_gap;
}
