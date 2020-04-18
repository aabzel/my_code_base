#include "str_ops.h"

#include "algorithms.h"
#include "custom_type.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#if 0
static int findIndOfFirstDiffFromStart (char *oldStr, char *newStr);
static int findIndOfFirstDiffFromEnd (char *oldStr, char *newStr);
#endif

static bool hash_table_char_put (char character, int indexInArray);
//static bool hash_table_char_remove (char character);
static void init_hash_table (void);

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
//bpfbhmipx 1


#if 0
static void full_str_with (char *s, char pattern, int size) {
    for (int i = 0; i < size; i++) {
        s [i] = pattern;
    }
}
#endif
//abcabcbb 8
//pwwkew
int lengthOfLongestSubstring (char * inStr) {
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
            for (j = 1; j <= (strLen-i); j++) {
                if (hash_table_char_check (inStr [i+j-1]) < 0) {
                    res = hash_table_char_put (inStr [i+j-1], i);
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

int find_max_sec (char * string, char sripChar) {
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
    char* oldSubString;
    char* newSubString;
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

//Examples:
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
    char* oldStr,
    int oldLen,
    char* newStr,
    int newLen,
    int *outOldSubStringLen,
    int *outNewSubStringLen,
    char **oldSubStr,
    char **newSubStr) {
//printf ("\n");
//print_str_head (oldStr, oldLen);
//printf (" ");
//print_str_head (newStr, newLen);
    if ((0 < oldLen) && (0 < newLen)) {
        if (oldStr [0] == newStr [0]) {
            find_diff (&oldStr [1], oldLen - 1, &newStr [1], newLen - 1, outOldSubStringLen, outNewSubStringLen, oldSubStr, newSubStr);
        } else {
            if (oldStr [oldLen - 1] == newStr [newLen - 1]) {
                //oldStr [oldLen - 1] = '\0';
                //newStr [newLen - 1] = '\0';
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
//O(N)
bool is_diff_chars (char *inStr, uint32_t len) {
    init_hash_table ();
    bool res=true;
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
        }else{
            res=false;
        }
    }else{
        res=false;
    }
    return res;
}
