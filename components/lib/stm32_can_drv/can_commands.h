#ifndef CAN_COMMANDS_H
#define CAN_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool can_reset_command(int32_t argc, char* argv[]);
bool can_check_id_command(int32_t argc, char* argv[]);
bool can_filter_command(int32_t argc, char* argv[]);
bool can_filter_set_command(int32_t argc, char* argv[]);
bool can_stat_command(int32_t argc, char* argv[]);
bool can_init_command(int32_t argc, char* argv[]);
bool can_diag_command(int32_t argc, char* argv[]);
bool can_errors_command(int32_t argc, char* argv[]);
bool can_send_command(int32_t argc, char* argv[]);
bool can_interrupts_command(int32_t argc, char* argv[]);

#define CAN_COMMANDS                                                              \
    SHELL_CMD("can_stat", "ct", can_stat_command, "Print CANs statistics"),       \
        SHELL_CMD("can_reset", "cr", can_reset_command, "CAN reset"),             \
        SHELL_CMD("can_id", "cid", can_check_id_command, "CAN check std id"),     \
        SHELL_CMD("can_init", "ci", can_init_command, "CAN init"),                \
        SHELL_CMD("can_int", "cin", can_interrupts_command, "CAN interrupts"),    \
        SHELL_CMD("can_errors", "ce", can_errors_command, "CAN errors"),          \
        SHELL_CMD("can_filter", "cf", can_filter_command, "CAN filter diag"),     \
        SHELL_CMD("can_filset", "cfs", can_filter_set_command, "CAN filter set"), \
        SHELL_CMD("can_diag", "cad", can_diag_command, "CAN diag"),               \
        SHELL_CMD("can_send", "cs", can_send_command, "CAN send"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_COMMANDS_H */
