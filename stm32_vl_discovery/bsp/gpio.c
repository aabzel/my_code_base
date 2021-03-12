#include "gpio.h"

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "pal_utils.h"
#include "stm32f1xx_hal.h"

bool gpio_init (void) {
    bool res = false;
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE ();
    __HAL_RCC_GPIOB_CLK_ENABLE ();
    __HAL_RCC_GPIOC_CLK_ENABLE ();
    __HAL_RCC_GPIOD_CLK_ENABLE ();
    res = init_pins ();
    return res;
}

uint32_t calc_port_addr (uint8_t port) {
    uint32_t addr = 0xFFFFFFFF;
    switch (port) {
    case PORT_A:
        addr = (uint32_t)GPIOA;
        break;
    case PORT_B:
        addr = (uint32_t)GPIOB;
        break;
    case PORT_C:
        addr = (uint32_t)GPIOC;
        break;
    case PORT_D:
        addr = (uint32_t)GPIOD;
        break;
    case PORT_E:
        addr = (uint32_t)GPIOE;
        break;
    default:
        break;
    }
    return addr;
}

uint8_t init_pin (const pin_info_t *pin_info) {
	uint8_t ret = 0;
    if ((0xFFFFFFFF != pin_info->Mode) && (0xFF != pin_info->pin_pad)) {

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)calc_port_addr ((uint8_t)PAD_TO_PORT (pin_info->pin_pad));

        uint16_t gpio_pin_mask = (1 << PAD_TO_PIN (pin_info->pin_pad));

        HAL_GPIO_WritePin (GPIOx, gpio_pin_mask, pin_info->PinState);

        GPIO_InitStruct.Pin = gpio_pin_mask;
        GPIO_InitStruct.Mode = pin_info->Mode;
        GPIO_InitStruct.Pull = pin_info->Pull;
        GPIO_InitStruct.Speed = pin_info->Speed;

        HAL_GPIO_Init (GPIOx, &GPIO_InitStruct);
        ret = 1;
    }
    return ret;
}
