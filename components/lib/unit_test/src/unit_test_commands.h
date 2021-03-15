#ifndef UNIT_TEST_COMMANDS_H_
#define UNIT_TEST_COMMANDS_H_

#include <stdint.h>
#include <stdbool.h>

#define UNIT_TEST_COMMANDS \
    SHELL_CMD ("test_all", "tsa", cmd_unit_test_list, "Print all unit tests"), \
    SHELL_CMD ("test_run", "tsr", cmd_unit_test_run, "Run test"), \
    SHELL_CMD("echo","e",cmd_echo, "Toggle echo"),

bool cmd_unit_test_list (int32_t argc, char *argv []);
bool cmd_unit_test_run (int32_t argc, char *argv []);
/*****************************************************************************
 * @brief   Enables/disables echo.
 * @param   argc args count.
 * @param   argv args container pointer.
 * @return  true if command executed successfully, false otherwise.
 *****************************************************************************/
bool cmd_echo (int32_t argc, char *argv []);

#endif /* UNIT_TEST_COMMANDS_H_ */
