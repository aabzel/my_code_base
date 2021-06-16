#ifndef UART_COMMON_H
#define UART_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct xUartHandle_t {
    uint16_t it_cnt;
    uint16_t rx_byte_cnt;
    uint16_t tx_byte_cnt;
    uint16_t tx_cpl_cnt;
    uint32_t* base_address;
    bool tx_it;
    bool init_done;
} UartHandle_t;

typedef enum {
    UART_ERROR_PE,
    UART_ERROR_FE,
    UART_ERROR_NE,
    UART_ERROR_ORE
} rx_uart_error_t;

const char* uart_error2str(rx_uart_error_t e);

#ifdef __cplusplus
}
#endif

#endif /* UART_COMMON_H */
