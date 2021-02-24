#include <stdint.h>

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

#include "main_loop.h"
#include "gpio.h"
#include "rx_uart.h"
#include "uarts.h"
#include "common_functions.h"
#include "log.h"
#include "device.h"

static void Error_Handler (void) {
    __disable_irq ();
    while (1) {
    }
}

static void SystemClock_Config (void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
    if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler ();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler ();
    }
}

void HAL_MspInit (void) {
    __HAL_RCC_AFIO_CLK_ENABLE ();
    __HAL_RCC_PWR_CLK_ENABLE ();

    __HAL_AFIO_REMAP_SWJ_NOJTAG ();
}

 int main (void) {
	//bool res = false;
    HAL_Init ();

    SystemClock_Config ();
    MX_GPIO_Init ();
    MX_USART1_UART_Init ();
	


    configureTimerForRunTimeStats ();
    uarts_init ();
    //start_banner ();
    //print_detected_board_type ();

    set_log_level (SYS, LOG_LEVEL_DEBUG);
    set_log_level (CAN, LOG_LEVEL_CRITICAL);

    LOG_NOTICE(SYS, "FW started");


    common_main_loop ( );
    while (1) {
        ;
    }

    return 0;
}
