#ifndef __UTESTS_H
#define __UTESTS_H

#include <stdint.h>

#include "utils.h"

typedef enum {
    FINE = 0,
    LL_ERROR = 99,
    NUM_ERROR
} error_t;

int unitTest (void);

bool test_linked_list (void);

#endif /* __UTESTS_H */
