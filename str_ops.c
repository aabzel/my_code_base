#include "str_ops.h"

#include "algorithms.h"
#include "custom_type.h"
#include "lifo_char.h"
#include "uTests.h"

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
static int findIndOfFirstDiffFromStart (char *oldStr, char *newStr);
static int findIndOfFirstDiffFromEnd (char *oldStr, char *newStr);
#endif

#if 0
static bool get_oparand (char *expression, int i);
#endif

static int parse_num_operands (char *expression);
static bool parse_single_char (char *expression);
static bool parse_or (char *expression);
static bool parse_and (char *expression);
static bool parse_not (char *expression);
static bool hash_table_char_put (char character, int indexInArray);
// static bool hash_table_char_remove (char character);
static void init_hash_table (void);

static int hash_table_char_check (char character);

// output: pointer address to the array of pointers
int split (char *source, char *delim, char ***outStrArr) {
    printf ("\n text  [%s] pattern [%s]\n", source, delim);
    *outStrArr = NULL;
    int numItem = 0, numItemInStr = 0;
    int j = 0;
    bool isFirst = true;
    int srcLen = strlen (source);
    int delimLen = strlen (delim);
    numItemInStr = count_amount_of_item (source, delim);
    char **arrStrings = malloc ((1 + numItem) * sizeof(char *));
    for (int k = 0; k < numItemInStr; k++) {
        printf ("\n address of ptrs: arrStrings[p]: [%p]", arrStrings [k]);
    }
    printf ("\n");
    if (*arrStrings) {
        for (int i = 0; i <= (srcLen - delimLen); i++) {
            int cmpRes = strncmp (delim, &source [i], delimLen);
            if (0 == cmpRes) {
                // printf ("\nSpot pattern\n");
                if (0 == i) {
                    // pattern in the first
                    numItem++;
                    isFirst = false;
                    char *str = select_sub_string (&source [i + delimLen], delim);
                    printf (" [%s] ", str);
                    arrStrings [j++] = (char *) str;
                } else if ((srcLen - delimLen) == i) {
                    // pattern in the end
                    if (0 == numItem) {
                        char *str = select_sub_string (&source [0], delim);
                        printf (" [%s] ", str);
                        arrStrings [j++] = (char *) str;
                        numItem = 1;
                    }
                } else {
                    // pattern in the middle
                    if (true == isFirst) {
                        char *str = select_sub_string (&source [0], delim);
                        if (str) {
                            printf (" [%s] ", str);
                            arrStrings [j++] = (char *) str;

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
                    arrStrings [j++] = (char *) str;
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

// strstr
int count_amount_of_item (char *source, char *delim) {
    int numItem = 0;
    bool isFirst = true;
    int srcLen = strlen (source);
    int delimLen = strlen (delim);
    if (delimLen < srcLen) {
        for (int i = 0; i <= (srcLen - delimLen); i++) {
            int cmpRes = strncmp (delim, &source [i], delimLen);
            if (0 == cmpRes) {
                // printf ("\nSpot pattern\n");
                if (0 == i) {
                    // pattern in the first
                    isFirst = false;
                    numItem++;
                } else if ((srcLen - delimLen) == i) {
                    // pattern in the end
                    if (0 == numItem) {
                        numItem = 1;
                    }

                } else {
                    // pattern in the middle
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

bool isNumber (char *s) {
    bool res = false;
    res = is_float_number (s);
    // printf ("\n instr [%s]", s);
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
        // strtod_success = false;
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

bool try_dec_char_to_u8 (uint8_t dec_char, uint8_t *dec_char_to_u8_value) {
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
#if 0
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
#endif
static void init_hash_table (void) {
    gHashSize = 0;
    int sizeOfArray = sizeof(gCharHashTable) / sizeof(gCharHashTable [0]);
    for (int i = 0; i < sizeOfArray; i++) {
        gCharHashTable [i] = -1;
    }
}
// bpfbhmipx 1

#if 0
static void full_str_with (char *s, char pattern, int size) {
    for (int i = 0; i < size; i++) {
        s [i] = pattern;
    }
}
#endif
// abcabcbb 8
// pwwkew
int lengthOfLongestSubstring (char *inStr) {
    int maxNumUnicChars = 0;
    bool res;
    uint32_t i, j;

#if DEBUG_LENGTHOFLONGESTSUBSTRING
    printf ("\n str: %s ", inStr);
#endif
    if (inStr) {
        uint32_t strLen = strlen (inStr);
        for (i = 0; i < strLen; i++) {
            init_hash_table ();
            for (j = 1; j <= (strLen - i); j++) {
                if (hash_table_char_check (inStr [i + j - 1]) < 0) {
                    res = hash_table_char_put (inStr [i + j - 1], i);
                    if (false == res) {
                        printf ("\n Error\n");
                    }
                    maxNumUnicChars = update_max (maxNumUnicChars, j);
                } else {
                    break;
                }
            }
        }
    }

    return maxNumUnicChars;
}

#if 0
int lengthOfLongestSubstring_slow (char * inStr) {
    int maxNumUnicChars = 0;
    bool res;
    uint32_t i, j;
    int amountOfChars = 0;
#if DEBUG_LENGTHOFLONGESTSUBSTRING
    printf ("\n str: %s ", inStr);
#endif
    if (inStr) {
        uint32_t strLen = strlen (inStr);
        for (i = 0; i < strLen; i++) {
            for (j = 1; j <= (strLen-i); j++) {
                amountOfChars = j;
                res = is_diff_chars (&inStr [i], amountOfChars);
                if (true == res) {
                    maxNumUnicChars = update_max (maxNumUnicChars, amountOfChars);
                }else{
                    break;
                }
            }
        }
    }

    return maxNumUnicChars;
}
#endif

int find_max_sec (char *string, char sripChar) {
    int maxCnt = 0;
    int curCnt = 0;
    int strLen = strlen (string);
    for (int i = 0; i < strLen; i++) {
        if (sripChar != string [i]) {
            curCnt++;
        } else {
            curCnt = 0;
        }
        maxCnt = update_max (maxCnt, curCnt);
    }
    return maxCnt;
}

bool test_lengthOfLongestSubstring (void) {
    int val;
    bool res;
    res = is_diff_chars ("12345", 5);
    if (false == res) {
        return false;
    }

    res = is_diff_chars ("1214", 4);
    if (true == res) {
        return false;
    }

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
    char *oldSubString;
    char *newSubString;
    int oldSubStringLen = -1;
    int newSubStringLen = -1;
    int cmpRes = 0;
    // "aaabb"
    // "aaa11bb"
    detect_change ("aaabb", "aaa11bb", &oldSubString, &oldSubStringLen, &newSubString, &newSubStringLen);
    if (0 != oldSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (2 != newSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    cmpRes = strncmp (newSubString, "11", 2);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, newSubString);
        return false;
    }

    detect_change ("aaa11bb", "aaabb", &oldSubString, &oldSubStringLen, &newSubString, &newSubStringLen);
    if (2 != oldSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (0 != newSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    cmpRes = strncmp (oldSubString, "11", 2);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, oldSubString);
        return false;
    }

    detect_change ("aa111bb", "aa22bb", &oldSubString, &oldSubStringLen, &newSubString, &newSubStringLen);
    if (3 != oldSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (2 != newSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    cmpRes = strncmp (oldSubString, "111", 3);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, oldSubString);
        return false;
    }
    cmpRes = strncmp (newSubString, "22", 2);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, newSubString);
        return false;
    }

    return true;
}

//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2
//"aabb"5,   "aa11bb"7  oldSub""0    newSub"11"2
//"abb"5,   "a11bb"7  oldSub""0    newSub"11"2
//"bb"5,   "11bb"7  oldSub""0    newSub"11"2
//"b"5,   "11b"7  oldSub""0    newSub"11"2
//""0,   "11"2  oldSub""0    newSub"11"2

// Examples:
//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2    < "11" inserted at index 3  oldSubStringLen 0  newSubStringLen: 2
//"aa111bb"7, "aa22bb"6   oldSub"111"3 newSub"22"2    < "11" inserted at index 3  oldSubStringLen 3  newSubStringLen: 2
void detect_change (char *oldStr, char *newStr, char **oldSubStr, int *oldSubStringLen, char **newSubStr, int *newSubStringLen) {
    (void) *oldSubStr;
    (void) *newSubStr;
    *oldSubStringLen = 0;
    *newSubStringLen = 0;
    int oldStrLen = strlen (oldStr);
    int newStrLen = strlen (newStr);
    find_diff (oldStr, oldStrLen, newStr, newStrLen, oldSubStringLen, newSubStringLen, oldSubStr, newSubStr);
}

#if 0
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
    int val = -1;
    if (oldStr && newStr) {
        char *replicaOld = strdup (oldStr);
        char *replicaNew = strdup (newStr);
        if (replicaOld && replicaNew) {
            int oldStrLen = strlen (oldStr);
            int newStrLen = strlen (newStr);
            printf ("\nreplicaOld [%s]", replicaOld);
            printf ("\nreplicaNew [%s]", replicaNew);
            reverse_string (replicaOld);
            reverse_string (replicaNew);
            val = findIndOfFirstDiffFromStart (replicaOld, replicaNew);
            val = max (newStrLen, oldStrLen) - val - 1;
            free (replicaOld);
            free (replicaNew);
        } else {
            printf ("\nError\n");
        }
    }
    return val;
}
#endif

void reverse_string (char *inOutStr) {
    int oldStrLen = strlen (inOutStr);
    reverseString (inOutStr, oldStrLen);
}

void reverseString (char *inOutStr, int length) {
    for (int i = 0; i < (length / 2); i++) {
        swap_char (&inOutStr [i], &inOutStr [(length - 1) - i]);
    }
}

bool test_reverse (void) {
    int cmpRes = 0;
    char tempStr [100];
    strcpy (tempStr, "12345");
    reverseString (tempStr, 5);
    cmpRes = strcmp (tempStr, "54321");
    if (0 != cmpRes) {
        printf ("\ntempStr [%s]\n", tempStr);
        return false;
    }

    return true;
}

void find_diff (
    char *oldStr,
    int oldLen,
    char *newStr,
    int newLen,
    int *outOldSubStringLen,
    int *outNewSubStringLen,
    char **oldSubStr,
    char **newSubStr) {
    // printf ("\n");
    // print_str_head (oldStr, oldLen);
    // printf (" ");
    // print_str_head (newStr, newLen);
    if ((0 < oldLen) && (0 < newLen)) {
        if (oldStr [0] == newStr [0]) {
            find_diff (&oldStr [1], oldLen - 1, &newStr [1], newLen - 1, outOldSubStringLen, outNewSubStringLen, oldSubStr, newSubStr);
        } else {
            if (oldStr [oldLen - 1] == newStr [newLen - 1]) {
                // oldStr [oldLen - 1] = '\0';
                // newStr [newLen - 1] = '\0';
                find_diff (oldStr, oldLen - 1, newStr, newLen - 1, outOldSubStringLen, outNewSubStringLen, oldSubStr, newSubStr);
            } else {
                *outOldSubStringLen = oldLen;
                *outNewSubStringLen = newLen;
                *oldSubStr = oldStr;
                *newSubStr = newStr;
                printf ("\n");
                print_str_head (oldStr, oldLen);
                printf ("\n");
                print_str_head (newStr, newLen);
            }
        }
    } else {
        *outOldSubStringLen = oldLen;
        *outNewSubStringLen = newLen;
        *oldSubStr = oldStr;
        *newSubStr = newStr;
        printf ("\n");
        print_str_head (oldStr, oldLen);
        printf ("\n");
        print_str_head (newStr, newLen);
    }
}

void print_str_head (char *inStr, uint32_t len) {
#if 0
    printf ("\n %s len %d\n ",inStr,len);
#endif
    printf ("[");
    if ((uint32_t) len < (uint32_t) strlen (inStr)) {
        for (uint32_t i = 0; i < len; i++) {
            printf ("%c", inStr [i]);
        }
    }
    printf ("]");
}

//
//
// O(N)
bool is_diff_chars (char *inStr, uint32_t len) {
    init_hash_table ();
    bool res = true;
    if (inStr && 0 < len) {
        uint32_t strLen = strlen (inStr);
        if (len <= strLen) {
            for (uint32_t i = 0; i < len; i++) {
                if (hash_table_char_check (inStr [i]) < 0) {
                    bool res = hash_table_char_put (inStr [i], i);
                    if (false == res) {
                        printf ("\n Error\n");
                    }
                } else {
                    return false;
                }
            }
        } else {
            res = false;
        }
    } else {
        res = false;
    }
    return res;
}

int myAtoi (char *str) {
    int val = 0;
    bool res;
    res = try_strl2int32_dec (str, strlen (str), &val);
    if (false == res) {
        printf ("\nError!\n");
    }
    return val;
}

bool test_myAtoi (void) {
    int val;
    char inStr [40];

    strcpy (inStr, "20000000000000000000");
    val = myAtoi (inStr);
    if (INT32_MAX != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "+1");
    val = myAtoi (inStr);
    if (1 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "-91283472332");
    val = myAtoi (inStr);
    if (INT32_MIN != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "4193 with words");
    val = myAtoi (inStr);
    if (4193 != val) {
        printf ("\n%s %d [%s] outVal [%d]", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "-42");
    val = myAtoi (inStr);
    if (-42 != val) {
        printf ("\n%s %d val %d exp(%d)", __FUNCTION__, __COUNTER__, val, -42);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "   -42");
    val = myAtoi (inStr);
    if (-42 != val) {
        printf ("\n%s %d [%s] val %d exp(%d)", __FUNCTION__, __COUNTER__, inStr, val, -42);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
    }

    strcpy (inStr, "words and 987");
    val = myAtoi (inStr);
    if (0 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "21");
    val = myAtoi (inStr);
    if (21 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }
    return true;
}

bool try_strl2int32_dec (const char s32_dec_str [], int32_t s32_dec_str_len, int32_t * const s32_dec_value) {
    int64_t s32l_dec_result = 0;
    int32_t i = 0;
    while ((' ' == s32_dec_str [i]) && (i < s32_dec_str_len)) {
        i++;
    }
    bool s32l_dec_success = try_strl2int64_dec ((s32_dec_str + i), s32_dec_str_len - i, &s32l_dec_result);

    if (true == s32l_dec_success) {
        if ((INT32_MAX < s32l_dec_result)) {
            *s32_dec_value = INT32_MAX;
        } else {
            if (s32l_dec_result < INT32_MIN) {
                *s32_dec_value = INT32_MIN;
            } else {
                *s32_dec_value = (int32_t) s32l_dec_result;
            }
        }
    } else {
        s32l_dec_success = false;
        *s32_dec_value = 0;
    }

    return s32l_dec_success;
}

bool try_strl2int64_dec (const char s64_dec_str [], int32_t s64_dec_str_len, int64_t *s64_dec_value) {
    bool s64l_dec_success = true;
    bool s64l_dec_signed = false;
    bool signePresent = false;
    int64_t s64l_dec_result = 0;

    int32_t s64l_dec_str_index;

    signePresent = is_signe (s64_dec_str [0]);
    if (true == signePresent) {
        s64l_dec_signed = is_signed (s64_dec_str [0]);
    }

    if ((s64l_dec_signed == true) && (s64_dec_str_len < 2)) {
        s64l_dec_success = false;
    }

    if (s64l_dec_success == true) {
        if (true == signePresent) {
            s64l_dec_str_index = 1;
        } else {
            s64l_dec_str_index = 0;
        }

        for (; s64l_dec_str_index < s64_dec_str_len; s64l_dec_str_index++) {
            uint8_t s64_dec_str_char = (uint8_t) s64_dec_str [s64l_dec_str_index];
            uint8_t s64_dec_str_number = 0U;
            int64_t s64_dec_temp_value = 0;

            s64l_dec_success = try_dec_char_to_u8 (s64_dec_str_char, &s64_dec_str_number);
            if (s64l_dec_success == true) {
                if (s64l_dec_result < (INT64_MAX / 10)) {
                    s64_dec_temp_value = (s64l_dec_result * 10) + (int64_t) s64_dec_str_number;
                } else {
#ifdef DEBUG_ITOA
                    printf ("\n stop overflow may happen [%lld]\n", (long long int) s64l_dec_result);
#endif
                    s64_dec_temp_value = INT64_MAX;
                }

            } else {
                s64l_dec_success = true;
                break;
            }

            if (s64l_dec_result <= s64_dec_temp_value) {
                s64l_dec_result = s64_dec_temp_value;
            } else {
                /*crash! int64_t overflow detected*/
                s64l_dec_result = INT64_MAX;
#ifdef DEBUG_ITOA
                printf ("\n type overflow [%lld] [%lld]\n", (long long int) s64l_dec_result, (long long int) s64_dec_temp_value);
#endif
            }
        }
    }

    if (s64l_dec_signed == true) {
        *s64_dec_value = -s64l_dec_result;
    } else {
        *s64_dec_value = s64l_dec_result;
    }

    return s64l_dec_success;
}

bool is_signe (const char first_str_char) {
    bool signePresent = false;
    if (('-' == first_str_char) || ('+' == first_str_char)) {
        signePresent = true;
    }

    return signePresent;
}

bool is_signed (const char first_str_char) {
    bool negative = false;
    if (first_str_char == '-') {
        negative = true;
    }
    return negative;
}

bool test_num_to_bin_str (void) {
    int cmpRes = 0;
    cmpRes = strcmp ("1010_1010_1010_1010_1010_1010_1010_1010", uint32_to_bin_str (0xAAAAAAAA));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("0101_0101_0101_0101_0101_0101_0101_0101", uint32_to_bin_str (0x55555555));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("0000_0000_0000_0000_0000_0000_0000_0000", uint32_to_bin_str (0x00000000));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("1111_1111_1111_1111_1111_1111_1111_1111", uint32_to_bin_str (0xFFFFFFFF));
    if (0 != cmpRes) {
        return false;
    }
    return true;
}
//
// 1111_1111_1111_1111_1111_1111_1111_1111
char *uint32_to_bin_str (uint32_t const inVal32bit) {
    static char outBitStr [40] = "";
    int8_t rBit = 0;
    uint8_t cell = 0u, bitCnt = 0u;
    uint32_t mask = 0u;
    for (rBit = 31; 0 <= rBit; rBit--) {
        if (cell < sizeof(outBitStr)) {
            if (4u == bitCnt) {
                outBitStr [cell] = '_';
                bitCnt = 0u;
                cell++;
            }
            mask = (uint32_t) (((uint32_t) 1u) << ((uint32_t) rBit));
            bitCnt++;
            if (0u != (inVal32bit & mask)) {
                outBitStr [cell] = '1';
            } else {
                outBitStr [cell] = '0';
            }
        }
        cell++;
    }
    return outBitStr;
}

// "&(t,f)"
// "|(f,t)"
// "|(&(t,f,t),!(t))"
// "!(f)"

bool parseBoolExpr (char *expression) {
    bool res = false;
    if (expression) {
        int inStrlen = strlen (expression);
        if (1 == inStrlen) {
            return parse_single_char (expression);
        }
        if (0 < inStrlen) {
            switch (expression [0]) {
                case '(': {
                }
                    break;
                case '|': {
                    res = parse_or (&expression [1]);
                }
                    break;
                case '!': {
                    res = parse_not (&expression [1]);
                }
                    break;
                case '&': {
                    res = parse_and (&expression [1]);
                }
                    break;
                default: {
                    printf ("\n\r error\n\r");
                }
                    break;
            }
        }
    }
    return res;
}

static bool parse_single_char (char *expression) {
    switch (expression [0]) {
        case 't': {
            return true;
        }
            break;
        case 'f': {
            return false;
        }

        default: {
            printf ("error");
        }
            break;
    }
    return false;
}

//   "(f,t)"
//   "(&(t,f,t),!(t))"
static bool parse_or (char *expression) {
    bool res = false;
    if (expression) {
        int inStrLen = strlen (expression);
        if (0 < inStrLen) {
            int amountOfoperand = parse_num_operands (expression);
            res = false;
            for (int i = 0; i < amountOfoperand; i++) {
                // res |= get_oparand (expression, i);
            }
        }
    }
    return res;
}

// "(t,f,t)"          3
// "(t,f)"            2
// "(f,t)"            2
// "(&(t,f,t),!(t))"  2
// "(&(t,&(f,t),t),!(t))"  2
static bool parse_and (char *expression) {
    bool res = false;
    if (expression) {
        int inStrLen = strlen (expression);
        if (0 < inStrLen) {
            int amountOfoperand = parse_num_operands (expression);
            res = true;
            for (int i = 0; i < amountOfoperand; i++) {
                // res &= get_oparand (expression, i);
            }
        }
    }
    return res;
}
//                               level of nesting
// "(t,f,t)"               3     1
// "(t,f)"                 2     1
// "(&(t,f,t),!(t))"       2     2
// "(&(t,&(f,t),t),!(t))"  2     3
static int parse_num_operands (char *expression) {
    int numOfOperands = 0;
    if (expression) {
        Lifo_array_t lifoObj;
        int inStrLen = strlen (expression);
        if (0 < inStrLen) {
            char *array = malloc (inStrLen);
            if (array) {
                lifo_init (&lifoObj, inStrLen, array);
                for (int i = 0; i < inStrLen; i++) {
                    char outChar = 'a';
                    if (is_bracket (expression [i])) {
                        lifo_peek (&lifoObj, &outChar);
                        if (true == brackets_same_type (outChar, expression [i])) {
                            lifo_pull (&lifoObj, &outChar);
                        } else {
                            lifo_push (&lifoObj, expression [i]);
                        }

                    } else {
                        if (',' == expression [i]) {
                            if (1 == lifoObj.lifoStat.len) {
                                numOfOperands++;
                            }
                        }
                    }
                }
            numOfOperands++;
            }
        }
    }
    return numOfOperands;
}

bool test_parse_num_operands (void) {
    EXPECT_EQ(3, parse_num_operands ("(t,f,t)"));
    EXPECT_EQ(2, parse_num_operands ("(t,f)"));
    EXPECT_EQ(2, parse_num_operands ("(&(t,f,t),!(t))"));
    EXPECT_EQ(2, parse_num_operands ("(&(t,&(f,t),t),!(t))"));
    return true;
}

//(f)
static bool parse_not (char *expression) {
    bool res = false;
    if (expression) {
        int inStrLen = strlen (expression);
        if (1 == inStrLen) {
            return !parse_single_char (expression);
        } else {
            res = !parseBoolExpr (expression);
        }
    }
    return res;
}

bool test_parseBoolExpr (void) {
    bool res = false;
    res = parseBoolExpr ("!(f)");
    if (false == res) {
        return false;
    }
    res = parseBoolExpr ("|(&(t,f,t),!(t))");
    if (true == res) {
        return false;
    }

    res = parseBoolExpr ("|(f,t)");
    if (false == res) {
        return false;
    }
    res = parseBoolExpr ("&(t,f)");
    if (true == res) {
        return false;
    }
    return true;
}

//                               level of nesting
// "(t,f,t)"                    1
// "(t,f)"                      1
// "(&(t,f,t),!(t))"            2
// "(&(t,&(f,t),t),!(t))"       3
int calc_paratasis_nesting (char *s, int * const amountOfPairs) {
    bool res;
    int nestDepth = -1;
    (*amountOfPairs) = 0u;
    res = is_valid_parentheses (s);
    if (res) {
        nestDepth = 0;
        int strLen = strlen (s);
        char *array = malloc (strLen);
        if (array) {
            Lifo_array_t lifoObj;
            lifo_init (&lifoObj, strLen, array);
            for (int i = 0; i < strLen; i++) {
                char outChar = 'a';
                if (is_bracket (s [i])) {
                    lifo_peek (&lifoObj, &outChar);
                    if (true == brackets_same_type (outChar, s [i])) {
                        lifo_pull (&lifoObj, &outChar);
                        (*amountOfPairs)++;
                    } else {
                        lifo_push (&lifoObj, s [i]);
                        nestDepth = max (lifoObj.lifoStat.len, nestDepth);
                    }
                }
            }
            free (array);
        }
    }
    return nestDepth;
}

bool test_calc_paratasis_nesting (void) {
    int amountOfPairs = 0;
    EXPECT_EQ(1, calc_paratasis_nesting ("(t,f,t)", &amountOfPairs));
    EXPECT_EQ(1, amountOfPairs);

    EXPECT_EQ(1, calc_paratasis_nesting ("(t,f)", &amountOfPairs));
    EXPECT_EQ(1, amountOfPairs);

    EXPECT_EQ(2, calc_paratasis_nesting ("(&(t,f,t),!(t))", &amountOfPairs));
    EXPECT_EQ(3, amountOfPairs);

    EXPECT_EQ(3, calc_paratasis_nesting ("(&(t,&(f,t),t),!(t))", &amountOfPairs));
    EXPECT_EQ(4, amountOfPairs);

    return true;
}

bool is_valid_parentheses (char *s) {
    bool res = false;
    Lifo_array_t lifoObj;
    int strLen = strlen (s);
    char *array = malloc (strLen);
    if (array) {
        lifo_init (&lifoObj, strLen, array);
        char outChar = 'a';
        for (int i = 0; i < strLen; i++) {
            outChar = 'a';
            if (is_bracket (s [i])) {
                lifo_peek (&lifoObj, &outChar);
                if (true == brackets_same_type (outChar, s [i])) {
                    lifo_pull (&lifoObj, &outChar);
                } else {
                    lifo_push (&lifoObj, s [i]);
                }

            }
        }
        if (0 == lifoObj.lifoStat.len) {
            res = true;
        }
        free (array);
    }
    return res;
}

bool test_Valid_Parentheses (void) {
    EXPECT_TRUE(is_valid_parentheses ("()[]{}"));
    EXPECT_TRUE(is_valid_parentheses ("(t,f,t)"));
    EXPECT_TRUE(is_valid_parentheses ("(&(t,&(f,t),t),!(t))"));
    return true;
}

bool is_bracket (char ch) {
    bool res = false;
    switch (ch) {
        case '}':
        case '{':
        case '[':
        case ']':
        case '(':
        case ')':
        case '>':
        case '<':
            res = true;
            break;
        default:
            res = false;
            break;
    }
    return res;
}

bool brackets_same_type (char open, char close) {
    if (('(' == open) && (')' == close)) {
        return true;
    }
    if (('[' == open) && (']' == close)) {
        return true;
    }
    if (('{' == open) && ('}' == close)) {
        return true;
    }
    if (('<' == open) && ('>' == close)) {
        return true;
    }
    return false;
}

#if 0
static bool get_oparand (char *expression, int i) { return false; }
#endif
