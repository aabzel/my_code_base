#include "test_byte_utils.h"

#include <stdio.h>

#include "byte_utils.h"
#include "uTests.h"

// 1010_1010  0101_0101   0xAA 0x55
static bool test_reverse_byte_order (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_EQ (0x2750485344C0CC78, reverse_byte_order_uint64 (0x78ccc04453485027));
    EXPECT_EQ (0x0807060504030201, reverse_byte_order_uint64 (0x0102030405060708));
    return true;
}

bool test_byte_utils (void) {
    printf ("\n[d] %s()", __FUNCTION__);

    EXPECT_TRUE (test_reverse_byte_order ());
    printf ("\n[d] %s() done", __FUNCTION__);
    return true;
}
