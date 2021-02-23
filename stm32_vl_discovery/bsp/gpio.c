#include "gpio.h"

#include "stm32f1xx_hal.h"

void MX_GPIO_Init (void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE ();
    __HAL_RCC_GPIOD_CLK_ENABLE ();
    __HAL_RCC_GPIOA_CLK_ENABLE ();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin (GPIOC, LD4_Pin | LD3_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : LD4_Pin LD3_Pin */
    GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);
}
