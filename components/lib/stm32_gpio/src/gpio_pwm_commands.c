#include "gpio_pwm_commands.h"

#include <inttypes.h>
#include <stdint.h>

#include "board.h"
#include "convert.h"
#include "gpio_pwm.h"
#include "gpio_utils.h"
#include "log.h"
#include "rx_uart.h"
#include "rx_uart_config.h"
#include "table_utils.h"

bool cmd_add_gpio_pwm (int32_t argc, char *argv[]) {
    bool res = false;
    if (5 == argc) {
        res = true;
        uint8_t gpio_pad = 0;
        bool state = 0;
        float_t freq = 0;
        float_t duty = 0;
        int64_t phase_us = 0;

        if (true == res) {
            res = parse_port_pin (argv[0], &gpio_pad);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse pad %s", argv[0]);
            }
        }
        if (true == res) {
            res = try_str2float (argv[1], &freq);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse freq %s", argv[1]);
            }
        }
        if (true == res) {
            res = try_str2float (argv[2], &duty);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse duty %s", argv[2]);
            }
        }
        if (true == res) {
            res = try_str2int64 (argv[3], &phase_us);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse phase  %s", argv[3]);
            }
        }
        if (true == res) {
            res = try_str2bool (argv[4], &state);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse state %s", argv[4]);
            }
        }
        if (true == res) {
            LOG_INFO (SYS, "set %s freq %f duty %f %% phase %" PRId64 " us %s", pad_name (gpio_pad), freq, duty,
                      phase_us, bool2name (state));
            res = add_gpio_pwm (gpio_pad, freq, duty, phase_us, state);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to add GPIO PWM task");
            }
        }
    } else {
        LOG_ERROR (SYS, "Usage: gpwm gpio freq duty phase_us state");
        LOG_INFO (SYS, "state [on-1 off-0 spare-2 ]");
    }
    return res;
}

bool cmd_gpio_pwm_diag (int32_t argc, char *argv[]) {
    bool res = false;
    (void)argv;
    if (0 == argc) {
        static const table_col_t cols[] = {{5, "pad"},  {7, "gpio"},  {5, "pin"},    {5, "state"},
                                           {9, "freq"}, {9, "duty%"}, {8, "phaseUs"}};
        table_header (DBG, cols, RX_ARRAY_SIZE (cols));
        for (uint16_t i = 0; i < NUM_OF_PWM_PADS; i++) {
            if (PAD_SPARE != pwmPadsTable[i].cur_satus) {
                rx_printf (TABLE_SEPARATOR " %3u ", pwmPadsTable[i].cur_pad);
                rx_printf (TABLE_SEPARATOR " %5s ", pad_name (pwmPadsTable[i].cur_pad));
                rx_printf (TABLE_SEPARATOR " %3u ", pad_to_pin_number (pwmPadsTable[i].cur_pad));
                rx_printf (TABLE_SEPARATOR " %3s ", bool2name (pwmPadsTable[i].cur_satus));
                rx_printf (TABLE_SEPARATOR " %7.2f ", pwmPadsTable[i].cur_frequency);
                rx_printf (TABLE_SEPARATOR " %7.2f ", pwmPadsTable[i].cur_duty_cycle);
                rx_printf (TABLE_SEPARATOR " %" PRId64 "", pwmPadsTable[i].cur_phase_us);

                rx_printf (CRLF);
            }
        }
        table_row_bottom (DBG, cols, RX_ARRAY_SIZE (cols));
    } else {
        LOG_ERROR (SYS, "syntax: dad");
    }
    return res;
}
