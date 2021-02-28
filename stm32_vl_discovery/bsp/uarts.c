#include <string.h>

#include "gpio.h"
#include "uart_driver_stm32.h"
#include "uarts.h"

uint32_t g_uart_tx_cnt = 0;
uint32_t g_uart_rx_cnt = 0;

UART_HandleTypeDef huart1;
uint8_t uart1RxBuffer[UART1_RX_BUFF_SIZE + 5];

bool MX_USART1_UART_Init (void) {
    bool res = false;
    g_uart_tx_cnt = 0;
    g_uart_rx_cnt = 0;

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init (&huart1) == HAL_OK) {
        HAL_UART_Transmit (&huart1, "[d] uart 1 init fine", strlen ("[d] start"), 100);
        res = true;
    }
    HAL_UART_Receive_IT (&huart1, &uart1RxBuffer[0], UART1_RX_BUFF_SIZE);
    return res;
}

void HAL_UART_MspInit (UART_HandleTypeDef *huart) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (huart->Instance == USART1) {

        __HAL_RCC_USART1_CLK_ENABLE ();

        __HAL_RCC_GPIOA_CLK_ENABLE ();

        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

        HAL_NVIC_SetPriority (USART1_IRQn, 5, 5);
        HAL_NVIC_EnableIRQ (USART1_IRQn);
    }
}

void HAL_UART_MspDeInit (UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        __HAL_RCC_USART1_CLK_DISABLE ();
        HAL_GPIO_DeInit (GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
        HAL_NVIC_DisableIRQ (USART1_IRQn);
    }
}

void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart) {
    HAL_GPIO_TogglePin (LD3_GPIO_Port, LD3_Pin);
    g_uart_rx_cnt++;
    if (USART1 == huart->Instance) {
        RX_UART_Recv_callback (huart, uart1RxBuffer[0]);
        HAL_UART_Receive_IT (&huart1, &uart1RxBuffer[0], UART1_RX_BUFF_SIZE);
    }
}

#if 0
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    g_uart_tx_cnt++;
    if (USART1 == huart->Instance) {
    }
}
#endif
