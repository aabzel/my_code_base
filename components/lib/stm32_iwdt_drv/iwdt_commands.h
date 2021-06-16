#ifndef IWDT_COMMANDS_H
#define IWDT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool iwdt_diag_command(int32_t argc, char* argv[]);

#define IWDT_COMMANDS                                 \
    SHELL_CMD("iwdt_diag", "iwdt", iwdt_diag_command, \
              "Independent WatchDog timer diag"),

#ifdef __cplusplus
}
#endif

#endif /* IWDT_COMMANDS_H */
