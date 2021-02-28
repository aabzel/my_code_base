#include "timers.h"

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "stm32f1xx_hal.h"

char g_tim1ItMode;
int g_tim1PeriodElapsedCnt;
char g_tim1ItMode = TIM_IT_MODE_CONTINUAL;
TIM_HandleTypeDef htim1;

bool timers_init (void) {
    __HAL_RCC_TIM1_CLK_ENABLE ();
    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority (TIM1_BRK_TIM15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ (TIM1_BRK_TIM15_IRQn);
    HAL_NVIC_SetPriority (TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ (TIM1_UP_TIM16_IRQn);
    HAL_NVIC_SetPriority (TIM1_TRG_COM_TIM17_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ (TIM1_TRG_COM_TIM17_IRQn);
    HAL_NVIC_SetPriority (TIM1_CC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ (TIM1_CC_IRQn);

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    // 24 MHz
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 24000;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 500;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    // htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init (&htim1);

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource (&htim1, &sClockSourceConfig);
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization (&htim1, &sMasterConfig);

    HAL_TIM_Base_Start_IT (&htim1);
    // launch_timer1_ms(1, TIM_IT_MODE_CONTINUAL);
    return true;
}

bool suspend_timer1 (void) {
    HAL_StatusTypeDef status;
    status = HAL_TIM_Base_Stop_IT (&htim1);
    //__HAL_TIM_SET_AUTORELOAD(&htim1, 0x7FFF);
    __HAL_TIM_SET_COUNTER (&htim1, 0);
    return true;
}

bool launch_timer1_ms (unsigned int ms, char mode) {
    if (TIM_IT_MODE_COUNT <= mode)
        return false;
    g_tim1ItMode = mode;

    HAL_StatusTypeDef status = 0;
    uint32_t hclkFreqHz = 0;
    uint16_t tim_prescaler = 0;

    hclkFreqHz = HAL_RCC_GetHCLKFreq ();
    tim_prescaler = (ms * (hclkFreqHz / 1000));

    suspend_timer1 ();
    __HAL_TIM_SET_PRESCALER (&htim1, tim_prescaler);
    //__HAL_TIM_SET_AUTORELOAD(&htim1, ms * 2);
    __HAL_TIM_SET_COUNTER (&htim1, 0);
    status = HAL_TIM_Base_Start_IT (&htim1);
    if (status != HAL_OK) {
        return false;
    }
    return true;
}

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        // isr must be called every 1ms
        g_tim1PeriodElapsedCnt++;
        if (TIM_IT_MODE_SINGLE == g_tim1ItMode) {
            // suspend_timer1();
        }
        HAL_GPIO_TogglePin (GPIOC, GPIO_PIN_9);
    }
}

bool tim_set (uint8_t tim_num, uint16_t prescaler, uint16_t period, uint8_t state) {
    bool res = false;
    if (1 == tim_num) {
        __HAL_TIM_SET_PSC (&htim1, prescaler);
        __HAL_TIM_SET_AUTORELOAD (&htim1, period);
        __HAL_TIM_SET_COUNTER (&htim1, 0);
        if (1 == state) {
            HAL_StatusTypeDef status = HAL_TIM_Base_Start_IT (&htim1);
            if (status != HAL_OK) {
                return false;
            }
        } else if (0 == state) {
            res = suspend_timer1 ();
        }
    }
    return res;
}
