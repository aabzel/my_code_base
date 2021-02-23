#ifndef EXTERNAL_UTILS_STM32_WATCHDOG_H_
#define EXTERNAL_UTILS_STM32_WATCHDOG_H_
#include <stdint.h>
#include <stdbool.h>

void wdt_reset_all (void);

void HardWareWdtEnable(bool status);


#endif /* EXTERNAL_UTILS_STM32_WATCHDOG_H_ */
