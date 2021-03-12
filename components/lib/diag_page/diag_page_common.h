#ifndef DIAG_PGE_COMMON_H
#define DIAG_PGE_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>

#include "ostream.h"

bool diag_page_common_init (void);
bool put_val_to_row (ostream_t *const stream, float_t const value);

#ifdef __cplusplus
}
#endif

#endif /* DIAG_PGE_COMMON_H */
