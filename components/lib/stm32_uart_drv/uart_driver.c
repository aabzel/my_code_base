#include "uart_driver.h"

#include "bit_utils.h"
#include "debug_uart.h"
#include "external_uart.h"
#include "stm32f4xx.h"
#include "sys.h"

#ifdef HAS_CLI
    #include "uart_string_reader.h"
#endif

xUartStatistic_t UartStat[UART_CNT] = {0};

bool init_uart_driver(void) {
    memset(&UartStat[0], 0x00, sizeof(UartStat));
    return true;
}

generic_writer_t* get_uart_writer(void) {
    return &dbg_o;
}

bool uart_send_debug(const unsigned char* tx_buffer, uint32_t len) {
    bool res = true;
    for (uint32_t i = 0; i < len; i++) {
        res = send_byte_dbg_uart(tx_buffer[i]) && res;
    }
    return res;
}

bool uart_send(uint8_t uart_num, uint8_t* array, uint32_t array_len) {
    bool res = false;
    if (8 == uart_num) {
        external_uart_write(EXTERNAL_UART_CTX2, array, array_len);
        res = true;
    }
    if (7 == uart_num) {
        res = uart_send_debug(array, array_len);
    }
    if (4 == uart_num) {
        external_uart_write(EXTERNAL_UART_CTX1, array, array_len);
        res = true;
    }
    return res;
}

bool uart_set_baudrate(uint8_t uart_num, uint32_t baudrate) {
    return false;
}

/*see Figure 4. STM32F413xG/H block diagram*/
static const uint32_t UartClockLUT[10] = {
    /*0  UART1  */ APB2_CLOCK_HZ,
    /*1  UART2  */ APB1_CLOCK_HZ,
    /*2  UART3  */ APB1_CLOCK_HZ,
    /*3  UART4  */ APB1_CLOCK_HZ,
    /*4  UART5  */ APB1_CLOCK_HZ,
    /*5  UART6  */ APB2_CLOCK_HZ,
    /*6  UART7  */ APB1_CLOCK_HZ,
    /*7  UART8  */ APB1_CLOCK_HZ,
    /*8  UART9  */ APB2_CLOCK_HZ,
    /*9  UART10 */ APB2_CLOCK_HZ};

uint32_t uart_get_baud_rate(uint8_t uart_num, uint16_t* mantissa,
                            uint16_t* fraction, uint8_t* over_sampling) {
    bool res = true;
    uint32_t baud_rate_reg = 0;
    uint32_t control_register1 = 0;
    uint32_t baud_rate = 0;
    switch (uart_num) {
        case 1:
            baud_rate_reg = USART1->BRR;
            control_register1 = USART1->CR1;
            break;
        case 2:
            baud_rate_reg = USART2->BRR;
            control_register1 = USART2->CR1;
            break;
        case 3:
            baud_rate_reg = USART3->BRR;
            control_register1 = USART3->CR1;
            break;
        case 4:
            baud_rate_reg = UART4->BRR;
            control_register1 = UART4->CR1;
            break;
        case 5:
            baud_rate_reg = UART5->BRR;
            control_register1 = UART5->CR1;
            break;
        case 6:
            baud_rate_reg = USART6->BRR;
            control_register1 = USART6->CR1;
            break;
        case 7:
            baud_rate_reg = UART7->BRR;
            control_register1 = UART7->CR1;
            break;
        case 8:
            baud_rate_reg = UART8->BRR;
            control_register1 = UART8->CR1;
            break;
        case 9:
            baud_rate_reg = UART9->BRR;
            control_register1 = UART9->CR1;
            break;
        case 10:
            baud_rate_reg = UART10->BRR;
            control_register1 = UART10->CR1;
            break;
        default:
            res = false;
            break;
    }
    if (true == res) {
        (*fraction) = MASK_4BIT & baud_rate_reg;
        (*mantissa) = MASK_12BIT & (baud_rate_reg >> 4);
        if (BIT_15 == (control_register1 & BIT_15)) {
            (*over_sampling) = 8U;
        } else {
            (*over_sampling) = 16U;
        }
        baud_rate =
            UartClockLUT[uart_num - 1] /
            ((*over_sampling) * ((*mantissa) + (*fraction) / (*over_sampling)));
    }

    return baud_rate;
}

uint8_t get_uart_index(USART_TypeDef* USARTx) {
    uint8_t uart_num = 0;
    if (USART1 == USARTx) {
        uart_num = 1;
    } else if (USART2 == USARTx) {
        uart_num = 2;
    } else if (USART3 == USARTx) {
        uart_num = 3;
    } else if (UART4 == USARTx) {
        uart_num = 4;
    } else if (UART5 == USARTx) {
        uart_num = 5;
    } else if (USART6 == USARTx) {
        uart_num = 6;
    } else if (UART7 == USARTx) {
        uart_num = 7;
    } else if (UART8 == USARTx) {
        uart_num = 8;
    } else if (UART9 == USARTx) {
        uart_num = 9;
    } else if (UART10 == USARTx) {
        uart_num = 10;
    } else {
        uart_num = 0;
    }

    return uart_num;
}

bool USART_ClearAllITPendingBit(USART_TypeDef* USARTx) {
    USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
    USART_ClearITPendingBit(USARTx, USART_IT_TXE);
    USART_ClearITPendingBit(USARTx, USART_IT_TC);
    USART_ClearITPendingBit(USARTx, USART_IT_FE);
    USART_ClearITPendingBit(USARTx, USART_IT_ORE_RX);
    USART_ClearITPendingBit(USARTx, USART_IT_IDLE);
    USART_ClearITPendingBit(USARTx, USART_IT_LBD);
    USART_ClearITPendingBit(USARTx, USART_IT_CTS);
    USART_ClearITPendingBit(USARTx, USART_IT_ERR);
    USART_ClearITPendingBit(USARTx, USART_IT_NE);
    USART_ClearITPendingBit(USARTx, USART_IT_ORE_ER);
    USART_ClearITPendingBit(USARTx, USART_IT_PE);
    return true;
}
