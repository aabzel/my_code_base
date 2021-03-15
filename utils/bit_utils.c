/*
 *
 * This is a file with some utility
 * functions mainly needed to boost readability in driver code.
 *
 * */
#include "bit_utils.h"

#ifdef X86
#include <stdio.h>
#endif

#include "byte_utils.h"

#define SKIP_ZER 0
#define CNT_ZER 1

/*
 * Function returns the number of set bits in binary  (Hamming weight)
 * representation of positive integer val
 * TODO: we can boost time of calculation by creating look up table for byte->am of bit
 *       It will reqire 512 byte of flash for 8bit value.
 *
 * */

uint8_t count_set_bits (uint32_t const inVal32bit) {
    uint8_t sum = 0;
    uint32_t val32bit = inVal32bit;
    while (0u != val32bit) {
        sum++;
        val32bit &= (val32bit - 1u);
    }
    return sum;
}

int proc_bit (int bit, int *cur_state, int *cnt) {
    int cur_gap = 0;
    if (SKIP_ZER == *cur_state) {
        if (0 == bit) {
            (*cur_state) = SKIP_ZER;
        }
        if (1 == bit) {
            (*cur_state) = CNT_ZER;
            (*cnt) = 0;
        }
    }
    if (CNT_ZER == *cur_state) {
        if (0 == bit) {
            (*cnt)++;
        }
        if (1 == bit) {
            cur_gap = *cnt;
            (*cnt) = 0;
        }
    }
    return cur_gap;
}

/*
 * This function converts a reflected binary
 * Gray code number to a binary number.
 * Each Gray code bit is exclusive-ored with all
 * more significant bits.
 */
unsigned int GrayToBinary (unsigned int num) {
    unsigned int mask = num >> 1;
    while (mask != 0) {
        num = num ^ mask;
        mask = mask >> 1;
    }
    return num;
}

/*
 * A more efficient version for Gray codes 32 bits or fewer
 * through the use of SWAR (SIMD within a register) techniques.
 * It implements a parallel prefix XOR function.  The assignment
 * statements can be in any order.
 *
 * This function can be adapted for longer Gray codes by adding steps.
 * A 4-bit variant changes a binary number (abcd)2 to (abcd)2 ^ (00ab)2,
 * then to (abcd)2 ^ (00ab)2 ^ (0abc)2 ^ (000a)2.
 */
unsigned int GrayToBinary32 (unsigned int num) {
    num = num ^ (num >> 16);
    num = num ^ (num >> 8);
    num = num ^ (num >> 4);
    num = num ^ (num >> 2);
    num = num ^ (num >> 1);
    return num;
}

#if 0
int binary_gap (int N) {
    int i = 0;
    // printf ("\n N %u\n", N);
    int max_gap = 0;
    int cur_cnt = 0;
    int cur_bit;
    int count_zero_mode = 0;
    for (i = 0; i < 32; i++) {
        cur_bit = N & (1 << i);
        if (0 < cur_bit) {
            //  printf ("cnt mode on i=%u\n", i);
            count_zero_mode = 1;
        }
        if (1 == count_zero_mode) {

            if (0 == cur_bit) {
                cur_cnt++;
                // printf ("+0 i=%u cnt %u\n", i, cur_cnt);
            } else {
                max_gap = max_int (max_gap, cur_cnt);
                cur_cnt = 0;
            }
        }
    }
    // write your code in C99 (gcc 6.2.0)
    return max_gap;
}
#endif

uint32_t reverseBits32 (uint32_t num) {
    uint32_t numOfbit = 4u * 8u;
    uint32_t reverseNum = 0u;
    uint32_t i;
    uint32_t temp;

    for (i = 0u; i < numOfbit; i++) {
        temp = (num & (1 << i));
        if (temp) {
            reverseNum |= (1 << ((numOfbit - 1) - i));
        }
    }
    return reverseNum;
}

uint64_t swap_bits (uint64_t in_val) {
    uint64_t out_val = 0U;
    for (uint16_t i = 0U; i < 64U; i++) {
        if ((((uint64_t)1U) << i) == ((((uint64_t)1U) << i) & in_val)) {
            out_val |= (((uint64_t)1) << (63U - i));
        }
    }

    return out_val;
}

uint32_t swap_bits_u32 (uint32_t in_val) {
    uint32_t out_val = 0U;
    for (uint32_t i = 0U; i < 32U; i++) {
        if ((((uint32_t)1U) << i) == ((((uint32_t)1U) << i) & in_val)) {
            out_val |= (((uint32_t)1) << (31U - i));
        }
    }

    return out_val;
}

int64_t powi (int base, int exp) {
    int64_t res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

uint8_t hamming_weight (uint32_t n) {
    uint8_t sum = 0;
    while (n != 0) {
#if DEBUG_HAMMING_WEIGHT
        printf ("\nn      :%s", uint32_to_bin_str (n));
        printf ("\n n-1   :%s", uint32_to_bin_str (n - 1));
        printf ("\nn&(n-1):%s", uint32_to_bin_str (n & (n - 1)));
        printf ("\n");
#endif
        sum++;
        n &= (n - 1);
    }
    return sum;
}

bool is_odd (int val) {
    bool res = false;
    if (val & 1) {
        res = true;
    }
    return res;
}

uint64_t extract_subval_from_64bit (uint64_t inVal, uint8_t maxBit, uint8_t minBit) {
    uint64_t outVal = 0;
    if ((minBit <= maxBit) && (maxBit <= 63) && (minBit <= 63)) {
        uint32_t mask = generate_64bit_left_mask (maxBit - minBit + 1);
        outVal = (inVal >> minBit);
        outVal = outVal & mask;
    }
    return outVal;
}

uint32_t extract_subval_from_32bit (uint32_t inVal, uint8_t maxBit, uint8_t minBit) {
    uint32_t outVal = 0;
    if ((minBit <= maxBit) && (maxBit <= 31) && (minBit <= 31)) {
        uint32_t mask = generate_32bit_left_mask (maxBit - minBit + 1);
        outVal = (inVal >> minBit);
        outVal = outVal & mask;
    }
    return outVal;
}

uint64_t generate_64bit_left_mask (uint8_t bitlen) {
    uint64_t mask = 0x00000000U;
    if (bitlen <= 64) {
        uint32_t i = 0U;
        for (i = 0U; i < bitlen; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

uint32_t generate_32bit_left_mask (uint8_t bitlen) {
    uint32_t mask = 0x00000000U;
    if (bitlen <= 32) {
        uint32_t i = 0U;
        for (i = 0U; i < bitlen; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

typedef union xUtmp64_bit_t {
    uint8_t ch[8];
    uint16_t wd[4];
    uint32_t dwd[2];
    uint64_t ldwd;
} UnTmp64_t;

// fe2_75048534_4
uint32_t eject_value_from_array (uint8_t *reg_array_blob, uint16_t reg_blob_len, uint16_t maxBit, uint16_t minBit) {
#ifdef X86
    printf ("\n[d] %s()", __FUNCTION__);
    print_mem_horisonal (stdout, reg_array_blob, reg_blob_len, false);
#endif
    // len*8....9876543210
    // maxBit from right
    // minBit from right
    uint32_t total_num_of_bit = 8 * reg_blob_len;
#ifdef DEBUG_BIT_UTILS
    printf ("\nbit width: %u bit", maxBit - minBit + 1);
    printf ("\n[%u....[%u....%u]..%u]", total_num_of_bit - 1, maxBit, minBit, 0);
#endif
    uint32_t sub_val = 0;
#ifdef DEBUG_BIT_UTILS
    printf ("\n total_num_of_bit %u bit %u byte", total_num_of_bit, reg_blob_len);
#endif
    if (maxBit < minBit) {
        return 0;
    }
    if (total_num_of_bit <= maxBit) {
        return 0;
    }
    uint16_t lbitPosMax = (total_num_of_bit - 1) - maxBit;
    uint16_t lbitPosMin = (total_num_of_bit - 1) - minBit;
#ifdef DEBUG_BIT_UTILS
    printf ("\n[%u....[%u....%u]..%u]", 0, lbitPosMax, lbitPosMin, total_num_of_bit - 1);
#endif
    uint16_t byteMax = lbitPosMax / 8;
    uint16_t byteMin = lbitPosMin / 8;
#ifdef DEBUG_BIT_UTILS
    printf ("\n  byteMaxBit: byte %u bit %u  ", byteMax, 7 - lbitPosMax % 8);
    printf ("\n  byteMinBit: byte %u bit %u  ", byteMin, 7 - lbitPosMin % 8);
#endif
    if (byteMax == byteMin) {
        sub_val = extract_subval_from_8bit (reg_array_blob[byteMin], 7 - lbitPosMax % 8, 7 - lbitPosMin % 8);
    } else {
        uint16_t byte_len = byteMin - byteMax + 1;
        if (3 == byte_len) {
            uint16_t max_bit = 7 - lbitPosMax % 8 + (byte_len - 1) * 8;
            uint16_t min_bit = 7 - lbitPosMin % 8;
            UnTmp64_t unVal;
            unVal.ldwd = 0;
            unVal.ch[0] = reg_array_blob[byteMax + 2];
            unVal.ch[1] = reg_array_blob[byteMax + 1];
            unVal.ch[2] = reg_array_blob[byteMax + 0];
            unVal.ch[3] = 0;
            unVal.ch[4] = 0;
            unVal.ch[5] = 0;
            unVal.ch[6] = 0;
            unVal.ch[7] = 0;
            unVal.ldwd = extract_subval_from_64bit (unVal.ldwd, max_bit, min_bit);
            sub_val = unVal.dwd[0];
        }
        if (5 == byte_len) {
            uint16_t max_bit = 7 - lbitPosMax % 8 + (byte_len - 1) * 8;
            uint16_t min_bit = 7 - lbitPosMin % 8;
            UnTmp64_t unVal;
            unVal.ldwd = 0;
            unVal.ch[0] = reg_array_blob[byteMax + 4];
            unVal.ch[1] = reg_array_blob[byteMax + 3];
            unVal.ch[2] = reg_array_blob[byteMax + 2];
            unVal.ch[3] = reg_array_blob[byteMax + 1];
            unVal.ch[4] = reg_array_blob[byteMax + 0];
            unVal.ch[5] = reg_array_blob[byteMax] * 0;
            unVal.ch[6] = reg_array_blob[byteMax] * 0;
            unVal.ch[7] = reg_array_blob[byteMax] * 0;
            // uint64_t sub_val64=0;
            // memcpy(&sub_val64, &reg_array_blob[byteMax], 8);
            unVal.ldwd = extract_subval_from_64bit (unVal.ldwd, max_bit, min_bit);
            sub_val = unVal.dwd[0];
        }

        if (4 == byte_len) {
            uint16_t max_bit = 7 - lbitPosMax % 8 + (byte_len - 1) * 8;
            uint16_t min_bit = 7 - lbitPosMin % 8;
            memcpy (&sub_val, &reg_array_blob[byteMax], byte_len);
            sub_val = reverse_byte_order_uint32 (sub_val);
            sub_val = extract_subval_from_32bit (sub_val, max_bit, min_bit);
        }
        if (2 == byte_len) {
            uint16_t sub_val16 = 0;
            uint16_t max_bit = (7 - (lbitPosMax % 8)) + (byte_len - 1) * 8;
            uint16_t min_bit = 7 - (lbitPosMin % 8);
            memcpy (&sub_val16, &reg_array_blob[byteMax], byte_len);
            sub_val16 = reverse_byte_order_uint16 (sub_val16);
            sub_val16 = extract_subval_from_16bit (sub_val16, max_bit, min_bit);
            sub_val = sub_val16;
        }
    }
    return sub_val;
}

uint8_t extract_subval_from_8bit (uint8_t inVal, uint8_t maxBit, uint8_t minBit) {
    uint8_t outVal = 0;
    if ((minBit < maxBit) && (maxBit <= 15) && (minBit <= 15)) {
        uint8_t mask = generate_8bit_left_mask (maxBit - minBit + 1);
        outVal = (inVal >> minBit);
        outVal = outVal & mask;
    }
    return outVal;
}

// 15 10
uint16_t extract_subval_from_16bit (uint16_t inVal, uint8_t maxBit, uint8_t minBit) {
    uint16_t outVal = 0;
    if ((minBit < maxBit) && (maxBit <= 15) && (minBit <= 15)) {
        uint16_t mask = generate_16bit_left_mask (maxBit - minBit + 1);
        outVal = (inVal >> minBit);
        outVal = outVal & mask;
    }
    return outVal;
}

/*num_of_bit 0......16*/
uint16_t calc_16_mask (uint8_t num_of_bit) {
    uint16_t mask = 0;
    if (num_of_bit <= 16) {
        for (int i = 0; i < num_of_bit; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

uint16_t generate_16bit_left_mask (uint8_t bitlen) {
    uint16_t mask = 0x0000;
    if (bitlen <= 16) {
        uint16_t i = 0;
        for (i = 0; i < bitlen; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

uint8_t generate_8bit_left_mask (uint8_t bitlen) {
    uint8_t mask = 0x00;
    if (bitlen <= 8) {
        uint8_t i = 0;
        for (i = 0; i < bitlen; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

/*
 *  Odd (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *  even (Amount of 1 bits is 2 4 6 8 10 and so 32)
 *
 *  returns 1 if the parity in inValue is Odd
 *  (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *
 *  inVal        bit        setBit  parity        return
 *  0          > 00       > 0  >    PARITY_EVEN   false
 *  1          > 01       > 1  >    PARITY_ODD    true
 *  2          > 10       > 1  >    PARITY_ODD    true
 *  3          > 11       > 2  >    PARITY_EVEN   false
 *  178        > 10110010 > 4  >    PARITY_EVEN   false
 *  0xFFFFFFFF > 1..111   > 32 >    PARITY_EVEN   false
 *  0xFFFFFFFE > 11..10   > 31 >    PARITY_ODD    true
 */
bool is_parity_odd (uint32_t const inVal) {
    bool otRet = false;
    uint8_t cntOnes = 0u;
    /*count set bits*/
    cntOnes = count_set_bits (inVal);
    if (0u < (cntOnes & 1u)) {
        otRet = true; /*(Amount of 1 bits is 1 3 5 7 9 and so 31)*/
    } else {
        otRet = false; /*(Amount of 1 bits is 2 4 6 8 10 and so 32)*/
    }

    return otRet;
}

/*
 return 0 if value contains only 1 bit set
 1, 2 4 8 16 32 64 128 512 ....
 */
bool is_power_of_two (uint32_t const val) {
    bool outRetPt = false;
    /*check power of two*/
    if (0u == (val & (val - 1u))) {
        /*only one bit set in the value */
        outRetPt = true;
    }
    if (0u == val) {
        outRetPt = false;
    }
    return outRetPt;
}

// O(1)  1+1+1+1+1 =5
uint8_t swap_bits_odd_even_fast (uint8_t x) {
    // Get all even bits of x
    uint8_t even_bits = x & 0xAAAAAAAA; //...1010
                                        // Get all odd bits of x
    uint8_t odd_bits = x & 0x55555555;  //...0101
    even_bits >>= 1;                    // Right shift even bits
    odd_bits <<= 1;                     // Left shift odd bits
    return (even_bits | odd_bits);      // Combine even and odd bits
}

int reverse_dec (int in_x) {
    int64_t rev_dec = 0;
    int64_t x = (int64_t)in_x;
#ifdef DEBUG
    printf ("\nx=%d", x);
#endif
    int sign = 1;
    if (0 == x) {
        return 0;
    }
    if (x < 0) {
        x = -x;
        sign = -1;
    }
    uint8_t arr[13];
    memset (arr, 0xFF, sizeof (arr));
    int cnt = 0;
    uint8_t digit = 0;
    while (0 < x) {
        digit = x % 10;
#ifdef DEBUG
        printf ("\n[%d]=%d ", cnt, digit);
#endif
        arr[cnt] = digit;
        x = x / 10;
        cnt++;
    }
#ifdef DEBUG
    printf ("\n");
#endif
    // cnt - rank of x
    int rank = cnt - 1;
    if (0 <= rank) {
        rev_dec = 0;
        for (int i = (rank); 0 <= i; i--) {
            int64_t power = powi (10, (rank - i));
            int64_t incriment = ((int64_t)arr[i]) * (int64_t)power;
#ifdef DEBUG
            printf ("\narr[%d]=%d power %I64d %I64d", i, arr[i], power, incriment);
#endif
            rev_dec += incriment;
        }
    }
#ifdef DEBUG
    printf ("\nrev_dec=%I64d", rev_dec);
#endif
    if (2147483647 < rev_dec) {
        rev_dec = 0;
    }
#ifdef DEBUG
    printf ("\nlim rev_dec=%I64d", rev_dec);
#endif
    rev_dec = rev_dec * sign;
    return rev_dec;
}

uint8_t swap_bits_u8 (uint8_t in_val) {
    uint8_t out_val = 0;
    uint8_t out = 0;
    for (uint8_t bit = 0U; bit <= 7U; bit++) {
        out |= (in_val & 1);
        out_val = out;
        out = out << 1;
        in_val = in_val >> 1;
    }
    return out_val;
}

// O(n) 4*(1+1+2(1+1)) = 4*(6) = 24
uint8_t swap_bits_odd_even (uint8_t in_val) {
    uint8_t out_val = 0;
    uint8_t mask_even = 0;
    uint8_t mask_odd = 0;
    for (uint8_t pair = 0; pair < 4; pair++) {
        mask_even = 1 << (pair * 2);
        mask_odd = 1 << (pair * 2 + 1);
        if (in_val & mask_even) { // 0 2 4
            out_val |= mask_odd;
        }
        if (in_val & mask_odd) { // 1 3 5
            out_val |= mask_even;
        }
    }
    return out_val;
}

uint8_t swap_bits_u8_slow (uint8_t in_val) {
    uint8_t out_val = 0;
    for (uint8_t bit = 0U; bit < 8U; bit++) {
        if ((((uint8_t)1U) << bit) == ((((uint8_t)1U) << bit) & in_val)) {
            out_val |= (((uint8_t)1) << (7U - bit));
        }
    }
    return out_val;
}

uint8_t reverse_bits_u8_fast (uint8_t in_val) {
    uint8_t out_val = 0, power = 7;
    while (in_val != 0) {
        out_val += (in_val & 1) << (power--);
        in_val = in_val >> 1;
    }
    return out_val;
}

int hammingDistance (int x, int y) {
    int temp = x ^ y;
    int dist = count_set_bits (temp);
    return dist;
}

int missingNumber (int *nums, int numsSize) {
    int missing = numsSize;
    int temp = 0;
    for (int i = 0; i < numsSize; i++) {
        missing ^= i ^ nums[i];
        temp ^= nums[i];
    }
    return missing;
}

int missingNumber_sum (int *nums, int numsSize) {
    // printf ("\n[d] %s()", __FUNCTION__);
    int total_sum = numsSize * (numsSize + 1) / 2;
    int cur_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        cur_sum += nums[i];
    }
    return total_sum - cur_sum;
}
