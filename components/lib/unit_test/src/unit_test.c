#include "unit_test.h"

#include <inttypes.h>
#include <stddef.h>

#include "log.h"
#include "io_utils.h"
#include "test_list.h"
#include "convert.h"
#include "test_list.h"
#include "str_utils.h"
#include "terminal_codes.h"
#include "unit_test_run.h"

extern const unit_test_info_t __begin_unit_test_info;
extern const unit_test_info_t __end_unit_test_info;

static void init_ctors (void);
static uint32_t unit_test_run_key (const char *key);
static uint32_t unit_test_run_name (const char *name);
static uint32_t unit_test_run_prefix (const char *prefix);
static uint32_t unit_test_run_range (uint32_t from_index, uint32_t to_index);

static void init_ctors (void) {

}

uint32_t get_unit_test_count (void) {
    int32_t test_count = UTEST_NUMBER;
    return (uint32_t) test_count;
}

void unit_test_init (void) {
    LOG_INFO (
        SYS,
        "Unit_test info begin at 0x%p end at 0x%p. %" PRIu32 " tests in firmware",
        &__begin_unit_test_info,
        &__end_unit_test_info,
        get_unit_test_count ());
    init_ctors ();
}

const unit_test_info_t* get_unit_test (uint32_t test_index) {
    const unit_test_info_t *res;
    if (  get_unit_test_count () <=test_index) {
        res = NULL;
    } else {
        res = &test_list[test_index];
    }
    return res;
}

void dump_unit_test_all (void) {
    uint32_t index;
    for (index = 0U; index < get_unit_test_count (); index++) {
        const unit_test_info_t *ui = get_unit_test (index);
        if (ui != NULL) {
            io_puts (ui->name);
            io_puts (".");
            io_puts (rx_utoa32 (index + 1U));
            io_puts (CRLF);
            io_flush();
        }
    }
}

void dump_unit_test_key (const char *key) {
    uint32_t index;
	LOG_INFO (SYS, "%s() key %s",__FUNCTION__, key);
    for (index = 0U; index < get_unit_test_count (); index++) {
        const unit_test_info_t *ui = get_unit_test (index);
        if (ui != NULL) {
            if (NULL != str_case_str (ui->name, key)) {
                io_puts (ui->name);
                io_puts (".");
                io_puts (rx_utoa32 (index + 1U));
                io_puts (CRLF);
                io_flush();
            }
        }
    }
}

static uint32_t unit_test_run_key (const char *key) {
    uint32_t index;
    LOG_INFO (SYS, "%s() key %s",__FUNCTION__, key);
    uint32_t count = 0U;
    for (index = 0U; index < get_unit_test_count (); index++) {
        const unit_test_info_t *ui = get_unit_test (index);
        if (ui != NULL) {
            if (NULL != str_case_str (ui->name, key)) {
                count += unit_test_run (index);
            }
        }
    }
    return count;
}

static uint32_t unit_test_run_name (const char *name) {
    uint32_t index;
    uint32_t count = 0U;
    for (index = 0U; index < get_unit_test_count (); index++) {
        const unit_test_info_t *ui = get_unit_test (index);
        if (ui != NULL) {
            if (0 == strcmp (name, ui->name)) {
                count += unit_test_run (index);
            }
        }
    }
    return count;
}

static uint32_t unit_test_run_prefix (const char *prefix) {
    uint32_t index;
    uint32_t count = 0U;
    size_t len = strlen (prefix);
    for (index = 0U; index < get_unit_test_count (); index++) {
        const unit_test_info_t *ui = get_unit_test (index);
        if (ui != NULL) {
            if (0 == strncmp (ui->name, prefix, len)) {
                count += unit_test_run (index);
            }
        }
    }
    return count;
}

static uint32_t unit_test_run_range (uint32_t from_index, uint32_t to_index) {
    uint32_t index;
    uint32_t count = 0U;
    for (index = from_index; index <= to_index; index++) {
        count += unit_test_run (index);
    }
    return count;
}

void unit_tests_run (const char *key) {
	LOG_INFO (SYS, "%s() key %s",__FUNCTION__, key);
    char test_name [100]="";
    uint32_t count = 0U;

    failed_tests_reset ();

    (void) strncpy (test_name, key, sizeof(test_name));
    test_name [sizeof(test_name) - 1U] = '\0';

    if (0U == count) {
        if (0 == strcmp (test_name, "*")) {
            count = unit_test_run_range (0U, get_unit_test_count () - 1U);
        }
    }

    if (0U == count) {
        if (strchr (test_name, (int16_t) '+') != NULL) {
            char *p = strchr (test_name, (int16_t) '+');
            *p = '\0';
            count = unit_test_run_key (test_name);
        }
    }
    if (0U == count) {
        if (strchr (test_name, (int32_t) '*') != NULL) {
            char *p = strchr (test_name, (int32_t) '*');
            *p = '\0';
            count = unit_test_run_prefix (test_name);
        }
    }

    if (0U == count) {
        uint32_t number;
        if (true == try_str2uint32 (test_name, &number)) {
            count = unit_test_run (number - 1U);
        }
    }
    if (0U == count) {
        count = unit_test_run_name (test_name);
    }
    if (0U == count) {
        if (strchr (test_name, (int32_t) '-') != NULL) {
            bool ok = true;
            uint32_t from_number, to_number;
            char *p = strchr (test_name, (int32_t) '-');
            *p = '\0';
            p++;
            if (true != try_str2uint32 (test_name, &from_number)) {
                ok = false;
                LOG_ERROR (SYS, "Invalid \"from\" test number %s", test_name);
            }
            if (true != try_str2uint32 (p, &to_number)) {
                ok = false;
                LOG_ERROR (SYS, "Invalid \"to\" test number %s", p);
            }
            if (true == ok) {
                count = unit_test_run_range (from_number - 1U, to_number - 1U);
            }
        }
    }
    if (0U == count) {
        io_printf (VT_SETCOLOR_RED "Test %s not found!" CRLF, key);
        io_puts ("!ERRTEST" VT_SETCOLOR_NORMAL CRLF);
    }
    if (count > 1U) {
        failed_tests_print ();
    }
    io_flush ();
}
