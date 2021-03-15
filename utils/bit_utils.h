#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MASK_0_BITS (uint32_t)0x00000000U
#define MASK_1_BITS (uint32_t)0x00000001U
#define MASK_2_BITS (uint32_t)0x00000003U
#define MASK_3_BITS (uint32_t)0x00000007U
#define MASK_4_BITS (uint32_t)0x0000000FU
#define MASK_5_BITS (uint32_t)0x0000001FU
#define MASK_6_BITS (uint32_t)0x0000003FU
#define MASK_7_BITS (uint32_t)0x0000007FU
#define MASK_8_BITS (uint32_t)0x000000FFU
#define MASK_9_BITS (uint32_t)0x000001FFU
#define MASK_10_BITS (uint32_t)0x000003FFU
#define MASK_11_BITS (uint32_t)0x000007FFU
#define MASK_12_BITS (uint32_t)0x00000FFFU
#define MASK_13_BITS (uint32_t)0x00001FFFU
#define MASK_14_BITS (uint32_t)0x00003FFFU
#define MASK_15_BITS (uint32_t)0x00007FFFU
#define MASK_16_BITS (uint32_t)0x0000FFFFU
#define MASK_17_BITS (uint32_t)0x0001FFFFU
#define MASK_18_BITS (uint32_t)0x0003FFFFU
#define MASK_19_BITS (uint32_t)0x0007FFFFU
#define MASK_20_BITS (uint32_t)0x000FFFFFU
#define MASK_21_BITS (uint32_t)0x001FFFFFU
#define MASK_22_BITS (uint32_t)0x003FFFFFU
#define MASK_23_BITS (uint32_t)0x007FFFFFU
#define MASK_24_BITS (uint32_t)0x00FFFFFFU
#define MASK_25_BITS (uint32_t)0x01FFFFFFU

int missingNumber (int *nums, int numsSize);
int hammingDistance (int x, int y);
uint8_t swap_bits_odd_even_fast (uint8_t x);
uint8_t swap_bits_odd_even (uint8_t val);
uint8_t generate_8bit_left_mask (uint8_t bitlen);
uint16_t generate_16bit_left_mask (uint8_t bitlen);
uint32_t generate_32bit_left_mask (uint8_t bitlen);
uint64_t generate_64bit_left_mask (uint8_t bitlen);
uint16_t calc_16_mask (uint8_t num_of_bit);
uint32_t eject_value_from_array (uint8_t *reg_array_blob, uint16_t reg_blob_len, uint16_t maxBit, uint16_t minBit);
bool is_power_of_two (uint32_t const val);
bool is_parity_odd (uint32_t const inVal);
uint8_t count_set_bits (uint32_t const inVal32bit);
int missingNumber_sum (int *nums, int numsSize);

uint8_t extract_subval_from_8bit (uint8_t inVal, uint8_t maxBit, uint8_t minBit);
uint16_t extract_subval_from_16bit (uint16_t inVal, uint8_t maxBit, uint8_t minBit);
uint32_t extract_subval_from_32bit (uint32_t inVal, uint8_t maxBit, uint8_t minBit);

#ifdef __cplusplus
}
#endif

#endif /* BIT_UTILS_H */
