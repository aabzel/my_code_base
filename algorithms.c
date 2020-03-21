#include "algorithms.h"

#include "permutations.h"
#include "str_ops.h"
#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int max (int val1, int val2) {
    int outVal = val1;
    if (val1 < val2) {
        outVal = val2;
    }
    return outVal;
}

int min (int val1, int val2) {
    int outVal = val2;
    if (val1 < val2) {
        outVal = val1;
    }
    return outVal;
}

/* Function to swap values at two pointers */
void swap (char * const x, char * const y) {
    if (x != y) {
        char temp;
        temp = *x;
        *x = *y;
        *y = temp;
    } else {
        //printf ("The same element\n");
    }

}

typedef struct xPox_t {
    int x;
    int y;
} xPox_t;

#define DIM_OF_LUTABLE (100)
static int lootUpTable [DIM_OF_LUTABLE] [DIM_OF_LUTABLE];

#define USE_PRINT_LT 0

#if USE_PRINT_LT
static void print_lookUpTable (void) {
    printf ("\n");
    int amountOflines = 0;
    int x, y;
    for (x = 0; x < DIM_OF_LUTABLE; x++) {
        for (y = 0; y < DIM_OF_LUTABLE; y++) {
            if (0 <= lootUpTable [x] [y]) {
                amountOflines++;
                printf ("\n x: %d y: %d: path: %d ", x + 1, y + 1, lootUpTable [x] [y]);
            }
        }
    }
    printf ("\n amountOflines: %d ", amountOflines);

}
#endif

int g_mantchCnt = 0;
int g_unMantchCnt = 0;
static void init_lookUpTable (void) {
    printf ("\n");
    g_mantchCnt = 0;
    g_unMantchCnt = 0;
    int x, y;
    for (x = 0; x < DIM_OF_LUTABLE; x++) {
        for (y = 0; y < DIM_OF_LUTABLE; y++) {
            lootUpTable [x] [y] = -1;
        }
    }
    lootUpTable [0] [0] = 1;
    lootUpTable [1] [1] = 2;
    lootUpTable [2] [1] = 3;

#if HINT
    lootUpTable [50] [8] = 1916797311;
    lootUpTable [37] [9] = 1101716330;
#endif

}

static void updateLookUpTabel (int xMax, int yMax, int amountOfPaths) {
    if (xMax <= DIM_OF_LUTABLE && yMax <= DIM_OF_LUTABLE) {
        lootUpTable [xMax - 1] [yMax - 1] = amountOfPaths;
    }
}

static bool is_val_in_look_up_table (int xMax, int yMax) {
    bool res = false;

    if ((0 < xMax) && (xMax <= DIM_OF_LUTABLE)) {
        if ((0 < yMax) && (yMax <= DIM_OF_LUTABLE)) {
            int val = lootUpTable [xMax - 1] [yMax - 1];
            if (0 <= val) {
                res = true;
            }
        }

    }
    return res;
}

int unique_paths (int xMax, int yMax) {
    int amountOfPaths = 0;
    bool res = false;
    if (1 == xMax || 1 == yMax) {
        return 1;
    }
    res = is_val_in_look_up_table (xMax, yMax);
    if (true == res) {
        int val = lootUpTable [xMax - 1] [yMax - 1];
        g_mantchCnt++;
        return val;
    }
    g_unMantchCnt++;
    int amountOfPaths1 = 0;
    int amountOfPaths2 = 0;
    amountOfPaths1 = unique_paths (xMax - 1, yMax);
    amountOfPaths2 = unique_paths (xMax, yMax - 1);
    amountOfPaths = (amountOfPaths1 + amountOfPaths2);

    updateLookUpTabel (xMax, yMax, amountOfPaths);
    return amountOfPaths;
}

// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int (const void * p1, const void * p2) {
    int x = *(int *) p1; // добываем из указателя значение по этому указателю
    int y = *(int *) p2; // добываем из указателя значение по этому указателю
    return x - y;
}

int uniquePaths (int xMax, int yMax) {
#if DEBUG_AM_PATH
    printf ("\n %s %d %d", __FUNCTION__, xMax, yMax);
#endif

    int amountOfPaths;
    init_lookUpTable ();
    amountOfPaths = unique_paths (xMax, yMax);
#if DEBUG_AM_PATH
    printf ("\n g_mantchCnt %d g_unMantchCnt %d", g_mantchCnt, g_unMantchCnt);
#endif
#if USE_PRINT_LT
    print_lookUpTable ();
#endif
    return amountOfPaths;
}

