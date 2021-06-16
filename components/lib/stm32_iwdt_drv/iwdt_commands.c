#include "iwdt_commands.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#include "bit_utils.h"
#include "io_utils.h"
#include "iwdt_driver.h"

static bool diag_page_iwdt(void) {
    io_printf("Prescaler value: %u " CRLF, code2PscLUT[MASK_3BIT & (IWDG->PR)]);
    io_printf("reload value: %u " CRLF, MASK_12BIT & (IWDG->RLR));
    io_printf("status: %u " CRLF, MASK_2BIT & (IWDG->SR));
    io_printf("timeout: %f s " CRLF, iwdt_get_timeout());
    io_printf(CRLF);
    return true;
}

bool iwdt_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = diag_page_iwdt();
    }
    return res;
}