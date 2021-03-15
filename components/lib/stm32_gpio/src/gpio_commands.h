#ifndef GPIO_COMMANDS_H
#define GPIO_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio_pwm_commands.h"

bool cmd_gpio_list (int32_t argc, char *argv []);
bool cmd_gpio_state (int32_t argc, char *argv []);
bool cmd_gpio_toggle (int32_t argc, char *argv []);
bool cmd_gpio_getp (int32_t argc, char *argv []);
bool cmd_gpio_setp (int32_t argc, char *argv []);

#define GPIO_COMMANDS \
	GPIO_PWM_COMMANDS \
    SHELL_CMD ("gpio_list", "gl", cmd_gpio_list, "GPIO list"),\
    SHELL_CMD ("gpio_state", "gs", cmd_gpio_state, "GPIO state (GPIO get or set)"), \
    SHELL_CMD ("gpio_toggle", "gt", cmd_gpio_toggle, "GPIO toggle"), \
    SHELL_CMD ("getp", "gp", cmd_gpio_getp, "Get GPIO port state"), \
    SHELL_CMD ("setp", "sp", cmd_gpio_setp, "Set GPIO port state"),


#ifdef __cplusplus
}
#endif

#endif /* GPIO_COMMANDS_H */
