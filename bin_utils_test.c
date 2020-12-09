#include "bin_utils_test.h"

#include <stdint.h>
#include <stdio.h>

#include "bin_utils.h"
#include "uTests.h"

static bool test_binary_gap (void) {
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

static bool test_binary_swap (void) {
    EXPECT_EQ (swap_bits (0), 0);
    EXPECT_EQ (swap_bits (1), 0x8000000000000000);
    EXPECT_EQ (swap_bits (0x8000000000000000), 1);
    EXPECT_EQ (swap_bits (0xF), 0xF000000000000000);
    EXPECT_EQ (swap_bits (0xAAAAAAAAAAAAAAAA), 0x5555555555555555);
    EXPECT_EQ (swap_bits (0xFFFFFFFFFFFFFFFF), 0xFFFFFFFFFFFFFFFF);

    return true;
}

static bool test_swap_bits_u8_slow (void) {
    EXPECT_EQ (swap_bits_u8_slow (0), 0);
    EXPECT_EQ (swap_bits_u8_slow (0x01), 0x80);
    EXPECT_EQ (swap_bits_u8_slow (0x80), 0x01);
    EXPECT_EQ (swap_bits_u8_slow (0x0F), 0xF0);
    EXPECT_EQ (swap_bits_u8_slow (0xAA), 0x55);
    EXPECT_EQ (swap_bits_u8_slow (0xFF), 0xFF);
    return true;
}

static bool test_binary_swap_u8 (void) {
    EXPECT_EQ (swap_bits_u8 (0), 0);
    EXPECT_EQ (swap_bits_u8 (0x01), 0x80);
    EXPECT_EQ (swap_bits_u8 (0x80), 0x01);
    EXPECT_EQ (swap_bits_u8 (0x0F), 0xF0);
    EXPECT_EQ (swap_bits_u8 (0xAA), 0x55);
    EXPECT_EQ (swap_bits_u8 (0xFF), 0xFF);
    return true;
}

static bool test_binary_swap_u8_all (void) {
    for (int val = 0; val <= 0xFF; val++) {
        uint8_t in_val = (uint8_t)val;
        EXPECT_EQ (swap_bits_u8 (in_val), swap_bits_u8_slow (in_val));
        EXPECT_EQ (reverse_bits_u8_fast (in_val), swap_bits_u8_slow (in_val));
    }
    return true;
}

static bool test_reverse_dec (void) {
    printf ("\n%s()", __FUNCTION__);
    EXPECT_EQ (sizeof (int64_t), 8);
    EXPECT_EQ (powi (10, 9), 1000000000);
    EXPECT_EQ (powi (10, 8), 100000000);
    EXPECT_EQ (powi (10, 0), 1);
    EXPECT_EQ (powi (10, 1), 10);
    EXPECT_EQ (powi (10, 2), 100);
    EXPECT_EQ (powi (10, 3), 1000);

    EXPECT_EQ (reverse_dec (1563847412), 0);
    EXPECT_EQ (reverse_dec (-2147483648), 0);
    EXPECT_EQ (reverse_dec (1534236469), 0);
    EXPECT_EQ (reverse_dec (1), 1);
    EXPECT_EQ (reverse_dec (-123), -321);
    EXPECT_EQ (reverse_dec (0), 0);
    EXPECT_EQ (reverse_dec (123), 321);
    EXPECT_EQ (reverse_dec (120), 21);
    return true;
}

bool test_bin_utils (void) {
    EXPECT_TRUE (test_binary_swap_u8_all ());
    EXPECT_TRUE (test_swap_bits_u8_slow ());
    EXPECT_TRUE (test_binary_swap_u8 ());
    EXPECT_TRUE (test_reverse_dec ());
    EXPECT_TRUE (test_binary_swap ());
    EXPECT_TRUE (test_binary_gap ());
    return true;
}
