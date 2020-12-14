#ifndef __STRING_OPS_H
#define __STRING_OPS_H

#include "custom_type.h"

#include <math.h>
#include <stdint.h>
#include <string.h>

#define DEBUG_PARSE_EXPRESS 0
#define DEBUG_PARSE_NOT 0
#define DEBUG_PARSE_AND 0
#define DEBUG_PARSE_OR 0

// #define DEBUG_ITOA

#define DEBUG_HASH_TABLE 0
#define DEBUG_LENGTHOFLONGESTSUBSTRING 0

#define DBL_MIN_10_EXP (-307)
#define DBL_MAX_10_EXP (308)
#define FLT_MAX (3.40282347e+38f)
#define FLT_MIN (1.175494350822287508e-38f)

typedef struct xString_t {
    char *ptr;
    int len;
} string_t;

#define NEW_LINE "\n\r"

bool parse_ip (char *inStr, uint16_t inStrLen, uint32_t *outIpAddr);
bool parse_mac (char *inStr, uint16_t inStrLen, uint8_t *outMacAddr);
bool parse_serial (char *inStr, uint16_t inStrLen, uint64_t *outSerial64bNumber);
bool parse_not (char *expression, int inStrLen);
bool parse_or (char *expression, int inStrLen);
bool parse_and (char *expression, int inStrLen);
int parse_num_operands (char *expression, int inStrLen);

bool is_camel_case (const char *in);
char *toSnakeCase (const char *in);
char *camel_case_2_snake_case (char *camel_case_str);

bool is_bracket (char ch);
bool parseBoolExpr (char *expression);
bool parse_bool_expr (char *expression, int inStrlen);
bool is_valid_parentheses (char *s);
int get_index_in_string (char *expression, int inStrLen, int operandNum, int *const operandLen);
bool brackets_same_type (char open, char close);
int calc_paratasis_nesting (char *s, int *const amountOfPairs);

bool parse_holder_name (char *inStr, uint16_t inStrLen, char *holderName);

bool compare_strings (char *stra, char *strb);
int myAtoi (char *str);

bool lower_case_str (char *str);
char *upper_case_str (char *str);

int replace_char (char *str, char orig, char rep);
bool try_strl2int64_dec (const char s64_dec_str[], int32_t s64_dec_str_len, int64_t *s64_dec_value);
bool try_strl2int32_dec (const char s32_dec_str[], int32_t s32_dec_str_len, int32_t *const s32_dec_value);
int find_max_sec (char *string, char sripChar);
int lengthOfLongestSubstring (char *s);

char *mac_to_str (uint8_t *mac_addr);
char *ip_to_str (uint8_t *ip_addr);
bool is_real_number (const char str[]);
bool is_float_number (const char float_str[]);
bool is_signed (const char first_str_char);
bool is_signe (const char first_str_char);
bool is_diff_chars (char *inStr, uint32_t len);
bool is_number (char letter);
bool is_valid_ip (char *inIpStr, unsigned char *outOctets);

bool replace_substring (char *inOutStr, char *orig, char *rep);
uint16_t count_substring (char *inStr, char *substr);
bool try_dec_char_to_u8 (uint8_t dec_char, uint8_t *dec_char_to_u8_value);
void reverse_string (char *inOutStr);
bool isNumber (char *s);
char *select_sub_string (char *text, char *tail);
const char *str_case_str (const char *const text, const char *const pattern);
void print_str_head (char *inStr, uint32_t len);
int count_amount_of_item (char *source, char *delin);
int split (char *source, char *delim, char ***outStrArr);
void reverseString (char *s, int length);
char *removeCharFromString (char *str, uint32_t delIndex);
void detect_change (char *oldStr, char *newStr, char **oldSubStr, int *oldSubStringLen, char **newSubStr,
                    int *newSubStringLen);
char *uint32_to_bin_str (uint32_t inVal32bit);
const char *utoa_bin16 (uint16_t u16_bin_data);
const char *utoa_bin24 (uint32_t u32_bin_data);
const char *utoa_bin32 (uint32_t u32_bin_data);

bool try_canch_hex_uint8 (char *inStr, int strLen, uint8_t *val8b);
bool try_canch_hex_uint16 (char *inStr, int strLen, uint16_t *val16b);
bool try_canch_hex_uint32 (char *inStr, int strLen, uint32_t *val32b);

bool parse_substr_name (const char *const inStr, uint16_t inStrLen, char *const outStr, char openBracket,
                        char closedBracket);

bool is_ip_number (char letter);
uint16_t calc_ip_val_len (char *inStr);
bool is_hex_number (char letter);
uint16_t calc_hex_val_len (char *inStr);
bool delete_char (char *inOutStr, int curIndex);

bool extract_numbers (char *s, int length);
void find_diff (char *oldStr, int oldLen, char *newStr, int newLen, int *outOldSubStringLen, int *outNewSubStringLen,
                char **oldSubStr, char **newSubStr);

char *str_append (char *in_str, char letter);
char *str_cat_dyn (char *in_str1, char *in_str2);

#endif /* __STRING_OPS_H */
