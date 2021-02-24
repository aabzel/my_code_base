#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define PIN_COUNT 64U

#define MCU_PACKAGE mcu_QFP64

#define PIN_NAME_MAX_LEN 13U
#define PIN_NAME_FORMAT "13s"

typedef struct {
    uint8_t pin_pad;
    const char* pin_name;
} pin_info_t;

extern pin_info_t pin_info[PIN_COUNT + 1U];


void init_pins (void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif 
