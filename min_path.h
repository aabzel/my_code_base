#ifndef MIN_PATH_H
#define MIN_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

#define DIM_OF_LUTABLE (100)

#define DEBUG_MIN_PATH_DIAG_END 1
#define DEBUG_MIN_PATH_DIAG 0
#define USE_PRINT_LT_DIAG 0
#define USE_PRINT_LT 0


typedef struct xCell_t {
    int x;
    int y;
    float val; //
} Cell_t;

int unique_path_diag (int xMax, int yMax);
int unique_paths (int xMax, int yMax);
int uniquePaths (int xMax, int yMax);
int uniquePathDiag (int xMax, int yMax);
int minPathSum (int* grid, int numLine, int numColumn);
int minPathDiagSum (int* grid, int numLine, int numColumn);
bool test_min_path (void);
bool test_min_path_diag (void);
bool minPath (int* grid, int numLine, int numColumn);
bool minPathDiag (int* grid, int numLine, int numColumn);

bool save_map_path_as_dot (char *fileName, int *grid, int numLine, int numColumn, Cell_t * const arrayOfDot, int sizeOfPath);
void print_path (Cell_t * const arrayOfDot, int sizeOfArray);

void find_min_path_diag (int* grid, int numLine, int numColumn, int minSum, Cell_t **minPathArr, int *minPathLen);
void find_min_path (int* grid, int numLine, int numColumn, int minSum, Cell_t **minPathArr, int *minPathLen);

bool save_array_as_dot (char *fileName, int *grid, int numLine, int numColumn);

bool init_rand_array (int *grid, int numLine, int numColumn);
bool init_one_map (int *grid, int numLine, int numColumn);
void init_rod_map (int *grid, int numLine, int numColumn);
void init_box_map (int *grid, int numLine, int numColumn);
void init_ramp_map (int *grid, int numLine, int numColumn);
void init_hole_map (int *grid, int numLine, int numColumn) ;
void print_lookUpTable (int *array);

#ifdef __cplusplus
}
#endif

#endif /* MIN_PATH_H */
