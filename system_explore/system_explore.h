#ifndef SYS_EXPLORE_H
#define SYS_EXPLORE_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>

bool test_free_zero(void) ;
bool test_heap(void) ;
bool test_heap_set (void);
bool test_malloc (void);
bool test_malloc_zero (void);
bool test_sbrk(int argc, char *argv[], int numAllocs, int blockSize, int freeStep, int freeMin, int freeMax) ;
 
#ifdef __cplusplus
}
#endif

// function to check permutations
#endif /* SYS_EXPLORE_H */
