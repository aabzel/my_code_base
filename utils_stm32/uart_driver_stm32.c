#include "uart_driver_stm32.h"

void RX_UART_IRQHandler(UartHandle_t* uart);

volatile uint32_t rxi_count;

#ifdef USART1_IS_SYNC
#error che
void USART1_IRQHandler(void);
void USART1_IRQHandler(void)
{
  HAL_USART_IRQHandler(&husart1);
}
#else /* USART1_IS_SYNC */
#if defined(HAS_IPP_USART1) || defined(HAS_IPP_UART1)
void USART1_IRQHandler(void);
void UART1_IRQHandler(void);
void USART1_IRQHandler(void) {
    RX_UART_IRQHandler (&huart1);
}
void UART1_IRQHandler(void) {
    RX_UART_IRQHandler (&huart1);
}
#endif
#endif /* USART1_IS_SYNC */


#ifdef USART2_IS_SYNC
void USART2_IRQHandler(void);
void USART2_IRQHandler(void)
{
  HAL_USART_IRQHandler(&husart2);
}
#else /* USART1_IS_SYNC */
#if defined(HAS_IPP_USART2) || defined(HAS_IPP_UART2)
void USART2_IRQHandler(void);
void UART2_IRQHandler(void);
void USART2_IRQHandler(void) {
    RX_UART_IRQHandler (&huart2);
}
void UART2_IRQHandler(void) {
    RX_UART_IRQHandler (&huart2);
}
#endif
#endif /* USART2_IS_SYNC */

#ifdef USART3_IS_SYNC
void USART3_IRQHandler(void);
void USART3_IRQHandler(void)
{
  HAL_USART_IRQHandler(&husart3);
}
#else /* USART3_IS_SYNC */
#if defined(HAS_IPP_USART3) || defined(HAS_IPP_UART3)
void USART3_IRQHandler(void);
void UART3_IRQHandler(void);
void USART3_IRQHandler(void) {
    RX_UART_IRQHandler (&huart3);
}
void UART3_IRQHandler(void) {
    RX_UART_IRQHandler (&huart3);
}
#endif
#endif /* USART3_IS_SYNC */

#ifdef USART4_IS_SYNC
void USART4_IRQHandler(void);
void USART4_IRQHandler(void)
{
  HAL_USART_IRQHandler(&husart4);
}
#else /* USART4_IS_SYNC */
#if defined(HAS_IPP_USART4) || defined(HAS_IPP_UART4)
void USART4_IRQHandler(void);
void UART4_IRQHandler(void);
void USART4_IRQHandler(void) {
    RX_UART_IRQHandler (&huart4);
}
void UART4_IRQHandler(void) {
    RX_UART_IRQHandler (&huart4);
}
#endif
#endif /* USART4_IS_SYNC */

#ifdef USART5_IS_SYNC
void USART5_IRQHandler(void);
void USART5_IRQHandler(void)
{
  HAL_USART_IRQHandler(&husart5);
}
#else /* USART5_IS_SYNC */
#if defined(HAS_IPP_USART5) || defined(HAS_IPP_UART5)
void USART5_IRQHandler(void);
void UART5_IRQHandler(void);
void USART5_IRQHandler(void) {
    RX_UART_IRQHandler(&huart5);
}
void UART5_IRQHandler(void) {
    RX_UART_IRQHandler(&huart5);
}
#endif
#endif /* USART5_IS_SYNC */

#ifdef USART6_IS_SYNC
void USART6_IRQHandler(void);
void USART6_IRQHandler(void)
{
  HAL_USART_IRQHandler(&husart6);
}
#else
#if defined(HAS_IPP_USART6) || defined(HAS_IPP_UART6)
void USART6_IRQHandler(void);
void UART6_IRQHandler(void);
void USART6_IRQHandler(void) {
    RX_UART_IRQHandler (&husart6);
}
void UART6_IRQHandler(void) {
    RX_UART_IRQHandler (&husart6);
}
#endif
#endif /* UART6_IS_SYNC */

#if 0
static inline void RX_UART_Transmit_IT(UART_HandleTypeDef *huart) {
#if (__STM32F4xx_CMSIS_VERSION>=0x02040300) || (defined(STM32L4))
    if (huart->gState == HAL_UART_STATE_BUSY_TX) {
#else
    if (huart->gState == HAL_UART_STATE_BUSY_TX) {
#endif

#ifdef STM32L4
        huart->Instance->TDR = (uint8_t) (*huart->pTxBuffPtr++ & (uint8_t) 0x00FF);
#else
        huart->Instance->DR = (uint8_t) (*huart->pTxBuffPtr++ & (uint8_t) 0x00FF);
#endif
        if (--huart->TxXferCount == 0) {
            /* Disable the UART Transmit Complete Interrupt */
            __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

            /* Enable the UART Transmit Complete Interrupt */
            __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
        }
    }
}

static inline void RX_UART_EndTransmit_IT(UART_HandleTypeDef *huart) {
    /* Disable the UART Transmit Complete Interrupt */
    __HAL_UART_DISABLE_IT(huart, UART_IT_TC);
#if (__STM32F4xx_CMSIS_VERSION>=0x02040300) || defined(STM32L4)
    huart->gState = HAL_UART_STATE_READY;
#else
    huart->gState = HAL_UART_STATE_READY;
#endif
    HAL_UART_TxCpltCallback (huart);
}

void RX_UART_IRQHandler(UART_HandleTypeDef* huart) {
    if (__HAL_UART_GET_FLAG (huart, UART_FLAG_PE) && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_PE)) {
        __HAL_UART_CLEAR_PEFLAG(huart);
        RX_UART_Error_callback (huart, UART_ERROR_PE);
    }
    if (__HAL_UART_GET_IT_SOURCE(huart, UART_IT_ERR)) {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE)) {
            __HAL_UART_CLEAR_FEFLAG(huart);
            RX_UART_Error_callback (huart, UART_ERROR_FE);
        }

        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE)) {
            __HAL_UART_CLEAR_NEFLAG(huart);
            RX_UART_Error_callback (huart, UART_ERROR_NE);
        }
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE)) {
            __HAL_UART_CLEAR_OREFLAG(huart);
            RX_UART_Error_callback (huart, UART_ERROR_ORE);
        }
    }

    if (__HAL_UART_GET_FLAG (huart, UART_FLAG_RXNE) && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE)) {
#ifdef STM32L4
        char c = huart->Instance->RDR & 0xFF;
#else
        char c = huart->Instance->DR & 0xFF;
#endif
        RX_UART_Recv_callback (huart, c);
    }
    if (__HAL_UART_GET_FLAG (huart, UART_FLAG_TXE) && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_TXE)) {
        RX_UART_Transmit_IT (huart);
    }
    if (__HAL_UART_GET_FLAG (huart, UART_FLAG_TC) && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_TC)) {
        RX_UART_EndTransmit_IT (huart);
    }
}

#endif
void RX_UART_Start_Receive(UartHandle_t* huart) {
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_PE);

    /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
    __HAL_UART_ENABLE_IT(huart, UART_IT_ERR);

    /* Enable the UART Data Register not empty Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}


void read_char(uart_string_reader_t* r) {
    enter_critical ();
    RX_UART_Start_Receive (r->huart);
    exit_critical ();
}
