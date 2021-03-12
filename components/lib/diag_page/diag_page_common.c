#include "diag_page_common.h"

#include <inttypes.h>

#include "board_config.h"
#include "device_flash_info.h"
#include "device_id.h"
#include "diag_page.h"
#include "diag_page_nums.h"
#include "diag_report.h"
#include "io_utils.h"
#include "rx_uart.h"
#include "shell.h"
#include "table_utils.h"
#include "task_info.h"

#ifdef HAS_PARAMS
#include "param_commands.h"
#include "param_storage.h"
#endif

#ifdef HAS_BOARD_TYPE_ID
#include "board_type_id.h"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

#ifndef HAS_MCAL
__attribute__ ((weak)) bool diag_page_version (ostream_t *stream) {
    print_version_s (stream);
#ifdef HAS_PARAMS
    oprintf (stream, "ParametersCRC:0x%08" PRIX32 CRLF, get_params_work_set_crc32 ());
#endif

#ifdef HAS_BL_FLASH_INFO
    oprintf (stream, "Bootloader: %s on %s Version %u.%u.%u.%u.%" PRIu32, (const char *)bl_flash_info.firmware_name,

#ifdef HAS_BOARD_TYPE_ID
             get_board_name (),
#else
             HARDWARE_NAME,
#endif

             bl_flash_info.version_generation, bl_flash_info.version_major, bl_flash_info.version_minor,
             bl_flash_info.version_fix, get_version_build ((const flash_info_t *)&bl_flash_info));
    oprintf (stream, " %u/%u/%u %02u:%02u:%02u", bl_flash_info.compile_day, bl_flash_info.compile_month,
             bl_flash_info.compile_year, bl_flash_info.compile_hour, bl_flash_info.compile_min,
             bl_flash_info.compile_sec);
    oprintf (stream, " 0x%08" PRIX32 CRLF, bl_flash_info.flash_crc);
#endif
    oprintf (stream, "Supported hardware: %s" CRLF, flash_info.supported_hardware);
    return true;
}
#endif /* HAS_MCAL */

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

bool diag_page_sysinfo (ostream_t *stream) {
    (void)stream;
    bool retval = true;
    return retval;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

bool diag_page_common_init (void) {
    bool diag_page_base_init_res = true;

    static diag_page_rec_t version_rec = {DIAG_PAGE_VERSION, "Version", diag_page_version, NULL};
    diag_page_base_init_res = diag_page_add (&version_rec) && diag_page_base_init_res;

    static diag_page_rec_t tasks_rec = {DIAG_PAGE_TASKS, "Tasks Information", diag_page_tasks, NULL};
    diag_page_base_init_res = diag_page_add (&tasks_rec) && diag_page_base_init_res;

    static diag_page_rec_t uarts_rec = {DIAG_PAGE_UARTS, "UART", diag_page_uarts, NULL};
    diag_page_base_init_res = diag_page_add (&uarts_rec) && diag_page_base_init_res;

    return diag_page_base_init_res;
}

bool put_val_to_row (ostream_t *const stream, float_t const value) {
    bool res = true;
    if (NULL == stream) {
        res = false;
    }
    if (true == res) {
        if (-0.5f <= ((float_t)value)) {
            oprintf (stream, " %5.2f " TABLE_SEPARATOR, ((float_t)value));
        } else {
            oprintf (stream, " ----- " TABLE_SEPARATOR);
        }
    }

    return res;
}
