#include "sys.h"

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "pal_utils.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "stm32f1xx_hal.h"

void print_sysinfo (void) {
    rx_printf ("RAM: 8 KB" CRLF);
    rx_printf ("Flash: 128 KB" CRLF);
    rx_printf ("Pins: 64 " CRLF);
    rx_printf ("Stack addr: %08x...%08x %u" CRLF, 0x20001FFF - 0x500, 0x20001FFF, 0x500);
    rx_printf ("RAM start addr: 0x20000000 " CRLF);
    rx_printf ("Flash start addr: 0x08000000 " CRLF);
    rx_printf ("top-of-stack: %x " CRLF, *((uint32_t *)0x00000000));
    rx_printf ("boot memory start: %x " CRLF, *((uint32_t *)0x00000004));
    // rx_printf("main %p", main);
    // rx_printf("Stack size: %u " CRLF, _Min_Stack_Size);
    print_vector_table ();
}

void print_vector_table (void) {
    rx_printf (CRLF "Vector table" CRLF);
    rx_printf ("Reset: %x " CRLF, *((uint32_t *)0x00000004));
    rx_printf ("Clock Security System: %x " CRLF, *((uint32_t *)0x00000008));
    rx_printf ("All class of fault: %x " CRLF, *((uint32_t *)0x0000000C));
    rx_printf ("Memory management: %x " CRLF, *((uint32_t *)0x00000010));
    rx_printf ("Pre-fetch fault: %x " CRLF, *((uint32_t *)0x00000014));
    rx_printf ("Undefined instruction: %x " CRLF, *((uint32_t *)0x00000018));
    rx_printf ("USART1 global interrupt: %x " CRLF, *((uint32_t *)0x000000D4));
    rx_printf ("USART2 global interrupt: %x " CRLF, *((uint32_t *)0x000000D8));
}


void Error_Handler (void) {
    __disable_irq ();
    while (1) {
    }
}
