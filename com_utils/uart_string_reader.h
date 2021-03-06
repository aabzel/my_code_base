#ifndef SRC_UART_STRING_READER_H
#define SRC_UART_STRING_READER_H

#include <stdbool.h>
#include <stdint.h>

#include "fifo_char_buffer.h"
#include "uart_common.h"

typedef void (*handle_string_f)(char *s);

typedef struct {
  UartHandle_t *huart;
  uint16_t string_size;
  handle_string_f callback;
  char *string;
  fifo_char_t fifo;
  uint16_t string_len;
  int64_t error_count;
  int64_t lost_char_count;
  int64_t total_char_count;
  int64_t total_string_count;
  bool echo;
} uart_string_reader_t;

extern uint64_t uart_rx_last_data_time_stamp_us;

bool uart_string_reader_init(uart_string_reader_t *r);
void uart_string_reader_rx_callback(uart_string_reader_t *r, char c);
void uart_string_reader_error_callback(uart_string_reader_t *r);
void uart_string_reader_proccess(uart_string_reader_t *r);
void uart_string_reader_clear_str(
    uart_string_reader_t *r); /* clear current string */
const char *uart_string_reader_get_str(const uart_string_reader_t *r);

#endif /* SRC_UART_STRING_READER_H */
