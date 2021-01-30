#include "check.h"
//#include "api-hal-task.h"
#include <stdio.h>

void __furi_abort(void);

// TODO printf doesnt work in ISR context
void __furi_check(void) {
    printf("assertion failed in release mode, switch to debug mode to see full assert info");
    __furi_abort();
}

// TODO printf doesnt work in ISR context
void __furi_check_debug(const char* file, int line, const char* function, const char* condition) {
    printf(
        "assertion \"%s\" failed: file \"%s\", line %d%s%s",
        condition,
        file,
        line,
        function ? ", function: " : "",
        function ? function : "");
 
    __furi_abort();
}

void __furi_abort(void) {
    static int cnt =0;

    printf("\n %s()",__FUNCTION__);

    cnt++;
}
