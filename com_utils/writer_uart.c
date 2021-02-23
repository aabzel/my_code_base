#include "writer_uart.h"

#ifdef SPC5
#include "uart_driver_spc5.h"
#include "board.h"
#ifdef ENABLE_CORE0
#include "multicore.h"
#endif
#endif

#ifdef SPC5
#define MAX_UART_BLOCK 4
#else
#define MAX_UART_BLOCK 100
#endif

void uart_writer_transmit (struct generic_writer_s* s) {
    const char* data;
    enter_critical ();

    s->total_char_count += s->in_transmit;
    if (s->in_transmit) {
        fifo_char_free(&s->fifo, s->in_transmit);
    }
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
    data = fifo_char_get_contiguous_block(&s->fifo, (fifo_index_t*)&s->in_transmit);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    if (s->in_transmit) {
        if (s->in_transmit > MAX_UART_BLOCK) {
            s->in_transmit = MAX_UART_BLOCK;
        }
#ifdef CUBEMX
        {
            UART_HandleTypeDef *huart=(UART_HandleTypeDef *)s->instance;
            HAL_UART_Transmit_IT (huart, (uint8_t*)data, s->in_transmit);
        }
#endif
#ifdef SPC5
        {
            linflex_t* linflexp = (linflex_t*) s->instance;
            linflexp->UARTCR.B.TXEN = 1;
            linflexp->UARTCR.B.TDFL = s->in_transmit - 1;
            linflexp->BDRL.B.DATA0 = *(const uint8_t*) data;
            if (s->in_transmit > 1) {
                linflexp->BDRL.B.DATA1 = *(const uint8_t*) (data + 1);
                if (s->in_transmit > 2) {
                    linflexp->BDRL.B.DATA2 = *(const uint8_t*) (data + 2);
                    if (s->in_transmit > 3) {
                        linflexp->BDRL.B.DATA3 = *(const uint8_t*) (data + 3);
                    }
                }
            }
        }
#endif
    } else {
#ifdef SPC5
        {
            linflex_t* linflexp = (linflex_t*) s->instance;
            linflexp->UARTCR.B.TXEN = 0;
        }
#endif
    }
    exit_critical ();
}
