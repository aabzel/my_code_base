#include "writer_uart.h"

#define MAX_UART_BLOCK 100

void uart_writer_transmit(struct generic_writer_s *s) {
	const char *data = NULL;
	enter_critical();

	//s->total_char_count += s->in_transmit;
	if (s->in_transmit) {
		fifo_char_free(&s->fifo, s->in_transmit);
	}
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
	data = fifo_char_get_contiguous_block(&s->fifo,
			(fifo_index_t*) &s->in_transmit);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
	if (s->in_transmit) {
		s->total_char_count += s->in_transmit;
		if (s->in_transmit > MAX_UART_BLOCK) {
			s->in_transmit = MAX_UART_BLOCK;
		}
#ifdef CUBEMX

			UART_HandleTypeDef *huart = (UART_HandleTypeDef*) s->instance;
			HAL_UART_Transmit_IT(huart, (uint8_t*) data, s->in_transmit);

#endif
	}
	exit_critical();
}
