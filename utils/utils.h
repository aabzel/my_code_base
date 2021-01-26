#ifndef __UTILS_H
#define __UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#if 0
#include "bin_heap_array.h"
#include "linked_list.h"
#include "linked_list_array.h"
#endif

#include "custom_type.h"


#include <stdint.h>

#define NOT_NUM (-999999)
#define INT_MIN (-2147483648)
#define INT_MAX (2147483647)

#define DEBUG_INSERT 0
#define DEBUR_LET_POS 0
#define DEBUG_ARG 0
#define DEBUG_REMAIN_ALPH 0

extern char pemutationFile[100];
extern char kitFile[100];

struct Results {
    int *res;
    int R; // Length of the array
};

struct Results solution (int *A, int N, int F, int M);

void print_biggest_mantissa (void);

int solution4 (int n);
bool print_mem_ascii (uint8_t *memPtr, uint32_t numByte);
float power_of (uint32_t base, int32_t exponent);
char *portNumToStr (uint8_t port);
void print_pad_nums (void);
bool test_my_printf (void);
bool my_printf (const char *format, ...);
bool is_digit (char ch);
unsigned summ (unsigned char num, unsigned first, ...);
void init_double_array (double *ptrArray, int size);
uint32_t reverseBits32 (uint32_t num);
uint8_t hamming_weight (uint32_t n);
unsigned int GrayToBinary32 (unsigned int num);
unsigned int GrayToBinary (unsigned int num);
uint32_t bin_to_gray (uint32_t num);
char *format_time_txt (void);
void init_file_name (void);
// cur date string
double calc_median_naiv (int *const inArr, int sizeOfArr);
char *generate_num_string (int n);
void print_sub_str (char *const str, int len);
void print_array (int *alphabet, int sizeOfAlphabet, int k);
void print_array_int (int *alphabet, int sizeOfAlphabet);
bool print_mem_vertical (uint8_t *memPtr, uint32_t numByte, bool printChars);
bool print_mem_horisonal (uint8_t *memPtr, uint32_t numByte);
double avrage_two (int val1, int val2);
uint32_t max_val (uint32_t amountofbit);
int *grayCode (int n, int *returnSize);
void print_bit_representation (float val);

double calc_median (int *const inArr, int sizeOfArr);
long long summ_array (int const *const inArr, int sizeOfArr);
double avrage_two (int val1, int val2);
void print_array_double (double *alphabet, int sizeOfAlphabet);
bool is_odd (int val);

void print_indent (int indent);

double calc_average (int const *const inArr, int sizeOfArr);
void print_bytes (uint32_t byte);
int parse_num_of_args (const char *format);
uint16_t extract_subval_from_16bit (uint16_t inVal, uint8_t maxBit, uint8_t minBit);
uint16_t generate_16bit_left_mask (uint8_t bitlen);
uint32_t generate_32bit_left_mask (uint8_t bitlen);

bool is_double_arr_equal (double *arr1, double *arr2, int arrSize);

uint16_t float_to_uint16 (float val);
double fraction (uint32_t mantissa);
float construct_32bit_float (uint32_t integer, uint32_t fractional);
double fraction_sim (uint32_t mantissa);
float cacl_percent (float numerator, float denominator);
uint32_t pack_ipv4 (uint8_t ipAddrByte1, uint8_t ipAddrByte2, uint8_t ipAddrByte3, uint8_t ipAddrByte4);
bool print_mac_addr (uint8_t *mac_addr);
uint16_t reverse_byte_order_uint16 (const uint16_t in2byteVal);
uint32_t reverse_byte_order_uint32 (const uint32_t in4byteVal);

bool print_mac_addr (uint8_t *mac_addr);

#ifdef __cplusplus
}
#endif

#endif /* __UTILS_H */
