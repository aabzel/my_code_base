#include "iwdt_driver.h"

#include <stdbool.h>
#include <stdint.h>

#include "bit_utils.h"
#include "stm32f4xx.h"

uint16_t code2PscLUT[8] = {4, 8, 16, 32, 64, 128, 256, 0};

float iwdt_get_timeout(void) {
    float iwdt_timeout_s = 0.0f;
    uint32_t prescaler = code2PscLUT[MASK_3BIT & (IWDG->PR)];
    uint32_t reload = MASK_12BIT & (IWDG->RLR);
    float low_speed_internal_per = 1.0f / ((float)F_LSI_HW);
    iwdt_timeout_s = low_speed_internal_per * ((float)(reload * prescaler));
    return iwdt_timeout_s;
}

bool iwdt_set_timeout(float des_timeout) {
    /*TODO: implement later*/
    return false;
}