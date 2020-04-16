#include "str_ops.h"

#include "algorithms.h"
#include "custom_type.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

static int findIndOfFirstDiffFromStart (char *oldStr, char *newStr);
static int findIndOfFirstDiffFromEnd (char *oldStr, char *newStr);
static bool hash_table_char_put (char character, int indexInArray);
static bool hash_table_char_remove (char character);
static void init_hash_table (void);
static bool clear_all_left_chars (char *str, int index);
static int hash_table_char_check (char character);

//output: pointer address to the array of pointers
int split (char *source, char *delim, char ***outStrArr) {
    printf ("\n text  [%s] pattern [%s]\n", source, delim);
    *outStrArr = NULL;
    int numItem = 0, numItemInStr = 0;
    int j = 0;
    bool isFirst = true;
    int srcLen = strlen (source);
    int delimLen = strlen (delim);
    numItemInStr = count_amount_of_item (source, delim);
    char** arrStrings = malloc ((1 + numItem) * sizeof(char*));
    for (int k = 0; k < numItemInStr; k++) {
        printf ("\n address of ptrs: arrStrings[p]: [%p]", arrStrings [k]);
    }
    printf ("\n");
    if (*arrStrings) {
        for (int i = 0; i <= (srcLen - delimLen); i++) {
            int cmpRes = strncmp (delim, &source [i], delimLen);
            if (0 == cmpRes) {
                //printf ("\nSpot pattern\n");
                if (0 == i) {
                    //pattern in the first
                    numItem++;
                    isFirst = false;
                    char *str = select_sub_string (&source [i + delimLen], delim);
                    printf (" [%s] ", str);
                    arrStrings [j++] = (char*) str;
                } else if ((srcLen - delimLen) == i) {
                    //pattern in the end
                    if (0 == numItem) {
                        char *str = select_sub_string (&source [0], delim);
                        printf (" [%s] ", str);
                        arrStrings [j++] = (char*) str;
                        numItem = 1;
                    }
                } else {
                    //pattern in the middle
                    if (true == isFirst) {
                        char *str = select_sub_string (&source [0], delim);
                        if (str) {
                            printf (" [%s] ", str);
                            arrStrings [j++] = (char*) str;

                        } else {
                            printf ("\n malloc Error! \n");
                        }
                        numItem += 2;
                        isFirst = false;
                    } else {
                        numItem++;
                    }
                    char *str = select_sub_string (&source [i + delimLen], delim);
                    printf (" [%s] ", str);
                    arrStrings [j++] = (char*) str;
                }
            }
        }

        *outStrArr = arrStrings;
    } else {
        printf ("malloc error");
    }
    printf ("\n ");
    return numItemInStr;
}
//(qwerrty    RE)   return   "qwerty"
//(qweRTy    RT)   return   "qwe"
//(QWerty    QW)   return   ""
char *select_sub_string (char *text, char *tail) {
    char *outStr = NULL;
    if (text && tail) {
        bool isPatternSpot = false;
        int lenText = strlen (text);
        int lenTail = strlen (tail);
        if (lenTail < lenText) {
            for (int i = 0; i <= (lenText - lenTail); i++) {
                int cmpRes = strncmp (&text [i], tail, lenTail);
                if (0 == cmpRes) {
                    isPatternSpot = true;
                    if (0 < i) {
                        outStr = malloc (sizeof(char) * i + 1);
                        if (outStr) {
                            memset (outStr, 0x00, sizeof(char) * (i + 1));
                            memcpy (outStr, text, sizeof(char) * i);
                            return outStr;
                        }
                    } else {
                        outStr = strdup ("");
                        if (outStr) {
                            return outStr;
                        }
                    }
                }
            }
            if (false == isPatternSpot) {
                outStr = strdup (text);
                if (outStr) {
                    return outStr;
                }
            }
        }
    }
    return outStr;
}

//strstr
int count_amount_of_item (char *source, char *delim) {
    int numItem = 0;
    bool isFirst = true;
    int srcLen = strlen (source);
    int delimLen = strlen (delim);
    if (delimLen < srcLen) {
        for (int i = 0; i <= (srcLen - delimLen); i++) {
            int cmpRes = strncmp (delim, &source [i], delimLen);
            if (0 == cmpRes) {
                //printf ("\nSpot pattern\n");
                if (0 == i) {
                    //pattern in the first
                    isFirst = false;
                    numItem++;
                } else if ((srcLen - delimLen) == i) {
                    //pattern in the end
                    if (0 == numItem) {
                        numItem = 1;
                    }

                } else {
                    //pattern in the middle
                    if (true == isFirst) {
                        numItem += 2;
                        isFirst = false;
                    } else {
                        numItem++;
                    }
                }
            }
        }

    }
    return numItem;
}

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

static int gHashSize = 0;
static int gCharHashTable [512] =
    { 0 };

static bool hash_table_char_put (char character, int indexInArray) {
    bool res = false;
    if (0 <= gCharHashTable [(int) character]) {
#if DEBUG_HASH_TABLE
        printf ("\nCollision\n");
#endif
    } else {
#if DEBUG_HASH_TABLE
        printf ("new in table [%c] %d", character, indexInArray);
#endif
        gCharHashTable [(int) character] = indexInArray;
        gHashSize++;
        res = true;
    }
    return res;
}

static int hash_table_char_check (char character) {
    if (0 <= gCharHashTable [(int) character]) {
        return gCharHashTable [(int) character];
    } else {
        return -1;
    }
}
static bool hash_table_char_remove (char character) {
    if (0 < character) {
        if (0 <= gCharHashTable [(int) character]) {
            gCharHashTable [(int) character] = -1;
            gHashSize--;
            return true;
        } else {
#if DEBUG_HASH_TABLE
            printf ("\nUnable to remove absent char [%c]\n", character);
#endif
            return false;
        }
    } else {
        printf ("\nOut of bound [%d]!\n", (int) character);
        return false;
    }
}

static void init_hash_table (void) {
    gHashSize = 0;
    int sizeOfArray = sizeof(gCharHashTable) / sizeof(gCharHashTable [0]);
    for (int i = 0; i < sizeOfArray; i++) {
        gCharHashTable [i] = -1;
    }
}
//bpfbhmipx 1
static bool clear_all_left_chars (char *str, int index) {
#if DEBUG_HASH_TABLE
    printf (" discard all left from ind: %d inclusive", index);
    printf (" {");
    for (int i = 0; i <= index; i++) {
        printf ("%c", str [i]);
    }
    printf ("}");

#endif
    bool res;
    //for (int i = 0; i <= index; i++) {
    if (0 <= hash_table_char_check (str [index])) {
        res = hash_table_char_remove (str [index]);
    }
    //}
    return res;
}

static void full_str_with (char *s, char pattern, int size) {
    for (int i = 0; i < size; i++) {
        s [i] = pattern;
    }
}
//abcabcbb 7
//pwwkew
int lengthOfLongestSubstring (char * s) {
    int maxNumUnicChars = 0;

#if DEBUG_LENGTHOFLONGESTSUBSTRING
    printf ("\n str: %s ", s);
#endif
    init_hash_table ();
    if (s) {
        int strLen = strlen (s);
        char *locStr = (char *) malloc (sizeof(char) * strLen + 1);
        if (!locStr) {
            return 0;
        } else {
            full_str_with (locStr, '_', strLen);
            locStr [strLen] = '\0';
        }
        int winEnd = 0;
        int lastIndexOfChar = 0;
        while (winEnd < strLen) {
#if DEBUG_LENGTHOFLONGESTSUBSTRING
            printf ("\n:%d <%d>", winEnd, gHashSize);
#endif
            lastIndexOfChar = hash_table_char_check (s [winEnd]);
            if (lastIndexOfChar < 0) {
                /*new val*/
#if DEBUG_LENGTHOFLONGESTSUBSTRING
                printf ("new %c ", s [winEnd]);
#endif
                hash_table_char_put (s [winEnd], winEnd);
                locStr [winEnd] = s [winEnd];

            } else {
                // same val
#if DEBUG_LENGTHOFLONGESTSUBSTRING
                printf ("old %c %d", s [winEnd], lastIndexOfChar);
#endif
                clear_all_left_chars (s, lastIndexOfChar);
                locStr [lastIndexOfChar] = '_';
                hash_table_char_put (s [winEnd], winEnd);
                locStr [winEnd] = s [winEnd];

            }
#if DEBUG_LENGTHOFLONGESTSUBSTRING
            printf (":gHashSize <%d>", gHashSize);
#endif
            maxNumUnicChars = update_max (maxNumUnicChars, gHashSize);
            winEnd++;
        }
        printf ("\n\n (%s)\n", locStr);

    }
    return maxNumUnicChars;
}

bool test_lengthOfLongestSubstring (void) {
    int val;

    val = lengthOfLongestSubstring ("pwwkew");
    if (3 != val) {
        printf ("\npwwkew val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("bpfbhmipx");
    if (7 != val) {
        printf ("\nbpfbhmipx val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("aab");
    if (2 != val) {
        printf ("\naab val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("abcabcbb");
    if (3 != val) {
        printf ("\nabcabcbb val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("bbbbb");
    if (1 != val) {
        printf ("\nbbbbb val:%d \n", val);
        return false;
    }

    return true;
}

bool test_detect_change (void) {
    char* change;
    int subStringLen;
    int cmpRes = 0;
    // "aaabb"
    // "aaa11bb"
    change = detect_change ("aaabb", "aaa11bb", &subStringLen, (char *) NULL, (char *) NULL);
    if (2 != subStringLen) {
        return false;
    }
    cmpRes = strncmp (change, "11", 2);
    if (cmpRes) {
        return false;
    }

    change = detect_change ("aaa11bb", "aaabb", &subStringLen, (char *) NULL, (char *) NULL);
    if (2 != subStringLen) {
        return false;
    }
    cmpRes = strncmp (change, "11", 2);
    if (cmpRes) {
        return false;
    }

    change = detect_change ("aa111bb", "aa22bb", &subStringLen, (char *) NULL, (char *) NULL);
    if (2 != subStringLen) {
        return false;
    }
    cmpRes = strncmp (change, "11", 2);
    if (cmpRes) {
        return false;
    }
    return false;
}

//Examples:
//"aaabb", "aaa11bb"     < "11" inserted at index 3
//"aa111bb", "aa22bb"     < "11" inserted at index 3
char* detect_change (char *oldStr, char *newStr, int *subStringLen, char *oldSubStr, char *newSubStr) {
    (void) *oldSubStr;
    (void) *newSubStr;
    int oldStrLen = strlen (oldStr);
    int newStrLen = strlen (newStr);
    //relatively larger size string
    int indexOfFirstDiffLeft = findIndOfFirstDiffFromStart (oldStr, newStr);
    int indexOfFirstDiffRigt = findIndOfFirstDiffFromEnd (oldStr, newStr);

    if (oldStrLen == newStrLen) {
        if (indexOfFirstDiffLeft < indexOfFirstDiffRigt) {
            *subStringLen = indexOfFirstDiffRigt - indexOfFirstDiffLeft;
            return &oldStr [indexOfFirstDiffLeft];
        } else {
            *subStringLen = 0;
            return NULL;
        }
    } else if (newStrLen < oldStrLen) {
        if (indexOfFirstDiffLeft < indexOfFirstDiffRigt) {
            *subStringLen = indexOfFirstDiffRigt - indexOfFirstDiffLeft;
            return &oldStr [indexOfFirstDiffLeft];
        } else {
            *subStringLen = 0;
            return NULL;
        }
    } else if (oldStrLen < newStrLen) {
        if (indexOfFirstDiffLeft < indexOfFirstDiffRigt) {
            *subStringLen = indexOfFirstDiffRigt - indexOfFirstDiffLeft;
            return &newStr [indexOfFirstDiffLeft];
        } else {
            *subStringLen = 0;
            return NULL;
        }
    } else {
        printf ("\nUnreachable branch\n");
    }
    return NULL;
}

static int findIndOfFirstDiffFromStart (char *oldStr, char *newStr) {
    if (oldStr && newStr) {
        int oldStrLen = strlen (oldStr);
        int newStrLen = strlen (newStr);
        for (int i = 0; i < min (oldStrLen, newStrLen); i++) {
            if (oldStr [i] != newStr [i]) {
                return i;
            }
        }
    }
    return -1;
}

static int findIndOfFirstDiffFromEnd (char *oldStr, char *newStr) {
    if (oldStr && newStr) {
        int oldStrLen = strlen (oldStr);
        int newStrLen = strlen (newStr);
        char *replicaOld = strdup (oldStr);
        char *replicaNew = strdup (newStr);
        reverseString (replicaOld, oldStrLen);
        reverseString (replicaNew, newStrLen);
    }
    return -1;
}

void reverseString (char *inOutStr, int length) {
    for (int i = 0; i < (length / 2); i++) {
        swap_char (&inOutStr [i], &inOutStr [(length-1) - i]);
    }
}

bool test_reverse (void) {
    int cmpRes = 0;
    char tempStr [100];
    strcpy(tempStr,"12345");
    reverseString (tempStr, 5);
    cmpRes = strcmp (tempStr, "54321");
    if (0 != cmpRes) {
        printf("\ntempStr [%s]\n",tempStr);
        return false;
    }

    return true;
}

