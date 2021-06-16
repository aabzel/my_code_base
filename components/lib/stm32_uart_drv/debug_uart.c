#include "debug_uart.h"

#include <string.h>

#ifndef USE_UART_DEBUG_PORT
    #error Add USE_UART_DEBUG_PORT macro to build
#endif

#ifdef HAS_CLI
    #include "uart_string_reader.h"
#endif /*HAS_CLI*/

#include <stdbool.h>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "uart_common.h"

UartHandle_t huart_dbg = {0};

#ifdef USE_FREERTOS
    #include "portmacro.h"
SemaphoreHandle_t DebugUartMutex = NULL;
#endif

bool send_byte_dbg_uart(uint8_t tx_byte) {
#ifdef 0
    bool is_it = isFromInterrupt();
    if (false == is_it) {
        BaseType_t sem_res = pdFALSE;
        if (NULL != DebugUartMutex) {
            sem_res = xSemaphoreTake(DebugUartMutex, 0);
            if (pdFALSE == sem_res) {
                return false;
            }
        }
    }
#endif
    bool res = true;
    uint32_t cnt = 0;
    uint32_t init_dbg_uart_tx_byte_cnt = 0;
    init_dbg_uart_tx_byte_cnt = huart_dbg.tx_cpl_cnt;

    USART_ClearITPendingBit(DEBUG_UART, USART_IT_TC);

    UartStat[get_uart_index(DEBUG_UART)].tx_cnt++;

    USART_SendData(DEBUG_UART, (uint16_t)tx_byte);
    while (init_dbg_uart_tx_byte_cnt == huart_dbg.tx_cpl_cnt) {
        cnt++;
        if (USART_GetFlagStatus(DEBUG_UART, USART_FLAG_TC) == SET) {
            res = true;
            break;
        }
        if (10000 < cnt) {
            res = false;
            break;
        }
    }
    /*TODO: UnLock semaphore*/
#ifdef 0
    if (false == is_it) {
        if (NULL != DebugUartMutex) {
            xSemaphoreGive(DebugUartMutex);
        }
    }
#endif

    return res;
}

void UART_TxCpltCallback(UartHandle_t* UartHandle) {
    if (DEBUG_UART == ((USART_TypeDef*)UartHandle->base_address)) {
        dbg_o.f_transmit(&dbg_o);
    }
}

void UART_RxCharCpltCallback(char ch) {
#ifdef HAS_CLI
    uart_string_reader_rx_callback(&cmd_reader, ch);
#endif
}

static void init_debug_uart_gpio(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    /* Already enabled. Otherwise error occurs.
  RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  */

    GPIO_PinAFConfig(DEBUG_UART_TX_PORT, GPIO_PinSource8, GPIO_AF_UART7);
    GPIO_PinAFConfig(DEBUG_UART_RX_PORT, GPIO_PinSource7, GPIO_AF_UART7);

    GPIO_InitStructure.GPIO_Pin = DEBUG_UART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DEBUG_UART_TX_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = DEBUG_UART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(DEBUG_UART_RX_PORT, &GPIO_InitStructure);
}

static void init_dbg_uart_interrupts(void) {
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = DEBUG_UART_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_EnableIRQ(UART7_IRQn);
}

void DebugUartInit(void) {
    memset(&huart_dbg, 0x00, sizeof(huart_dbg));
    huart_dbg.base_address = (uint32_t*)DEBUG_UART;
    strncpy(UartStat[get_uart_index(DEBUG_UART)].name, "CLI",
            sizeof(UartStat[get_uart_index(DEBUG_UART)].name));
    UartStat[get_uart_index(DEBUG_UART)].rx_cnt = 0;
    UartStat[get_uart_index(DEBUG_UART)].tx_cnt = 0;
#ifdef USE_FREERTOS
    if (DebugUartMutex == NULL)
        DebugUartMutex = xSemaphoreCreateMutex();
#endif

    USART_InitTypeDef USART_InitStructure = {0};
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

    init_debug_uart_gpio();

    init_dbg_uart_interrupts();

    USART_InitStructure.USART_BaudRate = DEBUG_UART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(DEBUG_UART, &USART_InitStructure);

    USART_Cmd(DEBUG_UART, ENABLE);

    USART_ClearITPendingBit(DEBUG_UART, USART_IT_RXNE);
    USART_ClearITPendingBit(DEBUG_UART, USART_IT_TC);
    // USART_ClearITPendingBit(DEBUG_UART, USART_IT_TXE);

    USART_ITConfig(DEBUG_UART, USART_IT_RXNE, ENABLE);
    USART_ITConfig(DEBUG_UART, USART_IT_TC, ENABLE);
    // USART_ITConfig(DEBUG_UART, USART_IT_TXE, ENABLE);

    huart_dbg.init_done = true;
}

void deinit_debug_uart_gpio(void) {
}

void DebugUartDeInit(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_Cmd(DEBUG_UART, DISABLE);

    __DEBUG_UART_CLOCK_DISABLE();

    /* Configure UART pins as analog */
    GPIO_InitStructure.GPIO_Pin = DEBUG_UART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(DEBUG_UART_TX_PORT, &GPIO_InitStructure);

    deinit_debug_uart_gpio();
}

void pflush_uart(void) {
}

int putchar_uart(int ch) {
    send_byte_dbg_uart(ch);
    return ch;
}

void tune_read_char(void) {
    uart7_start_receive();
}

void uart7_start_receive(void) {
    USART_ClearITPendingBit(DEBUG_UART, USART_IT_RXNE);
    USART_ClearITPendingBit(DEBUG_UART, USART_IT_TC);
    USART_ClearITPendingBit(DEBUG_UART, USART_IT_PE);
    USART_ClearITPendingBit(DEBUG_UART, USART_IT_TXE);

    USART_ITConfig(DEBUG_UART, USART_IT_RXNE, ENABLE);
    USART_ITConfig(DEBUG_UART, USART_IT_TC, ENABLE);
}

void uart_error_callback(rx_uart_error_t error) {
    (void)error;
#ifdef HAS_CLI
    uart_string_reader_error_callback(&cmd_reader);
#endif /*HAS_CLI*/
    writer_error_callback(&dbg_o);
}

void procDebugUartIrqHandler(void) {
    huart_dbg.it_cnt++;
    if (USART_GetITStatus(DEBUG_UART, USART_IT_RXNE)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_RXNE);
        uint16_t rx_byte = USART_ReceiveData(DEBUG_UART);
#if HAS_CLI
        UART_RxCharCpltCallback(rx_byte);
#endif
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_TXE)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_TXE);
        huart_dbg.tx_byte_cnt++;
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_TC)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_TC);
        huart_dbg.tx_it = true;
        huart_dbg.tx_cpl_cnt++;
        UartStat[7].rx_cnt++;
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_FE)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_FE);
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_ORE_RX)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_ORE_RX);
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_IDLE)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_IDLE);
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_LBD)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_LBD);
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_CTS)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_CTS);
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_ERR)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_ERR);
#if HAS_CLI
        uart_error_callback(0);
#endif
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_NE)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_NE);
#if HAS_CLI
        uart_error_callback(0);
#endif
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_ORE_ER)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_ORE_ER);
#if HAS_CLI
        uart_error_callback(0);
#endif
    }
    if (USART_GetITStatus(DEBUG_UART, USART_IT_PE)) {
        USART_ClearITPendingBit(DEBUG_UART, USART_IT_PE);
#if HAS_CLI
        uart_error_callback(0);
#endif
    }
}
