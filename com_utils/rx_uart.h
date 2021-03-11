#ifndef SRC_UART_H
#define SRC_UART_H

#include "device.h"
#include "oprintf.h"
#include "rx_uart_config.h"
#include "uart_string_reader.h"
#include "writer_generic.h"

#if !defined(CUBEMX) || defined(HAS_IPP_UART)
#define UART_WRITER(os, uart, size) extern generic_writer_t os;
UART_WRITERS
#undef UART_WRITER

#define UART_READER(r, uart, string_len, queue_size, callback) extern uart_string_reader_t r;
UART_READERS
#undef UART_READER
#endif

//#define UART_READER_PROC(r, uart, string_len, queue_size, callback) uart_string_reader_proccess (&r);


bool cmd_uarts (int32_t argc, char *argv[]);
bool diag_page_uarts (ostream_t *stream);
void process_uarts (void);
bool uarts_init (void);

uart_string_reader_t *get_uart_reader (const UartHandle_t *h);
generic_writer_t *get_uart_writer (const UartHandle_t *h);
bool print_mem(uint8_t *addr, int32_t len);

#endif /* SRC_UART_H_ */
