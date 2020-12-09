#ifndef __BINARY_UTILS_H
#define __BINARY_UTILS_H

#include <stdint.h>

#define DEBUG

int binary_gap (int N);
uint64_t swap_bits (uint64_t in_val);
int reverse_dec (int x);
int64_t powi (int base, int exp);
uint8_t swap_bits_u8 (uint8_t in);
uint8_t swap_bits_u8_slow (uint8_t in_val);
uint8_t reverse_bits_u8_fast (uint8_t n);

#endif /* __BINARY_UTILS_H */
