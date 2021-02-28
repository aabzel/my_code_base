#include "stm32f1xx_it.h"

#include "gpio.h"
#include "spi.h"
#include "timers.h"
#include "uarts.h"

void NMI_Handler (void) {

    while (1) {
    }
}
void SPI1_IRQHandler (void) { HAL_SPI_IRQHandler (&hspi1); }

#if 0

void HardFault_Handler (void) {
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while (1) {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
}
#endif

void MemManage_Handler (void) {
    while (1) {
    }
}

void BusFault_Handler (void) {

    while (1) {
    }
}

void UsageFault_Handler (void) {

    while (1) {
    }
}

void SVC_Handler (void) {}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler (void) {
    /* USER CODE BEGIN DebugMonitor_IRQn 0 */

    /* USER CODE END DebugMonitor_IRQn 0 */
    /* USER CODE BEGIN DebugMonitor_IRQn 1 */

    /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler (void) {
    /* USER CODE BEGIN PendSV_IRQn 0 */

    /* USER CODE END PendSV_IRQn 0 */
    /* USER CODE BEGIN PendSV_IRQn 1 */

    /* USER CODE END PendSV_IRQn 1 */
}

void SysTick_Handler (void) { HAL_IncTick (); }

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

void USART1_IRQHandler (void) { HAL_UART_IRQHandler (&huart1); }

void TIM1_BRK_TIM15_IRQHandler (void) { HAL_TIM_IRQHandler (&htim1); }

void TIM1_UP_TIM16_IRQHandler (void) { HAL_TIM_IRQHandler (&htim1); }

void TIM1_TRG_COM_TIM17_IRQHandler (void) { HAL_TIM_IRQHandler (&htim1); }

void TIM1_CC_IRQHandler (void) { HAL_TIM_IRQHandler (&htim1); }
