#ifndef UTILS_SHELL_TEST_BOARDS_H
#define UTILS_SHELL_TEST_BOARDS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "device.h"
#include "ostream.h"

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_repeat (int32_t argc, char *argv[]);
bool cmd_launch_function (int32_t argc, char *argv[]);
bool cmd_try_stack (int32_t argc, char *argv[]);

#define TEST_DEFAULT_COMMANDS                                                                                          \
    SHELL_CMD ("launch_function", "lfun", cmd_launch_function, "Launch any function by address in ROM"),               \
        SHELL_CMD ("try_stack", "tstk", cmd_try_stack, "Explore stack RAM"),                                           \
        SHELL_CMD ("repeat", "rpt", cmd_repeat, "Repeat any command N time with period"),

#ifdef __cplusplus
}
#endif

#endif /* UTILS_SHELL_TEST_BOARDS_H */
