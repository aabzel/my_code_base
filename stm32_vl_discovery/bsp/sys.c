#include "sys.h"

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "none_blocking_pause.h"
#include "pal_utils.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "stm32f1xx_hal.h"

bool find_addr_by_val(uint16_t byte_num, uint32_t val, uint32_t start_addr,
		uint32_t end_addr) {
	bool res = false;
	uint32_t cnt=0;
	if (1 == byte_num) {
		uint8_t value = (uint8_t) val;
		uint8_t *ptr = (uint8_t*) start_addr;
		for (ptr = (uint8_t*) start_addr; ptr < ((uint8_t*) end_addr); ptr++) {
			if ((*ptr) == value) {
				rx_printf("%u: addr *(0x%p): 0x%x/%u" CRLF,cnt, ptr, value, value);
				res = true;
			}
			wait_in_loop_ms(2);
		}
	}

	if (2 == byte_num) {
		uint16_t value = (uint16_t) val;
		uint16_t *ptr = (uint16_t*) start_addr;
		for (ptr = (uint16_t*) start_addr; ptr < ((uint16_t*) end_addr);
				ptr++) {
			if ((*ptr) == value) {
				rx_printf("%u: addr *(0x%p): 0x%x/%u" CRLF,cnt, ptr, value, value);
				res = true;
			}
			wait_in_loop_ms(2);
		}
	}

	if (4 == byte_num) {
		uint32_t value = (uint32_t) val;
		uint32_t *ptr = (uint32_t*) start_addr;
		for (ptr = (uint32_t*) start_addr; ptr < ((uint32_t*) end_addr);
				ptr++) {
			if ((*ptr) == value) {
				rx_printf("%u: addr *(0x%p): 0x%x/%u" CRLF,cnt, ptr, value, value);
				res = true;
			}
			wait_in_loop_ms(2);
		}
	}
	return res;
}

void print_sysinfo(void) {
	rx_printf("RAM: 8 KB" CRLF);
	rx_printf("Flash: 128 KB" CRLF);
	rx_printf("Pins: 64 " CRLF);
	rx_printf("Stack addr: %08x...%08x %u" CRLF, 0x20001FFF - 0x500, 0x20001FFF,
			0x500);
	rx_printf("RAM addr:   0x%08x....0x%08x " CRLF, RAM_START, RAM_END);
	rx_printf("Flash addr: 0x%08x....0x%08x " CRLF, ROM_START, ROM_END);
	rx_printf("top-of-stack: %x " CRLF, *((uint32_t*) 0x00000000));
	rx_printf("boot memory start: %x " CRLF, *((uint32_t*) 0x00000004));
	// rx_printf("main %p", main);
	// rx_printf("Stack size: %u " CRLF, _Min_Stack_Size);
	print_vector_table();
}

void print_vector_table(void) {
	rx_printf(CRLF "Vector table" CRLF);
	rx_printf("Reset: %x " CRLF, *((uint32_t*) 0x00000004));
	rx_printf("Clock Security System: %x " CRLF, *((uint32_t*) 0x00000008));
	rx_printf("All class of fault: %x " CRLF, *((uint32_t*) 0x0000000C));
	rx_printf("Memory management: %x " CRLF, *((uint32_t*) 0x00000010));
	rx_printf("Pre-fetch fault: %x " CRLF, *((uint32_t*) 0x00000014));
	rx_printf("Undefined instruction: %x " CRLF, *((uint32_t*) 0x00000018));
	rx_printf("USART1 global interrupt: %x " CRLF, *((uint32_t*) 0x000000D4));
	rx_printf("USART2 global interrupt: %x " CRLF, *((uint32_t*) 0x000000D8));
}

void Error_Handler(void) {
	__disable_irq();
	while (1) {
	}
}
