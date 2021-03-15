#ifndef SRC_UART_H
#define SRC_UART_H

#include "device.h"
#include "oprintf.h"
#include "rx_uart_config.h"
#include "uart_string_reader.h"
#include "writer_generic.h"

#define UART_TX_ARRAY_SIZE    600U
#define UART_RX_ARRAY_SIZE    500U
#define UART_RX_FIFO_ARRAY_SIZE  100U


extern generic_writer_t dbg_o;

bool uarts_init (void);
bool diag_page_uarts (ostream_t *stream);
void process_uarts (void);
bool cmd_uarts (int32_t argc, char *argv[]);

uart_string_reader_t *get_uart_reader (const UartHandle_t *h);
generic_writer_t *get_uart_writer (const UartHandle_t *h);
bool print_mem (uint8_t *addr, int32_t len);

#endif /* SRC_UART_H */
