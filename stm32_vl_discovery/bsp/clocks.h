#ifndef CLOCKS_H
#define CLOCKS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

extern uint32_t g_up_time_ms;

bool SystemClock_Config (void);

#ifdef __cplusplus
}
#endif

#endif // CLOCKS_H
