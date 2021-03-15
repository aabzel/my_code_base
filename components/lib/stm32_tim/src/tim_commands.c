#include "tim_commands.h"

#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "timers.h"
#include "clocks.h"
#include "diag_page.h"
#include "diag_report.h"
#include "gpio_diag_page.h"
#include "log.h"
#include "rx_io.h"
#include "rx_uart.h"

#define __HAL_TIM_GET_PRESCALER(__HANDLE__)  ( (uint32_t)0x0000FFFF&((__HANDLE__)->Instance->PSC))

uint64_t umull(uint32_t op1, uint32_t op2) {
    uint64_t result;
    asm volatile(
        "umull %Q[dwresult], %R[dwresult], %[operand_1], %[operand_2]"
        :[dwresult] "=r" (result)
        :[operand_1] "r" (op1), [operand_2] "r" (op2)
    );
    return result;
}

uint64_t mul64 ( uint32_t a, uint32_t b ){
    return( ( 0x00000000FFFFFFFF&((uint64_t)a))*
    	    ( 0x00000000FFFFFFFF&((uint64_t)b)));
}

bool cmd_tim_get(int32_t argc, char *argv[]) {
	bool res = false;
	uint32_t hclkFreqHz = 0;
	hclkFreqHz = HAL_RCC_GetHCLKFreq();
	rx_printf("up_time: %u ms" CRLF, g_up_time_ms);
	rx_printf("sizeof(uint64_t): %u  "CRLF, sizeof(uint64_t));
	rx_printf("HCLK: %u Hz"CRLF, hclkFreqHz);
	rx_printf("TIM1 prescaler: %u "CRLF, __HAL_TIM_GET_PRESCALER(&htim1));
	rx_printf("TIM1 period: %u "CRLF, __HAL_TIM_GET_AUTORELOAD(&htim1));
	rx_printf("TIM1 counter: %u "CRLF, htim1.Instance->CNT);
	rx_printf("TIM1 capture/compare register 1: %u "CRLF, htim1.Instance->CCR1);
	rx_printf("TIM1 capture/compare register 2: %u "CRLF, htim1.Instance->CCR2);
	rx_printf("TIM1 capture/compare register 3: %u "CRLF, htim1.Instance->CCR3);
	rx_printf("TIM1 capture/compare register 4: %u "CRLF, htim1.Instance->CCR4);
	uint32_t temp =( __HAL_TIM_GET_AUTORELOAD(&htim1))*( __HAL_TIM_GET_PRESCALER(&htim1));
	rx_printf("TIM1 temp: %u [ms] "CRLF, temp);
	uint64_t temp10x3 = mul64 (1000,temp); // error
	rx_printf("TIM1 temp10x3: %lu %lu"CRLF, temp10x3/4294967296UL,temp10x3%4294967296UL);
	rx_printf("TIM1 temp10x3: %llu [ms] "CRLF, temp10x3);
	uint64_t petiod_it_ms =  (temp10x3) / ( hclkFreqHz);

	rx_printf("TIM1 Int period: %llu [ms] "CRLF, petiod_it_ms);
	float_t petiod_it = (float_t) ((float_t) temp) / ((float_t) hclkFreqHz);
	rx_printf("TIM1 temp %f Int period: %f [s] %f [ms] "CRLF, ((float_t) temp),petiod_it,
			petiod_it * 1000.0f);

	return res;
}


//tim timnum1 prec period on/off
bool cmd_tim_set(int32_t argc, char *argv[]) {
    bool res = false;
    if (4 == argc) {
        res = true;
        uint8_t tim_num = 0;
		uint16_t prescaler = 0;
		uint16_t period = 0;
        bool state = 0;


        if (true == res) {
            res = try_str2uint8 (argv[0], &tim_num);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse tim_num  %s", argv[0]);
            }
        }
        if (true == res) {
            res = try_str2uint16 (argv[1], &prescaler);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse prescaler %s", argv[1]);
            }
        }
        if (true == res) {
            res = try_str2uint16 (argv[2], &period);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse period %s", argv[2]);
            }
        }
        if (true == res) {
            res = try_str2bool (argv[3], &state);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse state %s", argv[3]);
            }
        }
        if (true == res) {
            LOG_INFO (SYS, "set TIM%u prescaler %u period %u %s", tim_num, prescaler, period,
                       bool2name (state));
            res = tim_set (tim_num, prescaler, period, state);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to set TIM%u",tim_num);
            }
        }
    } else {
        LOG_ERROR (SYS, "Usage: tims tim_num prescaler period state");
        LOG_INFO (SYS, "tims [1..]");
        LOG_INFO (SYS, "prescaler [0...0xFFFF]");
        LOG_INFO (SYS, "period [0...0xFFFF]");
        LOG_INFO (SYS, "state [on-1 off-0 spare-2 ]");
    }
    return res;
}

