#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "pal_utils.h"

#include "stm32f1xx_hal.h"
//#include "stm32f100xb.h"
//#include "stm32f1xx_hal_gpio.h"

#define PIN_COUNT 64U

#define MCU_PACKAGE mcu_QFP64

#define PIN_NAME_MAX_LEN 13U
#define PIN_NAME_FORMAT "13s"

#define BLUE_LED_PIN 8U
#define BLUE_LED_PORT PORT_C
#define BLUE_LED_PAD PAD_EX (BLUE_LED_PORT, BLUE_LED_PIN)

#define GREEN_LED_PIN 9U
#define GREEN_LED_PORT PORT_C
#define GREEN_LED_PAD PAD_EX (GREEN_LED_PORT, GREEN_LED_PIN)

#define USART1_TX_PIN 9U
#define USART1_TX_PORT PORT_A
#define USART1_TX_PAD PAD_EX (USART1_TX_PORT, USART1_TX_PIN)

#define USART1_RX_PIN 10U
#define USART1_RX_PORT PORT_A
#define USART1_RX_PAD PAD_EX (USART1_RX_PORT, USART1_RX_PIN)

typedef struct {
    mcu_pin_number_t mcu_pin;
    uint8_t pin_pad;
    const char *pin_name;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
    GPIO_PinState PinState; // size ?
    // function ?
    // in/out
} pin_info_t;

extern const pin_info_t pin_info[];

bool init_pins (void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
