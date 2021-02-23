#ifndef DIAG__PAGE_COMMANDS_H_
#define DIAG__PAGE_COMMANDS_H_

#include "diag_page.h"
#include "shell.h"

#ifdef __cplusplus
extern "C" {
#endif

bool diag_page_list_cmd (int32_t argc, char *argv []);

#ifndef HAS_MCAL

#define cmd_diag_report diag_page_list_cmd

#define DIAG_COMMANDS \
    SHELL_CMD("diag_page", "dr", diag_page_list_cmd, "lists all diagnostic pages"), \

#endif

#ifdef __cplusplus
}
#endif

#endif /* DIAG__PAGE_COMMANDS_H_ */
