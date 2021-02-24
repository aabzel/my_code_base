#ifndef DIAG__REPORT_H_
#define DIAG__REPORT_H_

#ifdef HAS_DIAG_PAGE
#include "diag_page_commands.h"

#else /* HAS_DIAG_PAGE */
#include "ostream.h"
#include <stdbool.h>

#define DIAG_PAGE_INDEX (0u)
#define DIAG_PAGE_VERSION (1u)
#define DIAG_PAGE_CAN (2u)
#define DIAG_PAGE_MODEL (4u)
#define DIAG_PAGE_SYSINFO (5u)
#define DIAG_PAGE_TASKS (6u)
#define DIAG_PAGE_UARTS (7u)
#define DIAG_PAGE_PARAMS (8u)
#define DIAG_PAGE_ADC (9u)
#define DIAG_PAGE_TEMP_SENSOR (11u)
#define DIAG_PAGE_BRIDGE (13u)

bool diag_report (uint8_t page, ostream_t *stream);
bool diag_page_base (uint8_t page, ostream_t *stream);
bool diag_page_version (ostream_t *stream);
bool diag_page_sysinfo (ostream_t *stream);
bool diag_page_index (ostream_t *stream);

bool show_diag_report (uint8_t page_number);
bool dump_diag_report (uint8_t page_number);
bool cmd_diag_report (int32_t argc, char *argv[]);

#define DIAG_COMMANDS SHELL_CMD ("diag_report", "dr", cmd_diag_report, "Diagnostics report"),

#endif /* HAS_DIAG_PAGE */

#endif /* DIAG__REPORT_H_ */
