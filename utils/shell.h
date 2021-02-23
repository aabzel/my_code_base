#ifndef UTILS_SHELL_H_
#define UTILS_SHELL_H_
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "device.h"
#include "ostream.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SHELL_MAX_ARG_COUNT 12
#define SHELL_MAX_CMD_LEN 40

extern bool show_shell_prompt;
extern bool user_mode;
typedef bool (*shellcmd_t)(int32_t argc, char *argv[]);

typedef struct {
    const char *short_name;
    const char *long_name;
    const char *description;
    const shellcmd_t handler;
} shell_cmd_info_t;

#define SHELL_CMD(long_cmd, short_cmd, func, description) {short_cmd, long_cmd, description, func}

#ifdef ENABLE_CORE0
#include "multicore.h"
#else
#define DEFAULT_CORE0_COMMANDS
#endif

#ifdef EXT_WDT_PRESENT
#define EXT_WDT_TEST SHELL_CMD("wd_test_hw", "hwd_test", cmd_wd_test_hw, "Stop board (for hardware watchdog test)"),
#else
#define EXT_WDT_TEST
#endif

#ifdef TEST_FIRMWARE
bool cmd_read_memory (int32_t argc, char *argv []);

#define TEST_FIRMWARE_COMMANDS \
    SHELL_CMD("read_mem", "rm", cmd_read_memory, "Read memory address"), \
    SHELL_CMD("uarts","u", cmd_uarts, "Print UARTs statistics"),
#else
#define TEST_FIRMWARE_COMMANDS
#endif

#if defined (BOOTLOADER)
#define DEFAULT_COMMANDS \
    SHELL_CMD("help","h",cmd_help, "Print list of shell commands"), \
    SHELL_CMD("version", "vi", cmd_version, "Print version information"), \
    SHELL_CMD("sysinfo","si", cmd_sysinfo, "Print information about threads & OS"), \
    SHELL_CMD("soft_reboot", "reboot", cmd_soft_reboot, "Reboot board"), \
    SHELL_CMD("wd_test", "wd_test", cmd_wd_test, "Stop board (for watchdog test)"), \
    EXT_WDT_TEST \
    DEFAULT_CORE0_COMMANDS
#else
#define DEFAULT_COMMANDS \
    SHELL_CMD("help","h", cmd_help, "Print list of shell commands"), \
    SHELL_CMD("version", "vi", cmd_version, "Print version information"), \
    SHELL_CMD("sysinfo","si", cmd_sysinfo, "Print information about threads & OS"), \
    SHELL_CMD("soft_reboot", "reboot", cmd_soft_reboot, "Reboot board"), \
    SHELL_CMD("wd_test", "wd_test", cmd_wd_test, "Stop board (for watchdog test)"), \
    EXT_WDT_TEST \
    TEST_FIRMWARE_COMMANDS \
    DEFAULT_CORE0_COMMANDS
#endif

#define COMMANDS_END         SHELL_CMD(NULL,NULL,NULL,NULL)

void process_shell_cmd(char* cmd_line);
void shell_prompt(void);
void print_version (void);
void print_version_s (ostream_t* stream);

bool cmd_help(int32_t argc, char *argv[]);
bool cmd_version(int32_t argc, char *argv[]);
void start_banner(void);
bool dump_cmd_result(bool res);
bool dump_cmd_result_ex(bool res, const char* message);
bool cmd_wd_test(int32_t argc, char *argv[]);
bool cmd_wd_test_hw (int32_t argc, char *argv []);

bool cmd_sysinfo(int32_t argc, char *argv[]);
void help_dump_key (const char *subName1, const char *subName2);

void reboot(void);
bool cmd_soft_reboot(int32_t argc, char *argv[]);
#ifdef  __cplusplus
}
#endif

#endif /* UTILS_SHELL_H_ */
