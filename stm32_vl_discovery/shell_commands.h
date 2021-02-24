#include <stdio.h>

#include "common_commands.h"
#include "log.h"
#include "shell.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHELL_COMMANDS \
	COMMON_COMMANDS\
    LOG_COMMANDS

#ifdef __cplusplus
} /* extern "C" */
#endif
