#include "rx_uart.h"

#include <inttypes.h>
#include <stdbool.h>

#include "convert.h"
#include "diag_page_nums.h"
#include "diag_report.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "oprintf.h"
#include "rx_io.h"
#include "rx_uart_config.h"
#include "rx_uart_misra.h"
#include "rx_utils.h"
#include "sections.h"
#include "table_utils.h"
#include "watchdog.h"
#include "writer_generic.h"
#include "writer_uart.h"

#include "uart_driver_stm32.h"

#ifdef EMBEDDED_TEST
#include "print_buffer.h"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

static char dbg_o_data[UART_TX_ARRAY_SIZE];
generic_writer_t dbg_o = {
    {writer_putc, writer_puts},         // ostream_t
    0,                                  // fifo_index_t
    0,                                  // lost_char_count
    0,                                  // total_char_count
    0,                                  // error_count
    {{sizeof (dbg_o_data), 0, 0, 0, 0}, // fifo_index_info_t
     dbg_o_data},                       // fifo_char_t
    uart_writer_transmit,               // f_transmit
    (void *)(&huart1)                   // instance
};

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

bool uarts_init_done = false;

static char cmd_reader_data[UART_RX_FIFO_ARRAY_SIZE];
static char cmd_reader_string[UART_RX_ARRAY_SIZE];
uart_string_reader_t cmd_reader = {&huart1,                    // UartHandle_t
                                   sizeof (cmd_reader_string), // string_size
                                   (process_shell_cmd),
                                   cmd_reader_string,
                                   {{(sizeof (cmd_reader_data)), 0, 0, 0, 0}, cmd_reader_data}, // fifo
                                   0,//string_len
                                   0,//error_count
                                   0,//lost_char_count
                                   0,//total_char_count
                                   0,//total_string_count
                                   false//echo
};

uart_string_reader_t *get_uart_reader (const UartHandle_t *UartHandle) {
    if (&huart1 == UartHandle) {
        return &cmd_reader;
    };
    return NULL;
}

generic_writer_t *get_uart_writer (const UartHandle_t *UartHandle) {
    if (UartHandle == &huart1) {
        return &dbg_o;
    }
    return NULL;
}

void RX_UART_Error_callback (UartHandle_t *UartHandle, rx_uart_error_t error) {
    (void)error;
    if (UartHandle == cmd_reader.huart) {
        uart_string_reader_error_callback (&cmd_reader);
    }
    if (UartHandle == &huart1) {
        writer_error_callback (&dbg_o);
    }
}

void HAL_UART_TxCpltCallback (UartHandle_t *UartHandle) {
    g_uart_tx_cnt++;
    if (UartHandle == &huart1) {
        dbg_o.f_transmit (&dbg_o);
    }
}

void RX_UART_Recv_callback (UartHandle_t *huart, char c) {
    if (huart == cmd_reader.huart) {
        uart_string_reader_rx_callback (&cmd_reader, c);
    }
}

bool diag_page_uarts (ostream_t *stream) {
    LOG_NOTICE (SYS, "%s()", __FUNCTION__);

    static const table_col_t cols[] = {
        {16, "Name"}, {17, "Total chars"}, {13, "Lost chars"}, {11, "Strings"}, {11, "Errors"},
    };

    table_header (&dbg_o.s, cols, RX_ARRAY_SIZE (cols));
    rx_printf (TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR "%12" PRId64 " " TABLE_SEPARATOR
                          "%10" PRId64 " " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,
               "cmd_reader", cmd_reader.total_char_count, cmd_reader.lost_char_count, cmd_reader.total_string_count,
               cmd_reader.error_count);

    rx_printf (TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR "%12" PRId64 " " TABLE_SEPARATOR
                          "           " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,
               "dbg_o", dbg_o.total_char_count, dbg_o.lost_char_count, dbg_o.error_count);

    table_row_bottom (&dbg_o.s, cols, RX_ARRAY_SIZE (cols));

    rx_printf ("rx %u byte "CRLF, g_uart_rx_cnt);
    rx_printf ("tx %u cnt "CRLF, g_uart_tx_cnt);
    return true;
}

bool uarts_init (void) {
    if (false == uart_string_reader_init (&cmd_reader)) {
        return false;
    }
    set_echo (true);
    uarts_init_done = true;
    return true;
}

void process_uarts (void) {
    static bool entry = false; /* recursive protection from test which call common_loop during execution */
    if (!entry) {
        entry = true;
        uart_string_reader_proccess (&cmd_reader);
        entry = false;
    }
}

void rx_putstr (const char *str) {
    if (uarts_init_done) {
        oputs (&dbg_o.s, str);
    }

    if (print_buf_stream_en) {
        oputs (print_buf_ostream (), str);
    }
}

void set_echo (bool echo_val) { cmd_reader.echo = echo_val; }

void rx_putchar (char ch) {
    if (uarts_init_done) {
        (&dbg_o.s)->f_putch (&dbg_o.s, ch);
    }
    if (print_buf_stream_en) {
        print_buf_ostream ()->f_putch (print_buf_ostream (), ch);
    }
}

void rx_printf (const char *format, ...) {
    if (uarts_init_done) {
        va_list vlist;
        va_start (vlist, format);
        ovprintf (&dbg_o.s, format, vlist);
        va_end (vlist);
    }
#ifdef UNIT_TEST_STREAM
    if (print_buf_stream_en) {
        va_list vlist;
        va_start (vlist, format);
        ovprintf (UNIT_TEST_STREAM, format, vlist);
        va_end (vlist);
    }
#endif
}

void rx_vprintf (const char *format, va_list vlist) {
#ifdef UNIT_TEST_STREAM
    if (print_buf_stream_en) {
        va_list vlist2;
        va_copy (vlist2, vlist);
        ovprintf (UNIT_TEST_STREAM, format, vlist2);
        va_end (vlist2);
    }
#endif
    if (uarts_init_done) {
        ovprintf (DBG, format, vlist);
    }
}

bool is_printf_clean (void) {
    if (uarts_init_done) {
        if (!writer_clean (&dbg_o)) {
            return false;
        }
    }
    return true;
}

void wait_for_printf (void) {
    if (uarts_init_done) {
        while (!writer_half_clean (&dbg_o)) {
            int32_t j;
            for (j = 0; j < 100000; j++) {
            }
            wdt_reset_all ();
        }
    }
}

void flush_printf (void) {
    if (uarts_init_done) {
        while ((isFromInterrupt () == false) && !writer_clean (&dbg_o)) {
        }
    }
}

bool cmd_uarts (int32_t argc, char *argv[]) {
    (void)argv;
    if (argc != 0) {
        LOG_ERROR (UART, "Usage: uarts: help");
        return dump_cmd_result (false);
    }
    return show_diag_report (DIAG_PAGE_UARTS);
}

ostream_t *get_console_stream (void) { return DBG; }

bool print_mem (uint8_t *addr, int32_t len) {
    rx_printf (CRLF);
    bool res = false;
    if (0 < len) {
        for (uint32_t pos = 0; pos < len; pos++) {
            if (0 == (pos % 16)) {
                rx_printf (CRLF);
            }
            rx_printf ("%02x", *(addr + pos));
            wait_in_loop_ms (3);
            res = true;
        }
        rx_printf (CRLF);
    }
    return res;
}
