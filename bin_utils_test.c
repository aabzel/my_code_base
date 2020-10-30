#include "bin_utils_test.h"

#include <stdio.h>

#include "bin_utils.h"
#include "uTests.h"

bool test_binary_gap (void) {
    int gap;
    gap = binary_gap (529); // 10 0001 0001
    if (4 != gap) {
        printf ("\ngap %u 2", gap);
        return false;
    }
    gap = binary_gap (1041);
    if (5 != gap) {
        printf ("\ngap %u 5", gap);
        return false;
    }
    gap = binary_gap (9);
    if (2 != gap) {
        printf ("\ngap %u 2", gap);
        return false;
    }
    gap = binary_gap (20);
    if (1 != gap) {
        printf ("\ngap %u 1", gap);
        return false;
    }
    return true;
}

bool test_binary_swap (void) {
	EXPECT_EQ(swap_bits(0), 0);
	EXPECT_EQ(swap_bits(1), 0x8000000000000000);
	EXPECT_EQ(swap_bits(0x8000000000000000), 1);
	EXPECT_EQ(swap_bits(0xF), 0xF000000000000000);
	EXPECT_EQ(swap_bits(0xAAAAAAAAAAAAAAAA), 0x5555555555555555);
	EXPECT_EQ(swap_bits(0xFFFFFFFFFFFFFFFF), 0xFFFFFFFFFFFFFFFF);

    return true;
}

bool test_bin_utils (void) {
	EXPECT_TRUE( test_binary_swap ());
	EXPECT_TRUE( test_binary_gap ());
	return true;
}
