#include <stdint.h>
#include "log.h"
#include "rx_uart.h"

#ifndef BOOTLOADER
/* The prototype shows it is a naked function - in effect this is just an
 assembly function. */

void HardFault_Handler(void) __attribute__( ( naked ) );
void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress);

/* The fault handler implementation calls a function called
 prvGetRegistersFromStack(). */

void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress) {
    /* These are volatile to try and prevent the compiler/linker optimizing them
     away as the variables never actually get used.  If the debugger won't show the
     values of the variables, make them global my moving their declaration outside
     of this function. */

//    r0 = pulFaultStackAddress [0];
//    r1 = pulFaultStackAddress [1];
//    r2 = pulFaultStackAddress [2];
//    r3 = pulFaultStackAddress [3];
//
//    r12 = pulFaultStackAddress [4];
    uint32_t lr = pulFaultStackAddress [5];
    uint32_t pc = pulFaultStackAddress [6];
    uint32_t psr = pulFaultStackAddress [7];
    (void)lr;
    (void)pc;
    (void)psr;
    LOG_CRITICAL(SYS,"Hard fault  pc=0x%lX, lr=0x%lX, psr=0x%lX", pc, lr, psr);
    /* When the following line is hit, the variables contain the register values. */
    for (;;)
        ;
}

void HardFault_Handler(void) {
    __asm volatile
    (
            " tst lr, #4                                                \n"
            " ite eq                                                    \n"
            " mrseq r0, msp                                             \n"
            " mrsne r0, psp                                             \n"
            " ldr r1, [r0, #24]                                         \n"
            " ldr r2, handler2_address_const                            \n"
            " bx r2                                                     \n"
            " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}

#endif //BOOTLOADER
