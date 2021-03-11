#include "test_bin_utils.h"

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



static bool test_extract_sub_val(void) {
    printf ("\n[d] %s()", __FUNCTION__);
    uint32_t sub_val;

    uint8_t reg_array_blob_40bit[]={0xfe,0x27,0x50,0x48,0x53};
    sub_val = eject_value_from_array(reg_array_blob_40bit, 5, 35, 4);
    EXPECT_EQ (0xe2750485, sub_val);

    //        fe2_75048534_4
    uint8_t reg_array_blob[]={0xfe,0x27,0x50,0x48,0x53,0x44};
    //8*6 = 48 bit

    sub_val = eject_value_from_array(reg_array_blob, 6, 35, 4);
    EXPECT_EQ (0x75048534, sub_val);

    sub_val = eject_value_from_array(reg_array_blob, 6, 7+4, 0+4);
    EXPECT_EQ (0x34, sub_val);

    sub_val= eject_value_from_array(reg_array_blob, 6, 7, 0);
    EXPECT_EQ (0x44, sub_val);

    printf ("\n[d] %s() end", __FUNCTION__);
    return true;
}


bool test_extract_subval_utils16 (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    EXPECT_EQ (0x0034, extract_subval_from_16bit (0x5344, 11, 4));
    EXPECT_EQ (0x000f, extract_subval_from_16bit (0xF000, 15, 12));
    EXPECT_EQ (0x000f, extract_subval_from_16bit (0x0F00, 11, 8));
    EXPECT_EQ (0x000f, extract_subval_from_16bit (0x000F, 3, 0));
    return true;
}



bool test_bin_utils (void) {
    printf ("\n[d] %s()", __FUNCTION__);

    EXPECT_TRUE (test_extract_subval_utils16 ());
    EXPECT_TRUE (test_extract_sub_val ());

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
    EXPECT_EQ (0x0001, generate_16bit_left_mask (1));
    EXPECT_EQ (0x0003, generate_16bit_left_mask (2));
    EXPECT_EQ (0x000f, generate_16bit_left_mask (4));
    EXPECT_EQ (0x001f, generate_16bit_left_mask (5));
    EXPECT_EQ (0x000f, extract_subval_from_16bit (0xF000, 15, 12));
    EXPECT_EQ (0x000f, extract_subval_from_16bit (0x0F00, 11, 8));
    EXPECT_EQ (0x000f, extract_subval_from_16bit (0x000F, 3, 0));
    EXPECT_EQ (0x80000000, reverseBits32 (0x00000001));
    EXPECT_EQ (0xF0000000, reverseBits32 (0x0000000F));
    EXPECT_EQ (3, hamming_weight (56));

    return true;
}
