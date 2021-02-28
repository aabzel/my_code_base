#ifndef TIMERS_H
#define TIMERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "stm32f1xx_hal.h"

typedef enum timInterruptMode {
    TIM_IT_MODE_OFF = 0,
    TIM_IT_MODE_CONTINUAL = 1,
    TIM_IT_MODE_SINGLE = 2,
    TIM_IT_MODE_COUNT
} TimInterruptMode_t;

extern TIM_HandleTypeDef htim1;
extern char g_tim1ItMode;
extern int g_tim1PeriodElapsedCnt;

#define __HAL_TIM_SET_PSC(__HANDLE__, __PRESC__)                                                                       \
    do {                                                                                                               \
        (__HANDLE__)->Instance->PSC = (__PRESC__);                                                                     \
        (__HANDLE__)->Init.Prescaler = (__PRESC__);                                                                    \
    } while (0)

bool timers_init (void);
bool suspend_timer1 (void);
bool launch_timer1_ms (unsigned int ms, char mode);
bool tim_set (uint8_t tim_num, uint16_t prescaler, uint16_t period, uint8_t state);

#ifdef __cplusplus
}
#endif

#endif // TIMERS_H
