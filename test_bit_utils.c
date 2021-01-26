#include "test_bit_utils.h"

#include "bit_utils.h"
#include "uTests.h"

// 1010_1010  0101_0101   0xAA 0x55
static bool test_swap_bits_odd_even (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_EQ (0xF0, swap_bits_odd_even (0xF0));
    EXPECT_EQ (0x02, swap_bits_odd_even (0x01));
    EXPECT_EQ (0x01, swap_bits_odd_even (0x02));
    EXPECT_EQ (0xAA, swap_bits_odd_even (0x55));
    EXPECT_EQ (0x55, swap_bits_odd_even (0xAA));
    EXPECT_EQ (43, swap_bits_odd_even (23));

    for (int i = 0; i < 255; i++) {
        EXPECT_EQ (swap_bits_odd_even_fast (i), swap_bits_odd_even (i));
    }
    return true;
}

static bool test_missing_number (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    int nums1[3] = {3, 0, 1};
    EXPECT_EQ (2, missingNumber (nums1, 3));
    int nums2[2] = {0, 1};
    EXPECT_EQ (2, missingNumber (nums2, 2));
    int nums3[9] = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    EXPECT_EQ (8, missingNumber (nums3, 9));
    int nums4[1] = {0};
    EXPECT_EQ (1, missingNumber (nums4, 1));

    EXPECT_EQ (missingNumber_sum (nums3, 9), missingNumber (nums3, 9));
    EXPECT_EQ (missingNumber_sum (nums4, 1), missingNumber (nums4, 1));

    return true;
}

bool test_bit_utils (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_TRUE (test_missing_number ());
    EXPECT_EQ (2, hammingDistance (1, 4));

    EXPECT_TRUE (test_swap_bits_odd_even ());
    EXPECT_EQ (MASK_0_BITS, calc_16_mask (0));
    EXPECT_EQ (MASK_1_BITS, calc_16_mask (1));
    EXPECT_EQ (MASK_2_BITS, calc_16_mask (2));
    EXPECT_EQ (MASK_3_BITS, calc_16_mask (3));
    EXPECT_EQ (MASK_4_BITS, calc_16_mask (4));
    EXPECT_EQ (MASK_5_BITS, calc_16_mask (5));
    EXPECT_EQ (MASK_6_BITS, calc_16_mask (6));
    EXPECT_EQ (MASK_7_BITS, calc_16_mask (7));
    EXPECT_EQ (MASK_8_BITS, calc_16_mask (8));
    EXPECT_EQ (MASK_9_BITS, calc_16_mask (9));
    EXPECT_EQ (MASK_10_BITS, calc_16_mask (10));
    EXPECT_EQ (MASK_11_BITS, calc_16_mask (11));
    EXPECT_EQ (MASK_12_BITS, calc_16_mask (12));
    EXPECT_EQ (MASK_13_BITS, calc_16_mask (13));
    EXPECT_EQ (MASK_14_BITS, calc_16_mask (14));
    EXPECT_EQ (MASK_15_BITS, calc_16_mask (15));
    EXPECT_EQ (MASK_16_BITS, calc_16_mask (16));

    uint32_t reg16bitVal;
    reg16bitVal = generate_16bit_left_mask (1);
    if (0x0001 != reg16bitVal) {
        return GENERATE_BIT_MASK_ERROR;
    }
    reg16bitVal = generate_16bit_left_mask (2);
    if (0x0003 != reg16bitVal) {
        return GENERATE_BIT_MASK_ERROR;
    }
    reg16bitVal = generate_16bit_left_mask (4);
    if (0x000f != reg16bitVal) {
        return GENERATE_BIT_MASK_ERROR;
    }
    reg16bitVal = generate_16bit_left_mask (5);
    if (0x001f != reg16bitVal) {
        return GENERATE_BIT_MASK_ERROR;
    }
    reg16bitVal = extract_subval_from_16bit (0xF000, 15, 12);
    if (0x000f != reg16bitVal) {
        return EXTRACT_BITS_ERROR;
    }

    // 0x0f00   0000 1111 0000 0000
    reg16bitVal = extract_subval_from_16bit (0x0F00, 11, 8);
    if (0x000f != reg16bitVal) {
        return EXTRACT_BITS_ERROR;
    }
    reg16bitVal = extract_subval_from_16bit (0x000F, 3, 0);
    if (0x000f != reg16bitVal) {
        return EXTRACT_BITS_ERROR;
    }

    uint32_t n;
    n = reverseBits32 (0x00000001);
    if (0x80000000 != n) {
        return REV_BIT_ERROR;
    }
    n = reverseBits32 (0x0000000F);
    if (0xF0000000 != n) {
        return REV_BIT_ERROR;
    }

    uint8_t numSetBit = hamming_weight (56);
    if (3 != numSetBit) {
        printf ("\n numSetBit:%d\n", numSetBit);
        return ONE_BIT_ERROR;
    }

    return true;
}
