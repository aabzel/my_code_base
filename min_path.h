#ifndef MIN_PATH_H
#define MIN_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom_type.h"

int minPathSum (int* grid, int numLine, int numColumn);
bool test_min_path (void);

bool save_array_as_dot (char *fileName,int *grid, int numLine, int numColumn);
bool init_rand_array (int *grid, int numLine, int numColumn);

#ifdef __cplusplus
}
#endif

#endif /* MIN_PATH_H */
