#ifndef UARTS_H
#define UARTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

extern uint32_t g_uart_tx_cnt;
extern uint32_t g_uart_rx_cnt;
#define UART1_RX_BUFF_SIZE   (1)

extern UART_HandleTypeDef huart1;

void MX_USART1_UART_Init (void);

#ifdef __cplusplus
}
#endif

#endif /* UARTS_H */
