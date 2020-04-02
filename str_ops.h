#ifndef __STRING_OPS_H
#define __STRING_OPS_H

#include "custom_type.h"

#include <stdint.h>
#include <string.h>
#include <math.h>

#define DBL_MIN_10_EXP  (-307)
#define DBL_MAX_10_EXP  (308)
#define FLT_MAX         (3.40282347e+38f)
#define FLT_MIN         (1.175494350822287508e-38f)

// time complexity O(T*P)
const char *str_case_str (const char * const text, const char * const pattern);
char *removeCharFromString (char *str, uint32_t delIndex);
bool isNumber (char * s);
bool try_dec_char_to_u8 (uint8_t dec_char, uint8_t * dec_char_to_u8_value);
bool is_float_number (const char float_str [] ) ;
#endif /* __STRING_OPS_H */
