#ifndef MIN_PATH_H
#define MIN_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

typedef struct xCell_t {
    int x;
    int y;
    int val;
} Cell_t;

int minPathSum (int* grid, int numLine, int numColumn);
bool test_min_path (void);
bool minPath (int* grid, int numLine, int numColumn);

bool save_map_path_as_dot (char *fileName, int *grid, int numLine, int numColumn, Cell_t * const arrayOfDot, int sizeOfPath);
void print_path (Cell_t * const arrayOfDot, int sizeOfArray);
void find_min_path (int* grid, int numLine, int numColumn, int minSum, Cell_t **minPathArr, int *minPathLen);
bool save_array_as_dot (char *fileName, int *grid, int numLine, int numColumn);
bool init_rand_array (int *grid, int numLine, int numColumn);

#ifdef __cplusplus
}
#endif

#endif /* MIN_PATH_H */
