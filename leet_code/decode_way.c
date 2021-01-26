#include "decode_way.h"

#include "algorithms.h"
#include "array_type.h"
#include "arrays.h"
#include "convert.h"
#include "str_ops.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gway = 0;
static char lookUpTable[27] = {'_', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static void num_decoding (char *in_str, int *inArr, int arrSize) {
    // printf("\n%s() [%s]", __FUNCTION__, in_str);
    bool res;
    static int end = 1;
    if ((NULL != in_str) && (true == is_dec_digit (in_str[0])) && (0 < strlen (in_str))) {
        uint8_t val;
        if (2 <= strlen (in_str)) {
            res = try_strl2uint8 (&in_str[0], 2, &val);
            if (true == res) {
                if ((10 <= val) && (val <= 26)) {
                    int *cur_arr;
                    // cur_arr = add_val_to_end_array(inArr, arrSize, val);
                    num_decoding (&in_str[2], cur_arr, arrSize + 1);
                    // free(cur_arr );
                } else {
                    printf ("\nError val %u", val);
                }
            } else {
                printf ("\n Unable to parse 2d [%s]", &in_str[0]);
            }
        }
        res = try_strl2uint8 (&in_str[0], 1, &val);
        if (true == res) {
            if (0 < val) {
                int *cur_arr;
                // cur_arr = add_val_to_end_array(inArr, arrSize, val);
                num_decoding (&in_str[1], cur_arr, arrSize + 1);
                // free(cur_arr );
            }
        } else {
            printf ("\n Unable to parse 1d [%s]", &in_str[0]);
        }

    } else {
        // if (inArr) {
        //		printf("\n(");
        //	for (int i = 0; i < arrSize; i++) {
        //		printf(" %c,", lookUpTable[inArr[i]]);
        //	}
        //	printf(" )\n");
        //}
        // printf(".");
        end = 0;
        gway++;
        // if ((0 == inArr[0]) && (1 == arrSize)) {
        //	gway = 0;
        //}
    }
    // return ways;
}

// int numDecodings(char *in_str) {
//	gway = 0;
//	num_decoding(in_str, NULL, 0);
//	return gway;
//}

// 20
int numDecodings (char *s) {
    if (0 == strlen (s) || s[0] == '0') {
        return 0;
    }
    // r2: decode ways of s[i-2] , r1: decode ways of s[i-1]
    int r1 = 1, r2 = 1;
    for (int i = 1; i < strlen (s); i++) {
        // zero voids ways of the last because zero cannot be used separately
        if (s[i] == '0') {
            r1 = 0;
        }
        // possible two-digit letter, so new r1 is sum of both while new r2 is the old r1
        if ((s[i - 1] == '1') || ((s[i - 1] == '2') && (s[i] <= '6'))) {
            r1 = r2 + r1;
            r2 = r1 - r2;
        } else {
            // one-digit letter, no new way added
            r2 = r1;
        }
    }

    return r1;
}
