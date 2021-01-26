#ifndef TREE_LIONS_H
#define TREE_LIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define EMPTY_ALLOWED

#define NUM_OF_STATES (4 * 4 * 4 * 4)

typedef enum { IN_M = 0, IN_MM = 1, IN_ML = 2 } eInputs_t;

typedef enum { DIR_LEFT = 0, DIR_RIGHT = 1 } eDir_t;
//
// 0 num of Lion on left shore
// 1 num of men on left shore
// 2 num of Lion on right shore
// 3 num of men on right shore
// 4 -boat pos 0-left 1-right shore
typedef struct xState_t {
    int state[5]; // LMLMB
} State_t;

bool run_tree_lions (void);
bool test_lion_man_task (void);

#ifdef __cplusplus
}
#endif

#endif /* TREE_LIONS_H */
