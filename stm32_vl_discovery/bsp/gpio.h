#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "stm32f1xx_hal.h"

#define LD4_Pin GPIO_PIN_8
#define LD4_GPIO_Port GPIOC

#define LD3_Pin GPIO_PIN_9
#define LD3_GPIO_Port GPIOC

#define TMS_SWDIO_Pin GPIO_PIN_13
#define TMS_SWDIO_GPIO_Port GPIOA

#define TCK_SWCLK_Pin GPIO_PIN_14
#define TCK_SWCLK_GPIO_Port GPIOA

bool init_pin (const pin_info_t *pin_info);
bool gpio_init (void);
uint32_t calc_port_addr (uint8_t port);

#ifdef __cplusplus
}
#endif

#endif // GPIO_H
