#include "dsol_tasks.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uTests.h"

uint8_t g_value = 6;

volatile uint8_t *const reg = (uint8_t *)&g_value; // регистр блока периферии
// ожидание появления флага
void IO_Wait_For_Reg_Change (uint8_t bitmask) {
    uint8_t orig = (*reg) & bitmask;
    while (orig == ((*reg) & bitmask)) { /* ничего не делать */
        ;
    }
}

bool test_switch (int x) {
    printf ("\n [d] %s()", __FUNCTION__);
    switch (x) {
    case 1:
    case 2:
        printf ("\n [d] %d", 2);
    case 15:
        printf ("\n [d] %d", 15);
        break;
    case 13:
    case 22:
        printf ("\n [d] %d", 22);
        break;
    case 42:
    default:
        printf ("\n [d] dflt");
        break;
    }
    return true;
}

bool test_dsol (void) {
    printf ("\n [d] %s()", __FUNCTION__);
    EXPECT_EQ (12, MUL (1 + 2, 2 + 2));
    EXPECT_EQ (4400, MUL (55, 40 + 40));
    EXPECT_EQ (604800, SECONDS_PER_WEEK);

    uint8_t a;
    a |= (1 << 3);  // set bit
    a &= ~(1 << 3); // reset bit

    test_switch (1);

    uint8_t *ptr = NULL;
    printf ("\n [d] sizeof (ptr) %d ", sizeof (ptr));
    EXPECT_EQ (4, sizeof (ptr));

    printf ("\n [d] %s() done", __FUNCTION__);

    return true;
}
