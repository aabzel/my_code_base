#ifndef GPIO_PWM_H
#define GPIO_PWM_H

#ifdef HAS_GPIO_PWM

#include <stdbool.h>
#include <stdint.h>

#include "float_utils.h"
#include "pal_utils.h"

#define NUM_OF_PWM_PADS (10U)

typedef enum { PAD_SPARE = 2U, PAD_ON = true, PAD_OFF = false } pwmPadStates_t;

typedef struct xPWMpad_t {
    pad_t cur_pad;
    float_t cur_duty_cycle;
    float_t cur_frequency;
    int64_t cur_phase_us;
    uint8_t cur_satus; /*on off spare*/
} pwmPad_t;

extern pwmPad_t pwmPadsTable[NUM_OF_PWM_PADS];

bool init_gpio_pwm (void);
bool add_gpio_pwm (pad_t in_pad, float_t in_freq, float_t duty, int64_t phase_us, uint8_t in_state);
bool process_gpio_pwm (void);
bool cmd_gpio_pwm_diag (int32_t argc, char *argv[]);

#endif /*HAS_GPIO_PWM*/

#endif /* GPIO_PWM_H */
