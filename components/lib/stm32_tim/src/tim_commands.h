#ifndef TIM_COMMANDS_H
#define TIM_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "tim_commands.h"

bool cmd_tim_get (int32_t argc, char *argv []);
bool cmd_tim_set (int32_t argc, char *argv []);

#define TIM_COMMANDS \
    SHELL_CMD ("tim_get", "timg", cmd_tim_get, "Timer info"),\
    SHELL_CMD ("tim_set", "tims", cmd_tim_set, "Timer set"), 

#ifdef __cplusplus
}
#endif

#endif /* TIM_COMMANDS_H */
