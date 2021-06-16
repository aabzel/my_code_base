#ifndef CLOCK_COMMANDS_H
#define CLOCK_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool clock_diag_command(int32_t argc, char* argv[]);

#define CLOCK_COMMANDS \
    SHELL_CMD("clock_diag", "cd", clock_diag_command, "Show clock diag"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_COMMANDS_H */
