#ifndef RX_IO_H
#define RX_IO_H

#ifndef __MISRA_16_1
#include <stdarg.h>
#endif
#include "rx_utils.h"
#include <stdbool.h>


#ifdef  __cplusplus
extern "C" {
#endif

#define CRLF "\r\n"

#ifndef __MISRA_16_1
#ifdef NO_EMBEDED
#define _SE "\n"
typedef void (*print_callback_t)(const char* str);
extern print_callback_t print_callback_f;
#endif /*NO_EMBEDED*/
#endif

void rx_putstr (const char * str);
void rx_putstrln (const char * str);

#ifdef __ghs__
#pragma ghs startnomisra
#endif

#ifndef __MISRA_16_1
void rx_printf(const char *_format, ...) __attribute__((format(printf, 1, 2)));
void rx_vprintf (const char *format, va_list vlist);
#endif

#ifdef __ghs__
#pragma ghs endnomisra
#endif

void rx_putchar (char c);
bool is_printf_clean (void);
void wait_for_printf (void);
void flush_printf (void);

#ifdef  __cplusplus
}
#endif

#endif /* RX_IO_H */
