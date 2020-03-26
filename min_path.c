#include "min_path.h"

#include "algorithms.h"
#include "arrays.h"
#include "custom_type.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int g_mantchCnt = 0;
int g_unMantchCnt = 0;

static int lootUpTable [DIM_OF_LUTABLE] [DIM_OF_LUTABLE];
static int UniqPathDiagLootUpTable [DIM_OF_LUTABLE] [DIM_OF_LUTABLE];

/*
 *
 Given a m x n grid filled with non-negative numbers, find a path from
 top left to bottom right which minimizes the sum of all numbers along its path.

 Note: You can only move either down or right at any point in time.
 */

static int min_path (
    int* grid,
    int numLine,
    int numColumn,
    int curCellx,
    int curCelly,
    int curPrevSumm,
    int minSum,
    Cell_t * const dotArr,
    int lenOfCurrPath,
    Cell_t ** finalPath,
    int *lenOfFinalPath);

static int min_path_diag (
    int* grid,
    int numLine,
    int numColumn,
    int curCellx,
    int curCelly,
    int curPrevSumm,
    int minSum,
    Cell_t * const dotArr,
    int lenOfCurrPath,
    Cell_t ** finalPath,
    int *lenOfFinalPath);

static bool is_val_in_look_up_table (int * const table, int x, int y);
static void updateLookUpTabel (int * const matrix, int x, int y, int val);
static void initUniqPathDiagLookUpTable (void);
static void init_lookUpTable (void);
static bool is_exist_in_path (int x, int y, Cell_t * const arrayOfDot, int sizeOfPath);
static int min_path_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm);
static int min_path_diag_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm);

int minPathDiagSum (int* grid, int numLine, int numColumn) {
    int curSum = 0;
    int minPathSum = 0;
    int minPathSum1 = 0;
    int minPathSum2 = 0;
    int minPathSum3 = 0;
    int x = 0;
    int y = 0;
    curSum = *((int *) grid + x * numColumn + y);
    minPathSum1 = min_path_diag_sum (grid, numLine, numColumn, x + 1, y + 1, curSum);
    minPathSum2 = min_path_diag_sum (grid, numLine, numColumn, x, y + 1, curSum);
    minPathSum3 = min_path_diag_sum (grid, numLine, numColumn, x + 1, y, curSum);
    minPathSum = min3 (minPathSum1, minPathSum2, minPathSum3);
    return minPathSum;
}

int minPathSum (int* grid, int numLine, int numColumn) {
    int curSum = 0;
    int minPathSum = 0;
    int minPathSum1 = 0;
    int minPathSum2 = 0;
    int x = 0;
    int y = 0;
    curSum = *((int *) grid + x * numColumn + y);
    minPathSum1 = min_path_sum (grid, numLine, numColumn, x, y + 1, curSum);
    minPathSum2 = min_path_sum (grid, numLine, numColumn, x + 1, y, curSum);
    minPathSum = min (minPathSum1, minPathSum2);
    return minPathSum;
}

void find_min_path (int* grid, int numLine, int numColumn, int minSum, Cell_t **minPathArr, int *minPathLen) {
    int curSum = 0;
    int x = 0;
    int y = 0;
    int lenOfCurrPath = 0;
    *minPathLen = 0;
    *minPathArr = NULL;
    //printf ("\n[%d,%d]->", 0, 0);
    curSum = *((int *) grid + x * numColumn + y);
    lenOfCurrPath = 1;

    Cell_t currPath1 [1];
    currPath1 [0].x = 0;
    currPath1 [0].y = 0;
    currPath1 [0].val = curSum;
    min_path (grid, numLine, numColumn, x, y + 1, curSum, minSum, currPath1, lenOfCurrPath, minPathArr, minPathLen);
    if ((0 == minPathLen) && (NULL == *minPathArr)) {
        Cell_t currPath2 [1];
        currPath2 [0].x = 0;
        currPath2 [0].y = 0;
        currPath2 [0].val = curSum;
        min_path (grid, numLine, numColumn, x + 1, y, curSum, minSum, currPath2, lenOfCurrPath, minPathArr, minPathLen);
    }
    //printf ("\n[%d,%d]->", 0, 0);

}

/* ак получить на выходе св€занный список с координатами наименьшего пути?*/
/*«аписывать в файл все пути а потом произвести его синтаксический разбор и выбрать тот, что дошел до конца. (медленно)*/
/*ѕри каждом вызове функции min_path передавать в нее список уже пройденных точек. ѕри
 * достижении тупика удал€ть этот список. ѕри достижении цели возвращать этот список*/
void find_min_path_diag (int* grid, int numLine, int numColumn, int minSum, Cell_t **minPathArr, int *minPathLen) {
    int curSum = 0;
    int x = 0;
    int y = 0;
    int lenOfCurrPath = 0;
    *minPathLen = 0;
    *minPathArr = NULL;
    //printf ("\n[%d,%d]->", 0, 0);
    curSum = *((int *) grid + x * numColumn + y);
    lenOfCurrPath = 1;

    if ((0 == *minPathLen) && (NULL == *minPathArr)) {
        Cell_t *currPath1 = malloc (sizeof(Cell_t));
        if (currPath1) {
            currPath1->x = 0;
            currPath1->y = 0;
            currPath1->val = curSum;
            min_path_diag (grid, numLine, numColumn, x + 1, y + 1, curSum, minSum, currPath1, lenOfCurrPath, minPathArr, minPathLen);
        }
    }

    if ((0 == *minPathLen) && (NULL == *minPathArr)) {
        Cell_t *currPath2 = malloc (sizeof(Cell_t));
        if (currPath2) {
            currPath2->x = 0;
            currPath2->y = 0;
            currPath2->val = curSum;
            min_path_diag (grid, numLine, numColumn, x + 1, y, curSum, minSum, currPath2, lenOfCurrPath, minPathArr, minPathLen);
        }
    }

    if ((0 == *minPathLen) && (NULL == *minPathArr)) {
        Cell_t *currPath3 = malloc (sizeof(Cell_t));
        if (currPath3) {
            currPath3->x = 0;
            currPath3->y = 0;
            currPath3->val = curSum;
            min_path_diag (grid, numLine, numColumn, x, y + 1, curSum, minSum, currPath3, lenOfCurrPath, minPathArr, minPathLen);
        }
    }

    //printf ("\n[%d,%d]->", 0, 0);

}

bool minPathDiag (int* grid, int numLine, int numColumn) {
    int numPath = uniquePathDiag (numLine, numColumn);
    printf ("\n Amount of Path %d\n", numPath);
    int mPathSum = minPathDiagSum (grid, numLine, numColumn);
    printf ("\n sumOfMinPath: [%d]\n", mPathSum);
    Cell_t *minPath = NULL;
    int minPathLen;
    find_min_path_diag (grid, numLine, numColumn, mPathSum, &minPath, &minPathLen);
    if (minPath) {
        //print_path (minPath, minPathLen);
        save_map_path_as_dot ("minPathDiag.dot", grid, numLine, numColumn, minPath, minPathLen);
        printf ("\n find_min_path done !\n");
        free(minPath);
    } else {
        printf ("\n\n\n min path not found ! \n\n");
    }

    return true;
}

bool minPath (int* grid, int numLine, int numColumn) {
    int numPath = uniquePaths (numLine, numColumn);
    printf ("\n Amount of Path %d", numPath);
    int mPathSum = minPathSum (grid, numLine, numColumn);
    printf ("\n sumOfMinPath %d", mPathSum);
    Cell_t *minPath = NULL;
    int minPathLen;
    find_min_path (grid, numLine, numColumn, mPathSum, &minPath, &minPathLen);
    if (minPath) {
        //print_path (minPath, minPathLen);
        save_map_path_as_dot ("minPath.dot", grid, numLine, numColumn, minPath, minPathLen);
        printf ("\n find_min_path done !\n");
    } else {
        printf ("\n min path not found !\n");
    }

    return true;
}

int uniquePathDiag (int xMax, int yMax) {
    int amountOfPaths;
    initUniqPathDiagLookUpTable ();
    amountOfPaths = unique_path_diag (xMax, yMax);
#if USE_PRINT_LT_DIAG
    printf ("\n %dx%d amountOfPaths %d", xMax, yMax, amountOfPaths);
    print_lookUpTable ((int *) UniqPathDiagLootUpTable);
#endif
    return amountOfPaths;
}

int unique_path_diag (int xMax, int yMax) {
    int amountOfPaths = 0;
    bool res = false;
    if (1 == xMax || 1 == yMax) {
        amountOfPaths = UniqPathDiagLootUpTable [0] [0];
    } else {
        res = is_val_in_look_up_table ((int *) UniqPathDiagLootUpTable, xMax, yMax);
        if (true == res) {
            amountOfPaths = UniqPathDiagLootUpTable [xMax - 1] [yMax - 1];
            g_mantchCnt++;
        } else {
            g_unMantchCnt++;
            int amountOfPaths1 = 0;
            int amountOfPaths2 = 0;
            int amountOfPaths3 = 0;
            amountOfPaths1 = unique_path_diag (xMax - 1, yMax);
            amountOfPaths2 = unique_path_diag (xMax, yMax - 1);
            amountOfPaths3 = unique_path_diag (xMax - 1, yMax - 1);
            amountOfPaths = (amountOfPaths1 + amountOfPaths2 + amountOfPaths3);

            updateLookUpTabel ((int *) UniqPathDiagLootUpTable, xMax, yMax, amountOfPaths);
        }
    }

    return amountOfPaths;
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
    print_lookUpTable ((int*) lootUpTable);
#endif
    return amountOfPaths;
}

static int min_path (
    int* grid,
    int numLine,
    int numColumn,
    int curCellx,
    int curCelly,
    int curPrevSumm,
    int minSum,
    Cell_t * const dotArr,
    int lenOfCurrPath,
    Cell_t ** finalPath,
    int *lenOfFinalPath) {
    static int callDeep = 1;
    callDeep++;
    int curOutSum = 0;
    int minPathSum1 = 0, minPathSum2 = 0, minPathSum = 0;
    int curCellVal = 0;
    Cell_t *locArr = NULL;
    if (minSum < curPrevSumm) {
        //free LL of dots
        free (dotArr);
#if DEBUG_MIN_PATH
        printf ("-deadlock\n");
#endif
        return curPrevSumm;
    } else {
        curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
        // create a copy of LL in heap mem
        locArr = (Cell_t *) memdup (dotArr, (lenOfCurrPath + 1) * sizeof(Cell_t));
        if (locArr) {
            locArr [lenOfCurrPath].x = curCellx;
            locArr [lenOfCurrPath].y = curCelly;
            locArr [lenOfCurrPath].val = curCellVal;
        } else {
            printf ("\nLack of heap memory");
        }
        // add a dot to LL
#if DEBUG_MIN_PATH
        printf ("[%d,%d]->", curCellx, curCelly);
#endif
    }
    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum1 = min_path (
                grid,
                numLine,
                numColumn,
                curCellx,
                curCelly + 1,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
            minPathSum2 = min_path (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
            minPathSum = min (minPathSum1, minPathSum2);
        } else {
            //curCelly=numLine-1
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
        }
    } else {
        //curCellx=numColumn-1
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path (
                grid,
                numLine,
                numColumn,
                curCellx,
                curCelly + 1,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1
            minPathSum = curPrevSumm + curCellVal;
            //Print final Arrays
#if DEBUG_MIN_PATH
            print_path (locArr, lenOfCurrPath + 1);
#endif
            *finalPath = locArr;
            *lenOfFinalPath = lenOfCurrPath + 1;
            //return LL to up
#if DEBUG_MIN_PATH
            printf (" EndOfRoute! Sum: %d len: %d\n", minPathSum, callDeep);
#endif
        }
    }

    callDeep--;

    return minPathSum;
}

static int min_path_diag (
    int* grid,
    int numLine,
    int numColumn,
    int curCellx,
    int curCelly,
    int curPrevSumm,
    int minSum,
    Cell_t * const dotArr,
    int lenOfCurrPath,
    Cell_t ** finalPath,
    int *lenOfFinalPath) {
    static int callDeep = 1;
    callDeep++;
    int curOutSum = 0;
    int minPathSum1 = 0, minPathSum2 = 0, minPathSum3 = 0, minPathSum = 0;
    int curCellVal = 0;
    Cell_t *locArr = NULL;
    if (minSum < curPrevSumm) {
        //free LL of dots
        free (dotArr);
#if DEBUG_MIN_PATH_DIAG
        printf ("\n->[%d][%d]-deadlock\n", curCellx, curCelly);
#endif
        return curPrevSumm;
    } else {
        curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
        // create a copy of LL in heap mem
        locArr = (Cell_t *) memdup (dotArr, (lenOfCurrPath + 1) * sizeof(Cell_t));
        if (locArr) {
            locArr [lenOfCurrPath].x = curCellx;
            locArr [lenOfCurrPath].y = curCelly;
            locArr [lenOfCurrPath].val = curCellVal;
        } else {
            printf ("\n  Lack of heap memory!\n");
        }
        // add a dot to LL
#if DEBUG_MIN_PATH_DIAG
        printf ("[%d,%d]->", curCellx, curCelly);
#endif
    }
    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum1 = min_path_diag (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly + 1,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
            minPathSum2 = min_path_diag (
                grid,
                numLine,
                numColumn,
                curCellx,
                curCelly + 1,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
            minPathSum3 = min_path_diag (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
            minPathSum = min3 (minPathSum1, minPathSum2, minPathSum3);
        } else {
            //curCelly=numLine-1
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path_diag (
                grid,
                numLine,
                numColumn,
                curCellx + 1,
                curCelly,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
        }
    } else {
        //curCellx=numColumn-1
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path_diag (
                grid,
                numLine,
                numColumn,
                curCellx,
                curCelly + 1,
                curOutSum,
                minSum,
                locArr,
                lenOfCurrPath + 1,
                finalPath,
                lenOfFinalPath);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1
            minPathSum = curPrevSumm + curCellVal;
            //Print final Arrays
#if DEBUG_MIN_PATH_DIAG
            print_path (locArr, lenOfCurrPath + 1);
#endif
            if (minPathSum == minSum) {
                *finalPath = locArr;
                *lenOfFinalPath = lenOfCurrPath + 1;
#if DEBUG_MIN_PATH_DIAG_END
                printf (" EndOfRoute! Sum: %d lenOfPath: %d\n", minPathSum, lenOfCurrPath + 1);
#endif
            }else{
                free(locArr);
            }
            //return LL to up
        }
    }

    callDeep--;

    return minPathSum;
}

static int min_path_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm) {
    int curOutSum = 0;
    int minPathSum1 = 0, minPathSum2 = 0, minPathSum = 0;

    int curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum1 = min_path_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curOutSum);
            minPathSum2 = min_path_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curOutSum);
            minPathSum = min (minPathSum1, minPathSum2);
        } else {
            //curCelly=numLine-1
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curOutSum);
        }
    } else {
        //curCellx=numColumn-1
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curOutSum);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1
            minPathSum = curPrevSumm + curCellVal;
        }
    }
    return minPathSum;
}

static int min_path_diag_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm) {
    int curOutSum = 0;
    int minPathSum1 = 0, minPathSum2 = 0, minPathSum3 = 0, minPathSum = 0;

    int curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum1 = min_path_diag_sum (grid, numLine, numColumn, curCellx + 1, curCelly + 1, curOutSum);
            minPathSum2 = min_path_diag_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curOutSum);
            minPathSum3 = min_path_diag_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curOutSum);
            minPathSum = min3 (minPathSum1, minPathSum2, minPathSum3);
        } else {
            //curCelly=numLine-1
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path_diag_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curOutSum);
        }
    } else {
        //curCellx=numColumn-1
        if (curCelly < (numLine - 1)) {
            curOutSum = curPrevSumm + curCellVal;
            minPathSum = min_path_diag_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curOutSum);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1
            minPathSum = curPrevSumm + curCellVal;
        }
    }
    return minPathSum;
}

bool test_min_path_diag (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathDiagSum ((int *) grid, numOfLine, numOfcolomn);
    if (5 == minSum) {
        res = true;
    } else {
        return false;
    }
#define TEST_DIM 3
    int grid1 [TEST_DIM] [TEST_DIM];
    res = init_one_map ((int *) grid1, TEST_DIM, TEST_DIM);
    minSum = minPathDiagSum ((int *) grid1, TEST_DIM, TEST_DIM);
    if (TEST_DIM == minSum) {
        res = true;
    } else {
        return false;
    }
#define TEST_DIM2 8
    int grid2 [TEST_DIM2] [TEST_DIM2];
    //init_rod_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    //init_rand_array((int *) grid2, TEST_DIM2, TEST_DIM2);
    init_box_map((int *) grid2, TEST_DIM2, TEST_DIM2);
    //init_ramp_map ((int *) grid2, TEST_DIM2, TEST_DIM2);
    minPathDiag ((int *) grid2, TEST_DIM2, TEST_DIM2);
    //int grid2 [10] [10];
    //numOfLine = 10;
    //numOfcolomn = 10;
    //init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    //init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    //minSum = minPathSum ((int *) grid2, 10, 10);
    //save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    //minPath ((int *) grid2, numOfLine, numOfcolomn);

    return res;
}

bool test_min_path (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int numOfLine = 3;
    int numOfcolomn = 3;
    minSum = minPathSum ((int *) grid, numOfLine, numOfcolomn);
    if (7 == minSum) {
        res = true;
    } else {
        return false;
    }
    //save_array_as_dot ("map1.dot", (int *) grid, 3, 3);

    //minPath ((int *) grid, sizeOfGrid, gridColSize);
    int grid2 [10] [10];
    numOfLine = 10;
    numOfcolomn = 10;
    init_ramp_map ((int *) grid2, numOfLine, numOfcolomn);
    //init_rand_array ((int *) grid2, numOfLine, numOfcolomn);
    //minSum = minPathSum ((int *) grid2, 10, 10);
    //save_array_as_dot ("map.dot", (int *) grid2, 10, 10);
    minPath ((int *) grid2, numOfLine, numOfcolomn);

    return res;
}

bool init_rand_array (int *grid, int numLine, int numColumn) {
    time_t t;
    bool res = false;
    if (NULL != grid) {
        res = true;
        srand ((unsigned) time (&t));
        for (int x = 0; x < numLine; x++) {
            for (int y = 0; y < numColumn; y++) {
                int number = rand () / 100;
                *((int *) grid + x * numColumn + y) = number;

            }
        }
    }

    return res;
}

bool init_one_map (int *grid, int numLine, int numColumn) {
    time_t t;
    bool res = false;
    if (NULL != grid) {
        res = true;
        srand ((unsigned) time (&t));
        for (int x = 0; x < numLine; x++) {
            for (int y = 0; y < numColumn; y++) {
                *((int *) grid + x * numColumn + y) = 1;

            }
        }
    }
    return res;
}

void init_rod_map (int *grid, int numLine, int numColumn) {
    init_one_map (grid, numLine, numColumn);
    int x = numLine / 2;
    int y = 0;
    for (y = 0; y < ((numColumn / 2) + 1); y++) {
        *((int *) grid + x * numColumn + y) = 100;
    }

    y = numColumn / 3;
    for (x = 0; x < ((numLine / 4) + 2); x++) {
        *((int *) grid + x * numColumn + y) = 200;
    }
}



void init_box_map (int *grid, int numLine, int numColumn) {
    init_one_map (grid, numLine, numColumn);
    int x = 0;
    int y = 0;
    for (y = 1; y < numColumn-1; y++) {
        for (x = 1; x < numLine-1; x++) {
            *((int *) grid + x * numColumn + y) = 99999;
        }
    }

}

void init_hole_map (int *grid, int numLine, int numColumn) {
    init_one_map (grid, numLine, numColumn);
    int x = numLine / 2;
    int y = 0;
    for (y = 0; y < numColumn; y++) {
        for (x = 0; x < numLine; x++) {
            *((int *) grid + x * numColumn + y) = 3 * abs (x - numLine / 2) + 3 * abs (y - numColumn / 2);
        }
    }
}

void init_ramp_map (int *grid, int numLine, int numColumn) {
    //init_one_map ((int *) grid, numLine, numColumn);
    int x = 0;
    int y = 0;
    for (y = 0; y < numColumn; y++) {
        for (x = 0; x < numLine; x++) {
            int val = 1+y*y;
            *((int *) grid + x * numColumn + y) =1+ val;
        }
    }
}

bool save_array_as_dot (char *fileName, int *grid, int numLine, int numColumn) {
    bool res = false;
    FILE * stream = NULL;
    stream = fopen (fileName, "w");
    if (stream) {
        fprintf (stream, "digraph {\n");
        fprintf (stream, "  tbl [\n");
        fprintf (stream, "    shape=plaintext\n");
        fprintf (stream, "    label=<\n");
        fprintf (stream, "      <table border='0' cellborder='1'  cellspacing='0'>\n");
        if (NULL != grid) {
            for (int x = 0; x < numLine; x++) {
                fprintf (stream, "          ");
                fprintf (stream, "<tr> ");
                for (int y = 0; y < numColumn; y++) {
                    fprintf (stream, "<td >%d</td> ", *((int *) grid + x * numColumn + y));
                }
                fprintf (stream, " </tr>\n");
            }
        }
        fprintf (stream, "    </table>\n");
        fprintf (stream, "  >];\n");
        fprintf (stream, "}\n");

        res = true;
    }

    return res;
}

bool save_map_path_as_dot (char *fileName, int *grid, int numLine, int numColumn, Cell_t * const arrayOfDot, int sizeOfPath) {
    bool res = false;
    FILE * stream = NULL;
    stream = fopen (fileName, "w");
    if (stream) {
        fprintf (stream, "digraph {\n");
        fprintf (stream, "  tbl [\n");
        fprintf (stream, "    shape=plaintext\n");
        fprintf (stream, "    label=<\n");
        fprintf (stream, "      <table border='0' cellborder='1'  cellspacing='0'>\n");
        if (NULL != grid) {
            for (int x = 0; x < numLine; x++) {
                fprintf (stream, "          ");
                fprintf (stream, "<tr> ");
                for (int y = 0; y < numColumn; y++) {
                    bool res;
                    res = is_exist_in_path (x, y, arrayOfDot, sizeOfPath);
                    if (true == res) {
                        fprintf (stream, "<td BGCOLOR=\"yellow\">%d</td> ", *((int *) grid + x * numColumn + y));
                    } else {
                        fprintf (stream, "<td>%d</td> ", *((int *) grid + x * numColumn + y));
                    }
                }
                fprintf (stream, " </tr>\n");
            }
        }
        fprintf (stream, "    </table>\n");
        fprintf (stream, "  >];\n");
        fprintf (stream, "}\n");
        res = true;
    }

    return res;
}

static bool is_exist_in_path (int x, int y, Cell_t * const arrayOfDot, int sizeOfPath) {
    bool res = false;
    if (NULL != arrayOfDot) {
        if (0 < sizeOfPath) {
            for (int i = 0; i < sizeOfPath; i++) {
                if ((arrayOfDot [i].x == x) && (arrayOfDot [i].y == y)) {
                    res = true;
                }
            }
        }
    }
    return res;
}

void print_path (Cell_t * const arrayOfDot, int sizeOfPath) {
    if (NULL != arrayOfDot) {
        if (0 < sizeOfPath) {
            printf ("\n");
            for (int i = 0; i < sizeOfPath; i++) {
                printf ("[%d %d]->", arrayOfDot [i].x, arrayOfDot [i].y);
            }
            printf ("\n");
        }
    } else {
        printf ("\nNull Array");
    }
}

int unique_paths (int xMax, int yMax) {
    int amountOfPaths = 0;
    bool res = false;
    if (1 == xMax || 1 == yMax) {
        return 1;
    }
    res = is_val_in_look_up_table ((int *) lootUpTable, xMax, yMax);
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

    updateLookUpTabel ((int *) lootUpTable, xMax, yMax, amountOfPaths);
    return amountOfPaths;
}

static void initUniqPathDiagLookUpTable (void) {
    g_mantchCnt = 0;
    g_unMantchCnt = 0;
    int x = 0, y = 0;
    for (x = 0; x < DIM_OF_LUTABLE; x++) {
        for (y = 0; y < DIM_OF_LUTABLE; y++) {
            UniqPathDiagLootUpTable [x] [y] = -1;
        }
    }
    UniqPathDiagLootUpTable [1 - 1] [1 - 1] = 1;  // 1x1
    UniqPathDiagLootUpTable [1 - 1] [2 - 1] = 1;  // 1x2
    UniqPathDiagLootUpTable [2 - 1] [1 - 1] = 1;  // 2x1
    UniqPathDiagLootUpTable [2 - 1] [2 - 1] = 3;  // 2x2
    UniqPathDiagLootUpTable [2 - 1] [3 - 1] = 5;  // 2x3
    UniqPathDiagLootUpTable [3 - 1] [1 - 1] = 1;  // 3x1
    UniqPathDiagLootUpTable [3 - 1] [2 - 1] = 5;  // 3x2
    UniqPathDiagLootUpTable [3 - 1] [3 - 1] = 13; // 3x3
    //UniqPathDiagLootUpTable [3-1] [4-1] = ?; // 3x4
}

static void init_lookUpTable (void) {
    //printf ("\n");
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

static void updateLookUpTabel (int * const matrix, int x, int y, int val) {
    if ((x <= DIM_OF_LUTABLE) && (y <= DIM_OF_LUTABLE)) {
        //lootUpTable [xMax - 1] [yMax - 1] = amountOfPaths;
        //*((int *) matrix + x * DIM_OF_LUTABLE + y) = val;
        if (matrix == (int *) UniqPathDiagLootUpTable) {
            UniqPathDiagLootUpTable [x - 1] [y - 1] = val;
        }
    }
}

static bool is_val_in_look_up_table (int * const table, int x, int y) {
    bool res = false;
    int val = -1;
    if ((0 < x) && (x <= DIM_OF_LUTABLE)) {
        if ((0 < y) && (y <= DIM_OF_LUTABLE)) {
            if (table == (int *) UniqPathDiagLootUpTable) {
                val = UniqPathDiagLootUpTable [x - 1] [y - 1];
            }
            //int val = UniqPathDiagLootUpTable [xMax - 1] [yMax - 1];
            //int val = *((int *) table + x * DIM_OF_LUTABLE + y);
            if (0 <= val) {
                res = true;
            }
        }
    }
    return res;
}

void print_lookUpTable (int * const array) {
    printf ("\n");
    int amountOflines = 0;
    if (array != (int *) UniqPathDiagLootUpTable) {
        printf ("\n  Undef table! ");
        return;
    }
    int x = 0, y = 0;
    int val = 0;
    for (x = 0; x < DIM_OF_LUTABLE; x++) {
        for (y = 0; y < DIM_OF_LUTABLE; y++) {
            //val = *((int*) array + x * DIM_OF_LUTABLE + y);
            val = UniqPathDiagLootUpTable [x] [y];
            if (0 <= val) {
                amountOflines++;
                printf ("\n x: %d y: %d: path: %d ", x + 1, y + 1, val);
            }
        }
    }
    printf ("\n amountOflines: %d ", amountOflines);
}

