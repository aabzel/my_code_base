#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx.h"
#include "uart_common.h"
#include "writer_generic.h"

#define UART_RX_FIFO_ARRAY_SIZE 100U
#define UART_TX_ARRAY_SIZE 600U
#define UART_RX_ARRAY_SIZE 500U

#define DBG_STREAM (&dbg_o.s)

#ifdef HAS_CLI
void process_uarts(void);
#endif

#define UART_CNT 10U

typedef struct xUartStatistic_t {
    char name[40];
    uint32_t tx_cnt;
    uint32_t rx_cnt;
} xUartStatistic_t;

extern xUartStatistic_t UartStat[UART_CNT];

bool init_uart_driver(void);
bool uart_send_debug(const unsigned char* tx_buffer, uint32_t len);
bool uart_send(uint8_t uart_num, uint8_t* array, uint32_t array_len);
void UART_TxCpltCallback(UartHandle_t* UartHandle);
uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa,
                            uint16_t* fraction, uint8_t* over_sampling);
uint8_t get_uart_index(USART_TypeDef* USARTx);
bool USART_ClearAllITPendingBit(USART_TypeDef* USARTx);
bool uart_set_baudrate(uint8_t uart_num, uint32_t baudrate);

#ifdef __cplusplus
}
#endif

#endif /* UART_DRIVER_H */
