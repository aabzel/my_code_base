#include "min_path.h"

#include "algorithms.h"
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

static int min_path_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm);

int minPathSum (int* grid, int numLine, int numColumn) {
    int numPath;
    int curSum = 0;
    int minPathSum = 0;
    int minPathSum1 = 0;
    int minPathSum2 = 0;
    numPath = uniquePaths (numLine, numColumn);
    printf ("\n Amount of Path %d", numPath);
    int x = 0;
    int y = 0;
    curSum = *((int *) grid + x * numColumn + y);
    minPathSum1 = min_path_sum (grid, numLine, numColumn, x, y + 1, curSum);
    minPathSum2 = min_path_sum (grid, numLine, numColumn, x + 1, y, curSum);
    minPathSum = min (minPathSum1, minPathSum2);
    printf ("\n sumOfMinPath %d", minPathSum);
    return minPathSum;
}

static int min_path_sum (int* grid, int numLine, int numColumn, int curCellx, int curCelly, int curPrevSumm) {
    int curOutSum = 0;
    int minPathSum = 0;
    int minPathSum1 = 0;
    int minPathSum2 = 0;
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
    int sizeOfGrid = 3; //sizeof(grid)/sizeof(grid[0]);
    int gridColSize = 3;
    minSum = minPathSum ((int *) grid, sizeOfGrid, gridColSize);
    if (7 == minSum) {
        res = true;
    }

    int grid2 [10] [10];
    init_rand_array ((int *)grid2, 10, 10);
    minSum = minPathSum ((int *)grid2, 10, 10);
    save_array_as_dot ("map.dot",(int *)grid2, 10, 10);

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



bool save_array_as_dot (char *fileName,int *grid, int numLine, int numColumn) {
    bool res = false;
    FILE * stream = NULL;
    stream = fopen (fileName, "w");
    if(stream){
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
                    fprintf (stream, "<td >%d</td> ",*((int *) grid + x * numColumn + y) );
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

/*
digraph {

  tbl [

    shape=plaintext
    label=<

      <table border='0' cellborder='1'  cellspacing='0'>
        <tr><td >00</td><td >01</td><td>02</td></tr>
        <tr><td>10</td><td >11</td><td>12</td></tr>
        <tr><td>20</td><td>21</td><td>22</td></tr>


      </table>

    >];

}
*/
