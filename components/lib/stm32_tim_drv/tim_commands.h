#ifndef TIM_COMMANDS_H
#define TIM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool tim_diag_command(int32_t argc, char* argv[]);
bool time_diag_command(int32_t argc, char* argv[]);
bool tim_init_command(int32_t argc, char* argv[]);
bool tim_set_command(int32_t argc, char* argv[]);
bool tim_set_prescaler_command(int32_t argc, char* argv[]);

#define TIM_COMMANDS                                                    \
    SHELL_CMD("tim_init", "ti", tim_init_command, "tim init"),          \
        SHELL_CMD("tim_set", "ts", tim_set_command, "tim set"),         \
        SHELL_CMD("tim_set_psc", "tsp", tim_set_prescaler_command,      \
                  "tim set prescaler"),                                 \
        SHELL_CMD("tim_diag", "td", tim_diag_command, "Show tim diag"), \
        SHELL_CMD("time_diag", "tid", time_diag_command, "Show time diag"),

#ifdef __cplusplus
}
#endif

#endif /* TIM_COMMANDS_H */
