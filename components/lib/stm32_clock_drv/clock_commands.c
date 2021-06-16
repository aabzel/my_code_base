#include "clock_commands.h"

#include <inttypes.h>

#include "bit_utils.h"
#include "convert.h"
#include "io_utils.h"
#include "log.h"
#include "ostream.h"
#include "stm32f4xx.h"

bool clock_diag_command(int32_t argc, char* argv[]) {
    uint32_t rcc_cr = RCC->CR;
    if (BIT_0 == (BIT_0 & rcc_cr)) {
        io_printf("Internal high-speed clock enable" CRLF);
    } else {
        io_printf("Internal high-speed clock disable" CRLF);
    }
    if (BIT_16 == (BIT_16 & rcc_cr)) {
        io_printf("HSE oscillator ON" CRLF);
    } else {
        io_printf("HSE oscillator OFF" CRLF);
    }
    if (BIT_24 == (BIT_24 & rcc_cr)) {
        io_printf("PLL ON" CRLF);
    } else {
        io_printf("PLL OFF" CRLF);
    }
    uint32_t pll_configuration_register = RCC->PLLCFGR;
    uint32_t pllr = extract_subval_from_32bit(pll_configuration_register, 30, 28);
    io_printf("pllr %u" CRLF, pllr);

    uint32_t pllq = extract_subval_from_32bit(pll_configuration_register, 27, 24);
    io_printf("pllq %u" CRLF, pllq);
    if (BIT_22 == (BIT_22 & pll_configuration_register)) {
        io_printf("HSE oscillator clock selected as PLL" CRLF);
    } else {
        io_printf("HSI clock selected as PLL" CRLF);
    }
    uint32_t pllp = extract_subval_from_32bit(pll_configuration_register, 17, 16);
    io_printf("pllp %u" CRLF, pllp);

    uint32_t plln = extract_subval_from_32bit(pll_configuration_register, 14, 6);
    io_printf("plln %u" CRLF, plln);

    uint32_t pllm = extract_subval_from_32bit(pll_configuration_register, 5, 0);
    io_printf("pllm %u" CRLF, pllm);

    uint32_t clock_configuration_register = RCC->CFGR;
    uint32_t ppre2 =
        extract_subval_from_32bit(clock_configuration_register, 15, 13);
    io_printf("PPRE2 %u" CRLF, ppre2);

    uint32_t ppre1 =
        extract_subval_from_32bit(clock_configuration_register, 12, 10);
    io_printf("PPRE1 %u" CRLF, ppre1);

    uint32_t hpre = extract_subval_from_32bit(clock_configuration_register, 7, 4);
    io_printf("HPRE %u" CRLF, hpre);

    uint32_t sws = extract_subval_from_32bit(clock_configuration_register, 3, 2);
    io_printf("SWS %u %s" CRLF, sws);

    uint32_t rcc_apb1enr = RCC->APB1ENR;
    io_printf("RCC_APB1ENR 0x%08x 0b%s" CRLF, rcc_apb1enr,
              utoa_bin32(rcc_apb1enr));

    uint32_t rcc_apb2enr = RCC->APB2ENR;
    io_printf("RCC_APB2ENR 0x%08x 0b%s" CRLF, rcc_apb2enr,
              utoa_bin32(rcc_apb2enr));

    io_printf(CRLF);
    return false;
}
