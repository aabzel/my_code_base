#include "shell_test_boards.h"

#include <string.h>

#include "convert.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "shell.h"

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
