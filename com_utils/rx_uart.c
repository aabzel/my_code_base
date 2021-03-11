#include "rx_uart.h"

#include <inttypes.h>
#include <stdbool.h>

#include "rx_uart_misra.h"
#include "convert.h"
#include "diag_report.h"
#include "log.h"
#include "oprintf.h"
#include "rx_io.h"
#include "rx_uart_config.h"
#include "rx_utils.h"
#include "sections.h"
#include "table_utils.h"
#include "diag_page_nums.h"
#include "watchdog.h"
#include "writer_generic.h"
#include "writer_uart.h"
#include "none_blocking_pause.h"


#ifdef CUBEMX
#include "uart_driver_stm32.h"
#endif

#ifdef EMBEDDED_TEST
#include "print_buffer.h"
#endif


#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif

#if defined(SPC58xC) || defined(SPC58xN)
#include "sections.h"
#define SECTION SRAM2 ("noinit")
#else
#define SECTION
#endif

#ifdef ENABLE_MULTICORE
#define UART_WRITER(os, uart, size)                                                                                    \
    NOINIT static char os##_data[(size)] SECTION;                                                                      \
    generic_writer_t (os) = {{writer_putc, writer_puts},                                                               \
                             0,                                                                                        \
                             0,                                                                                        \
                             0,                                                                                        \
                             0,                                                                                        \
                             FIFO_CHAR_INIT_WITH_IC_MUTEX ((size), (os##_data), IC_MUTEX_LOG),                         \
                             uart_writer_transmit,                                                                     \
                             (void *)(uart)};
UART_WRITERS
#else
#define UART_WRITER(os, uart, size)                                                                                    \
    NOINIT static char os##_data[(size)] SECTION;                                                                      \
    generic_writer_t (os) = {{writer_putc, writer_puts},                                                               \
                             0,                                                                                        \
                             0,                                                                                        \
                             0,                                                                                        \
                             0,                                                                                        \
                             FIFO_CHAR_INIT ((size), (os##_data)),                                                     \
                             uart_writer_transmit,                                                                     \
                             (void *)(uart)};
UART_WRITERS
#endif
#undef UART_WRITER

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

bool uarts_init_done = false;
#define UART_READER(r, uart, str_size, queue_size, f_callback)                                                         \
    NOINIT static char r##_data[(queue_size)] SECTION;                                                                 \
    NOINIT static char r##_string[(str_size)] SECTION;                                                                 \
    uart_string_reader_t (r) = {/*.huart = */ (uart),                                                                  \
                                /*.string_size = */ (str_size),                                                        \
                                /*.callback = */ (f_callback),                                                         \
                                /*.string = */ r##_string,                                                             \
                                /*.fifo = */ FIFO_CHAR_INIT (queue_size, r##_data),                                    \
                                /*.string_len = */ 0,                                                                  \
                                /*.error_count = */ 0,                                                                 \
                                /*.lost_char_count = */ 0,                                                             \
                                /*.total_char_count = */ 0,                                                            \
                                /*.total_string_count = */ 0,                                                          \
                                /*.echo = */ false};
UART_READERS
#undef UART_READER

#define UART_READER(r, uart, string_len, queue_size, callback)                                                         \
    if (uart == h) {                                                                                                   \
        return &r;                                                                                                     \
    };
uart_string_reader_t *get_uart_reader (const UartHandle_t *h) {
    UART_READERS
    return NULL;
}
#undef UART_READER

#define UART_WRITER(os, uart, size)                                                                                    \
    if (h == uart) {                                                                                                   \
        return &os;                                                                                                    \
    }
generic_writer_t *get_uart_writer (const UartHandle_t *h) {
    UART_WRITERS
    return NULL;
}
#undef UART_WRITER

#if defined(CUBEMX)
void RX_UART_Error_callback (UartHandle_t *UartHandle, rx_uart_error_t error) {
    /* void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
         LOG_ERROR(UART, "%s: %s error", #r, uart_error2str(error)); */

    (void)error; /* UNUSED */

#define UART_READER(r, uart, string_len, queue_size, callback)                                                         \
    if (UartHandle == r.huart) {                                                                                       \
        uart_string_reader_error_callback (&r);                                                                        \
    }
    UART_READERS
#undef UART_READER
#define UART_WRITER(os, uart, size)                                                                                    \
    if (UartHandle == uart) {                                                                                          \
        writer_error_callback (&os);                                                                                   \
    }
    UART_WRITERS
#undef UART_WRITER
}
#endif

#if defined(CUBEMX)
void HAL_UART_TxCpltCallback (UartHandle_t *UartHandle) {
#define UART_WRITER(os, uart, size)                                                                                    \
    if (UartHandle == uart) {                                                                                          \
        os.f_transmit (&os);                                                                                           \
    }
    UART_WRITERS
#undef UART_WRITER
}

void RX_UART_Recv_callback (UartHandle_t *_uart, char c) {
#define UART_READER(r, uart, string_len, queue_size, callback)                                                         \
    if (_uart == r.huart) {                                                                                            \
        uart_string_reader_rx_callback (&r, c);                                                                        \
    }
    UART_READERS
#undef UART_READER
}

/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
#define UART_READER(r, uart, string_len, queue_size, callback) if (UartHandle == r.huart) {
uart_string_reader_rx_callback(&r, r.char_to_get); } UART_READERS #undef  UART_READER
}*/

#endif

#define UART_READER(r, uart, string_len, queue_size, callback)                                                         \
    oprintf (stream,                                                                                                   \
             TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR "%12" PRId64 " " TABLE_SEPARATOR      \
                        "%10" PRId64 " " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,                            \
             #r, r.total_char_count, r.lost_char_count, r.total_string_count, r.error_count);

#define GENERIC_WRITER(os)                                                                                             \
    oprintf (stream,                                                                                                   \
             TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR "%12" PRId64 " " TABLE_SEPARATOR      \
                        "           " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,                               \
             #os, os.total_char_count, os.lost_char_count, os.error_count);

#define UART_WRITER(os, uart, size) GENERIC_WRITER (os)


bool diag_page_uarts (ostream_t *stream) {
    static const table_col_t cols[] = {
        {16, "Name"}, {17, "Total chars"}, {13, "Lost chars"}, {11, "Strings"}, {11, "Errors"},
    };

    table_header (stream, cols, RX_ARRAY_SIZE (cols));
    UART_READERS
    UART_WRITERS
    table_row_bottom (stream, cols, RX_ARRAY_SIZE (cols));
    return true;
}


#undef UART_READER
#undef UART_WRITER

#ifdef CUBEMX
#define READER_PORT_INIT(uart)
#endif


#define UART_WRITER(os, uart, size)                                                                                    \
    sciEnableNotification (uart, SCI_FE_INT | SCI_OE_INT | SCI_PE_INT | SCI_RX_INT | SCI_TX_INT | SCI_BREAK_INT);
#define UART_READER(r, uart, string_len, queue_size, callback)                                                         \
    READER_PORT_INIT (uart);                                                                                           \
    if (!uart_string_reader_init (&r)) {                                                                               \
        return false;                                                                                                  \
    }

bool uarts_init (void) {
    UART_READERS
    set_echo (true);
    uarts_init_done = true;
    return true;
}
#undef UART_READER
#undef UART_WRITER

#define UART_READER(r, uart, string_len, queue_size, callback) uart_string_reader_proccess (&r);
void process_uarts (void) {
    static bool entry = false; /* recursive protection from test which call common_loop during execution */
    if (!entry) {
        entry = true;
        UART_READERS
        entry = false;
    }
}

#undef UART_READER
void rx_putstr (const char *str) {
    if (uarts_init_done) {
        oputs (DBG, str);
    }
#ifdef UNIT_TEST_STREAM
    if (print_buf_stream_en) {
        oputs (UNIT_TEST_STREAM, str);
    }
#endif
}

void set_echo (bool echo_val) { cmd_reader.echo = echo_val; }

void rx_putchar (char ch) {
    if (uarts_init_done) {
        DBG->f_putch (DBG, ch);
    }
#ifdef UNIT_TEST_STREAM
    if (print_buf_stream_en) {
        UNIT_TEST_STREAM->f_putch (UNIT_TEST_STREAM, ch);
    }
#endif
}

void rx_printf (const char *format, ...) {
    if (uarts_init_done) {
        va_list vlist;
        va_start (vlist, format);
        ovprintf (DBG, format, vlist);
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
    return dump_cmd_result (show_diag_report (DIAG_PAGE_UARTS));
}

ostream_t *get_console_stream (void) { return DBG; }

bool print_mem(uint8_t *addr, int32_t len) {
	rx_printf(CRLF);
	bool res = false;
	if (0 < len) {
		for (uint32_t pos = 0; pos < len; pos++) {
			if (0 == (pos % 16)) {
				rx_printf(CRLF);
			}
			rx_printf("%02x", *(addr + pos));
			wait_in_loop_ms(3);
			res = true;
		}
		rx_printf(CRLF);
	}
	return res;
}
