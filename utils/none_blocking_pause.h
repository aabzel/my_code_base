#ifndef NONE_BLOCKING_PAUSE_H
#define NONE_BLOCKING_PAUSE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef  __cplusplus
extern "C" {
#endif

bool wait_in_loop_ms (uint64_t wait_pause_ms);

#ifdef  __cplusplus
}
#endif

#endif /* NONE_BLOCKING_PAUSE_H */
