#include <inttypes.h>
#include "diag_page.h"
#include "device_flash_info.h"
#include "io_utils.h"
#include "diag_report.h"
#include "diag_page_common.h"
#include "table_utils.h"

#ifndef HAS_MCAL
#include "device_id.h"
#include "task_info.h"
#include "board_config.h"
#endif

#ifdef HAS_CAN
#include "canif.h"
#include "canif_commands.h"
#include "can_ccp_data.h"
#endif

#ifdef HAS_CAN_MESSAGE_MANAGER
#include "can_message_manager.h"
#endif

#ifdef HAS_TSENS
#include "tsens.h"
#endif

#ifdef HAS_PARAMS
#include "param_commands.h"
#endif

#ifdef SPC5
#include "stack_utils.h"
#endif

#if defined(SPC58)
#include "mem_utils_spc5.h"
#endif

#ifdef HAS_PARAMS
#include "param_storage.h"
#endif

#ifdef MODEL_STEP
#include "model_run.h"
#endif

#ifdef HAS_BOARD_TYPE_ID
#include "board_type_id.h"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

#ifndef HAS_MCAL
__attribute__((weak)) bool diag_page_version (ostream_t* stream) {
    print_version_s(stream);
#ifdef HAS_PARAMS
    oprintf (stream, "ParametersCRC:0x%08" PRIX32 CRLF, get_params_work_set_crc32());
#endif
#ifdef HAS_BL_FLASH_INFO
    oprintf (stream, "Bootloader: %s on %s Version %u.%u.%u.%u.%" PRIu32,
        (const char*)bl_flash_info.firmware_name,
#ifdef HAS_BOARD_TYPE_ID
        get_board_name (),
#else
        HARDWARE_NAME,
#endif
        bl_flash_info.version_generation, bl_flash_info.version_major, bl_flash_info.version_minor, bl_flash_info.version_fix, get_version_build((const flash_info_t*)&bl_flash_info));
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
    oprintf (stream, "Supported hardware: %s" CRLF, flash_info.supported_hardware);
    return true;
}
#endif /* HAS_MCAL */

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

bool diag_page_sysinfo (ostream_t* stream) {
    (void)stream; /* May be UNUSED */
    bool retval = true;
#ifdef SPC5
    retval = diag_page_stack(stream) && retval;
#endif
#if defined(SPC58)
    retval = diag_page_mem(stream) && retval;
#endif
#ifdef HAS_TSENS
    oprintf (stream, "MCU Temperature: %2.1f" CRLF, getTSENS_Temp());
#endif
    return retval;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


bool diag_page_common_init (void) {
    bool diag_page_base_init_res = true;

#ifndef HAS_MCAL
    static diag_page_rec_t version_rec =
        { DIAG_PAGE_VERSION, "Version", diag_page_version, NULL };
    diag_page_base_init_res = diag_page_add (&version_rec) && diag_page_base_init_res;

    static diag_page_rec_t tasks_rec =
        { DIAG_PAGE_TASKS, "Tasks Information", diag_page_tasks, NULL };
    diag_page_base_init_res = diag_page_add (&tasks_rec) && diag_page_base_init_res;

#ifdef TEST_FIRMWARE
    {
        static diag_page_rec_t uarts_rec =
            { DIAG_PAGE_UARTS, "UART's", diag_page_uarts, NULL };
        diag_page_base_init_res = diag_page_add (&uarts_rec) && diag_page_base_init_res;
    }
#endif
#endif /* HAS_MCAL */

#ifdef SPC5
    {
        static diag_page_rec_t sysinfo_rec =
            { DIAG_PAGE_SYSINFO, "Memory Information", diag_page_sysinfo, NULL };
        diag_page_base_init_res = diag_page_add (&sysinfo_rec) && diag_page_base_init_res;
    }
#endif

#ifdef MODEL_STEP
    {
        static diag_page_rec_t model_rec =
            { DIAG_PAGE_MODEL, "Model Execition Information", diag_page_model, NULL };
        diag_page_base_init_res = diag_page_add (&model_rec) && diag_page_base_init_res;
    }
#endif

    return diag_page_base_init_res;
}

bool put_val_to_row (ostream_t * const stream, float_t const value) {
    bool res = true;
    if (NULL == stream) {
        res = false;
    }
    if (true == res) {
        if (-0.5f <= ((float_t) value)) {
            oprintf (stream, " %5.2f " TABLE_SEPARATOR, ((float_t) value));
        } else {
            oprintf (stream, " ----- " TABLE_SEPARATOR);
        }
    }

    return res;
}
