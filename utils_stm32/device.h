#ifndef EXTERNAL_UTILS_DEVICE_STM32_H
#define EXTERNAL_UTILS_DEVICE_STM32_H

#include <stdint.h>
#include <stdbool.h>

#include "rx_utils.h"
#include "uarts.h"
#include "watchdog.h"

#define COUNTER_FREQ (HAL_RCC_GetSysClockFreq()/1000000)

#define _disable_interrupt_() __disable_irq()
#define _enable_interrupt_() __enable_irq()

#define isFromInterrupt() ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0)

#define US_TO_COUNTER(us) (uint64_t)((uint64_t)(us) * (COUNTER_FREQ))
#define MS_TO_COUNTER(ms) (uint64_t)(((ms) * 1000UL) * (COUNTER_FREQ))
#define COUNTER_TO_US(counter) ((counter) / (COUNTER_FREQ))
#define COUNTER_TO_MS(counter) ((counter) / ((COUNTER_FREQ) * 1000))

#ifdef	__cplusplus
extern "C" {
#endif

extern uint32_t critical_nesting_level;
#define CRITICAL_LEVEL    critical_nesting_level


static INLINE void enter_critical(void) {
    if (!isFromInterrupt ()) {
		if (CRITICAL_LEVEL == 0) {
			_disable_interrupt_ ();
		}
		CRITICAL_LEVEL++;
	}
}


static INLINE void exit_critical(void) {
    if (!isFromInterrupt ()) {
        if (CRITICAL_LEVEL) {
            CRITICAL_LEVEL--;
            if (CRITICAL_LEVEL == 0) {
                _enable_interrupt_ ();
            }
        }
    }
}

uint32_t getRunTimeCounterValue32 (void);
uint64_t getRunTimeCounterValue64 (void);
void configureTimerForRunTimeStats (void);
void delay (uint32_t delay_in_ms);
void delay_wd (uint32_t delay_in_ms);
void delay_us (uint32_t delay_in_us);
void delay_us_wd (uint32_t delay_in_us);
uint32_t get_time_ms32 (void);
uint64_t get_time_ms64 (void);
uint64_t get_time_us (void);

#ifdef  __cplusplus
}
#endif

#endif /* EXTERNAL_UTILS_DEVICE_STM32_H */
