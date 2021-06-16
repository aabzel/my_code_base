#ifndef IWDT_DRIVER_H
#define IWDT_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx.h"

#define F_LSI_HW 40000.0f

extern uint16_t code2PscLUT[8];

float iwdt_get_timeout(void);

#ifdef __cplusplus
}
#endif

#endif /* IWDT_DRIVER_H */
