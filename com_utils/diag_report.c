#include <inttypes.h>

#include "diag_report.h"
#include "convert.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "oprintf.h"
#include "device.h"
#include "uart_string_reader.h"

#include "rx_uart_config.h"
#include "rx_utils.h"
#include "log.h"
#include "device_flash_info.h"
#include "device_id.h"
#include "task_info.h"
#include "common_stream.h"

#ifdef HAS_TSENS
#include "tsens.h"
#endif

#if SPC5
#include "stack_utils.h"
#endif

#if defined(SPC58)
#include "mem_utils_spc5.h"
#endif

#ifdef MODEL_STEP
#include "model_run.h"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

__attribute__((weak)) bool diag_page_version (ostream_t* stream) {
    oprintf (stream, "%s on %s", (const char*)(flash_info.firmware_name), (const char*)(flash_info.hardware_name));
#if defined(BOOTLOADER) && defined(CUBEMX)
    oputs (stream, " BOOTLOADER");
#endif
    oprintf (stream, " Version %u.%u.%u.%u.%" PRIu32, flash_info.version_generation, flash_info.version_major, flash_info.version_minor, flash_info.version_fix, get_version_build((const flash_info_t*)&flash_info));
    oputs (stream, CRLF);
    oprintf (stream, "FlashId=0x%08" PRIX32 CRLF, get_flash_crc ((const flash_info_t *) &flash_info));
    oprintf (stream, "Serial=%" PRIX64 CRLF, get_device_serial ());
#ifdef SPC58
    oprintf (stream, "MCU=%s %s" CRLF, get_mcu_name (), get_mcu_mask_id());
#else
    oprintf (stream, "MCU=%s" CRLF, get_mcu_name ());
#endif
    oprintf (
        stream,
        "Compile time %u/%u/%u %02u:%02u:%02u" CRLF,
        flash_info.compile_day,
        flash_info.compile_month,
        flash_info.compile_year,
        flash_info.compile_hour,
        flash_info.compile_min,
        flash_info.compile_sec);
    oprintf (
        stream,
        "Flash size=%" PRIu32 " (0x%08" PRIX32 ") flash CRC32=0x%08" PRIX32 CRLF,
        flash_info.flash_size,
        flash_info.flash_size,
        flash_info.flash_crc);
#ifdef HAS_BL_FLASH_INFO
    oprintf (stream, "%s on %s version %u.%u.%u.%u.%" PRIu32, (const char*)bl_flash_info.firmware_name, (const char*)bl_flash_info.hardware_name, bl_flash_info.version_generation, bl_flash_info.version_major, bl_flash_info.version_minor, bl_flash_info.version_fix, get_version_build((const flash_info_t*)&bl_flash_info));
    oprintf (
        stream,
        " %u/%u/%u %02u:%02u:%02u",
        bl_flash_info.compile_day,
        bl_flash_info.compile_month,
        bl_flash_info.compile_year,
        bl_flash_info.compile_hour,
        bl_flash_info.compile_min,
        bl_flash_info.compile_sec);
    oprintf (stream, " 0x%08" PRIX32 CRLF, bl_flash_info.flash_crc);
#endif
    return true;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

__attribute__((weak)) bool diag_page_sysinfo (ostream_t* stream) {
    (void)stream; /* May be unused depending on configuration */
#ifdef SPC5
    if (!diag_page_stack(stream)) {
        return false;
    }
#endif
#if defined(SPC58)
    if (!diag_page_mem(stream)) {
        return false;
    }
#endif
#ifdef HAS_TSENS
    oprintf (stream, "MCU Temperature: %1.2f" CRLF, getTSENS_Temp());
#endif
    return true;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

bool diag_page_base (uint8_t page, ostream_t* stream) {
    bool res;
    switch (page) {
        case DIAG_PAGE_INDEX:
            oprintf (stream, "%u Version" CRLF, DIAG_PAGE_VERSION);
#ifdef HAS_CAN
            oprintf (stream, "%u CAN" CRLF, DIAG_PAGE_CAN);
#endif /* HAS_CAN */
#ifdef TEST_FIRMWARE
            oprintf (stream, "%u UARTS" CRLF, DIAG_PAGE_UARTS);
#endif
#ifdef MODEL_STEP
            oprintf (stream, "%u Model" CRLF, DIAG_PAGE_MODEL);
#endif
            oprintf (stream, "%u SysInfo" CRLF, DIAG_PAGE_SYSINFO);
#ifdef TASKS
            oprintf (stream, "%u Tasks" CRLF, DIAG_PAGE_TASKS);
#endif
#ifdef HAS_PARAMS
            oprintf (stream, "%u Parameters" CRLF, DIAG_PAGE_PARAMS);
#endif
            res = diag_page_index (stream);
            break;
        case DIAG_PAGE_VERSION:
            res = diag_page_version (stream);
            break;
#ifdef HAS_CAN
            case DIAG_PAGE_CAN:
            res = diag_page_can (stream);
            break;
#endif /* HAS_CAN */
#ifdef TEST_FIRMWARE
        case DIAG_PAGE_UARTS:
            res = diag_page_uarts (stream);
            break;
#endif
#ifdef MODEL_STEP
        case DIAG_PAGE_MODEL:
            res = diag_page_model (stream);
            break;
#endif
#ifdef SPC5
        case DIAG_PAGE_SYSINFO:
            res = diag_page_sysinfo (stream);
            break;
#endif
#ifdef TASKS
        case DIAG_PAGE_TASKS:
            res = diag_page_tasks(stream);
            break;
#endif
        default:
            res = diag_report (page, stream);
            break;
    }
    return res;
}

bool show_diag_report (uint8_t page_number) {
    bool result = true;
    int64_t char_at_start;
    flush_printf ();
    char_at_start = dbg_o.total_char_count;
    if (!diag_page_base (page_number, DBG)) {
        result = false;
    }
    flush_printf ();
    LOG_DEBUG (SYS, "%lld chars in report", dbg_o.total_char_count - char_at_start);
    return result;
}

bool dump_diag_report (uint8_t page_number) {
    bool result = true;
    ostream_t* s = ccp_stream_init ();
    if (!diag_page_base (page_number, s)) {
        result = false;
    }
    ccp_stream_dump ("!D");
    return result;
}

bool cmd_diag_report (int32_t argc, char *argv []) {
    uint8_t page_number = DIAG_PAGE_INDEX;
    if (argc != 0 && argc != 1) {
        LOG_ERROR (SYS, "Usage: diag_report [page_number]");
        return dump_cmd_result (false);
    }
    if (argc >= 1) {
        if (!try_str2uint8 (argv [0], &page_number)) {
            LOG_ERROR (SYS, "Invalid page number [%s]", argv [0]);
            return dump_cmd_result (false);
        }
    }
    return dump_cmd_result (show_diag_report (page_number));
}
