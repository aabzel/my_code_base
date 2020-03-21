#include "min_path.h"

#include "algorithms.h"
#include "arrays.h"
#include "custom_type.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static bool is_exist_in_path (int x, int y, Cell_t * const arrayOfDot, int sizeOfPath);
static int min_path_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm);

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
/* ак получить на выходе св€занный список с координатами наименьшего пути?*/
/*«аписывать в файл все пути а потом произвести его синтаксический разбор и выбрать тот, что дошел до конца. (медленно)*/
/*ѕри каждом вызове функции min_path передавать в нее список уже пройденных точек. ѕри
 * достижении тупика удал€ть этот список. ѕри достижении цели возвращать этот список*/
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
        lenOfCurrPath = 1;
        Cell_t currPath2 [1];
        currPath2 [0].x = 0;
        currPath2 [0].y = 0;
        currPath2 [0].val = curSum;
        min_path (grid, numLine, numColumn, x + 1, y, curSum, minSum, currPath2, lenOfCurrPath, minPathArr, minPathLen);
    }
    //printf ("\n[%d,%d]->", 0, 0);

}

bool minPath (int* grid, int numLine, int numColumn) {
    int numPath = uniquePaths (numLine, numColumn);
    printf ("\n Amount of Path %d", numPath);
    int mPathSum = minPathSum (grid, numLine, numColumn);
    printf ("\n sumOfMinPath %d", mPathSum);
    Cell_t *minPath = NULL;
    int minPathLen;
    find_min_path (grid, numLine, numColumn, mPathSum, &minPath, &minPathLen);
    print_path (minPath, minPathLen);
    save_map_path_as_dot ("minPath.dot", grid, numLine, numColumn, minPath, minPathLen);
    printf ("\n find_min_path done !\n");
    return true;
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
            print_path (locArr, lenOfCurrPath + 1);
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

bool test_min_path (void) {
    bool res = false;
    int grid [3] [3] =
        {
            { 1, 3, 1 },
            { 1, 5, 1 },
            { 4, 2, 1 } };
    int minSum;
    int sizeOfGrid = 3;
    int gridColSize = 3;
    minSum = minPathSum ((int *) grid, sizeOfGrid, gridColSize);
    if (7 == minSum) {
        res = true;
    } else {
        return false;
    }
    save_array_as_dot ("map1.dot", (int *) grid, 3, 3);

    minPath ((int *) grid, sizeOfGrid, gridColSize);
    //int grid2 [10] [10];
    //init_rand_array ((int *) grid2, 10, 10);
    //minSum = minPathSum ((int *) grid2, 10, 10);
    //save_array_as_dot ("map.dot", (int *) grid2, 10, 10);

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
                        fprintf (stream, "<td> %d </td> ", *((int *) grid + x * numColumn + y));
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
    }
}
