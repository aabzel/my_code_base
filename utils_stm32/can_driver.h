#ifndef UTILS_CAN_DRIVER_H_
#define UTILS_CAN_DRIVER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "device.h"
#include "can_driver_stm32.h"
#include "fifo_can_buffer.h"

typedef struct can_device_s {
    CanHandle_t* can_handle;
    uint8_t number;
    int16_t speed;
    fifo_can_t fifo;
    volatile uint32_t error_count;
    volatile uint32_t tx_queue_full_count;
    volatile uint32_t rx_queue_full_count;
    volatile uint32_t rx_overflow_count;
    volatile uint32_t rx_count;
    volatile uint32_t tx_count;
    bool debug_mode;
    can_error_info_t error_info;
} can_device_t;

extern fifo_can_t can_rx_queue;

#define MAX_CAN_NUMBER 2
extern can_device_t can1;
extern can_device_t can2;
#define HAS_CAN1
#define HAS_CAN2
#define FIRST_CAN_NUMBER (1U)
#define FIRST_CAN_DEVICE (&can1)


#ifdef CAN_GENERATED_FOR_MISRA
#define FIRST_CAN (FIRST_CAN_NUMBER)
#else /* CAN_GENERATED_FOR_MISRA */
#define FIRST_CAN (FIRST_CAN_DEVICE)
#endif /* CAN_GENERATED_FOR_MISRA */

#define CAN_TX_QUEUE_SIZE 100
#define CAN_RX_QUEUE_SIZE 100

extern uint8_t can_number_map[MAX_CAN_NUMBER];
extern can_device_t* can_device_map[MAX_CAN_NUMBER];

#ifdef __cplusplus
extern "C"
{
#endif

void RX_CAN_Init(void);

bool can_transmit(can_device_t *hcan, const can_message_t* msg);
bool can_transmit_to_can(const can_device_t* hcan);
bool can_set_speed(can_device_t* hcand, int new_speed, bool loopback);
bool can_queue_empty(const can_device_t* hcan);
can_device_t* can_device_by_number(uint8_t number);
bool can_transmit_n(const can_message_t* msg);
bool can_transmit_to_can_n(uint8_t can_number);
void can_report_errors(void);
void can_report_error_info(can_device_t* canp);
bool can_busoff(const can_device_t* hcan);

typedef enum {
    lec_No_Error,
    lec_Stuff_Error,
    lec_Form_Error,
    lec_Acknowledgment_Error,
    lec_Bit_recessive_Error,
    lec_Bit_dominant_Error,
    lec_CRC_Error,
    lec_Reset
} can_lec_t;

const char* lec2str(can_lec_t lec);
can_device_t* get_first_can(void);
bool can_valid_n(int can_number);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_CAN_DRIVER_H_ */
