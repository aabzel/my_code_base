#include "unit_test_commands.h"
#include "unit_test.h"
#include "log.h"
#include "io_utils.h"
#include "convert.h"
#ifdef HAS_MCAL
#include "shell.h"
#endif

/*****************************************************************************
 * @brief   Adds shell commands.
 *
 * @attention  Violates #2101-D: MISRA 2012 Rule 1.2: language extensions are not allowed
 *****************************************************************************/

bool cmd_unit_test_list (int32_t argc, char *argv []) {
    bool res = true;
    LOG_INFO (SYS, "%s() key %u",__FUNCTION__, argc);
    if ((0 != argc) && (1 != argc)) {
        io_puts (""
            "Usage: tsa - Print all test" CRLF
        "Usage: tsa sample - Print all test that contain sub name \"sample\"" CRLF);
        res = false;
    }
    if (0 == argc) {
        dump_unit_test_all ();
    }
    if (1 == argc) {
        dump_unit_test_key (argv [0]);
    }
    io_puts ("!OKTEST" CRLF);
    io_flush ();
    return res;
}

bool cmd_unit_test_run (int32_t argc, char *argv []) {
    bool res = true;
    LOG_INFO (SYS, "%s() key %u",__FUNCTION__, argc);
    uint32_t repeat_count = 1;
    if ((1 != argc) && (2 != argc)) {
        res = false;
    }
    if (argc == 2) {
        if (!try_str2uint32 (argv [1], &repeat_count)) {
            io_printf ("Can't convert string [%s] to test repeat count (uint32)" CRLF, argv [1]);
            res = false;
        } else {
            if (repeat_count == 0U) {
                io_printf ("Test repeat count can't be equal to zero" CRLF);
                res = false;
            }
        }
    }
    if (res == true) {
        while (repeat_count != 0U) {
            unit_tests_run (argv [0]);
            repeat_count--;
        }
    }
    if (res == false) {
        io_puts (""
            "test_run bad format" CRLF
        "Usage: tsr test_name [repeat_count]" CRLF
        "    test_name: test name pattern, test sequential number or test range" CRLF
        "    repeat_count: repeat test call count, valid values 1-255(default=1)" CRLF
        "examples:" CRLF
        "    tsr *               : run all test" CRLF
        "    tsr simple*         : run all tests which names starting with \"simple\"" CRLF
        "    tsr simple+         : run all tests which names contain string \"simple\"" CRLF
        "    tsr simple_test     : run test with name \"simple_test\"" CRLF
        "    tsr 13              : run test with sequential number 13" CRLF
        "    tsr 1-13            : run tests with sequential numbers in range 1-13" CRLF
        "    tsr simple_test 10  : run test with name \"simple_test\" ten times" CRLF
        "    tsr 1-13 10         : run tests with sequential numbers in range 1-13 ten times" CRLF);
    }
    return res;
}

bool cmd_echo (int32_t argc, char *argv []) {
    bool echo = false;
    bool res = true;
    if (argc != 1) {
        io_printf ("!ERROR Invalid call!" CRLF);
        res = false;
    } else {
        if (!try_str2bool (argv [0], &echo)) {
            io_puts ("!ERROR Invalid argument!" CRLF);
            res = false;
        } else {
            shell_set_echo (echo);
            io_puts ("!OK" CRLF);
        }
    }
    return res;
}
