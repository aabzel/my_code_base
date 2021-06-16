/*
 * File Name          : debug_uart.h
 */

#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#ifdef USE_UART_DEBUG_PORT

    #ifdef __cplusplus
extern "C" {
    #endif

    #include "uart_driver.h"

    #include <stdbool.h>
    #include <stdint.h>

    #include "io_utils.h"
    #include "stm32f4xx.h"
    #include "stm32f4xx_usart.h"

extern UartHandle_t huart_dbg;

void DebugUartInit(void);
void pflush_uart(void);
int putchar_uart(int ch);
void DebugUartDeInit(void);
void procDebugUartIrqHandler(void);
void tune_read_char(void);
void uart7_start_receive(void);
void deinit_debug_uart_gpio(void);
bool send_byte_dbg_uart(uint8_t tx_byte);

    #ifdef USE_FREERTOS
        #include "FreeRTOS.h"
        #include "semphr.h"
        #include "task.h"

extern SemaphoreHandle_t DebugUartMutex;
        #define __DEBUG_UART_GRAB() (xSemaphoreTake(DebugUartMutex, portMAX_DELAY))
        #define __DEBUG_UART_RELEASE() (xSemaphoreGive(DebugUartMutex))
    #else
        #define __DEBUG_UART_GRAB()
        #define __DEBUG_UART_RELEASE()
    #endif /*USE_FREERTOS*/

    #define DEBUG_UART UART7
    #define DEBUG_UART_IRQHandler UART7_IRQHandler
    #define DEBUG_UART_BAUDRATE 921600U
    #define DEBUG_UART_TX_PIN GPIO_Pin_8
    #define DEBUG_UART_TX_PORT GPIOE
    #define DEBUG_UART_RX_PIN GPIO_Pin_7
    #define DEBUG_UART_RX_PORT GPIOE
    #define DEBUG_UART_PRIORITY 13

    #define __DEBUG_UART_CLOCK_ENABLE() \
        (RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE))
    #define __DEBUG_UART_CLOCK_DISABLE() \
        (RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, DISABLE))

    #define __DEBUG_UART_REMAP_ENABLE()                                           \
        do {                                                                      \
            GPIO_PinAFConfig(DEBUG_UART_TX_PORT, GPIO_PinSource8, GPIO_AF_UART7); \
            GPIO_PinAFConfig(DEBUG_UART_RX_PORT, GPIO_PinSource7, GPIO_AF_UART7); \
        } while (0);

    #ifdef __cplusplus
}
    #endif

#endif /*USE_UART_DEBUG_PORT*/

#endif /* DEBUG_UART_H */
