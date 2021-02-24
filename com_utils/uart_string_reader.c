#include "uart_string_reader.h"

#include <stdint.h>
#include <string.h>

#include "device.h"
#include "rx_io.h"
#include "timer_utils.h"

#ifdef CUBEMX
#include "uart_driver_stm32.h"
#endif

uint64_t uart_rx_last_data_time_stamp_us = 0U;

void uart_string_reader_clear_str (uart_string_reader_t *r) {
    r->string_len = 0;
    r->string[0] = 0;
}

bool uart_string_reader_init (uart_string_reader_t *r) {
    (void)(r);
    read_char (r);
    return true;
}

void uart_string_reader_rx_callback (uart_string_reader_t *r, char c) {
    if (!fifo_char_add (&r->fifo, c)) {
        r->lost_char_count++;
    }
}

void uart_string_reader_error_callback (uart_string_reader_t *r) {
    r->error_count++;
    read_char (r);
}

void uart_string_reader_proccess (uart_string_reader_t *r) {
    while (1) {
        fifo_index_t size = 0, i;
        const char *p = fifo_char_get_contiguous_block (&r->fifo, &size);
        if (size == 0) {
            break;
        } else {
            uart_rx_last_data_time_stamp_us = get_time_us ();
        }
        for (i = 0; i < size; i++) {
            char c = p[i];
            r->total_char_count++;
            if (c != '\n') {
                if (r->echo) {
                    rx_putchar (c);
                }
                switch (c) {
                case '\b':
                    if (r->string_len) {
                        r->string[r->string_len] = 0;
                        r->string_len--;
                    }
                    if (r->echo) {
                        rx_putchar (' ');
                        rx_putchar ('\b');
                    }
                    break;
                case '\r':
                    if (r->echo) {
                        rx_putchar ('\n');
                    }
                    r->string[r->string_len] = 0;
                    r->total_string_count++;
                    if (r->callback) {
                        r->callback (r->string);
                    }
                    r->string_len = 0;
                    r->string[0] = 0;
                    break;
                default:
                    if (r->string_len < r->string_size) {
                        r->string[r->string_len] = c;
                        r->string_len++;
                    } else {
                        r->lost_char_count++;
                    }
                    break;
                }
            }
        }
        fifo_char_free (&r->fifo, size);
    }
}

const char *uart_string_reader_get_str (const uart_string_reader_t *r) { return r->string; }
