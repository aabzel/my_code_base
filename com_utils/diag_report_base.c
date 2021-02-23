#include "diag_report.h"
#include "rx_utils.h"

__attribute__((weak)) bool diag_report(uint8_t page, ostream_t* stream) {
    (void)page;
    (void)stream;
    return false;
}

__attribute__((weak)) bool diag_page_index(ostream_t* stream) {
    (void)stream;
    return true;
}

