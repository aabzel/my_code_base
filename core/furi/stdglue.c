#include "stdglue.h"
//#include <main.h>

#include <stdio.h>
#include <string.h>

 
static ssize_t stdout_write(void* _cookie, const char* data, size_t size) {
    if(data ) {
    printf("\n[UART] %s",data);
        /*
         * This means that we should flush internal buffers.  Since we
         * don't we just return.  (Remember, "handle" == -1 means that all
         * handles should be flushed.)
         */
        return size;
    }

    return  0;
}

bool furi_stdglue_init() {
 
    return false;
}
