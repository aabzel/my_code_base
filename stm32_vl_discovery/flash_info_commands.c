/*****************************************************************************
 * @file    flash_info_commands.c
 * 
 * @attention  Violates #2101-D: MISRA 2012 Rule 1.2: language extensions are
 * not allowed
 *****************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "diag_page.h"

#ifdef HAS_MCAL
#include "shell.h"

static bool flash_info_version_cmd (int32_t argc, char *argv []);

static bool flash_info_version_cmd (int32_t argc, char *argv []) {
    (void) argc;
    (void) argv;

    bool res = show_diag_page (DIAG_PAGE_VERSION);
    return shell_dump_cmd_result (res);
}

/*****************************************************************************
 * @brief   Adds shell commands.
 *****************************************************************************/
#pragma ghs nowarning 2101
SHELL_CMD_REGISTER ("flash_info", "version", "vi", flash_info_version_cmd, "prints firmware version information")
#pragma ghs endnowarning 2101
#endif
