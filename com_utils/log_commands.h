#ifndef LOG_COMMANDS_H_
#define LOG_COMMANDS_H_

#include <stdint.h>
#include <stdbool.h>

bool cmd_log_level(int32_t argc, char *argv[]);

#ifdef TEST_FIRMWARE
bool cmd_log_color(int32_t argc, char *argv[]);
bool cmd_log_flush(int32_t argc, char *argv[]);
#define LOG_COMMANDS_TEST \
    SHELL_CMD("log_flush","lf",cmd_log_flush,"Enable/Disable wait for UART queue flush after every log line"), \
    SHELL_CMD("log_color","lc",cmd_log_color,"Enable/Disable colored log"),
#else
#define LOG_COMMANDS_TEST
#endif

#define LOG_COMMANDS \
    SHELL_CMD("log_level","ll",cmd_log_level,"Set or print log levels"), \
    LOG_COMMANDS_TEST


#endif
