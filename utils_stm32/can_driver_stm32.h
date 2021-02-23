#ifndef __CAN_DRIVER_HAL_H_
#define __CAN_DRIVER_HAL_H_

#include "can.h"
#include "oprintf.h"
#include "table_utils.h"
#include "can_driver.h"
#include "can_message.h"
typedef CAN_HandleTypeDef CanHandle_t;

typedef struct {
    uint8_t fake;
} can_error_info_t;

#define ERROR_INFO_INIT {0}

struct can_device_s;
typedef struct can_device_s can_device_t;

const table_col_t* can_registers_cols(void);
bool can_transmit_force(can_device_t *hcan, const can_message_t* msg);
void can_irq_error(can_device_t* hcand, int can_number);
void can_irq_rx1(can_device_t *hcan);
void can_irq_rx0(can_device_t *hcan);
void can_irq_tx(can_device_t *hcan);
bool can_tx_mailboxes_empty(const can_device_t *hcan);
bool can_has_empty_tx_mailbox(const can_device_t *hcan);

#endif /* __CAN_DRIVER_HAL_H_ */
