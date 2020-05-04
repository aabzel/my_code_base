#ifndef FIFO_INDEX_H
#define FIFO_INDEX_H

#include <stdint.h>
#include "custom_type.h"
//#include "rx_utils.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define RING_INVALID_INDEX 0xFFFFU

typedef uint16_t fifo_index_t;

typedef struct {
    fifo_index_t size;
    volatile fifo_index_t start;
    volatile fifo_index_t end;
    volatile fifo_index_t count;
    volatile bool errors;
} fifo_index_info_t;

#ifdef __ghs__
/* #1862-D: MISRA 2004 Rule 19.7: function-like macro not allowed -- use function instead */
#pragma ghs nowarning 1862
#endif
#define FIFO_INDEX_INIT(size) {(size), 0, 0, 0, false}
#ifdef __ghs__
/* warning #1862-D: MISRA 2004 Rule 19.7: function-like macro not allowed -- use function instead */
#pragma ghs endnowarning 1862
#endif

void fifo_index_init (fifo_index_info_t* r_init, fifo_index_t size_init);
bool fifo_index_valid (const fifo_index_info_t* r_valid);

fifo_index_t fifo_index_add(fifo_index_info_t* r_add);
fifo_index_t fifo_index_get (fifo_index_info_t* r_get);
fifo_index_t fifo_index_continuus_used_size (const fifo_index_info_t* r_cus);
void fifo_index_free (fifo_index_info_t* r_free, fifo_index_t size_free);
fifo_index_t fifo_index_get_used (const fifo_index_info_t* r_used);
fifo_index_t fifo_index_get_size (const fifo_index_info_t* r_size);

#ifdef	__cplusplus
}
#endif

#endif /* FIFO_INDEX_H */
