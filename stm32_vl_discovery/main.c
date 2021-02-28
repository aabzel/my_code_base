#include <stdint.h>

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

#include "clocks.h"
#include "common_functions.h"
#include "convert.h"
#include "device.h"
#include "gpio.h"
#include "gpio_diag_page.h"
#include "gpio_pwm.h"
#include "log.h"
#include "main_loop.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "spi.h"
#include "timers.h"
#include "uarts.h"

static void Error_Handler (void) {
    __disable_irq ();
    while (1) {
    }
}

void HAL_MspInit (void) {
    __HAL_RCC_AFIO_CLK_ENABLE ();
    __HAL_RCC_PWR_CLK_ENABLE ();
    __GPIOA_CLK_ENABLE ();
    __GPIOB_CLK_ENABLE ();

    __HAL_AFIO_REMAP_SWJ_NOJTAG ();
    __HAL_RCC_TIM1_CLK_ENABLE ();
    __SPI1_CLK_ENABLE ();

    HAL_NVIC_SetPriority (TIM1_BRK_TIM15_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ (TIM1_BRK_TIM15_IRQn);

    HAL_NVIC_SetPriority (SPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ (SPI1_IRQn);

    HAL_TIM_Base_Start_IT (&htim1);
}

int main (void) {
    bool res = false;
    HAL_Init ();
    set_log_level (SYS, LOG_LEVEL_DEBUG);
    set_log_level (CAN, LOG_LEVEL_CRITICAL);

    res = SystemClock_Config ();
    LOG_NOTICE (SYS, "[d] Clock init ", (true == res) ? "OK" : "Err");
    res = gpio_init ();
    LOG_NOTICE (SYS, "[d] GPIO init ", (true == res) ? "OK" : "Err");
    res = spi1_init ();
    LOG_NOTICE (SYS, "[d] SPI init ", (true == res) ? "OK" : "Err");
    res = init_gpio_pwm ();
    LOG_NOTICE (SYS, "[d] GPIO pwm init ", (true == res) ? "OK" : "Err");
    res = gpio_diag_page_init ();
    MX_USART1_UART_Init ();
    res = timers_init ();
    LOG_NOTICE (SYS, "[d] TIM init ", (true == res) ? "OK" : "Err");

    configureTimerForRunTimeStats ();
    uarts_init ();
    // start_banner ();
    // print_detected_board_type ();

    LOG_NOTICE (SYS, "FW started");
    LOG_NOTICE (SYS, "main %p", main);
    LOG_NOTICE (SYS, "PORT_A %s", utoa_bin16 (pal_readport (PORT_A)));

    common_main_loop ();
    while (1) {
    }

    return 0;
}
