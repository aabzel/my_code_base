#include "russian_doll_envelopes.h"

#include "algorithms.h"
#include "arrays.h"
#include "custom_type.h"
#include "permutations.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxEnvelopes (int **envelopes, int envelopesSize, int *envelopesColSize) {
    int amount = 1;
    if (envelopes) {
        if (0 < envelopesSize) {
            int amountOfCombinations;
            amountOfCombinations = factorial (envelopesSize);
#if DEBUG_INPUT
            for (int i = 0; i < envelopesSize; i++) {
                printf ("\n %d %d", envelopes[i][0], envelopes[i][1]);
            }
            printf ("\n %d", amountOfCombinations);
#endif
            // how many ways to list envelops
            // printf ("\n Progress %d\n", amountOfCombinations);
            int spotPermutCnt = 0;
            for (int i = 0; i < amountOfCombinations; i++) {
                // get array of indeces
                // if (0 == (i % (amountOfCombinations / 1000))) {
                //    printf ("\r %d", i);
                //}
                int *arraOfIndex = malloc (sizeof (int) * envelopesSize);
                if (arraOfIndex) {
                    memset (arraOfIndex, 0, sizeof (int) * envelopesSize);
                    bool res = false;
                    res = get_i_permutation_of_n (envelopesSize, i, arraOfIndex);
                    if (true == res) {
                        spotPermutCnt++;
#if DEBUG_PROGRESS
                        printf ("\n i: %d/%d ", i, amountOfCombinations);
#endif

#if DEBUG_ENVELOP_PERMUTATION
                        print_curr_array (arraOfIndex, envelopesSize);
#endif
                        // 0 3
                        // 01 12 23
                        int cntNesting = 1;
                        for (int invel = 0; invel < (envelopesSize - 1); invel++) {
                            xEnvelop_t container = {0, 0};
                            xEnvelop_t object = {0, 0};
                            int indexOfContainer = arraOfIndex[invel];
                            int indexOfObject = arraOfIndex[invel + 1];
                            if ((0 <= indexOfContainer) && (indexOfContainer < envelopesSize)) {
                                container.widths = envelopes[indexOfContainer][0];
                                container.heights = envelopes[indexOfContainer][1];
                            } else {
                                printf ("\n%s indexOfContainer %d \n", __FUNCTION__, indexOfContainer);
                            }
                            if ((0 <= indexOfObject) && (indexOfObject < envelopesSize)) {
                                object.widths = envelopes[indexOfObject][0];
                                object.heights = envelopes[indexOfObject][1];
                            } else {
                                printf ("\n%s indexOfObject %d \n", __FUNCTION__, indexOfObject);
                            }
                            if (is_fit (container, object)) {
                                cntNesting++;
                                amount = max (amount, cntNesting);
                            } else {
                                cntNesting = 1;
                            }
                        }
#if DEBUG_ENVEL1
                        printf (" : %d", cntNesting);
#endif
                        amount = max (amount, cntNesting);
                    } else {
                        printf ("\n i: undetermined permutation %d/%d ", i, amountOfCombinations);
                    }
                    free (arraOfIndex);
                }
            }
            if (spotPermutCnt != amountOfCombinations) {
                printf ("\n%s not all permutation checked ! %d/%d\n", __FUNCTION__, spotPermutCnt,
                        amountOfCombinations);
            }
            if (envelopesColSize) {
                *envelopesColSize = 2;
            }
        }
    }
    return amount;
}

// как передбрать все пути
// как перебрать все перестановки 1......envelopesSize порядок имеет значение envelopesSize! способов 4!=
// пройтсь по всей ветке посчитать количество вложенных конвертов сравнить с массимальным если получилось больше то
// запомить это число

bool is_fit (xEnvelop_t container, xEnvelop_t object) {
    bool res = false;
    if (object.widths < container.widths) {
        if (object.heights < container.heights) {
            res = true;
        }
    }
    return res;
}
