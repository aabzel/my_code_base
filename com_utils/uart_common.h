#ifndef UART_COMMON_H_
#define UART_COMMON_H_

#include "device.h"

#if defined(CUBEMX)
    typedef UART_HandleTypeDef UartHandle_t;
#elif defined(SPC5)
#include "uart_driver_spc5.h"
    typedef linflex_t UartHandle_t;
#else
    typedef void UartHandle_t;
#error "No MCU defined to support UART"
#endif

typedef enum {
    UART_ERROR_PE,
    UART_ERROR_FE,
    UART_ERROR_NE,
    UART_ERROR_ORE
} rx_uart_error_t;

const char* uart_error2str(rx_uart_error_t e);
#endif /* UART_COMMON_H_ */
