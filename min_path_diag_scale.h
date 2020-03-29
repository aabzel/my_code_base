#ifndef MIN_PATH_DIAG_SCALE_H
#define MIN_PATH_DIAG_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"
#include "min_path.h"

#define DEBUG_MIN_DIAG_SCALE 0
#define DEBUG_MIN_PATH_DIAG_SCALE 1

#define SQRT2 (1.414213f)

#define DIAG_ENTRY (true)
#define STRAIGHT_ENTRY (false)

int uniquePathDiagScale (int xMax, int yMax);
float minPathDiagScaleSum (int* grid, int numLine, int numColumn);
bool minPathDiagScale (int* grid, int numLine, int numColumn);
void find_min_path_diag_stale (int* grid, int numLine, int numColumn, float minSum, Cell_t **minPathArr, int *minPathLen);

#ifdef __cplusplus
}
#endif

#endif /* MIN_PATH_DIAG_SCALE_H */
