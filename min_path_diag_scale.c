#include "min_path_diag_scale.h"

#include "algorithms.h"
#include "arrays.h"
#include "float_utils.h"

#include <stdlib.h>
#include <math.h>

static float min_path_diag_scale_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, float curPrevSumm, bool isDiagEntry);

static float min_path_diag_scale (
    int* grid,
    int numLine,
    int numColumn,
    int curCellx,
    int curCelly,
    float curPrevSumm,
    float minSum,
    Cell_t * const dotArr,
    int lenOfCurrPath,
    Cell_t ** finalPath,
    int *lenOfFinalPath,
    bool isDiag);

float minPathDiagScaleSum (int* grid, int numLine, int numColumn) {
    float curSum1 = 0.0f;
    float curSum2 = 0.0f;
    float curSum3 = 0.0f;
    float minPathSum = 0;

    float minPathSum1 = 0.0f;
    float minPathSum2 = 0.0f;
    float minPathSum3 = 0.0f;
    int x = 0;
    int y = 0;
    int currCellVal = (*((int *) grid + x * numColumn + y));
    curSum1 = (1.4142) * ((float) currCellVal) / (2.0f);
    minPathSum1 = min_path_diag_scale_sum (grid, numLine, numColumn, x + 1, y + 1, curSum1, DIAG_ENTRY);

    curSum2 = ((float) currCellVal) / (2.0f);
    minPathSum2 = min_path_diag_scale_sum (grid, numLine, numColumn, x, y + 1, curSum2, STRAIGHT_ENTRY);

    curSum3 = ((float) currCellVal) / (2.0f);
    minPathSum3 = min_path_diag_scale_sum (grid, numLine, numColumn, x + 1, y, curSum3, STRAIGHT_ENTRY);

    minPathSum = min3f (minPathSum1, minPathSum2, minPathSum3);
    return minPathSum;
}

static float min_path_diag_scale_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, float curPrevSumm, bool isDiagEntry) {
#if DEBUG_MIN_DIAG_SCALE
    printf ("\n %dx%d-curPrevSumm: %f", curCellx, curCelly, curPrevSumm);
#endif
    float curAddSumIn = 0.0f;
    float curAddSumOut = 0.0f;
    float minPathSum = 0.0f;
    float minPathSum1 = 0.0f, minPathSum2 = 0.0f, minPathSum3 = 0.0f;
    float curTotalSum1, curTotalSum2, curTotalSum3;
    int curCellVal = 0.0;
    if ((curCellx < numColumn) && (curCelly < numLine)) {
        curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
        if (isDiagEntry) {
            curAddSumIn = (1.414213) * ((float) curCellVal) / (2.0f);
        } else {
            curAddSumIn = ((float) curCellVal) / (2.0f);
        }
    } else {
        printf ("\n Out of bound!\n");
        return 9999990.0f;
    }

    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {
            curAddSumOut = ((1.414213f) * ((float) curCellVal) / (2.0f));
            curTotalSum1 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum1 = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx + 1, curCelly + 1, curTotalSum1, DIAG_ENTRY);

            curAddSumOut = (((float) curCellVal) / (2.0f));
            curTotalSum2 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum2 = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curTotalSum2, STRAIGHT_ENTRY);

            curAddSumOut = (((float) curCellVal) / (2.0f));
            curTotalSum3 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum3 = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curTotalSum3, STRAIGHT_ENTRY);

            minPathSum = min3f (minPathSum1, minPathSum2, minPathSum3);
        } else {
            //curCelly = numLine-1
            curAddSumOut = (((float) curCellVal) / (2.0f));
            curTotalSum1 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curTotalSum1, STRAIGHT_ENTRY);
        }
    } else {
        //curCellx = numColumn-1
        if (curCelly < (numLine - 1)) {
            curAddSumOut = (((float) curCellVal) / (2.0f));
            curTotalSum1 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curTotalSum1, STRAIGHT_ENTRY);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1

            minPathSum = curPrevSumm + curAddSumIn;
            printf ("\n Final minPathSum: %f", minPathSum);
        }
    }
    return minPathSum;
}

bool minPathDiagScale (int* grid, int numLine, int numColumn) {
    bool res = false;
    int numPath = uniquePathDiag (numLine, numColumn);
    printf ("\n %dx%d Amount of Path %d\n\n", numLine, numColumn, numPath);
    float mPathSum = minPathDiagScaleSum (grid, numLine, numColumn);
    printf ("\n %dx%d  sumOfMinPathDiagScale: [%f]\n\n", numLine, numColumn, mPathSum);
    Cell_t *minPath = NULL;
    int minPathLen;
    find_min_path_diag_stale ((int*) grid, numLine, numColumn, mPathSum, &minPath, &minPathLen);
    if (minPath) {
        //print_path (minPath, minPathLen);
        save_map_path_as_dot ("minPathDiagScale.dot", grid, numLine, numColumn, minPath, minPathLen);
        printf ("\n find_min_path done !\n");
        free (minPath);
        res = true;
    } else {
        res = false;
        printf ("\n\n\n\a min path NOT FOUND ! \n\n");
    }
    return res;
}

void find_min_path_diag_stale (int* grid, int numLine, int numColumn, float minSum, Cell_t **minPathArr, int *minPathLen) {
    float outSumm = 0.0f;
    int x = 0;
    int y = 0;
    int lenOfCurrPath = 0;
    *minPathLen = 0;
    *minPathArr = NULL;
    int curCellVal = *((int *) grid + x * numColumn + y);
    lenOfCurrPath = 1;

    if ((0 == *minPathLen) && (NULL == *minPathArr)) {
        Cell_t *currPath1 = malloc (sizeof(Cell_t));
        if (currPath1) {
            outSumm = ((float) curCellVal) * (SQRT2) / (2.0f);
            currPath1->x = 0;
            currPath1->y = 0;
            currPath1->val = outSumm;
            min_path_diag_scale ((int*) grid, numLine, numColumn, x + 1, y + 1, outSumm, minSum, currPath1, lenOfCurrPath, minPathArr, minPathLen,
            true);
        }
    }

    if ((0 == *minPathLen) && (NULL == *minPathArr)) {
        Cell_t *currPath2 = malloc (sizeof(Cell_t));
        if (currPath2) {
            outSumm = ((float) curCellVal) / (2.0f);
            currPath2->x = 0;
            currPath2->y = 0;
            currPath2->val = outSumm;
            min_path_diag_scale ((int*) grid, numLine, numColumn, x + 1, y, outSumm, minSum, currPath2, lenOfCurrPath, minPathArr, minPathLen, false);
        }
    }

    if ((0 == *minPathLen) && (NULL == *minPathArr)) {
        Cell_t *currPath3 = malloc (sizeof(Cell_t));
        if (currPath3) {
            outSumm = ((float) curCellVal) / (2.0f);
            currPath3->x = 0;
            currPath3->y = 0;
            currPath3->val = outSumm;
            min_path_diag_scale ((int*) grid, numLine, numColumn, x, y + 1, outSumm, minSum, currPath3, lenOfCurrPath, minPathArr, minPathLen, false);
        }
    }
}

static float min_path_diag_scale (
    int* grid,
    int numLine,
    int numColumn,
    int curCellx,
    int curCelly,
    float curPrevSumm,
    float minSum,
    Cell_t * const dotArr,
    int lenOfCurrPath,
    Cell_t ** finalPath,
    int *lenOfFinalPath,
    bool isDiag) {
    static int callDeep = 1;

    float curAddSumIn = 0.0f;
    float curAddSumOut = 0.0f;
    callDeep++;
    float minPathSum1 = 0, minPathSum2 = 0, minPathSum3 = 0, minPathSum = 0;
    int curCellVal = 0;
    Cell_t *locArr = NULL;

    /*TODO: check matrix border*/
    if ((curCellx < (numColumn)) && (curCelly < (numLine))) {
        curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
        if (true == isDiag) {
            curAddSumIn = ((float) curCellVal) * sqrt (2.0f) / (2.0f);
        } else {
            curAddSumIn = ((float) curCellVal) / (2.0f);
        }
    } else {
        printf ("\nOut of bound x: %d y: %d  in %dx%d\n", curCellx, curCelly, numLine, numColumn);
        free (dotArr);
        return 9999999999;
    }

    if (minSum < (curPrevSumm + curAddSumIn)) {
        free (dotArr);
#if DEBUG_MIN_PATH_DIAG_SCALE_DEADLOC
        printf ("\n->[%d][%d] %d-deadlock\n", curCellx, curCelly, curPrevSumm + curAddSumIn);
#endif
        return curPrevSumm;
    } else {
        // create a copy of LL in heap mem
        locArr = (Cell_t *) memdup (dotArr, (lenOfCurrPath + 1) * sizeof(Cell_t));
        if (locArr) {
            locArr [lenOfCurrPath].x = curCellx;
            locArr [lenOfCurrPath].y = curCelly;
            locArr [lenOfCurrPath].val = curCellVal;
        } else {
            printf ("\n  Lack of heap memory!\n");
            return 99999999;
        }
        // add a dot to LL
#if DEBUG_MIN_PATH_DIAG
        printf ("[%d,%d]->", curCellx, curCelly);
#endif
    }
    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {

            curAddSumOut = ((float) curCellVal) * sqrt (2.0f) / (2.0f);
            float curTotalSum1 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum1 = min_path_diag_scale (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly + 1,
                curTotalSum1,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath,
                true);

            curAddSumOut = ((float) curCellVal) / (2.0f);
            float curTotalSum2 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum2 = min_path_diag_scale (
                grid,
                numLine,
                numColumn,
                curCellx,
                curCelly + 1,
                curTotalSum2,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath,
                false);

            curAddSumOut = ((float) curCellVal) / (2.0f);
            float curTotalSum3 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum3 = min_path_diag_scale (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly,
                curTotalSum3,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath,
                false);

            minPathSum = min3f (minPathSum1, minPathSum2, minPathSum3);
        } else {
            //curCelly=numLine-1
            curAddSumOut = ((float) curCellVal) / (2.0f);
            float curTotalSum1 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum = min_path_diag_scale (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly,
                curTotalSum1,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath,
                false);
        }
    } else {
        //curCellx=numColumn-1
        if (curCelly < (numLine - 1)) {
            curAddSumOut = ((float) curCellVal) / (2.0f);
            float curTotalSum1 = curPrevSumm + curAddSumIn + curAddSumOut;
            minPathSum = min_path_diag_scale (
                grid,
                numLine,
                numColumn,
                curCellx,
                curCelly + 1,
                curTotalSum1,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath,
                false);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1
            minPathSum = curPrevSumm + curAddSumIn;
            //Print final Arrays
#if DEBUG_MIN_PATH_DIAG
            print_path (locArr, lenOfCurrPath + 1);
#endif
#if DEBUG_MIN_PATH_DIAG_END
            printf (" End ! Sum: %f lenOfPath: %d\n", minPathSum, lenOfCurrPath + 1);
#endif
            if (is_floats_equal (minPathSum, minSum)) {
                *finalPath = locArr;
                *lenOfFinalPath = lenOfCurrPath + 1;
#if DEBUG_MIN_PATH_DIAG_END
                printf (" EndOfRoute! Sum: %f lenOfPath: %d\n", minPathSum, lenOfCurrPath + 1);
#endif
            } else {
                free (locArr);
            }
            //return LL to up
        }
    }

    callDeep--;

    return minPathSum;
}

