#ifndef DIAG__PAGE_COMMON_H_
#define DIAG__PAGE_COMMON_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <math.h>

bool diag_page_common_init (void);
bool put_val_to_row (ostream_t * const stream, float_t const value);

#ifdef  __cplusplus
}
#endif

#endif /* DIAG__PAGE_COMMON_H_ */
