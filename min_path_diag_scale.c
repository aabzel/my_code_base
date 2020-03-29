#include "min_path_diag_scale.h"

#include "algorithms.h"

#include <math.h>

static float min_path_diag_scale_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, float curPrevSumm, bool isDiagEntry);

float minPathDiagScalseSum (int* grid, int numLine, int numColumn) {
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
    float curAddSum1 = 0.0f;
    float curAddSum2 = 0.0f;
    float minPathSum = 0.0f;
    float minPathSum1 = 0.0f, minPathSum2 = 0.0f, minPathSum3 = 0.0f;
    float curTotalSum1, curTotalSum2, curTotalSum3;
    int curCellVal = *((int *) grid + curCellx * numColumn + curCelly);
    if (isDiagEntry) {
        curAddSum1 =  (1.414213) * ((float) curCellVal) / (2.0f);
    } else {
        curAddSum1 = ((float) curCellVal) / (2.0f);
    }
    if (curCellx < (numColumn - 1)) {
        if (curCelly < (numLine - 1)) {
            curAddSum2 = ( (1.414213) * ((float) curCellVal) / (2.0f));
            curTotalSum1 = curPrevSumm + curAddSum1 + curAddSum2;
            minPathSum1 = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx + 1, curCelly + 1, curTotalSum1, DIAG_ENTRY);

            curAddSum2 = (((float) curCellVal) / (2.0f));
            curTotalSum2 = curPrevSumm + curAddSum1 + curAddSum2;
            minPathSum2 = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curTotalSum2, STRAIGHT_ENTRY);

            curAddSum2 = (((float) curCellVal) / (2.0f));
            curTotalSum3 = curPrevSumm + curAddSum1 + curAddSum2;
            minPathSum3 = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curTotalSum3, STRAIGHT_ENTRY);

            minPathSum = min3f (minPathSum1, minPathSum2, minPathSum3);
        } else {
            //curCelly = numLine-1
            curAddSum2 = (((float) curCellVal) / (2.0f));
            curTotalSum1 = curPrevSumm + curAddSum1 + curAddSum2;
            minPathSum = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx + 1, curCelly, curTotalSum1, STRAIGHT_ENTRY);
        }
    } else {
        //curCellx = numColumn-1
        if (curCelly < (numLine - 1)) {
            curAddSum2 = (((float) curCellVal) / (2.0f));
            curTotalSum1 = curPrevSumm + curAddSum1 + curAddSum2;
            minPathSum = min_path_diag_scale_sum (grid, numLine, numColumn, curCellx, curCelly + 1, curTotalSum1, STRAIGHT_ENTRY);
        } else {
            //curCellx=numColumn-1
            //curCelly=numLine-1

            minPathSum = curPrevSumm + curAddSum1;
            printf ("\n final minPathSum: %f", minPathSum);
        }
    }
    return minPathSum;
}

