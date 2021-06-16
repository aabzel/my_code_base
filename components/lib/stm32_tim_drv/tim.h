#ifndef TIM_H
#define TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define HW_TIM_CNT 14U

extern const uint8_t TimBusLUT[HW_TIM_CNT];

void delay_ms(uint32_t ms);
uint8_t tim_get_status(uint8_t tim_num);
uint16_t tim_get_cnt16(uint8_t tim_num);
uint32_t tim_get_cnt32(uint8_t tim_num);
uint16_t tim_get_prescaler(uint8_t tim_num);
uint16_t tim_get_period(uint8_t tim_num);
const char* tim_get_dir(uint8_t tim_num);
float calc_tim_min_period(uint8_t tim_num);
float calc_tim_max_period(uint8_t tim_num);
bool tim_init_ll(uint8_t tim_num, uint32_t period, uint16_t prescaler,
                 uint16_t division, uint16_t counter_mode, uint32_t cnt,
                 bool new_state);
bool tim_set(uint8_t tim_num, float des_period, float accuracy);
uint32_t RTOS_AppGetRuntimeCounterValue(void);
bool RTOS_AppConfigureTimerForRuntimeStats(void);
bool tim_set_prescaler_us(uint8_t tim_num, uint32_t prescaler_us);
uint64_t getRunTimeCounterValue64(void);

#ifdef __cplusplus
}
#endif

#endif /* TIM_H */
