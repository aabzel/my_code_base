#ifndef GPIO_PWM_COMMANDS_H
#define GPIO_PWM_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_GPIO_PWM
bool cmd_add_gpio_pwm (int32_t argc, char *argv[]);
bool cmd_gpio_pwm_diag (int32_t argc, char *argv[]);

#define GPIO_PWM_COMMANDS                                                                                              \
    SHELL_CMD ("gpio_pwm", "gpwm", cmd_add_gpio_pwm, "Set GPIO PWM"),                                                  \
        SHELL_CMD ("gpio_pwm_diag", "gpwmd", cmd_gpio_pwm_diag, "Get GPIO PWM diag"),
#endif

#endif /* GPIO_PWM_COMMANDS_H */
