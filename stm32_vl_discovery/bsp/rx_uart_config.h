#ifndef SRC_RX_UART_CONFIG_H
#define SRC_RX_UART_CONFIG_H

#include "shell.h"

#include "writer_generic.h"

extern generic_writer_t dbg_o;

#define DBG_UART1 &huart1

#define UART_WRITERS UART_WRITER (dbg_o, DBG_UART1, 1000)

#define UART_READERS UART_READER (cmd_reader, DBG_UART1, 1000, 1000, process_shell_cmd)

#define DBG (&dbg_o.s)

#endif /* SRC_RX_UART_CONFIG_H */
