#include "log.h"

#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#ifdef __GCC__
#include <strings.h>
#endif

#include "convert.h"
#include "device.h"
#include "rx_io.h"
#include "terminal_codes.h"

static char log_level_name (log_level_t level);
static void set_log_level_all (log_level_t level);
static INLINE bool is_log_enabled (log_level_t level, log_facility_t facility);

#ifdef HAS_IPP_RTC
#include "rtc_time.h"
#endif

log_level_t log_levels[ALL_FACILITY];

/* XCP Measurement
   !!VARIABLE log_flush
   !!GROUP General\Log
   !!TYPE bool
   !!DESCRIPTION Wait for log flush after every LOG_* function call
   !!END
 */
bool log_flush = false;
/* XCP Measurement
   !!VARIABLE log_colored
   !!GROUP General\Log
   !!TYPE bool
   !!DESCRIPTION Use ANSII ESC codes for colred log
   !!END
 */
bool log_colored = true;
/* XCP Measurement
   !!VARIABLE log_facility_name
   !!GROUP General\Log
   !!TYPE bool
   !!DESCRIPTION Display log facility in log output
   !!END
 */
bool log_facility_name = true;
#ifdef EMBEDDED_TEST
bool log_zero_time = false;
#endif

static char log_level_name (log_level_t level) {
    char result = 'U';
    switch (level) {
    case LOG_LEVEL_UNKNOWN:
        result = 'U';
        break;
    case LOG_LEVEL_PARANOID:
        result = 'P';
        break;
    case LOG_LEVEL_DEBUG:
        result = 'D';
        break;
    case LOG_LEVEL_NOTICE:
        result = 'N';
        break;
    case LOG_LEVEL_INFO:
        result = 'I';
        break;
    case LOG_LEVEL_WARNING:
        result = 'W';
        break;
    case LOG_LEVEL_ERROR:
        result = 'E';
        break;
    case LOG_LEVEL_CRITICAL:
        result = 'C';
        break;

    default:
        result = '?';
        break;
    }
    return result;
}

const char *log_level_color (log_level_t level) {
    const char *result = VT_SETCOLOR_NORMAL;
    switch (level) {
    case LOG_LEVEL_UNKNOWN:
        result = VT_SETCOLOR_NORMAL;
        break;
    case LOG_LEVEL_PARANOID:
        result = VT_SETCOLOR_PARANOID;
        break;
    case LOG_LEVEL_DEBUG:
        result = VT_SETCOLOR_BLUE;
        break;
    case LOG_LEVEL_NOTICE:
        result = VT_SETCOLOR_NOTICE;
        break;
    case LOG_LEVEL_INFO:
        result = VT_SETCOLOR_GREEN;
        break;
    case LOG_LEVEL_WARNING:
        result = VT_SETCOLOR_YELLOW;
        break;
    case LOG_LEVEL_ERROR:
        result = VT_SETCOLOR_RED;
        break;
    case LOG_LEVEL_CRITICAL:
        result = VT_SETCOLOR_RED;
        break;

    default:
        result = "?";
        break;
    }
    return result;
}

static void set_log_level_all (log_level_t level) {
    uint32_t f;
    for (f = 0; f < sizeof (log_levels) / sizeof (log_levels[0]); f++) {
        log_levels[f] = level;
    }
}

void set_log_level (log_facility_t facility, log_level_t level) {
    if (facility == ALL_FACILITY) {
        set_log_level_all (level);
    }
    if (UNKNOWN_FACILITY < facility && facility < ALL_FACILITY) {
        log_levels[facility] = level;
    }
}

log_level_t get_log_level (log_facility_t facility) {
    log_level_t level = LOG_LEVEL_UNKNOWN;
    if (UNKNOWN_FACILITY < facility && facility < ALL_FACILITY) {
        level = log_levels[facility];
    }
    return level;
}

static INLINE bool is_log_enabled (log_level_t level, log_facility_t facility) {
    if (level < get_log_level (facility)) {
        return false;
    }
    return true;
}

const char *facility2str (log_facility_t facility) {
    const char *facility_str = "?";
    switch (facility) {
    case UNKNOWN_FACILITY:
        facility_str = "?";
        break;
    case SYS:
        facility_str = "SYS";
        break;
    case USER1:
        facility_str = "USER1";
        break;
    case USER2:
        facility_str = "USER2";
        break;
    case USER5:
        facility_str = "USER5";
        break;

    case UART:
        facility_str = "UART";
        break;

    case SPI:
        facility_str = "SPI";
        break;

    case DIAG:
        facility_str = "DIAG";
        break;
    case ALL_FACILITY:
        facility_str = "*";
        break;
    default:
        facility_str = "?";
        break;
    }
    return facility_str;
}

bool log_write_begin (log_level_t level, log_facility_t facility) {
    bool res = false;

    if (is_log_enabled (level, facility)) {
#ifdef ENABLE_MULTICORE
        ic_mutex_lock (IC_MUTEX_LOG);
#endif
        uint64_t now = get_time_ms64 ();
#ifdef EMBEDDED_TEST
        if (log_zero_time) {
            now = 0;
        }
#endif
        if (log_colored) {
            rx_putstr (log_level_color (level));
        }
        rx_printf ("%" PRIu32 ".%03" PRIu32, (uint32_t) (now / 1000), (uint32_t) (now % 1000));
        rx_printf (":%c ", log_level_name (level));
        if (log_facility_name) {
            rx_printf ("[%s] ", facility2str (facility));
        }
        res = true;
    }
    return res;
}

void log_write_end (void) {
    if (log_colored) {
        rx_putstr (VT_SETCOLOR_NORMAL);
    }
    rx_putstr (CRLF);
#ifndef NO_EMBEDED
    if (log_flush) {
        flush_printf ();
    }
#endif
}

void log_write_ (log_level_t level, log_facility_t facility, const char *format, ...) {
    if (log_write_begin (level, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_PARN (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_PARANOID, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_DEBUG (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_DEBUG, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_NOTICE (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_NOTICE, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_INFO (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_INFO, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_WARNING (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_WARNING, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_ERROR (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_ERROR, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}

void LOG_CRITICAL (log_facility_t facility, const char *format, ...) {
    if (log_write_begin (LOG_LEVEL_CRITICAL, facility)) {
        va_list va;
        va_start (va, format);
        rx_vprintf (format, va);
        va_end (va);
        log_write_end ();
    }
}
