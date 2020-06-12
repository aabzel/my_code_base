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

#define NEW_LINE "\n\r"

bool is_bracket (char ch);
bool parseBoolExpr (char *expression);
bool parse_bool_expr (char *expression, int inStrlen);
bool is_valid_parentheses (char *s);
int get_index_in_string (char *expression, int inStrLen, int operandNum, int * const operandLen);
bool brackets_same_type (char open, char close);
int calc_paratasis_nesting (char *s, int * const amountOfPairs);

bool compare_strings (char *stra, char *strb);
int myAtoi (char *str);
int replace_char (char *str, char orig, char rep);
bool try_strl2int64_dec (const char s64_dec_str [], int32_t s64_dec_str_len, int64_t *s64_dec_value);
bool try_strl2int32_dec (const char s32_dec_str [], int32_t s32_dec_str_len, int32_t * const s32_dec_value);
int find_max_sec (char *string, char sripChar);
int lengthOfLongestSubstring (char *s);
int replace_char (char *str, char orig, char rep);
bool reblace_substring (char *inOutStr, char *orig, char *rep);
void reverse_string (char *inOutStr);
char *select_sub_string (char *text, char *tail);
const char *str_case_str (const char * const text, const char * const pattern);
char *removeCharFromString (char *str, uint32_t delIndex);
bool isNumber (char *s);
bool is_real_number (const char str []);
bool try_dec_char_to_u8 (uint8_t dec_char, uint8_t *dec_char_to_u8_value);
bool is_float_number (const char float_str []);
int count_amount_of_item (char *source, char *delin);
int split (char *source, char *delim, char ***outStrArr);
bool is_signed (const char first_str_char);
bool is_signe (const char first_str_char);
void print_str_head (char *inStr, uint32_t len);
bool is_diff_chars (char *inStr, uint32_t len);
void reverseString (char *s, int length);
void detect_change (char *oldStr, char *newStr, char **oldSubStr, int *oldSubStringLen, char **newSubStr, int *newSubStringLen);
char *uint32_to_bin_str (uint32_t inVal32bit);
const char* utoa_bin16 (uint16_t u16_bin_data);
const char* utoa_bin24 (uint32_t u32_bin_data);
const char* utoa_bin32 (uint32_t u32_bin_data);

void find_diff (
    char *oldStr,
    int oldLen,
    char *newStr,
    int newLen,
    int *outOldSubStringLen,
    int *outNewSubStringLen,
    char **oldSubStr,
    char **newSubStr);
bool test_lengthOfLongestSubstring (void);
bool test_detect_change (void);
bool test_num_to_bin_str (void);
bool test_myAtoi (void);
bool test_parse_not (void);
bool test_parse_and (void);
bool test_operand_extract (void);
bool test_calc_paratasis_nesting (void);
bool test_parse_num_operands (void);
bool test_Valid_Parentheses (void);
bool test_parseBoolExpr (void);
bool test_reverse (void);
bool test_str_char_replace (void);
bool test_replace_substr (void);

#endif /* __STRING_OPS_H */
