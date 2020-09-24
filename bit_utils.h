#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MASK_0_BITS    (uint32_t)0x00000000U
#define MASK_1_BITS    (uint32_t)0x00000001U
#define MASK_2_BITS    (uint32_t)0x00000003U
#define MASK_3_BITS    (uint32_t)0x00000007U
#define MASK_4_BITS    (uint32_t)0x0000000FU
#define MASK_6_BITS    (uint32_t)0x0000003FU
#define MASK_7_BITS    (uint32_t)0x0000007FU
#define MASK_8_BITS    (uint32_t)0x000000FFU
#define MASK_9_BITS    (uint32_t)0x000001FFU
#define MASK_10_BITS   (uint32_t)0x000003FFU
#define MASK_11_BITS   (uint32_t)0x000007FFU
#define MASK_12_BITS   (uint32_t)0x00000FFFU
#define MASK_13_BITS   (uint32_t)0x00001FFFU
#define MASK_16_BITS   (uint32_t)0x0000FFFFU
#define MASK_17_BITS   (uint32_t)0x0001FFFFU
#define MASK_18_BITS   (uint32_t)0x0003FFFFU
#define MASK_20_BITS   (uint32_t)0x000FFFFFU
#define MASK_21_BITS   (uint32_t)0x001FFFFFU
#define MASK_23_BITS   (uint32_t)0x007FFFFFU
#define MASK_24_BITS   (uint32_t)0x00FFFFFFU
#define MASK_25_BITS   (uint32_t)0x01FFFFFFU

bool is_power_of_two (uint32_t const val);
bool is_parity_odd (uint32_t const inVal);
uint8_t count_set_bits (uint32_t const inVal32bit);

#ifdef __cplusplus
}
#endif

#endif /* UTILITY_H_ */
