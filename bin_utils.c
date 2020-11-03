#include "bin_utils.h"

#include <math.h>
#include <string.h>

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
    // printf ("\n N %u\n", N);
    int max_gap = 0;
    int cur_cnt = 0;
    int cur_bit;
    int count_zero_mode = 0;
    for (i = 0; i < 32; i++) {
        cur_bit = N & (1 << i);
        if (0 < cur_bit) {
            //  printf ("cnt mode on i=%u\n", i);
            count_zero_mode = 1;
        }
        if (1 == count_zero_mode) {

            if (0 == cur_bit) {
                cur_cnt++;
                // printf ("+0 i=%u cnt %u\n", i, cur_cnt);
            } else {
                max_gap = max_int (max_gap, cur_cnt);
                cur_cnt = 0;
            }
        }
    }
    // write your code in C99 (gcc 6.2.0)
    return max_gap;
}

uint64_t swap_bits (uint64_t in_val) {
    uint64_t out_val = 0U;
    for (uint16_t i = 0U; i < 64U; i++) {
        if ((((uint64_t)1U) << i) == ((((uint64_t)1U) << i) & in_val)) {
            out_val |= (((uint64_t)1) << (63U - i));
        }
    }

    return out_val;
}

int64_t powi (int base, int exp) {
    int64_t res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

int reverse_dec (int in_x) {
    int64_t rev_dec = 0;
    int64_t x = (int64_t)in_x;
#ifdef DEBUG
    printf ("\nx=%d", x);
#endif
    int sign = 1;
    if (0 == x) {
        return 0;
    }
    if (x < 0) {
        x = -x;
        sign = -1;
    }
    uint8_t arr[13];
    memset (arr, 0xFF, sizeof (arr));
    int cnt = 0;
    uint8_t digit = 0;
    while (0 < x) {
        digit = x % 10;
#ifdef DEBUG
        printf ("\n[%d]=%d ", cnt, digit);
#endif
        arr[cnt] = digit;
        x = x / 10;
        cnt++;
    }
#ifdef DEBUG
    printf ("\n");
#endif
    // cnt - rank of x
    int rank = cnt - 1;
    if (0 <= rank) {
        rev_dec = 0;
        for (int i = (rank); 0 <= i; i--) {
            int64_t power = powi (10, (rank - i));
            int64_t incriment = ((int64_t)arr[i]) * (int64_t)power;
#ifdef DEBUG
            printf ("\narr[%d]=%d power %I64d %I64d", i, arr[i], power, incriment);
#endif
            rev_dec += incriment;
        }
    }
#ifdef DEBUG
    printf ("\nrev_dec=%I64d", rev_dec);
#endif
    if (2147483647 < rev_dec) {
        rev_dec = 0;
    }
#ifdef DEBUG
    printf ("\nlim rev_dec=%I64d", rev_dec);
#endif
    rev_dec = rev_dec * sign;
    return rev_dec;
}
