#include "rx_io.h"

#ifdef NO_EMBEDED

#include <stdio.h>

print_callback_t print_callback_f;

void rx_putstr(const char *str) {
    rx_printf("%s", str);
}

void rx_putchar(char c) {
    rx_printf("%c", c);
}

void rx_printf(const char *format, ...) {
    va_list vlist;
    va_start(vlist, format);
    rx_vprintf(format, vlist);
    va_end(vlist);
}

void rx_vprintf(const char *format, va_list vlist) {
    if (print_callback_f) {
        static char buff[100000];
        vsnprintf(buff,sizeof(buff),format,vlist);
        print_callback_f(buff);
    } else {
        vprintf(format, vlist);
    }
}

void flush_printf(void) {
}

void wait_for_printf (void) {
}

#endif /* NO_EMBEDED */

void rx_putstrln(const char * str) {
    rx_putstr(str);
    rx_putstr(CRLF);
}

