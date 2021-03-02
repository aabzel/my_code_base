#include "shell.h"

#include <ctype.h>
#include <inttypes.h>
#include <string.h>

#if defined(__GCC__)
#include <strings.h>
#endif

#include "board_config.h"
#include "convert.h"
#include "device_flash_info.h"
#include "device_id.h"
#include "version.h"
#include "clocks.h"
#include "sys.h"
#include "diag_report.h"
#include "io_utils.h"
#include "log_commands.h"
#include "none_blocking_pause.h"
#include "oprintf.h"
#include "read_mem.h"
#include "rx_uart.h"
#include "rx_uart_misra.h"
#include "shell_commands.h"
#include "str_utils.h"
#include "terminal_codes.h"
#include "watchdog.h"


#ifdef EMBEDDED_TEST
#include "print_buffer.h"
#endif

#ifdef HAS_BOARD_TYPE_ID
#include "board_type_id.h"
#endif

static const shell_cmd_info_t shell_commands[] = {SHELL_COMMANDS COMMANDS_END};

bool show_shell_prompt = true;
bool user_mode = true;

/*logic AND for keyWords */
static bool is_print_cmd (const shell_cmd_info_t *const cmd, const char *const subName1, const char *const subName2) {
    bool res = false;
    if (NULL != cmd) {
        if ((NULL == subName1) && (NULL == subName2)) {
            res = true;
        } else if ((NULL != subName1) && (NULL == subName2)) {
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
        } else if ((NULL != subName1) && (NULL != subName2)) {
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
    const shell_cmd_info_t *cmd = shell_commands;
    rx_printf ("Available commands: ");
    rx_putstr (CRLF);
    rx_putstr ("|   short |          long command | Description" CRLF);
    rx_putstr ("|---------|-----------------------|-----" CRLF);
    while (cmd->handler) {
        if (is_print_cmd (cmd, subName1, subName2)) {
            rx_printf ("|%8s |%22s | %s" CRLF, cmd->short_name ? cmd->short_name : "",
                       cmd->long_name ? cmd->long_name : "", cmd->description ? cmd->description : "");

            flush_printf ();
        }
        cmd++;
    }
}

bool cmd_help (int32_t argc, char *argv[]) {
    bool res = false;
    if (3 <= argc) {
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

/* variable address can be obtained from *.elf due to readelf tool*/
bool cmd_read_memory (int32_t argc, char *argv[]) {
    bool res = false;
    if (1 == argc) {
        uint32_t address_val = 0u;
        uint32_t value = 0u;
        res = try_str2uint32 (argv[0], &address_val);
        if (false == res) {
            LOG_ERROR (SYS, "Invalid address hex value %s", argv[0]);
        } else {
            rx_printf ("address: 0x%08x\n\r", (unsigned int)address_val);
        }
        if (true == res) {
            value = read_addr_32bit (address_val);
            rx_printf ("value: 0x%08x 0b%s\n\r", (unsigned int)value, utoa_bin32 (value));
        }
    }
    if (2 == argc) {
        uint32_t address_val = 0u;
        uint32_t num_of_byte = 0u;
        uint8_t value_byte = 0u;
        uint32_t index = 0u;
        res = try_str2uint32 (argv[0], &address_val);
        if (false == res) {
            LOG_ERROR (SYS, "Invalid address hex value %s", argv[0]);
        } else {
            rx_printf ("address: 0x%08x \n\r", (unsigned int)address_val);
        }
        res = try_str2uint32 (argv[1], &num_of_byte);
        if (false == res) {
            LOG_ERROR (SYS, "Invalid amount of byte %s", argv[1]);
        } else {
            rx_printf ("num_of_byte: %d \n\r", (unsigned int)num_of_byte);
        }
        for (index = 0; index < num_of_byte; index++) {
            value_byte = read_addr_8bit (address_val + index);
            rx_printf ("%02x", (unsigned int)value_byte);
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

bool stack_dir(int *main_local_addr) {
	bool res = false;
	int32_t fun_local;
    if (main_local_addr < &fun_local) {
    	rx_printf("Stack grows from small addr to big addr -> \n"CRLF);
    } else {
    	rx_printf("Stack grows from big addr to small addr <- \n"CRLF);
    }
    return res;
}

bool explore_stack_dir(void) {
    // fun's local variable
	bool res=false;
	int32_t main_local;
    res = stack_dir(&main_local);
    return res;
}

typedef union union_u32_u8x {
	uint32_t i;
	uint8_t c[4];
} union_u32_u8x_t;

bool is_big_endian(void) {
	union_u32_u8x_t bint;
	bint.i = 0x01020304;
	return bint.c[0] == 1;
}

bool is_little_endian(void) {
	union_u32_u8x_t bint;
	bint.i = 0x01020304;
	return bint.c[0] == 4;
}

bool cmd_sysinfo(int32_t argc, char *argv[]) {
	(void) argv;
	bool res = false;
	if (argc != 0) {
		LOG_ERROR(SYS, "Usage: sysinfo");
		res = false;
	} else {
		rx_printf("up time: %u [ms] / %u [s]" CRLF, g_up_time_ms,
				g_up_time_ms / 1000);
		rx_printf("MCU = %s" CRLF, get_mcu_name());
		explore_stack_dir();
		print_sysinfo();
		if(is_little_endian()){
			rx_printf("Little endian" CRLF);
		}else{
			rx_printf("big endian" CRLF);
		}
		res = true;
	}

	return true;
}

bool cmd_wd_test (int32_t argc, char *argv[]) {
    uint32_t delay_in_ms = 1000;
    if (argc != 1) {
        LOG_ERROR (SYS, "Usage: wd_test time_ms");
        return false;
    }
    if (!try_str2uint32 (argv[0], &delay_in_ms)) {
        LOG_ERROR (SYS, "Invalid delay value %s", argv[0]);
        return false;
    }
    LOG_WARNING (SYS, "Delay for %" PRIu32 " ms", delay_in_ms);
    flush_printf ();
    delay (delay_in_ms);
    return true;
}

bool cmd_wd_test_hw (int32_t argc, char *argv[]) {
    uint32_t delay_in_ms = 1000;
    if (argc != 1) {
        LOG_ERROR (SYS, "Usage: wd_test_hw time_ms");
        return false;
    }
    if (!try_str2uint32 (argv[0], &delay_in_ms)) {
        LOG_ERROR (SYS, "Invalid delay value %s", argv[0]);
        return false;
    }
    LOG_WARNING (SYS, "Delay for %" PRIu32 " ms", delay_in_ms);
    flush_printf ();
    {
        uint32_t end_time = get_time_ms32 () + delay_in_ms;
        while (get_time_ms32 () <= end_time) {
#ifdef HAS_SWT
            wdt_reset_sw ();
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

void print_version (void) { print_version_s (get_console_stream ()); }

void print_version_s (ostream_t *stream) {
    const char *mcu;
    oprintf (stream, "%s ", HARDWARE_NAME);
    oprintf (stream, "%s ", __DATE__);
    oprintf (stream, "%s ", __TIME__);
    oprintf (stream, "%s ", __TIMESTAMP__ );
    oprintf (stream, "Cstd %u ", __STDC__ );
    oprintf (stream, "%u ", __STDC_VERSION__ );

#ifdef __GNUC__
    oputs (stream, " GCC");
#endif

#ifdef RELEASE
    oputs (stream, " Release");
#endif


#ifdef __DEBUG
    oputs (stream, " Debug");
#endif


    oprintf (stream, " Serial:%" PRIX64, get_device_serial ());
    mcu = get_mcu_name ();
    if ((NULL != mcu) && (*mcu != '\0')) {
        oprintf (stream, " MCU:%s", get_mcu_name ());
    }

    oputs (stream, " by aabdev");
    oputs (stream, CRLF);
}

void start_banner (void) {
    rx_putstr (VT_SETCOLOR_NORMAL "\n\n\n\r");
    print_version ();
#if !defined(FOR_BOOTLOADER) && !defined(BOOTLOADER)
    if (APP_START_ADDRESS) {
        LOG_ERROR (SYS, "FOR_BOOTLOADER not defined but application linked for bootloader use");
    }
#endif
}

bool cmd_version (int32_t argc, char *argv[]) {
    (void)(argv);
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

bool dump_cmd_result_ex (bool res, const char *message) {
#ifdef EMBEDDED_TEST
    STRNCPY (last_cmd_result_str, message);
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

void process_shell_cmd (char *cmd_line) {
    static int shell_argc = 0;
    static char *shell_argv[SHELL_MAX_ARG_COUNT];
    char *p = cmd_line;
    const shell_cmd_info_t *cmd = shell_commands;

    shell_argc = 0;
    memset (shell_argv, 0, sizeof (shell_argv));
    while ((shell_argc < SHELL_MAX_ARG_COUNT) && (*p != 0)) {
        while (isspace ((uint8_t)*p)) {
            p++;
        }
        if (*p != '\0') {
            shell_argv[shell_argc] = p;
            shell_argc++;
            while (*p && !isspace ((uint8_t)*p)) {
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
        if ((cmd->long_name && strcasecmp (cmd->long_name, shell_argv[0]) == 0) ||
            (cmd->short_name && strcasecmp (cmd->short_name, shell_argv[0]) == 0)) {
            cmd->handler (shell_argc - 1, shell_argv + 1);
            shell_prompt ();
            return;
        }
        cmd++;
    }
    if (user_mode) {
        LOG_ERROR (SYS, "Unknown command [%s]", shell_argv[0]);
    } else {
        dump_cmd_result_ex (false, "Unknown command");
    }
    shell_prompt ();
}

void reboot (void) {

    LOG_INFO (SYS, "Reboot device");
    flush_printf ();

#ifdef HAS_MODULE_POWER
    poweroff_5v_aux (0U);
#endif

    delay (10);
#ifdef EXT_WDT_PRESENT
    wdt_enable_ext (false);
#endif

#ifdef CUBEMX
    NVIC_SystemReset ();
#endif
}

bool cmd_soft_reboot (int32_t argc, char *argv[]) {
    (void)(argv);
    bool res = false;
    if (0 == argc) {
        res = true;
        reboot ();
    } else {
        LOG_ERROR (SYS, "Usage: reboot");
    }
    return res;
}

bool cmd_repeat (int32_t argc, char *argv[]) {
    bool res = false;
    if (3 == argc) {
        char command[50];
        res = true;
        uint32_t period_ms;
        uint32_t num;
        strncpy (command, argv[0], sizeof (command));
        if (true == res) {
            res = try_str2uint32 (argv[1], &period_ms);
        }
        if (true == res) {
            res = try_str2uint32 (argv[2], &num);
        }
        uint32_t iter = 0;
        for (iter = 0; iter < num; iter++) {
            process_shell_cmd (command);
            wait_in_loop_ms (period_ms);
        }
    } else {
        LOG_ERROR (SYS, "Usage: rpt command period times ");
    }
    return res;
}

static bool is_arr_pat (uint8_t *arr, uint32_t size, uint8_t patt) {
    bool res = true;
    for (uint32_t i = 0; i < size; i++) {
        if (patt != arr[i]) {
            res = false;
        }
    }
    return res;
}

static bool try_alloc_on_stack (int n, uint8_t pat) {
    uint8_t array[n];
    bool res = false;
    memset (array, pat, n);
    if (is_arr_pat (array, n, pat)) {
        res = true;
    }
    return res;
}

bool cmd_try_stack (int32_t argc, char *argv[]) {
    bool res = false;
    if (1 == argc) {
        res = true;
        uint32_t size = 0;
        if (true == res) {
            res = try_str2uint32 (argv[0], &size);
        }
        if (true == res) {
            res = try_alloc_on_stack (size, 0x5A);
        }

    } else {
        LOG_ERROR (SYS, "Usage: tstk size");
    }
    return res;
}

bool cmd_launch_function (int32_t argc, char *argv[]) {
    bool res = false;
    if (1 == argc) {
        res = true;
        uint32_t function_address = 0;
        void (*function_ptr) (void);
        if (true == res) {
            res = try_str2uint32 (argv[0], &function_address);
            if (false == res) {
                LOG_ERROR (SYS, "Unable to parse address %s", argv[0]);
            }
        }
        if (true == res) {
            function_ptr = (void (*) (void))function_address;
            function_ptr ();
        }

    } else {
        LOG_ERROR (SYS, "Usage: lfun func_address_hex");
    }
    return res;
}
