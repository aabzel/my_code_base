#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx.h"
#include "vega_can_typedefs.h"

#define CAN_CNT 3

typedef struct xCanStatistic_t {
    char name[40];
    uint32_t tx_cnt;
    uint32_t rx_cnt;
} CanStatistic_t;

extern CanStatistic_t CanStat[CAN_CNT];

CAN_TypeDef* get_can_reg(uint8_t can_num);
bool is_can_filter_active(uint8_t can_num, uint8_t filter_num);
float can_calc_bit_rate(uint32_t can_btr);
float can_calc_bit_time(uint32_t can_btr);
bool is_std_id_allowed(uint8_t can_num, uint16_t std_id);
bool add_id_to_list_filter(uint8_t can_num, uint16_t std_id);
bool can_send(uint8_t can_num, can_rx_frame_t frame);
bool can_reset(uint8_t can_num);
#ifdef __cplusplus
}
#endif

#endif /* CAN_DRIVER_H */
