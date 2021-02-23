#ifndef SRC_RX_UART_H_
#define SRC_RX_UART_H_

#include "oprintf.h"
#include "device.h"
#include "uart_string_reader.h"
#include "rx_uart_config.h"
#include "writer_generic.h"

#ifdef SPC5
#include "uart_driver_spc5.h"
#endif

#if !defined(CUBEMX) || defined(HAS_IPP_UART)
#define UART_WRITER(os, uart, size) extern generic_writer_t os;
	UART_WRITERS
#undef  UART_WRITER

#define UART_READER(r, uart, string_len, queue_size, callback) extern uart_string_reader_t r;
	UART_READERS
#undef  UART_READER
#endif

bool uarts_init (void);
void process_uarts (void);
bool cmd_uarts (int32_t argc, char *argv []);

uart_string_reader_t* get_uart_reader(const UartHandle_t* h);
generic_writer_t* get_uart_writer(const UartHandle_t* h);

#endif /* SRC_RX_UART_H_ */
