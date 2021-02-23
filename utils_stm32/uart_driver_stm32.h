#ifndef __UART_DRIVER_STM32_H_
#define __UART_DRIVER_STM32_H_
#include "uart_common.h"
#include <stdbool.h>
#include "uart_string_reader.h"

void HAL_UART_TxCpltCallback(UartHandle_t* uart);


void RX_UART_Start_Receive(UartHandle_t* uart);
void RX_UART_Error_callback(UartHandle_t* uart, rx_uart_error_t error);
void RX_UART_Recv_callback(UartHandle_t* uart, char c);
#define RX_UART_Send_callback(uart) HAL_UART_TxCpltCallback(uart)

void read_char(uart_string_reader_t* r);

#endif /* __UART_DRIVER_STM32_H_ */
