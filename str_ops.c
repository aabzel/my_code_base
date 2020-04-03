#include "str_ops.h"

#include "custom_type.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/*
 * Find the first occurrence of pattern in text, ignore case.
 */
bool is_real_number (const char str []);

// time complexity O(T*P)
const char *str_case_str (const char * const text, const char * const pattern) {
    const char *retPtr = NULL;
    if ((NULL != text) && (NULL != pattern)) {
        int i = 0;
        if ('\0' == (*pattern)) {
            retPtr = &text [0];
        } else {
            for (; '\0' != text [i]; ++i) {
                int j = 0;
                while (('\0' != text [i + j]) && ((tolower ((int) text [i + j]) == tolower ((int) pattern [j])))) {
                    ++j;
                }
                if ('\0' == (pattern [j])) {
                    retPtr = &text [i];
                    break;
                }
            }
        }
    }

    return retPtr;
}
char *removeCharFromString (char *str, uint32_t delIndex) {
    size_t alphabetLength = strlen (str);
    char *tempArray = malloc (alphabetLength);
    if (tempArray) {
        strcpy (tempArray, str);
        uint32_t index = 0;
        if (delIndex < (alphabetLength + 1)) {
            for (index = delIndex; index < (alphabetLength - 1); index++) {
                tempArray [index] = tempArray [index + 1];
            }
        }
        tempArray [alphabetLength - 1] = '\0';
        return tempArray;
    } else {
        printf ("Malloc error");
    }

    return NULL;
}

bool isNumber (char * s) {
    bool res = false;
    res = is_float_number (s);
    //printf ("\n instr [%s]", s);
    return res;
}

bool is_float_number (const char inStr []) {
    bool float_success = is_real_number (inStr);
    return float_success;
}

static bool is_space (const char character) {
    bool res = false;
    if (' ' == character) {
        res = true;
    }
    return res;
}

static bool is_spaces (const char str []) {
    bool res = true;
    uint32_t strLen = strlen (str);
    uint32_t strIndex = 0u;
    for (strIndex = 0; strIndex < strLen; strIndex++) {
        if (false == is_space ((char) (str [strIndex]))) {
            res = false;
        }
    }
    return res;
}


bool is_real_number (const char str []) {
    bool strtod_success = true;
    double_t number = 0.0;
    uint32_t str_index = 0U;
    int32_t s32_number;
    uint8_t num_digits = 0U;
    uint8_t num_decimals = 0U;
    uint8_t temp_value = 0U;
    uint32_t strLen = strlen (str);

    /* Skip leading whitespace */
    while (isspace ((int32_t) (str [str_index])) > 0) {
        str_index++;
    }

    /* Handle optional sign */
    if (('-' == str [str_index]) || ('+' == str [str_index])) {
        if ('-' == str [str_index]) {
        }
        str_index++;
    }

    if (0 == isdigit ((int32_t) (str [str_index]))) {
        //strtod_success = false;
        number = 0.0;
    } else {
        /* Process string of digits */
        while (0 < isdigit ((int32_t) (str [str_index]))) {
            (void) try_dec_char_to_u8 ((uint8_t) str [str_index], &temp_value);
            number = (number * 10.0) + (double_t) temp_value;
            str_index++;
            num_digits++;
        }
    }

    if (true == strtod_success) {
        /* Process decimal part  */
        if (str [str_index] == '.') {
            str_index++;
            if (0 < isdigit ((int32_t) (str [str_index]))) {
                while (0 < isdigit ((int32_t) (str [str_index]))) {
                    (void) try_dec_char_to_u8 ((uint8_t) str [str_index], &temp_value);
                    number = (number * 10.0) + (double_t) temp_value;
                    str_index++;
                    num_digits++;
                    num_decimals++;
                }
                /*12.4545[]*/
                if (' ' != str [str_index] && '\0' != str [str_index] && 'e' != str [str_index] && 'E' != str [str_index]) {
                    strtod_success = false;
                }

            } else {
                if (' ' != str [str_index] && '\0' != str [str_index] && 'e' != str [str_index] && 'E' != str [str_index]) {
                    strtod_success = false;
                }
            }
        } else {
            if ('\0' != str [str_index] && ' ' != str [str_index] && 'E' != str [str_index] && 'e' != str [str_index]) {
                strtod_success = false;
            }
        }
    }
    if (true == strtod_success) {
        if (num_digits == 0U) {
            strtod_success = false;
        }
    }

    if (true == strtod_success) {
        /* Correct for sign */

        /* Process an exponent string */
        if ((str [str_index] == 'e') || (str [str_index] == 'E')) {
            /* Handle optional sign */

            str_index++;

            if (('-' == str [str_index]) || ('+' == str [str_index])) {
                if ('-' == str [str_index]) {

                }
                str_index++;
            }
            if (false == isdigit ((int32_t) (str [str_index]))) {
                /* in case of "0e" */
                strtod_success = false;
            } else {
                /* Process string of digits */
                s32_number = 0;
                while (isdigit ((int32_t) (str [str_index])) > 0) {
                    (void) try_dec_char_to_u8 ((uint8_t) str [str_index], &temp_value);
                    s32_number = (s32_number * 10) + (int32_t) temp_value;
                    str_index++;
                }
                if (' ' != str [str_index] && ('\0' != str [str_index])) {
                    strtod_success = false;
                }
            }
        }
    }
    if (true == strtod_success) {
        if (str_index < (strLen - 1)) {
            /* "1 4" */
            strtod_success = is_spaces (&str [str_index]);
        }
    }
    return strtod_success;
}

bool try_dec_char_to_u8 (uint8_t dec_char, uint8_t * dec_char_to_u8_value) {
    uint8_t dec_char_to_u8_result = 0U;
    bool dec_char_to_u8_success = true;

    if ((dec_char < (uint8_t) '0') || (dec_char > (uint8_t) '9')) {
        dec_char_to_u8_success = false;
    }

    if (dec_char_to_u8_success == true) {
        dec_char_to_u8_result = dec_char - (uint8_t) '0';
    }

    *dec_char_to_u8_value = dec_char_to_u8_result;
    return dec_char_to_u8_success;
}

