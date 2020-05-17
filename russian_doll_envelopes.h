#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include "custom_type.h"

#define DEBUG_ENVEL1 0

typedef struct xEnvelop_t {
    uint32_t widths;
    uint32_t heights;
} xEnvelop_t;

bool is_fit (xEnvelop_t container, xEnvelop_t object);
int maxEnvelopes (int** envelopes, int envelopesSize, int* envelopesColSize);

#endif /* BOARD_H */
