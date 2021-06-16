#include "tim.h"

#include "bit_utils.h"
#include "float_utils.h"
#include "io_utils.h"
#include "misc.h"
#include "stddef.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_tim.h"
#include "sys.h"
#include "time_utilities.h"

void delay_ms(uint32_t ms) {
    uint32_t end_wait_time = SysTickReg + ms - 1;
    while (!timeAfter(SysTickReg, end_wait_time)) {
    };
}

const uint8_t TimBusLUT[HW_TIM_CNT] = {
    /*TIM1-APB2*/ APB2,
    /*TIM2-APB1*/ APB1,
    /*TIM3-APB1*/ APB1,
    /*TIM4-APB1*/ APB1,
    /*TIM5-APB1*/ APB1,
    /*TIM6-APB1*/ APB1,
    /*TIM7-APB1*/ APB1,
    /*TIM8-APB2*/ APB2,
    /*TIM9-APB2*/ APB2,
    /*TIM10-APB2*/ APB2,
    /*TIM11-APB2*/ APB2,
    /*TIM12-APB1*/ APB1,
    /*TIM13-APB1*/ APB1,
    /*TIM14-APB1*/ APB1};

static const uint32_t TimRccMaskLUT[HW_TIM_CNT] = {
    /*TIM1-APB2*/ RCC_APB2Periph_TIM1,
    /*TIM2-APB1*/ RCC_APB1Periph_TIM2,
    /*TIM3-APB1*/ RCC_APB1Periph_TIM3,
    /*TIM4-APB1*/ RCC_APB1Periph_TIM4,
    /*TIM5-APB1*/ RCC_APB1Periph_TIM5,
    /*TIM6-APB1*/ RCC_APB1Periph_TIM6,
    /*TIM7-APB1*/ RCC_APB1Periph_TIM7,
    /*TIM8-APB2*/ RCC_APB2Periph_TIM8,
    /*TIM9-APB2*/ RCC_APB2Periph_TIM9,
    /*TIM10-APB2*/ RCC_APB2Periph_TIM10,
    /*TIM11-APB2*/ RCC_APB2Periph_TIM11,
    /*TIM12-APB1*/ RCC_APB1Periph_TIM12,
    /*TIM13-APB1*/ RCC_APB1Periph_TIM13,
    /*TIM14-APB1*/ RCC_APB1Periph_TIM14};

static const uint8_t TimIRQnChannelLUT[HW_TIM_CNT] = {
    /*TIM1- */ TIM1_UP_TIM10_IRQn,
    /*TIM2- */ TIM2_IRQn,
    /*TIM3- */ TIM3_IRQn,
    /*TIM4- */ TIM4_IRQn,
    /*TIM5- */ TIM5_IRQn,
    /*TIM6- */ TIM6_DAC_IRQn,
    /*TIM7- */ TIM7_IRQn,
    /*TIM8- */ TIM8_UP_TIM13_IRQn,
    /*TIM9- */ TIM1_BRK_TIM9_IRQn,
    /*TIM10- */ TIM1_UP_TIM10_IRQn,
    /*TIM11- */ TIM1_TRG_COM_TIM11_IRQn,
    /*TIM12- */ TIM8_BRK_TIM12_IRQn,
    /*TIM13- */ TIM8_UP_TIM13_IRQn,
    /*TIM14- */ TIM8_TRG_COM_TIM14_IRQn

};

static TIM_TypeDef* get_tim_ptr(uint8_t tim_num) {
    TIM_TypeDef* TIMx = NULL;
    switch (tim_num) {
        case 1:
            TIMx = TIM1;
            break;
        case 2:
            TIMx = TIM2;
            break;
        case 3:
            TIMx = TIM3;
            break;
        case 4:
            TIMx = TIM4;
            break;
        case 5:
            TIMx = TIM5;
            break;
        case 6:
            TIMx = TIM6;
            break;
        case 7:
            TIMx = TIM7;
            break;
        case 8:
            TIMx = TIM8;
            break;
        case 9:
            TIMx = TIM9;
            break;
        case 10:
            TIMx = TIM10;
            break;
        case 11:
            TIMx = TIM11;
            break;
        case 12:
            TIMx = TIM12;
            break;
        case 13:
            TIMx = TIM13;
            break;
        case 14:
            TIMx = TIM14;
            break;
        default:
            TIMx = NULL;
            break;
    }
    return TIMx;
}

uint8_t tim_get_status(uint8_t tim_num) {
    bool res = true;
    uint8_t status = 0xFF;
    uint32_t tim_cr1 = 0;
    TIM_TypeDef* TIMx = get_tim_ptr(tim_num);
    if (TIMx) {
        res = true;
        tim_cr1 = TIMx->CR1;
    } else {
        res = false;
    }

    if (true == res) {
        status = MASK_1BIT & tim_cr1;
    }
    return status;
}

const char* tim_get_dir(uint8_t tim_num) {
    bool res = true;
    char* dir = "undef";
    uint32_t tim_cr1 = 0;

    TIM_TypeDef* TIMx = get_tim_ptr(tim_num);
    if (TIMx) {
        res = true;
        tim_cr1 = TIMx->CR1;
    } else {
        res = false;
    }

    if (true == res) {
        if (BIT_4 == (BIT_4 & tim_cr1)) {
            dir = "down";
        } else {
            dir = "up";
        }
    }
    return dir;
}

uint16_t tim_get_cnt16(uint8_t tim_num) {
    bool res = true;
    uint16_t tim_cnt = 0xFF;
    uint32_t tim_cnt32 = 0;
    TIM_TypeDef* TIMx = get_tim_ptr(tim_num);
    if (NULL != TIMx) {
        res = true;
        tim_cnt32 = TIMx->CNT;
    } else {
        res = false;
    }

    if (true == res) {
        tim_cnt = MASK_16BIT & tim_cnt32;
    }
    return tim_cnt;
}

uint32_t tim_get_cnt32(uint8_t tim_num) {
    uint32_t tim_cnt32 = 0;
    TIM_TypeDef* TIMx = get_tim_ptr(tim_num);
    if (NULL != TIMx) {
        tim_cnt32 = TIMx->CNT;
    }
    return tim_cnt32;
}

uint16_t tim_get_prescaler(uint8_t tim_num) {
    bool res = true;
    uint16_t tim_prescaler = 0xFF;
    uint32_t tim_prescaler32 = 0;

    TIM_TypeDef* TIMx = get_tim_ptr(tim_num);
    if (TIMx) {
        res = true;
        tim_prescaler32 = TIMx->PSC;
    } else {
        res = false;
    }

    if (true == res) {
        tim_prescaler = MASK_16BIT & tim_prescaler32;
    }
    return tim_prescaler;
}

uint16_t tim_get_period(uint8_t tim_num) {
    bool res = true;
    uint16_t tim_period = 0xFF;
    uint32_t tim_period32 = 0;

    TIM_TypeDef* TIMx = get_tim_ptr(tim_num);
    if (TIMx) {
        res = true;
        tim_period32 = TIMx->ARR;
    } else {
        res = false;
    }

    if (true == res) {
        tim_period = MASK_16BIT & tim_period32;
    }
    return tim_period;
}

bool tim_init_ll(uint8_t tim_num, uint32_t period, uint16_t prescaler,
                 uint16_t division, uint16_t counter_mode, uint32_t cnt,
                 bool new_state) {
    TIM_TypeDef* TIMx = NULL;
    TIMx = get_tim_ptr(tim_num);
    bool res = false;
    if (NULL != TIMx) {
        res = true;
        if (APB1 == TimBusLUT[tim_num - 1]) {
            RCC_APB1PeriphClockCmd(TimRccMaskLUT[tim_num - 1], ENABLE);
        }
        if (APB2 == TimBusLUT[tim_num - 1]) {
            RCC_APB2PeriphClockCmd(TimRccMaskLUT[tim_num - 1], ENABLE);
        }

        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        TIM_TimeBaseStructure.TIM_Period = period;
        TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
        TIM_TimeBaseStructure.TIM_ClockDivision = division;
        TIM_TimeBaseStructure.TIM_CounterMode = counter_mode;
        TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

        NVIC_InitTypeDef NVIC_InitStructure;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority =
            0; // Not used as 4 bits are used for the pre-emption priority
        NVIC_InitStructure.NVIC_IRQChannel = TimIRQnChannelLUT[tim_num - 1];
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
        TIM_ClearFlag(TIMx, TIM_FLAG_Update);
        TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
        TIM_SetCounter(TIMx, cnt);

        if (true == new_state) {
            TIM_Cmd(TIMx, ENABLE);
        } else {
            TIM_Cmd(TIMx, DISABLE);
        }
    }
    return res;
}

float calc_tim_min_period(uint8_t tim_num) {
    float min_period = 0.0f;
    uint8_t bus = TimBusLUT[tim_num - 1];
    if (APB1 == bus) {
        min_period = 1.0f / ((float)APB1_CLOCK_HZ);
    } else {
        min_period = 1.0f / ((float)APB2_CLOCK_HZ);
    }
    return min_period;
}
#define MAX_PRC 65535.0f
#define MAX_ARR 65535.0f

float calc_tim_max_period(uint8_t tim_num) {
    float t_apb = 0.0f;
    uint8_t bus = TimBusLUT[tim_num - 1];
    if (APB1 == bus) {
        t_apb = 1.0f / ((float)APB1_CLOCK_HZ);
    } else {
        t_apb = 1.0f / ((float)APB2_CLOCK_HZ);
    }
    float max_t_psc = t_apb * MAX_PRC;
    float min_period = max_t_psc * MAX_ARR;
    return min_period;
}

bool tim_set(uint8_t tim_num, float des_period, float accuracy) {
    bool res = false;
    float min_per = calc_tim_min_period(tim_num);
    float max_per = calc_tim_max_period(tim_num);
    float t_apb = 0.0f;
    float calc_period = 0.0f;
    uint8_t bus = TimBusLUT[tim_num - 1];
    if (APB1 == bus) {
        t_apb = 1.0f / ((float)APB1_CLOCK_HZ);
    } else {
        t_apb = 1.0f / ((float)APB2_CLOCK_HZ);
    }

    if ((min_per < des_period) && (des_period < max_per)) {
        res = true;
        float des_mult = des_period / t_apb;
        io_printf(CRLF " des_mult: %f " CRLF, des_mult);
        uint32_t prescaler = 0;
        for (prescaler = 1; prescaler < 0xFFFF; prescaler++) {
            float period = des_mult / ((float)prescaler);
            if (period <= MAX_ARR) {
                calc_period = t_apb * ((float)prescaler) * period;
                res = is_float_equal_absolute(calc_period, des_period, accuracy);
                if (true == res) {
                    res = tim_init_ll(tim_num, (uint32_t)period, (uint16_t)prescaler,
                                      (uint16_t)TIM_CKD_DIV1,
                                      (uint16_t)TIM_CounterMode_Up, 0, true);
                    break;
                }
            } else {
                res = false;
            }
        }
    }
    return res;
}

uint32_t RTOS_AppGetRuntimeCounterValue(void) {
    uint32_t cnt;
    cnt = tim_get_cnt32(1);
    return cnt;
}

bool RTOS_AppConfigureTimerForRuntimeStats(void) {
    bool res;
    /*Inctement with 10kHz*/
    res = tim_init_ll(1, 0xFFFF, 6000, (uint16_t)TIM_CKD_DIV1,
                      (uint16_t)TIM_CounterMode_Up, 0, true);
    return res;
}

bool tim_set_prescaler_us(uint8_t tim_num, uint32_t prescaler_us) {
    bool res = false;
    float t_apb = 0.0f;

    uint8_t bus = TimBusLUT[tim_num - 1];
    if (APB1 == bus) {
        t_apb = 1.0f / ((float)APB1_CLOCK_HZ);
    } else {
        t_apb = 1.0f / ((float)APB2_CLOCK_HZ);
    }

    TIM_TypeDef* TIMx = NULL;
    TIMx = get_tim_ptr(tim_num);
    if (NULL != TIMx) {
        res = true;
        uint32_t prescaler_reg =
            (uint32_t)((((float)prescaler_us) / 1000000.0f) / t_apb);
        io_printf(CRLF " PSC: %u " CRLF, prescaler_reg);
        TIMx->PSC = prescaler_reg;
    }
    return res;
}

uint64_t getRunTimeCounterValue64(void) {
    return 0;
}