/*****************************************************************************
 * @file    device_flash_info.c
 *
 * @attention Violates #2106-D: MISRA 2012 Rule 13.2: expression has
 * too many volatile reads.
 *
 * @attention Violates #2101-D: MISRA 2012 Rule 1.2: language extensions
 * are not allowed.
 *
 * @attention Violates #1836-D: MISRA 2012 Rule 11.8: cast drops "volatile".
 *
 * @attention Violates #2107-D: MISRA 2012 Rule 13.2: expression has too many
 * volatile writes.
 *
 * @attention Violates #1868-D: MISRA 2012 Rule 10.3: implicit conversion of
 * non-constant function argument not allowed.
 *
 * @attention Violates #2100-D: MISRA 2012 Rule 10.4: Usual arithmetic
 * conversions performed on operands with different essential type categories.
 *****************************************************************************/

#include "device_flash_info.h"
#include "flash_info_diag_page.h"
#include "pointer_utils.h"
#include "board_config.h"
#include "version.h"
#include "oprintf.h"
#if defined(SPC58) && defined(HAS_SPC58_RESET_INFO)
#    include "reboot_info.h"
#endif

#ifdef HAS_BOARD_TYPE_ID
#    include "board_type_id.h"
#endif

#include <inttypes.h>
#include <string.h>

_Static_assert (sizeof(HARDWARE_NAME) <= 9U,           "HARDWARE_NAME length must be <= 8");
_Static_assert (sizeof(VERSION_FIRMWARE_NAME) <= 17U,  "VERSION_FIRMWARE_NAME length must be <= 16");
#ifdef OVERRIDE_FIRMWARE_NAME
_Static_assert (sizeof(OVERRIDE_FIRMWARE_NAME) <= 17U, "OVERRIDE_FIRMWARE_NAME length must be <= 16");
#endif
_Static_assert (sizeof(flash_info_t) == 256U,          "Invalid flash_info_t structure size");

#ifndef VERSION_GENERATION
#    define VERSION_GENERATION  0U
#endif

#ifndef VERSION_FIX
#    define VERSION_FIX         0U
#endif

#ifndef VERSION_FIRMWARE_NAME
#    error Please define VERSION_FIRMWARE_NAME
#endif

#ifndef HARDWARE_NAME
#    error HARDWARE_NAME must be defined in board_config.h file
#endif

#ifndef SUPPORTED_HARDWARE
#    define SUPPORTED_HARDWARE "|" HARDWARE_NAME "|"
#endif

#ifdef SPC5
#    if !defined(__DEBUG) && !defined(RELEASE)
#        error __DEBUG or RELEASE must be defined
#    endif
#endif

#ifdef __ghs__
#    pragma ghs nowarning 2101
#    pragma ghs nowarning 1836
#    pragma ghs nowarning 2106
#    pragma ghs nowarning 2107
#    pragma ghs nowarning 1868
#    pragma ghs nowarning 2100
#endif

#ifdef HAS_BL_FLASH_INFO
const volatile flash_info_t bl_flash_info __attribute__((section(".BL_FLASH_INFO")));
#endif

/* @formatter:off */
const volatile flash_info_t flash_info __attribute__((section(".FLASH_INFO"))) =
{
    /* .signature           = */ FLASH_INFO_SIGNATURE,
    /* .info_version        = */ FLASH_INFO_VERSION,
    /* .compile_year        = */ 0,
    /* .compile_month       = */ 0,
    /* .compile_day         = */ 0,
    /* .compile_hour        = */ 0,
    /* .compile_min         = */ 0,
    /* .compile_sec         = */ 0,
    /* .flash_crc           = */ 0,
    /* .version_build16     = */ ((uint16_t)VERSION_BUILD),
    /* .version_build32     = */ VERSION_BUILD,
    /* .reserved1           = */ "",
    /* .flash_size          = */ 0,
    /* .reserved2           = */ "",
#ifdef OVERRIDE_FIRMWARE_NAME
    /* .firmware_name       = */ OVERRIDE_FIRMWARE_NAME,
#else
    /* .firmware_name       = */ VERSION_FIRMWARE_NAME,
#endif
    /* .hardware_name       = */ HARDWARE_NAME,
    /* .supported_hardware  = */ SUPPORTED_HARDWARE,
    /* .version_generation  = */ VERSION_GENERATION,
    /* .version_major       = */ VERSION_MAJOR,
    /* .version_minor       = */ VERSION_MINOR,
    /* reserved3            = */ "",
    /* .version_fix         = */ VERSION_FIX,
#ifdef __DEBUG
#    ifdef CHECK_ALL
            /* .target      = */ TARGET_DEBUG_CHECK,
#    else
            /* .target      = */ TARGET_DEBUG,
#    endif
#else
#    ifdef RELEASE
#        ifdef CHECK_ALL
            /* .target      = */ TARGET_RELEASE_CHECK,
#        else
            /* .target      = */ TARGET_RELEASE,
#        endif
#    else
        /* .target          = */ TARGET_NA,
#    endif
#endif
    /* reserved4            = */ ""
};
/* @formatter:on */

bool flash_info_init (void) {
    return flash_info_diag_page_init ();
}

void flash_info_print (ostream_t *stream, const volatile flash_info_t *fi) {
    const char* board;

#ifdef HAS_BOARD_TYPE_ID
    board = get_board_name ();
#else
    board = HARDWARE_NAME;
#endif

    oprintf (stream,
        "%s on %s Version %u.%u.%u.%u.%" PRIu32,
        fi->firmware_name,
        board,
        fi->version_generation,
        fi->version_major,
        fi->version_minor,
        fi->version_fix,
        fi->version_build32);

#ifdef RELEASE
#    ifdef CHECK_ALL
                oputs (stream, " ReleaseCheck");
#    else
                oputs (stream, " Release");
#    endif
#endif

#ifdef __DEBUG
#    ifdef CHECK_ALL
                oputs (stream, " DebugCheck");
#    else
                oputs (stream, " Debug");
#    endif
#endif

    oprintf (
        stream,
        " %u/%u/%u %02u:%02u:%02u",
        fi->compile_day,
        fi->compile_month,
        fi->compile_year,
        fi->compile_hour,
        fi->compile_min,
        fi->compile_sec);

    oprintf (stream, " CRC:%08" PRIX32 " ", fi->flash_crc);
}

bool is_flash_range_accessable (void const *addr, uint32_t size) {
    bool retval = true;

#if defined(SPC58) && defined(HAS_SPC58_RESET_INFO)
    void const * ecc_error_addr = u32_to_cvp (reboot_state.exception_frame.addr_error_ecc);
    void const * end_addr = u32_to_cvp ((cvp_2_u32 (addr) + size));

    bool lower_bound_check = (cvp_2_u32 (ecc_error_addr) >= cvp_2_u32 (addr));
    bool upper_bound_check = (cvp_2_u32 (ecc_error_addr) <= cvp_2_u32 (end_addr));
    retval = !((true == lower_bound_check) && (true == upper_bound_check));

#else
    (void) addr;
    (void) size;
#endif

    return retval;
}

#ifdef __ghs__
#    pragma ghs endnowarning 2100
#    pragma ghs endnowarning 1868
#    pragma ghs endnowarning 2107
#    pragma ghs endnowarning 2106
#    pragma ghs endnowarning 1836
#    pragma ghs endnowarning 2101
#endif
