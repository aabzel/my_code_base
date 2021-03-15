/*Software PWM for bring up and debug*/

#include "gpio_pwm.h"

#include <stdint.h>
#include <math.h>

#include "float_utils.h"
#include "pal_utils.h"
#include "table_utils.h"
#include "timer_utils.h"

pwmPad_t pwmPadsTable[NUM_OF_PWM_PADS];
static bool init_done;

static uint8_t calc_gpio_pwm_sample (uint64_t cur_time_us, float_t in_frequency, uint64_t in_phase_us,
                                     float_t in_duty_cycle) {
    float_t line_val = 0.0f;
    float_t saw_val = 0.0f;

    if (100.0f < in_duty_cycle) {
        in_duty_cycle = 100.0f;
    }
    if (in_duty_cycle < 0.0f) {
        in_duty_cycle = 0.0f;
    }
    float_t current_time_ms = ((float_t)cur_time_us) / 1000.0f;
    float_t current_phase_ms = ((float_t)in_phase_us) / 1000.0f;
    line_val = ((current_time_ms + current_phase_ms) / 1000.0f) * in_frequency; /*tune frequency*/
    saw_val = fmodf (line_val, 1.0f);                                           /*tune DutyCycle*/

    uint8_t logic_level = 0U;
    float_t val = (((1.0f - ((100.0f - in_duty_cycle)) / 100.0f)) - saw_val); /*tune DutyCycle*/
    if (0.0f < val) {
        logic_level = 1U;
    }

    return logic_level;
}

static void proc_gpio_pwm (pad_t pad, float_t des_duty_cycle, float_t des_frequency, int64_t des_phase) {
    uint64_t cur_time_us = get_time_us ();
    uint8_t amplitude = calc_gpio_pwm_sample (cur_time_us, des_frequency, des_phase, des_duty_cycle);
    pal_writepad_ex (pad, amplitude);
}

bool add_gpio_pwm (pad_t in_pad, float_t in_freq, float_t in_duty, int64_t phase_us, uint8_t in_state) {
    bool res = false;
    for (uint16_t i = 0U; i < NUM_OF_PWM_PADS; i++) {
        if (pwmPadsTable[i].cur_pad == in_pad) {
            pwmPadsTable[i].cur_duty_cycle = in_duty;
            pwmPadsTable[i].cur_frequency = in_freq;
            pwmPadsTable[i].cur_phase_us = phase_us;
            pwmPadsTable[i].cur_satus = in_state;
            res = true;
        }
    }
    if (false == res) {
        for (uint16_t i = 0; i < NUM_OF_PWM_PADS; i++) {
            if (PAD_SPARE == pwmPadsTable[i].cur_satus) {
                pwmPadsTable[i].cur_pad = in_pad;
                pwmPadsTable[i].cur_duty_cycle = in_duty;
                pwmPadsTable[i].cur_frequency = in_freq;
                pwmPadsTable[i].cur_phase_us = phase_us;
                pwmPadsTable[i].cur_satus = in_state;
                i = NUM_OF_PWM_PADS;
                res = true;
            }
        }
    }
    return res;
}

bool init_gpio_pwm (void) {
    bool res = false;
    for (uint16_t i = 0; i < NUM_OF_PWM_PADS; i++) {
        pwmPadsTable[i].cur_duty_cycle = -10.0;
        pwmPadsTable[i].cur_frequency = -10.0;
        pwmPadsTable[i].cur_phase_us = 0;
        pwmPadsTable[i].cur_satus = PAD_SPARE;
        res = true;
    }
    init_done = true;
    return res;
}

bool process_gpio_pwm (void) {
    bool res = false;
    if (true == init_done) {
        for (uint16_t i = 0U; i < NUM_OF_PWM_PADS; i++) {
            if (PAD_ON == pwmPadsTable[i].cur_satus) {
                proc_gpio_pwm (pwmPadsTable[i].cur_pad, pwmPadsTable[i].cur_duty_cycle, pwmPadsTable[i].cur_frequency,
                               pwmPadsTable[i].cur_phase_us);
                res = true;
            }
            if (PAD_OFF == pwmPadsTable[i].cur_satus) {
                pal_writepad_ex (pwmPadsTable[i].cur_pad, 0);
            }
        }
    }
    return res;
}
