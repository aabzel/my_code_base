/*****************************************************************************
 * @file    io.h
 * 
 * @details This include for compatibility with new MCAL based libraries
 *****************************************************************************/

#ifndef IO_H_
#define IO_H_

#ifdef HAS_MCAL
#error "This file can't be used in MCAL builds"
#else

#include "rx_io.h"
#include "rx_uart_misra.h"

#define io_printf rx_printf
#define io_puts rx_putstr
#define io_putc rx_putchar
#define io_flush flush_printf
#define shell_set_echo set_echo
#define io_stdout_stream_get get_console_stream

#endif /* HAS_MCAL */ 

#endif /* IO_H_ */
