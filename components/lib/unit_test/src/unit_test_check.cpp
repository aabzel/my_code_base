#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "unit_test_check.h"
#include "unit_test_run.h"
#include "print_buffer.h"

bool same_typef (float_t x, float_t y) {
    int xt = __fpclassifyf (x);
    int yt = __fpclassifyf (y);
    if ((xt == FP_INFINITE) || (xt == FP_NAN)) {
        return xt == yt;
    }
    return false;
}

bool same_type (double_t x, double_t y) {
    int xt = __fpclassifyd (x);
    int yt = __fpclassifyd (y);
    if ((xt == FP_INFINITE) || (xt == FP_NAN)) {
        return xt == yt;
    }
    return false;
}

void test_near (double_t x, double_t y, double_t error, const char *expected, const char *actual, const char *error_, const char *location) {
    double_t delta = fabs (x - y);
    if (!same_type (x, y) && (delta > error)) {
        test_failed = true;
        flush_printf ();
        wait_for_printf ();
        print_buf_stream_en = false;
        rx_printf ("TEST_NEAR FAILED at %s" CRLF, location);
        rx_printf ("|   First: %s (%g)" CRLF, expected, x);
        rx_printf ("|  Second: %s (%g)" CRLF, actual, y);
        rx_printf ("|   Delta: %g > %s (%g)" CRLF, delta, error_, error);
        print_buf_stream_en = true;
    }
}

void test_eq (double_t x, double_t y, const char *expected, const char *actual, const char *location) {
    if (!same_type (x, y) && !(x == y)) {
        test_failed = true;
        flush_printf ();
        wait_for_printf ();
        print_buf_stream_en = false;
        rx_printf ("TEST_EQ FAILED at %s" CRLF, location);
        rx_printf ("|   First: %s (%g)" CRLF, expected, x);
        rx_printf ("|  Second: %s (%g)" CRLF, actual, y);
        print_buf_stream_en = true;
    }
}

void test_eq (float_t x, float_t y, const char *expected, const char *actual, const char *location) {
    if (!same_type (x, y) && !(x == y)) {
        test_failed = true;
        flush_printf ();
        wait_for_printf ();
        print_buf_stream_en = false;
        rx_printf ("TEST_EQ FAILED at %s" CRLF, location);
        rx_printf ("|   First: %s (%g)" CRLF, expected, x);
        rx_printf ("|  Second: %s (%g)" CRLF, actual, y);
        print_buf_stream_en = true;
    }
}

void ut_dump_value (uint8_t v) {
    io_printf ("%" PRIu8 " 0x%" PRIX8, v, v);
}

void ut_dump_value (uint16_t v) {
    io_printf ("%" PRIu16 " 0x%" PRIX16, v, v);
}

void ut_dump_value (uint32_t v) {
    io_printf ("%" PRIu32 " 0x%" PRIX32, v, v);
}

void ut_dump_value (uint64_t v) {
    io_printf ("%" PRIu64 " 0x%" PRIX64, v, v);
}

void ut_dump_value (int8_t v) {
    io_printf ("%" PRId8 " 0x%" PRIX8, v, v);
}

void ut_dump_value (int16_t v) {
    io_printf ("%" PRId16 " 0x%" PRIX16, v, v);
}

void ut_dump_value (int32_t v) {
    io_printf ("%" PRId32 " 0x%" PRIX32, v, v);
}

void ut_dump_value (int64_t v) {
    io_printf ("%" PRId64 " 0x%" PRIX64, v, v);
}

void ut_dump_value (float_t v) {
    io_printf ("%g", v);
}

void ut_dump_value (double_t v) {
    io_printf ("%g", v);
}

void ut_dump_value (const void *v) {
    if (v == NULL) {
        io_puts ("NULL");
    } else {
        io_printf ("ptr: 0x%" PRIX32, (uint32_t) v);
    }
}

void ut_dump_value (bool v) {
    if (v) {
        io_puts ("true");
    } else {
        io_puts ("false");
    }
}

#ifndef __ghs__
void ut_dump_value (unsigned int v) {
    ut_dump_value((uint32_t)v);
}

void ut_dump_value (int v) {
    ut_dump_value((int32_t)v);
}
#else /* __ghs__ */
void ut_dump_value (unsigned long v) {
    ut_dump_value((uint64_t)v);
}
#endif /* __ghs__ */
