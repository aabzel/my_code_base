#ifndef MIN_PATH_DIAG_SCALE_H
#define MIN_PATH_DIAG_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"
#include "min_path.h"

#define DEBUG_MIN_DIAG_SCALE 0

#define DIAG_ENTRY (true)
#define STRAIGHT_ENTRY (false)

int uniquePathDiagScale (int xMax, int yMax);
float minPathDiagScalseSum (int* grid, int numLine, int numColumn);
bool minPathDiagScale (int* grid, int numLine, int numColumn);
//void find_min_path_diag_scale (int* grid, int numLine, int numColumn, int minSum, Cell_t **minPathArr, int *minPathLen, bool isDiag);

#ifdef __cplusplus
}
#endif

#endif /* MIN_PATH_DIAG_SCALE_H */
