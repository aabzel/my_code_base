#include "evbox_task.h"
#include "uTests.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STEP01 125
#define STEP12 375
#define STEP23 625
#define STEP34 875

#define DIFF 25

static unsigned int evaluate_down(unsigned int input_percent_10) {
    unsigned int out_val = 4U;
    if (input_percent_10 < (STEP01-DIFF)) {
        out_val = 0U;
    } else if (input_percent_10 < (STEP12-DIFF)) {
        out_val = 1U;
    } else if (input_percent_10 < (STEP23-DIFF)) {
        out_val = 2U;
    } else if (input_percent_10 < (STEP34-DIFF)) {
        out_val = 3U;
    } else {
    }
    return out_val;
}

static unsigned int evaluate_up(unsigned int input_percent_10) {
    unsigned int out_val = 0U;
    if ((STEP34+DIFF) < input_percent_10) {
        out_val = 4U;
    } else if ((STEP23+DIFF) < input_percent_10) {
        out_val = 3U;
    } else if ((STEP12+DIFF) < input_percent_10) {
        out_val = 2U;
    } else if ((STEP01+DIFF) < input_percent_10) {
        out_val = 1U;
    } else {
    }
    return out_val;
}

unsigned int hysteresis(unsigned int input_percent) {
    unsigned int input_percent_10 = input_percent * 10U;
    unsigned int out_val = 0;
    static unsigned int out_val_prev = 0;

    unsigned int out_val_up = evaluate_up(input_percent_10);
    unsigned int out_val_down = evaluate_down(input_percent_10);
    if (out_val_up == out_val_down) {
        out_val = out_val_up;
    } else {
/*hysteresis zone*/
#if 0
	  printf("\nin %u ", input_percent);
	  printf("up   %u ", out_val_up);
	  printf("down %u ", out_val_down);
	  printf("prev %u \n", out_val_prev);
#endif
        if (out_val_prev < out_val_up) {
            out_val = out_val_up;
        } else if (out_val_down < out_val_prev) {
            out_val = out_val_down;
        } else {
            out_val = out_val_prev;
        }
    }

    out_val_prev = out_val;
    return out_val;
}
