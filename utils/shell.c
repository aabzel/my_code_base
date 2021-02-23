#include "shell.h"

#include <ctype.h>
#include <inttypes.h>
#include <string.h>

#if defined(__GCC__)
#include <strings.h>
#endif

#include "io_utils.h"
#include "oprintf.h"
#ifdef TEST_FIRMWARE
#include "rx_uart.h"
#endif
#include "rx_uart_misra.h"
#include "str_utils.h"
#include "log_commands.h"
#include "convert.h"
#include "terminal_codes.h"
#include "device_id.h"
#include "diag_report.h"
#include "none_blocking_pause.h"
#include "shell_commands.h"
#include "watchdog.h"
#include "board_config.h"
#include "device_flash_info.h"

#ifdef HAS_TIC12400
#include "tic12400.h"
#endif

#ifdef HAS_CAN
#include "canif.h"
#endif

#if defined(SPC5) && !defined(BOOTLOADER)
#include "for_bootloader_commands.h"
#endif

#if defined(SPC58) && defined(FOR_BOOTLOADER)
#include "reboot_info.h"
#endif

#if defined(HAS_SPC58_RESET_INFO)
#include "exception_handlers.h"
#endif

#ifdef EMBEDDED_TEST
#include "print_buffer.h"
#endif

#ifdef HAS_BOARD_TYPE_ID
#include "board_type_id.h"
#endif

#ifdef HAS_MODULE_POWER
#include "module_power.h"
#endif

static const shell_cmd_info_t shell_commands [] = {
    SHELL_COMMANDS
    COMMANDS_END
};

bool show_shell_prompt = true;
bool user_mode = true;

#ifdef TEST_FIRMWARE
#include "read_mem.h"
#endif

/*logic AND for keyWords */
static bool is_print_cmd (const shell_cmd_info_t * const cmd, const char * const subName1, const char * const subName2) {
    bool res = false;
    if (NULL != cmd) {
        if ((NULL == subName1) && (NULL == subName2) ) {
            res = true;
        } else  if (  (NULL != subName1) && (NULL == subName2)) {
            /*one subname done*/
            res = false;
            if (NULL != cmd->short_name) {
                if (NULL != str_case_str (cmd->short_name, subName1)) {
                    res = true;
                }
            }
            if (NULL != cmd->long_name) {
                if (NULL != str_case_str (cmd->long_name, subName1)) {
                    res = true;
                }
            }
            if (NULL != cmd->description) {
                if (NULL != str_case_str (cmd->description, subName1)) {
                    res = true;
                }
            }
        } else if (  (NULL != subName1) && (NULL != subName2)) {
            /*two subnames done*/
            res = false;
            if (NULL != cmd->short_name) {
                if (NULL != str_case_str (cmd->short_name, subName1)) {
                    if (NULL != str_case_str (cmd->short_name, subName2)) {
                        res = true;
                    }
                }
            }
            if (NULL != cmd->long_name) {
                if (NULL != str_case_str (cmd->long_name, subName1)) {
                    if (NULL != str_case_str (cmd->long_name, subName2)) {
                        res = true;
                    }
                }
            }
            if (NULL != cmd->description) {
                if (NULL != str_case_str (cmd->description, subName1)) {
                    if (NULL != str_case_str (cmd->description, subName2)) {
                        res = true;
                    }
                }
            }
        }
    }

    return res;
}

void help_dump_key (const char *subName1, const char *subName2) {
    const shell_cmd_info_t* cmd = shell_commands;
    rx_printf ("Available commands: ");
    rx_putstr (CRLF);
    rx_putstr ("|   short |          long command | Description" CRLF);
    rx_putstr ("|---------|-----------------------|-----" CRLF);
    while (cmd->handler) {
        if (is_print_cmd (cmd, subName1, subName2)) {
            rx_printf (
                "|%8s |%22s | %s" CRLF,
                cmd->short_name ? cmd->short_name : "",
                cmd->long_name ? cmd->long_name : "",
                cmd->description ? cmd->description : "");

            flush_printf ();
        }
        cmd++;
    }
}

bool cmd_help (int32_t argc, char *argv[]) {
    bool res = false;
    if (3<=argc) {
        rx_printf ("Usage: help [subname1]  " CRLF);
        rx_printf ("       help [subname1]  [subname2]" CRLF);
        res = false;
    } else {
        if (0 == argc) {
            help_dump_key (NULL, NULL);
            res = true;
        }
        if (1 == argc) {
            help_dump_key (argv[0], NULL);
            res = true;
        }
        if (2 == argc) {
            help_dump_key (argv[0], argv[1]);
            res = true;
        }
    }

    return res;
}

#ifdef TEST_FIRMWARE

/* variable address can be obtained from *.elf due to readelf tool*/
bool cmd_read_memory (int32_t argc, char *argv []) {
    bool res = false;
    if (1 == argc) {
        uint32_t address_val = 0u;
        uint32_t value = 0u;
        res = try_str2uint32 (argv [0], &address_val);
        if (false == res) {
            LOG_ERROR (SYS, "Invalid address hex value %s", argv [0]);
        } else {
            rx_printf ("address: 0x%08x\n\r", (unsigned int) address_val);
        }
        if (true == res) {
            value = read_addr_32bit (address_val);
            rx_printf ("value: 0x%08x 0b%s\n\r", (unsigned int) value, utoa_bin32(value));
        }
    }
    if (2 == argc) {
        uint32_t address_val = 0u;
        uint32_t num_of_byte = 0u;
        uint8_t value_byte = 0u;
        uint32_t index = 0u;
        res = try_str2uint32 (argv [0], &address_val);
        if (false == res) {
            LOG_ERROR (SYS, "Invalid address hex value %s", argv [0]);
        } else {
            rx_printf ("address: 0x%08x \n\r", (unsigned int) address_val);
        }
        res = try_str2uint32 (argv [1], &num_of_byte);
        if (false == res) {
            LOG_ERROR (SYS, "Invalid amount of byte %s", argv [1]);
        } else {
            rx_printf ("num_of_byte: %d \n\r", (unsigned int) num_of_byte);
        }
        for (index = 0; index < num_of_byte; index++) {
            value_byte = read_addr_8bit (address_val + index);
            rx_printf ("%02x", (unsigned int) value_byte);
        }
        rx_printf ("\n\r");
    }

    if ((0 == argc) || (2 < argc)) {
        LOG_ERROR (SYS, "Usage: read_mem: address num_of_byte");
        LOG_INFO (SYS, "Usage: address 0xXXXXXXXX");
        LOG_INFO (SYS, "Usage: num_of_byte [0...]");
    }
    return res;
}
#endif

bool cmd_sysinfo (int32_t argc, char *argv []) {
    (void) argv;
    if (argc != 0) {
        LOG_ERROR (SYS, "Usage: sysinfo: help");
        return false;
    }
    rx_printf ("Mcu=%s" CRLF, get_mcu_name ());
#ifdef SPC5
    return show_diag_report (DIAG_PAGE_SYSINFO);
#else
    return true;
#endif
}

bool cmd_wd_test (int32_t argc, char *argv []) {
    uint32_t delay_in_ms = 1000;
    if (argc != 1) {
        LOG_ERROR (SYS, "Usage: wd_test time_ms");
        return false;
    }
    if (!try_str2uint32 (argv [0], &delay_in_ms)) {
        LOG_ERROR (SYS, "Invalid delay value %s", argv [0]);
        return false;
    }
    LOG_WARNING (SYS, "Delay for %" PRIu32 " ms", delay_in_ms);
    flush_printf ();
    delay (delay_in_ms);
    return true;
}

bool cmd_wd_test_hw (int32_t argc, char *argv []) {
    uint32_t delay_in_ms = 1000;
    if (argc != 1) {
        LOG_ERROR (SYS, "Usage: wd_test_hw time_ms");
        return false;
    }
    if (!try_str2uint32 (argv [0], &delay_in_ms)) {
        LOG_ERROR (SYS, "Invalid delay value %s", argv [0]);
        return false;
    }
    LOG_WARNING (SYS, "Delay for %" PRIu32 " ms", delay_in_ms);
    flush_printf ();
    {
        uint32_t end_time = get_time_ms32 () + delay_in_ms;
        while (get_time_ms32 () <= end_time) {
#ifdef HAS_SWT
            wdt_reset_sw();
#endif
        }
    }
    return true;
}

void shell_prompt (void) {
    if (show_shell_prompt) {
        rx_putstr ("-->");
    }
}

void print_version (void) {
    print_version_s (get_console_stream ());
}

void print_version_s (ostream_t* stream) {
#ifdef CAN_FLASHER_ON_SPC58
/* Substitution for flash_tool*/
    oprintf (stream, "CanFlasher on CanFlash Version 0.4.4.0.23 GCC Release 19/1/2020 23:19:09 FlashId:2707ABC4 Serial:202B17BC00C0 by Arrival\r\n");
#else
    const char* mcu;
    oprintf (
        stream,
        "%s on %s Version %u.%u.%u.%u.%" PRIu32,
        flash_info.firmware_name,
#ifdef HAS_BOARD_TYPE_ID
        get_board_name (),
#else
        HARDWARE_NAME,
#endif
        flash_info.version_generation,
        flash_info.version_major,
        flash_info.version_minor,
        flash_info.version_fix,
        flash_info.version_build32);
#ifdef __ghs__
    oputs (stream, " GHS");
#else
#ifdef __GNUC__
    oputs (stream, " GCC");
#endif
#endif

#ifdef RELEASE
#ifdef CHECK_ALL
    oputs (stream, " ReleaseCheck");
#else
    oputs (stream, " Release");
#endif
#endif

#ifdef __DEBUG
#ifdef CHECK_ALL
    oputs (stream, " DebugCheck");
#else
    oputs (stream, " Debug");
#endif
#endif

    oprintf (
        stream,
        " %u/%u/%u %02u:%02u:%02u",
        flash_info.compile_day,
        flash_info.compile_month,
        flash_info.compile_year,
        flash_info.compile_hour,
        flash_info.compile_min,
        flash_info.compile_sec);
    oprintf (stream, " FlashId:0x%08" PRIX32, get_flash_crc ((const flash_info_t*)&flash_info));
    oprintf (stream, " Serial:%" PRIX64, get_device_serial ());
    mcu = get_mcu_name ();
    if ((NULL != mcu) && (*mcu != '\0')) {
        oprintf (stream, " MCU:%s", get_mcu_name ());
    }
#ifdef SPC58
    oputs (stream, " ");
    oputs (stream, get_mcu_mask_id ());
#endif
    oputs (stream, " by Arrival");
    oputs (stream, CRLF);
#endif
}

void start_banner (void) {
    rx_putstr (VT_SETCOLOR_NORMAL "\n\n\n\r");
    print_version ();
#if !defined(FOR_BOOTLOADER) && !defined(BOOTLOADER)
    if (APP_START_ADDRESS) {
        LOG_ERROR(SYS, "FOR_BOOTLOADER not defined but application linked for bootloader use");
    }
#endif
}

bool cmd_version (int32_t argc, char *argv []) {
    (void) (argv);
    if (argc != 0) {
        LOG_ERROR (SYS, "Usage: version");
        return false;
    }
    if (!user_mode) {
        rx_printf ("!VI ");
    }
    print_version ();
    return dump_cmd_result (true);
}

bool dump_cmd_result (bool res) {
#ifndef EMBEDDED_TEST
    if (user_mode) {
        if (res) {
            LOG_INFO (SYS, "Ok!");
        } else {
            LOG_ERROR (SYS, "Failed!");
        }
    } else {
#endif
    if (res) {
        rx_putstr ("!OK" CRLF);
    } else {
        rx_putstr ("!ERROR" CRLF);
    }
#ifndef EMBEDDED_TEST
    }
#endif
    return res;
}

bool dump_cmd_result_ex (bool res, const char* message) {
#ifdef EMBEDDED_TEST
    STRNCPY(last_cmd_result_str, message);
#endif
    if (user_mode) {
        if (res) {
            LOG_INFO (SYS, "Ok: %s", message);
        } else {
            LOG_ERROR (SYS, "Failed: %s", message);
        }
    } else {
        if (res) {
            rx_printf ("!OK %s" CRLF, message);
        } else {
            rx_printf ("!ERROR %s" CRLF, message);
        }
    }
    return res;
}

void process_shell_cmd (char* cmd_line) {
    static int shell_argc = 0;
    static char *shell_argv [SHELL_MAX_ARG_COUNT];
    char*p = cmd_line;
    const shell_cmd_info_t* cmd = shell_commands;

    shell_argc = 0;
    memset(shell_argv, 0, sizeof(shell_argv));
    while ((shell_argc < SHELL_MAX_ARG_COUNT) && (*p != 0)) {
        while (isspace((uint8_t ) *p)) {
            p++;
        }
        if (*p != '\0') {
            shell_argv [shell_argc] = p;
            shell_argc++;
            while (*p && !isspace((uint8_t ) *p)) {
                p++;
            }
            if (*p != '\0') {
                *p = '\0';
                p++;
            }
        }
    }
    if (shell_argc == 0) {
        shell_prompt ();
        return;
    }
    while (cmd->handler) {
        if ((cmd->long_name && strcasecmp (cmd->long_name, shell_argv [0]) == 0)
                || (cmd->short_name && strcasecmp (cmd->short_name, shell_argv [0]) == 0)) {
            cmd->handler (shell_argc - 1, shell_argv + 1);
            shell_prompt ();
            return;
        }
        cmd++;
    }
    if (user_mode) {
        LOG_ERROR (SYS, "Unknown command [%s]", shell_argv [0]);
    } else {
        dump_cmd_result_ex (false, "Unknown command");
    }
    shell_prompt ();
}

void reboot (void) {

    LOG_INFO (SYS, "Reboot device");
    flush_printf ();

#ifdef HAS_TIC12400
    tic12400_hw_reset ();
#endif

#ifdef HAS_MODULE_POWER
    poweroff_5v_aux (0U);
#endif

#if defined(HAS_SPC58_RESET_INFO)
    reset_exception_frame();
#endif
    delay (10);
#ifdef EXT_WDT_PRESENT
    wdt_enable_ext (false);
#endif

#if defined(SPC58) && defined(FOR_BOOTLOADER)
    reboot_info_reset_restart_counter ();
#endif

#ifdef HAS_MCAN
    (void) canif_deinit ();
#endif

#ifdef CUBEMX
    NVIC_SystemReset ();
#endif

#ifdef SPC5
    SPCSetRunMode (0x00);
#endif
}

bool cmd_soft_reboot (int32_t argc, char *argv []) {
    (void) (argv);
    bool res = false;
    if (0 == argc) {
      res=true;
      reboot ();
    } else {
        LOG_ERROR (SYS, "Usage: reboot");
    }
    return res;
}
