#ifndef __STRING_OPS_H
#define __STRING_OPS_H

#include "custom_type.h"

#include <stdint.h>
#include <string.h>
#include <math.h>

#define DEBUG_HASH_TABLE 0
#define DEBUG_LENGTHOFLONGESTSUBSTRING 1

#define DBL_MIN_10_EXP  (-307)
#define DBL_MAX_10_EXP  (308)
#define FLT_MAX         (3.40282347e+38f)
#define FLT_MIN         (1.175494350822287508e-38f)

// time complexity O(T*P)
int find_max_sec (char * string, char sripChar);
bool test_lengthOfLongestSubstring (void);
int lengthOfLongestSubstring (char * s);
void reverse_string (char *inOutStr);
char *select_sub_string (char *text, char *tail);
const char *str_case_str (const char * const text, const char * const pattern);
char *removeCharFromString (char *str, uint32_t delIndex);
bool isNumber (char * s);
bool is_real_number (const char str []);
bool try_dec_char_to_u8 (uint8_t dec_char, uint8_t * dec_char_to_u8_value);
bool is_float_number (const char float_str []);
int count_amount_of_item (char *source, char *delin);
int split (char *source, char *delim, char ***outStrArr);

void print_str_head (char *inStr, uint32_t len);
bool is_diff_chars (char *inStr, uint32_t len);
bool test_reverse (void);
void reverseString (char *s, int length);
bool test_detect_change (void);
void detect_change (char *oldStr, char *newStr, char **oldSubStr, int *oldSubStringLen, char **newSubStr, int *newSubStringLen);
void find_diff (
    char* oldStr,
    int oldLen,
    char* newStr,
    int newLen,
    int *outOldSubStringLen,
    int *outNewSubStringLen,
    char **oldSubStr,
    char **newSubStr);
#endif /* __STRING_OPS_H */
