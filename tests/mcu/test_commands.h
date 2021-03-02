#ifndef UNIT_TEST_COMMAND_H
#define UNIT_TEST_COMMAND_H

#include <stdbool.h>
#include <stdint.h>
 
bool cmd_test_run (int32_t argc, char *argv []);
bool cmd_test_all (int32_t argc, char *argv []);

#define UNIT_TEST_COMMANDS \
	SHELL_CMD ("run_test", "tsr", cmd_test_run, "Test run"),\
    SHELL_CMD ("print_test", "tsa", cmd_test_all, "Test list"),




#endif /* UNIT_TEST_COMMAND_H */
