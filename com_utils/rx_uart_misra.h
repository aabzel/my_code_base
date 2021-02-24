#ifndef RX_UART_MISRA_H_
#define RX_UART_MISRA_H_

#include "ostream.h"
#include <stdbool.h>

void set_echo (bool echo_val);

ostream_t *get_console_stream (void);
#ifdef TEST_FIRMWARE
bool diag_page_uarts (ostream_t *stream);
#endif

#endif /* RX_UART_MISRA_H_ */
