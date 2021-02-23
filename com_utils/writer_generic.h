#ifndef WRITER_GENERIC_H_
#define WRITER_GENERIC_H_
#include <stdbool.h>
#include <stdint.h>
#include "fifo_char_buffer.h"
#include "oprintf.h"

struct generic_writer_s;

typedef struct generic_writer_s {
    ostream_t s;
    volatile fifo_index_t in_transmit;
    volatile int64_t lost_char_count;
    volatile int64_t total_char_count;
    volatile int64_t error_count;
    fifo_char_t fifo;
    void (*f_transmit) (struct generic_writer_s* writer);
    volatile void* instance;
} generic_writer_t;

void writer_tx_callback(generic_writer_t* s);
void writer_error_callback(generic_writer_t* s);
void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);
bool writer_clean(const generic_writer_t* s);
bool writer_half_clean(const generic_writer_t* s);

#endif /* WRITER_GENERIC_H_ */
