#include "writer_generic.h"

#include <string.h>

#include "rx_utils.h"
#include "uart_common.h"

void writer_putc (void *_s, char ch) {
    generic_writer_t *s = (generic_writer_t *)_s;
    if (!fifo_char_add (&s->fifo, ch)) {
        s->lost_char_count++;
    } else {
        if (s->in_transmit == 0) {
            { enter_critical (); }
            if (s->in_transmit == 0) {
                s->f_transmit (s);
            }
            { exit_critical (); }
        }
    }
}

void writer_puts (void *_s, const char *str, int32_t len) {
    if (len == 1) {
        writer_putc (_s, *str);
    } else {
        generic_writer_t *s = (generic_writer_t *)_s;

        if (len < 0) {
            len = strlen (str);
        }
        while (len) {
            if (!fifo_char_add (&s->fifo, *str)) {
                s->lost_char_count += len;
            }
            str++;
            len--;
        }

        { enter_critical (); }
        if (s->in_transmit == 0 && fifo_char_get_used (&s->fifo)) {
            s->f_transmit (s);
        }
        { exit_critical (); }
    }
}

void writer_error_callback (generic_writer_t *s) { s->error_count++; }

bool writer_clean (const generic_writer_t *s) {
    { return ((fifo_char_get_used (&s->fifo) == 0 && s->in_transmit == 0)); }
}

bool writer_half_clean (const generic_writer_t *s) {
    { return (fifo_char_get_used (&s->fifo) < fifo_char_get_size (&s->fifo) / 2); }
}
