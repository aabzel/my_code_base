#include "board.h"

#include <stdbool.h>
#include <stdint.h>

#include "gpio.h"
#include "stm32f1xx_hal_gpio.h"

pin_info_t const pin_info[] = {
    {1, (uint8_t)0xFFU, "VBAT", 0xFFFFFFFF, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {2, PAD_EX (PORT_C, 13), "PC13", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {3, (uint8_t)0xFFU, "OSC32_IN", 0xFFFFFFFF, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {4, (uint8_t)0xFFU, "OSC32_OUT", 0xFFFFFFFF, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {5, (uint8_t)0xFFU, "OSC_IN", 0xFFFFFFFF, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {6, (uint8_t)0xFFU, "OSC_OUT", 0xFFFFFFFF, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {7, (uint8_t)0xFFU, "nRST", 0xFFFFFFFF, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {8, PAD_EX (PORT_C, 0), "PC0", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {9, PAD_EX (PORT_C, 1), "PC1", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {10, PAD_EX (PORT_C, 2), "PC2", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {11, PAD_EX (PORT_C, 3), "PC3", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {12, (uint8_t)0xFFU, "VSSA", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {13, (uint8_t)0xFFU, "VDDA", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {15, PAD_EX (PORT_A, 1), "PA1", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {16, PAD_EX (PORT_A, 2), "PA2", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {17, PAD_EX (PORT_A, 3), "PA3", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {18, (uint8_t)0xFF, "VSS4", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {19, (uint8_t)0xFF, "VDD4", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {20, PAD_EX (PORT_A, 4), "PA4", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {21, PAD_EX (PORT_A, 5), "SPI1_SCK", GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {22, PAD_EX (PORT_A, 6), "SPI1_MISO", GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {23, PAD_EX (PORT_A, 7), "SPI1_MOSI", GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {24, PAD_EX (PORT_C, 4), "PC4", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {25, PAD_EX (PORT_C, 5), "PC5", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {26, PAD_EX (PORT_B, 0), "PB0", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {27, PAD_EX (PORT_B, 1), "PB1", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {28, PAD_EX (PORT_B, 2), "PB2", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {14, PAD_EX (PORT_A, 0), "USER_BTN", GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {29, PAD_EX (PORT_B, 10), "CD_DET", GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {30, PAD_EX (PORT_B, 11), "PB11", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_PIN_SET},
    {31, (uint8_t)0xFF, "VSS1", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {32, (uint8_t)0xFF, "VDD1", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {33, PAD_EX (PORT_B, 12), "PB12", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {34, PAD_EX (PORT_B, 13), "PB13", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {35, PAD_EX (PORT_B, 14), "PB14", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {36, PAD_EX (PORT_B, 15), "PB15", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {37, PAD_EX (PORT_C, 6), "PC6", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {38, PAD_EX (PORT_C, 7), "PC7", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {39, BLUE_LED_PAD, "Blue Led", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_SET},
    {40, GREEN_LED_PAD, "Green Led", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_SET},
    {41, PAD_EX (PORT_A, 8), "PA8", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {42, USART1_TX_PAD, "USART1_TX", GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {43, USART1_RX_PAD, "USART1_RX", GPIO_MODE_AF_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {44, PAD_EX (PORT_A, 11), "PA11", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {45, PAD_EX (PORT_A, 12), "PA12", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {46, PAD_EX (PORT_A, 13), "PA13", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {47, (uint8_t)0xFF, "VSS_2", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {48, (uint8_t)0xFF, "VDD_2", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {49, PAD_EX (PORT_A, 14), "PA14", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {50, PAD_EX (PORT_A, 15), "PA15", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {51, PAD_EX (PORT_C, 10), "PC10", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {52, PAD_EX (PORT_C, 11), "PC11", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {53, PAD_EX (PORT_C, 12), "PC12", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {54, PAD_EX (PORT_D, 2), "PD2", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {55, PAD_EX (PORT_B, 3), "PB3", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {56, PAD_EX (PORT_B, 4), "PB4", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {57, PAD_EX (PORT_B, 5), "PB5", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {58, PAD_EX (PORT_B, 6), "PB6", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {59, PAD_EX (PORT_B, 7), "PB7", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {60, (uint8_t)0xFF, "BOOT0", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {61, PAD_EX (PORT_B, 8), "PB8", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {62, PAD_EX (PORT_B, 9), "PB9", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {63, (uint8_t)0xFF, "VSS_3", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},
    {64, (uint8_t)0xFF, "VDD_3", GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_PIN_RESET},

    {-1, (uint8_t)0xFFU, "END", 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

bool init_pins (void) {
    bool res = false;
    uint16_t cnt = 0;
    int pin_table_size = sizeof (pin_info) / (sizeof (pin_info[0]));
    for (int pin = 0; pin < pin_table_size; pin++) {
        cnt += (uint16_t)init_pin (&pin_info[pin]);
    }
    if (0 < cnt) {
        res = true;
    }
    return res;
}