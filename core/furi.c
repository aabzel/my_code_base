#include <stdint.h>

#include "furi.h"
#include "applications.h"

// for testing purpose
uint32_t exitcode = 0;

void set_exitcode(uint32_t _exitcode) {
    exitcode = _exitcode;
}

void furi_init() {



}

int systemd() {
    furi_init();

    printf("\n=== Bye from Flipper Zero! ===\n\n");
    return (int)exitcode;
}