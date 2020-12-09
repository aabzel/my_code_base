#include "check_address.h"

#include "uTests.h"
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <process.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

bool is_mapped (int *ptr, int len) {
    if (NULL == ptr) {
        return false;
    }
    bool valid = true;
    FILE *output = NULL;
    output = fopen ("text.bin", "bw");
    if (NULL != output) {
        ssize_t stat = write (output, ptr, len);
        if (stat != len) {
            printf ("\n Error %d ", stat);
            printf (" errno [%d] ", errno);
            printf (" prt %p ", ptr);
            valid = false;
            if (EFAULT == errno) {
                printf ("\n EFAULT %p ", ptr);
            }
        } else {
            printf ("\n fine %d \n", stat);
            printf ("\n fine %d \n", stat);
            printf ("\n fine %d \n", stat);
        }
        fclose (output);
    }

    return valid;
}

int glo = 5;
bool test_is_mapped (void) {
    int x = 5;
    int *junk1 = (int *)0xF243526F;
    int *junk2 = (int *)0xFA43526F;
    int *junk0 = (int *)0;
    EXPECT_TRUE (is_mapped (&x, 4));
    EXPECT_TRUE (is_mapped (&glo, 4));
    EXPECT_FALSE (is_mapped (junk0, 1));
    EXPECT_FALSE (is_mapped (junk1, 1));
    EXPECT_FALSE (is_mapped (junk2, 1));

    return true;
}
