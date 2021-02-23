/*****************************************************************************
 * @file    log_commands.c
 *
 * @attention Violates #2086-D: MISRA 2012 Rule 10.5: invalid cast from
 * number to enum: essential types do not match.
 * 
 * @attention Violates #2069-D: MISRA 2012 Rule 4.1: all octal or hex escape 
 * sequences may only be followed by an escape sequence
 * 
 * @attention Violates #2101-D: MISRA 2012 Rule 1.2: language extensions 
 * are not allowed.
 *****************************************************************************/

#include <string.h>
#include <strings.h> /* 'strcasecmp()' for ARM GCC builds */
#include "log_commands.h"
#include "io_utils.h"
#include "terminal_codes.h"
#include "convert.h"
#include "log.h"

#ifdef HAS_MCAL
#include "shell.h"
#endif

#ifdef __ghs__
#pragma ghs nowarning 2086
#pragma ghs nowarning 2069
#endif

static const char* log_level_name_long (log_level_t level);
static log_facility_t str2facility (const char* str);
static log_level_t str2level (const char* str);
static void report_log_leveles (void);

static const char* log_level_name_long (log_level_t level) {
    const char* result;
    switch (level) {
        case LOG_LEVEL_UNKNOWN:
            result = "?????";
            break;
        case LOG_LEVEL_PARANOID:
            result = "PARANOID";
            break;
        case LOG_LEVEL_DEBUG:
            result = "DEBUG";
            break;
        case LOG_LEVEL_NOTICE:
            result = "NOTICE";
            break;
        case LOG_LEVEL_INFO:
            result = "INFO";
            break;
        case LOG_LEVEL_WARNING:
            result = "WARNING";
            break;
        case LOG_LEVEL_ERROR:
            result = "ERROR";
            break;
        case LOG_LEVEL_CRITICAL:
            result = "CRITICAL";
            break;
        default:
            result = "?";
            break;
    }
    return result;
}

static log_facility_t str2facility (const char *str) {
    log_facility_t l;
    log_facility_t result = UNKNOWN_FACILITY;
    for (l = UNKNOWN_FACILITY; l <= ALL_FACILITY; l++) {
        if (0 == strcasecmp (facility2str(l), str)) {
            result = l;
            break;
        }
    }
    return result;
}

static log_level_t str2level (const char* str) {
    if (0 == strcasecmp (str, "P") || 0 == strcasecmp (str, "PARN") || 0 == strcasecmp (str, "PARANOID")) {
        return LOG_LEVEL_PARANOID;
    }
    if (0 == strcasecmp (str, "D") || 0 == strcasecmp (str, "DBG") || 0 == strcasecmp (str, "DEBUG")) {
        return LOG_LEVEL_DEBUG;
    }
    if (0 == strcasecmp (str, "n") || 0 == strcasecmp (str, "NOTI") || 0 == strcasecmp (str, "NOTICE")) {
        return LOG_LEVEL_NOTICE;
    }
    if (0 == strcasecmp (str, "I") || 0 == strcasecmp (str, "INF") || 0 == strcasecmp (str, "INFO")) {
        return LOG_LEVEL_INFO;
    }
    if (0 == strcasecmp (str, "W") || 0 == strcasecmp (str, "WARN") || 0 == strcasecmp (str, "WARNING")) {
        return LOG_LEVEL_WARNING;
    }
    if (0 == strcasecmp (str, "E") || 0 == strcasecmp (str, "ERR") || 0 == strcasecmp (str, "ERROR")) {
        return LOG_LEVEL_ERROR;
    }
    if (0 == strcasecmp (str, "C") || 0 == strcasecmp (str, "CRIT") || 0 == strcasecmp (str, "CRITICAL")) {
        return LOG_LEVEL_CRITICAL;
    }
    return LOG_LEVEL_UNKNOWN;
}

static void report_log_leveles (void) {
    log_facility_t f = UNKNOWN_FACILITY;
    f++;
    rx_printf ("|facility|  level |" CRLF);
    for (; f < ALL_FACILITY; f++) {
        rx_printf (
            "|%8s|%s%8s%s|" CRLF,
            facility2str(f),
            log_level_color (log_levels [f]),
            log_level_name_long (log_levels [f]),
            VT_SETCOLOR_NORMAL);
    }
}

bool cmd_log_level (int32_t argc, char *argv []) {
    log_facility_t facility;
    log_level_t level;
    if (argc > 2) {
        LOG_ERROR (SYS, "Usage log_level [facility|*|ALL [log_level]]");
        return false;
    }
    if (argc == 0) {
        report_log_leveles ();
        return false;
    }
    facility = str2facility (argv [0]);
    if (facility == UNKNOWN_FACILITY) {
        LOG_ERROR (SYS, "Unknown facility name %s", argv [0]);
        return false;
    }
    if (argc == 1) {
        if (facility == ALL_FACILITY) {
            report_log_leveles ();
        } else {
            rx_printf ("%s %s" CRLF, facility2str(facility), log_level_name_long (get_log_level (facility)));
        }
        return false;
    }
    level = str2level (argv [1]);
    if (level == LOG_LEVEL_UNKNOWN) {
        LOG_ERROR (SYS, "Unknown log level name %s", argv [1]);
        return false;
    }
    set_log_level (facility, level);
    return true;
}

#ifdef TEST_FIRMWARE
bool cmd_log_color (int32_t argc, char *argv []) {
    bool colored = false;
    if (argc != 1) {
        LOG_ERROR (SYS, "Usage log_color on|off");
        return false;
    }
    if (!try_str2bool (argv [0], &colored)) {
        LOG_ERROR (SYS, "Invalid flag value %s", argv [0]);
        return false;
    }
    log_colored = colored;
    return true;
}

bool cmd_log_flush (int32_t argc, char *argv []) {
    bool flag = false;
    if (argc != 1) {
        LOG_ERROR (SYS, "Usage log_flush on|off");
        return false;
    }
    if (!try_str2bool (argv [0], &flag)) {
        LOG_ERROR (SYS, "Invalid flag value %s", argv [0]);
        return false;
    }
    log_flush = flag;
    return true;
}
#endif /* TEST_FIRMWARE */

#ifdef __ghs__
#pragma ghs endnowarning 2069
#pragma ghs endnowarning 2086
#endif

#ifdef HAS_MCAL
/*****************************************************************************
 * @brief   Adds shell commands.
 *****************************************************************************/
#pragma ghs nowarning 2101
SHELL_CMD_REGISTER ("log", "log_level", "ll", cmd_log_level, "sets or prints log levels")
SHELL_DEBUG_CMD_REGISTER ("log", "log_flush", "lf", cmd_log_flush, "enables/disables wait for UART queue flush after every log line")
SHELL_DEBUG_CMD_REGISTER ("log", "log_color", "lc", cmd_log_color, "enables/disables colored log")
#pragma ghs endnowarning 2101
#endif
