#include "str_ops.h"

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "algorithms.h"
#include "convert.h"
//#include "custom_type.h"

#if 0
static int findIndOfFirstDiffFromStart (char *old_str, char *newStr);
static int findIndOfFirstDiffFromEnd (char *old_str, char *newStr);
#endif

#if 0
static bool get_oparand (char *expression, int i);
#endif

// static bool parse_single_char(char *expression);
static bool hash_table_char_put(char character, int indexInArray);
// static bool hash_table_char_remove (char character);
static void init_hash_table(void);

static int hash_table_char_check(char character);

// output: pointer address to the array of pointers
int split(char *source, char *delim, char ***outStrArr) {
  // printf ("\n text  [%s] pattern [%s]\n", source, delim);
  *outStrArr = NULL;
  int numItem = 0, numItemInStr = 0;
  int j = 0;
  bool isFirst = true;
  int srcLen = strlen(source);
  int delimLen = strlen(delim);
  numItemInStr = count_amount_of_item(source, delim);
  char **arrStrings = malloc((1 + numItem) * sizeof(char *));
  for (int k = 0; k < numItemInStr; k++) {
    // printf ("\n address of ptrs: arrStrings[p]: [%p]", arrStrings [k]);
  }
  // printf ("\n");
  if (*arrStrings) {
    for (int i = 0; i <= (srcLen - delimLen); i++) {
      int cmpRes = strncmp(delim, &source[i], delimLen);
      if (0 == cmpRes) {
        // //printf ("\nSpot pattern\n");
        if (0 == i) {
          // pattern in the first
          numItem++;
          isFirst = false;
          char *str = select_sub_string(&source[i + delimLen], delim);
          // printf (" [%s] ", str);
          arrStrings[j++] = (char *)str;
        } else if ((srcLen - delimLen) == i) {
          // pattern in the end
          if (0 == numItem) {
            char *str = select_sub_string(&source[0], delim);
            // printf (" [%s] ", str);
            arrStrings[j++] = (char *)str;
            numItem = 1;
          }
        } else {
          // pattern in the middle
          if (true == isFirst) {
            char *str = select_sub_string(&source[0], delim);
            if (str) {
              // printf (" [%s] ", str);
              arrStrings[j++] = (char *)str;

            } else {
              // printf ("\n malloc Error! \n");
            }
            numItem += 2;
            isFirst = false;
          } else {
            numItem++;
          }
          char *str = select_sub_string(&source[i + delimLen], delim);
          // printf (" [%s] ", str);
          arrStrings[j++] = (char *)str;
        }
      }
    }

    *outStrArr = arrStrings;
  } else {
    // printf ("malloc error");
  }
  // printf ("\n ");
  return numItemInStr;
}
//(qwerrty    RE)   return   "qwerty"
//(qweRTy    RT)   return   "qwe"
//(QWerty    QW)   return   ""
char *select_sub_string(char *text, char *tail) {
  char *outStr = NULL;
  if (text && tail) {
    bool isPatternSpot = false;
    int lenText = strlen(text);
    int lenTail = strlen(tail);
    if (lenTail < lenText) {
      for (int i = 0; i <= (lenText - lenTail); i++) {
        int cmpRes = strncmp(&text[i], tail, lenTail);
        if (0 == cmpRes) {
          isPatternSpot = true;
          if (0 < i) {
            outStr = malloc(sizeof(char) * i + 1);
            if (outStr) {
              memset(outStr, 0x00, sizeof(char) * (i + 1));
              memcpy(outStr, text, sizeof(char) * i);
              return outStr;
            }
          } else {
            outStr = strdup("");
            if (outStr) {
              return outStr;
            }
          }
        }
      }
      if (false == isPatternSpot) {
        outStr = strdup(text);
        if (outStr) {
          return outStr;
        }
      }
    }
  }
  return outStr;
}

// strstr
int count_amount_of_item(char *source, char *delim) {
  int numItem = 0;
  bool isFirst = true;
  int srcLen = strlen(source);
  int delimLen = strlen(delim);
  if (delimLen < srcLen) {
    for (int i = 0; i <= (srcLen - delimLen); i++) {
      int cmpRes = strncmp(delim, &source[i], delimLen);
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
bool is_real_number(const char str[]);

char *removeCharFromString(char *str, uint32_t delIndex) {
  size_t alphabetLength = strlen(str);
  char *tempArray = malloc(alphabetLength);
  if (tempArray) {
    strcpy(tempArray, str);
    uint32_t index = 0;
    if (delIndex < (alphabetLength + 1)) {
      for (index = delIndex; index < (alphabetLength - 1); index++) {
        tempArray[index] = tempArray[index + 1];
      }
    }
    tempArray[alphabetLength - 1] = '\0';
    return tempArray;
  } else {
    printf("Malloc error");
  }

  return NULL;
}

bool isNumber(char *s) {
  bool res = false;
  res = is_float_number(s);
  // printf ("\n instr [%s]", s);
  return res;
}

bool is_float_number(const char inStr[]) {
  bool float_success = is_real_number(inStr);
  return float_success;
}

static bool is_space(const char character) {
  bool res = false;
  if (' ' == character) {
    res = true;
  }
  return res;
}

static bool is_spaces(const char str[]) {
  bool res = true;
  uint32_t str_len = strlen(str);
  uint32_t strIndex = 0u;
  for (strIndex = 0; strIndex < str_len; strIndex++) {
    if (false == is_space((char)(str[strIndex]))) {
      res = false;
    }
  }
  return res;
}

bool is_real_number(const char str[]) {
  bool strtod_success = true;
  double_t number = 0.0;
  uint32_t str_index = 0U;
  int32_t s32_number;
  uint8_t num_digits = 0U;
  uint8_t num_decimals = 0U;
  uint8_t temp_value = 0U;
  uint32_t str_len = strlen(str);

  /* Skip leading whitespace */
  while (isspace((int32_t)(str[str_index])) > 0) {
    str_index++;
  }

  /* Handle optional sign */
  if (('-' == str[str_index]) || ('+' == str[str_index])) {
    if ('-' == str[str_index]) {
    }
    str_index++;
  }

  if (0 == isdigit((int32_t)(str[str_index]))) {
    // strtod_success = false;
    number = 0.0;
  } else {
    /* Process string of digits */
    while (0 < isdigit((int32_t)(str[str_index]))) {
      (void)try_dec_char_to_u8((uint8_t)str[str_index], &temp_value);
      number = (number * 10.0) + (double_t)temp_value;
      str_index++;
      num_digits++;
    }
  }

  if (true == strtod_success) {
    /* Process decimal part  */
    if (str[str_index] == '.') {
      str_index++;
      if (0 < isdigit((int32_t)(str[str_index]))) {
        while (0 < isdigit((int32_t)(str[str_index]))) {
          (void)try_dec_char_to_u8((uint8_t)str[str_index], &temp_value);
          number = (number * 10.0) + (double_t)temp_value;
          str_index++;
          num_digits++;
          num_decimals++;
        }
        /*12.4545[]*/
        if (' ' != str[str_index] && '\0' != str[str_index] &&
            'e' != str[str_index] && 'E' != str[str_index]) {
          strtod_success = false;
        }

      } else {
        if (' ' != str[str_index] && '\0' != str[str_index] &&
            'e' != str[str_index] && 'E' != str[str_index]) {
          strtod_success = false;
        }
      }
    } else {
      if ('\0' != str[str_index] && ' ' != str[str_index] &&
          'E' != str[str_index] && 'e' != str[str_index]) {
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
    if ((str[str_index] == 'e') || (str[str_index] == 'E')) {
      /* Handle optional sign */

      str_index++;

      if (('-' == str[str_index]) || ('+' == str[str_index])) {
        str_index++;
      }
      if (false == isdigit((int32_t)(str[str_index]))) {
        /* in case of "0e" */
        strtod_success = false;
      } else {
        /* Process string of digits */
        s32_number = 0;
        while (isdigit((int32_t)(str[str_index])) > 0) {
          (void)try_dec_char_to_u8((uint8_t)str[str_index], &temp_value);
          s32_number = (s32_number * 10) + (int32_t)temp_value;
          str_index++;
        }
        if (' ' != str[str_index] && ('\0' != str[str_index])) {
          strtod_success = false;
        }
      }
    }
  }
  if (true == strtod_success) {
    if (str_index < (str_len - 1)) {
      /* "1 4" */
      strtod_success = is_spaces(&str[str_index]);
    }
  }
  return strtod_success;
}

bool try_dec_char_to_u8(uint8_t dec_char, uint8_t *dec_char_to_u8_value) {
  uint8_t dec_char_to_u8_result = 0U;
  bool dec_char_to_u8_success = true;

  if ((dec_char < (uint8_t)'0') || (dec_char > (uint8_t)'9')) {
    dec_char_to_u8_success = false;
  }

  if (dec_char_to_u8_success == true) {
    dec_char_to_u8_result = dec_char - (uint8_t)'0';
  }

  *dec_char_to_u8_value = dec_char_to_u8_result;
  return dec_char_to_u8_success;
}

static int gHashSize = 0;
static int gCharHashTable[512] = {0};

static bool hash_table_char_put(char character, int indexInArray) {
  bool res = false;
  if (0 <= gCharHashTable[(int)character]) {
#if DEBUG_HASH_TABLE
    printf("\nCollision\n");
#endif
  } else {
#if DEBUG_HASH_TABLE
    printf("new in table [%c] %d", character, indexInArray);
#endif
    gCharHashTable[(int)character] = indexInArray;
    gHashSize++;
    res = true;
  }
  return res;
}

static int hash_table_char_check(char character) {
  if (0 <= gCharHashTable[(int)character]) {
    return gCharHashTable[(int)character];
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
static void init_hash_table(void) {
  gHashSize = 0;
  int sizeOfArray = sizeof(gCharHashTable) / sizeof(gCharHashTable[0]);
  for (int i = 0; i < sizeOfArray; i++) {
    gCharHashTable[i] = -1;
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
#if 0
int lengthOfLongestSubstring (char *inStr) {
    int maxNumUnicChars = 0;
    bool res;
    uint32_t i, j;

#if DEBUG_LENGTHOFLONGESTSUBSTRING
    printf ("\n str: %s ", inStr);
#endif
    if (inStr) {
        uint32_t str_len = strlen (inStr);
        for (i = 0; i < str_len; i++) {
            init_hash_table ();
            for (j = 1; j <= (str_len - i); j++) {
                if (hash_table_char_check (inStr[i + j - 1]) < 0) {
                    res = hash_table_char_put (inStr[i + j - 1], i);
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
#endif

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
        uint32_t str_len = strlen (inStr);
        for (i = 0; i < str_len; i++) {
            for (j = 1; j <= (str_len-i); j++) {
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

int find_max_sec (char *string, char sripChar) {
    int maxCnt = 0;
    int curCnt = 0;
    int str_len = strlen (string);
    for (int i = 0; i < str_len; i++) {
        if (sripChar != string[i]) {
            curCnt++;
        } else {
            curCnt = 0;
        }
        maxCnt = update_max (maxCnt, curCnt);
    }
    return maxCnt;
}
#endif
//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2
//"aabb"5,   "aa11bb"7  oldSub""0    newSub"11"2
//"abb"5,   "a11bb"7  oldSub""0    newSub"11"2
//"bb"5,   "11bb"7  oldSub""0    newSub"11"2
//"b"5,   "11b"7  oldSub""0    newSub"11"2
//""0,   "11"2  oldSub""0    newSub"11"2

// Examples:
//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2    < "11" inserted at index 3
//oldSubStringLen 0  newSubStringLen: 2 "aa111bb"7, "aa22bb"6   oldSub"111"3
//newSub"22"2    < "11" inserted at index 3  oldSubStringLen 3  newSubStringLen:
//2
void detect_change(char *old_str, char *newStr, char **oldSubStr,
                   int *oldSubStringLen, char **newSubStr,
                   int *newSubStringLen) {
  (void)*oldSubStr;
  (void)*newSubStr;
  *oldSubStringLen = 0;
  *newSubStringLen = 0;
  int old_str_len = strlen(old_str);
  int newStrLen = strlen(newStr);
  find_diff(old_str, old_str_len, newStr, newStrLen, oldSubStringLen,
            newSubStringLen, oldSubStr, newSubStr);
}

#if 0
static int findIndOfFirstDiffFromStart (char *old_str, char *newStr) {
    if (old_str && newStr) {
        int old_str_len = strlen (old_str);
        int newStrLen = strlen (newStr);
        for (int i = 0; i < min (old_str_len, newStrLen); i++) {
            if (old_str [i] != newStr [i]) {
                return i;
            }
        }
    }
    return -1;
}
static int findIndOfFirstDiffFromEnd (char *old_str, char *newStr) {
    int val = -1;
    if (old_str && newStr) {
        char *replicaOld = strdup (old_str);
        char *replicaNew = strdup (newStr);
        if (replicaOld && replicaNew) {
            int old_str_len = strlen (old_str);
            int newStrLen = strlen (newStr);
            printf ("\nreplicaOld [%s]", replicaOld);
            printf ("\nreplicaNew [%s]", replicaNew);
            reverse_string (replicaOld);
            reverse_string (replicaNew);
            val = findIndOfFirstDiffFromStart (replicaOld, replicaNew);
            val = max (newStrLen, old_str_len) - val - 1;
            free (replicaOld);
            free (replicaNew);
        } else {
            printf ("\nError\n");
        }
    }
    return val;
}

void reverse_string (char *inOutStr) {
    int old_str_len = strlen (inOutStr);
    reverseString (inOutStr, old_str_len);
}

void reverseString (char *inOutStr, int length) {
    for (int i = 0; i < (length / 2); i++) {
        swap_char (&inOutStr[i], &inOutStr[(length - 1) - i]);
    }
}
#endif
char findTheDifference(char *old_str, char *newStr) {
  printf("\n%s()", __FUNCTION__);
  char *oldSubStr = NULL;
  int oldSubStringLen = 0;
  char *newSubStr = NULL;
  char out_char = 0;
  int newSubStringLen = 0;
  detect_change(old_str, newStr, &oldSubStr, &oldSubStringLen, &newSubStr,
                &newSubStringLen);
  if (1 == newSubStringLen) {
    out_char = newSubStr[0];
  }
  if (1 == oldSubStringLen) {
    out_char = oldSubStr[0];
  }
  return out_char;
}

void find_diff(char *old_str, int oldLen, char *newStr, int newLen,
               int *outOldSubStringLen, int *outNewSubStringLen,
               char **oldSubStr, char **newSubStr) {
  // printf ("\n");
  // print_str_head (old_str, oldLen);
  // printf (" ");
  // print_str_head (newStr, newLen);
  if ((0 < oldLen) && (0 < newLen)) {
    if (old_str[0] == newStr[0]) {
      find_diff(&old_str[1], oldLen - 1, &newStr[1], newLen - 1,
                outOldSubStringLen, outNewSubStringLen, oldSubStr, newSubStr);
    } else {
      if (old_str[oldLen - 1] == newStr[newLen - 1]) {
        // old_str [oldLen - 1] = '\0';
        // newStr [newLen - 1] = '\0';
        find_diff(old_str, oldLen - 1, newStr, newLen - 1, outOldSubStringLen,
                  outNewSubStringLen, oldSubStr, newSubStr);
      } else {
        *outOldSubStringLen = oldLen;
        *outNewSubStringLen = newLen;
        *oldSubStr = old_str;
        *newSubStr = newStr;
        // printf ("\n");
        // print_str_head (old_str, oldLen);
        // printf ("\n");
        // print_str_head (newStr, newLen);
      }
    }
  } else {
    *outOldSubStringLen = oldLen;
    *outNewSubStringLen = newLen;
    *oldSubStr = old_str;
    *newSubStr = newStr;
    // printf ("\n");
    // print_str_head (old_str, oldLen);
    // printf ("\n");
    // print_str_head (newStr, newLen);
  }
}

void print_str_head(char *inStr, uint32_t len) {
#if 0
    printf ("\n %s len %d\n ",inStr,len);
#endif
  printf("[");
  if ((uint32_t)len < (uint32_t)strlen(inStr)) {
    for (uint32_t i = 0; i < len; i++) {
      printf("%c", inStr[i]);
    }
  }
  printf("]");
}

//
//
// O(N)
bool is_diff_chars(char *inStr, uint32_t len) {
  init_hash_table();
  bool res = true;
  if (inStr && 0 < len) {
    uint32_t str_len = strlen(inStr);
    if (len <= str_len) {
      for (uint32_t i = 0; i < len; i++) {
        if (hash_table_char_check(inStr[i]) < 0) {
          bool res = hash_table_char_put(inStr[i], i);
          if (false == res) {
            printf("\n Error\n");
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

#if 0
int myAtoi (char *str) {
    int val = 0;
    bool res;
    res = try_strl2int32_dec (str, strlen (str), &val);
    if (false == res) {
        printf ("\nError!\n");
    }
    return val;
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
#if 0
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
                    printf ("\n stop overflow may happen [%lld]\n", (long long int)s64l_dec_result);
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
                printf ("\n type overflow [%lld] [%lld]\n", (long long int)s64l_dec_result,
                        (long long int)s64_dec_temp_value);
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
#endif
bool is_signe (const char first_str_char) {
    bool signePresent = false;
    if (('-' == first_str_char) || ('+' == first_str_char)) {
        signePresent = true;
    }

    return signePresent;
}
#endif

bool is_signed(const char first_str_char) {
  bool negative = false;
  if (first_str_char == '-') {
    negative = true;
  }
  return negative;
}

//
// 1111_1111_1111_1111_1111_1111_1111_1111
char *uint32_to_bin_str(uint32_t inVal32bit) {
  static char outBitStr[40] = "";
  int8_t rBit = 0;
  uint8_t cell = 0u, bitCnt = 0u;
  uint32_t mask = 0u;
  for (rBit = 31; 0 <= rBit; rBit--) {
    if (cell < sizeof(outBitStr)) {
      if (4u == bitCnt) {
        outBitStr[cell] = '_';
        bitCnt = 0u;
        cell++;
      }
      mask = (uint32_t)(((uint32_t)1u) << ((uint32_t)rBit));
      bitCnt++;
      if (0u != (inVal32bit & mask)) {
        outBitStr[cell] = '1';
      } else {
        outBitStr[cell] = '0';
      }
    }
    cell++;
  }
  return outBitStr;
}
#if 0

// "&(t,f)"
// "|(f,t)"
// "|(&(t,f,t),!(t))"
// "!(f)"
// "(f)"

bool parseBoolExpr(char *expression) {
	bool res = false;
	if (expression) {
		int inStrlen = strlen(expression);
		if (0 < inStrlen) {
			res = parse_bool_expr(&expression[0], inStrlen);
		}
	}
	return res;
}

// "&(t,f)"
// "|(f,t)"
// "|(&(t,f,t),!(t))"
// "!(f)"
// "(f)"
bool parse_bool_expr(char *expression, int inStrLen) {
#if DEBUG_PARSE_EXPRESS
    printf (NEW_LINE "parse: <");
    print_sub_str (expression, inStrLen);
    printf ("> len: %d" NEW_LINE, inStrLen);
#endif
	bool res = false;
	if (expression) {
		if (1 == inStrLen) {
			return parse_single_char(expression);
		}
		if (0 < inStrLen) {
			switch (expression[0]) {
			case '(': {
				if (((char) 0x29) == expression[inStrLen - 1]) {
					res = parse_bool_expr(&expression[1], inStrLen - 2);
				} else {
					printf(NEW_LINE " error [%c] " NEW_LINE,
							expression[inStrLen - 1]);
				}
			}
				break;

			case '|': {
				//"(&(t,f,t),!(t))"
				res = parse_or(&expression[1], inStrLen - 1);
			}
				break;
			case '!': {
				//"!( &( !(&(f)), &(t), |(f,f,t) ) )"
				res = parse_not(&expression[1], inStrLen - 1);
			}
				break;
			case '&': {
				res = parse_and(&expression[1], inStrLen - 1);
			}
				break;
			default: {
				printf(NEW_LINE " error <");
				print_sub_str(expression, inStrLen);
				printf("> len: %d" NEW_LINE, inStrLen);
			}
				break;
			}
		}
	}
	return res;
}

static bool parse_single_char(char *expression) {
	switch (expression[0]) {
	case 't': {
		return true;
	}
		break;
	case 'f': {
		return false;
	}

	default: {
		printf("error");
	}
		break;
	}
	return false;
}

//   "(f,t)"
//   "(&(t,f,t),!(t))"
bool parse_or(char *expression, int inStrLen) {
	bool res = false;

	if (expression) {
#if DEBUG_PARSE_OR
        printf ("\n\r parse OR [");
        print_sub_str (expression, inStrLen);
        printf ("]");
#endif
		if (0 < inStrLen) {
			int amountOfoperand = parse_num_operands(expression, inStrLen);
			res = false;
			int index;
			int lenOfOperand = 0;
			printf(NEW_LINE);
			for (int operand = 0; operand < amountOfoperand; operand++) {
				index = get_index_in_string(expression, inStrLen, operand,
						&lenOfOperand);
				// printf ("OR operand %d: ", operand);
				print_sub_str(&expression[index], lenOfOperand);
				res |= parse_bool_expr(&expression[index], lenOfOperand);
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
bool parse_and(char *expression, int inStrLen) {
	bool res = false;
#if DEBUG_PARSE_AND
    printf (" parse AND [");
    print_sub_str (expression, inStrLen);
    printf ("] len: %d", inStrLen);
#endif

	if (expression) {
		if (0 < inStrLen) {
			int amountOfoperand = parse_num_operands(expression, inStrLen);
			res = true;
			int index;
			int lenOfOperand = 0;
			printf(NEW_LINE);
			for (int operand = 0; operand < amountOfoperand; operand++) {
				index = get_index_in_string(expression, inStrLen, operand,
						&lenOfOperand);
				// printf (" AND:%d: ", operand);
				print_sub_str(&expression[index], lenOfOperand);
				res &= parse_bool_expr(&expression[index], lenOfOperand);
			}
			// printf (NEW_LINE);
		}
	}
	return res;
}

#endif

int replace_char(char *out_str, char orig, char rep) {
  char *ix = out_str;
  int n = 0;
  while ((ix = strchr(ix, orig)) != NULL) {
    *ix++ = rep;
    n++;
  }
  return n;
}

#if 0
bool extract_numbers (char *inOutStr, int length) {
    int curIndex = 0;
    bool res = false;
    int curLen = length;
    for (curIndex = 0; curIndex < curLen; curIndex++) {
        if (false == is_hex_number (inOutStr[curIndex])) {
            res = delete_char (inOutStr, curIndex);
            if (true == res) {
                if (0 < curLen) {
                    curLen--;
                }
            }
        }
    }
    return res;
}
#endif

#if 0
uint16_t calc_ip_val_len (char *inStr) {
    uint16_t strValLen = 0;
    if (inStr) {
        bool runLoop = true;
        while (runLoop) {
            if (true == is_ip_number (inStr[strValLen])) {
                strValLen++;
            } else {
                runLoop = false;
            }
        }
    }
    return strValLen;
}
#endif

uint16_t calc_hex_val_len(char *inStr) {
  uint16_t strValLen = 0;
  if (inStr) {
    bool runLoop = true;
    while (runLoop) {
      if (true == is_hex_number(inStr[strValLen])) {
        strValLen++;
      } else {
        runLoop = false;
      }
    }
  }
  return strValLen;
}
#if 0
bool is_ip_number (char letter) {
    bool res = false;
    switch (letter) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
        res = true;
        break;
    }
    return res;
}
#endif

bool is_hex_number(char letter) {
  bool res = false;
  switch (letter) {
  case 'x':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
    res = true;
    break;
  }
  return res;
}

/// reg addr: 0x04 reg val: 0x0000 Ob_0000_0000_0000_0000
bool try_extract_hex_uint8(char *inStr, int str_len, uint8_t *val8b) {
  int i = 0;
  int startIndex = 0;
  bool res = false;
  int catch = 0;
  int hexValCnt = 0;
  int valLen = 0;
  for (i = 0; i < str_len; i++) {
    if (0 == catch) {
      if ('0' == inStr[i]) {
        valLen = 1;
        catch = 1;
        startIndex = i;
      }
    } else {
      if (1 == valLen) {
        if ('x' != inStr[i]) {
          catch = 0;
          valLen = 0;
        }
        valLen++;
      } else {
        if (true == is_hex_number(inStr[i])) {
          valLen++;
        } else {
          if ((' ' == inStr[i]) || (']' == inStr[i])) {
            hexValCnt++;

            if (4 == valLen) {
              res = try_strl2uint8_hex(&inStr[startIndex + 2], 2, val8b);
              // res = try_str2uint8 (&inStr[startIndex], val8b);
              return res;
            }
            catch = 0;
            valLen = 0;
          }
        }
      }
    }
  }
  return res;
}

/// reg addr: 0x04 reg val: 0x0000 Ob_0000_0000_0000_0000
bool try_extract_hex_uint16(char *inStr, int str_len, uint16_t *val16b) {
  int i = 0;
  (void)val16b;
  bool res = false;
  int catch = 0;
  int startIndex = 0;
  int hexValCnt = 0;
  int valLen = 0;
  for (i = 0; i < str_len; i++) {
    if (0 == catch) {
      if ('0' == inStr[i]) {
        valLen = 1;
        catch = 1;
        startIndex = i;
      }
    } else {
      if (1 == valLen) {
        if ('x' != inStr[i]) {
          catch = 0;
          valLen = 0;
        }
        valLen++;
      } else {
        if (true == is_hex_number(inStr[i])) {
          valLen++;
        } else {
          if (' ' == inStr[i]) {
            hexValCnt++;
            if (6 == valLen) {
              res = try_strl2uint16_hex(&inStr[startIndex + 2], 4, val16b);
              return res;
            }
            catch = 0;
            valLen = 0;
          }
        }
      }
    }
  }
  return res;
}

//< REG="Basic Control" Addr=0
bool parse_text_after_prefix(char *cur_file_str, int in_str_len, char *out_text,
                             uint16_t *text_len, char *prefix,
                             char terminator) {
  bool res = false;
  (*text_len) = 0;
  int prefix_len = strlen(prefix);
  char *ptr = strstr(cur_file_str, prefix);
  if (ptr) {
#ifdef DEBUG_GENERATE_REG_PARSER
    printf("\n spot prefix [%s]", prefix);
#endif
    res = true;
    int i = 0;
    for (i = 0; i < in_str_len; i++) {
      if (('"' != *(ptr + prefix_len + i)) &&
          (terminator != *(ptr + prefix_len + i))) {
        out_text[i] = *(ptr + prefix_len + i);
        (*text_len)++;
        res = true;
      } else {
        break;
      }
    }
    out_text[i] = 0x00;
  } else {
    res = false;
#ifdef DEBUG_GENERATE_REG_PARSER
    printf("\n lack of prefix [%s]", prefix);
#endif
  }
  return res;
}

bool try_extract_hex_uint8_array(char *inStr, int str_len, uint8_t *val_array,
                                 uint16_t *out_reg_blob_len) {
  bool res = false;
#ifdef DEBUG_EXTRACT_HEX_ARRAY
  printf("\n %s() %s len: %u", __FUNCTION__, inStr, str_len);
#endif
  (*out_reg_blob_len) = 0;
  char out_text[str_len * 2];
  uint16_t text_len = 0;
  res = parse_text_after_prefix(inStr, str_len, out_text, &text_len, "0s", '|');
  if (true == res) {
    uint32_t cnt = 0;
    uint32_t i = 0;
#ifdef DEBUG_EXTRACT_HEX_ARRAY
    printf("\n extracted [%s] %u", out_text, text_len);
#endif
    for (i = 0, cnt = 0; i < text_len; i += 2, cnt++) {
#ifdef DEBUG_EXTRACT_HEX_ARRAY
      printf("\n parse [%s]", &out_text[i]);
#endif
      res = try_strl2uint8_hex(&out_text[i], 2, &val_array[cnt]);
      if (true == res) {
        (*out_reg_blob_len)++;
      } else {

        printf("\n Unable to parse uint8 [%s]", &out_text[i]);
      }
    }
  }
  return res;
}

///      DEVICE_ID[0x01]: 0x00000020 0b_0000_0000_0000_0000_0000_0000_0010_0000
bool try_extract_hex_uint32(char *inStr, int str_len, uint32_t *val32b) {
  int i = 0;
  (void)val32b;
  bool res = false;
  int catch = 0;
  int startIndex = 0;
  int hexValCnt = 0;
  int valLen = 0;
  for (i = 0; i < str_len; i++) {
    if (0 == catch) {
      if ('0' == inStr[i]) {
        valLen = 1;
        catch = 1;
        startIndex = i;
      }
    } else {
      if (1 == valLen) {
        if ('x' != inStr[i]) {
          catch = 0;
          valLen = 0;
        }
        valLen++;
      } else {
        if (true == is_hex_number(inStr[i])) {
          valLen++;
        } else {
          if (' ' == inStr[i]) {
            hexValCnt++;
            if (10 == valLen) {
              res = try_strl2uint32_hex(&inStr[startIndex + 2], 8, val32b);
              return res;
            }
            catch = 0;
            valLen = 0;
          }
        }
      }
    }
  }
  return res;
}

#if 0
bool delete_char (char *inOutStr, int curIndex) {
    bool res = false;
    (void)inOutStr;
    (void)curIndex;
    return res;
}
#endif

#if 0
char *mac_to_str (uint8_t *mac_addr) {
    static char macStrOut[100] = "";
    snprintf ((char *)macStrOut, sizeof (macStrOut), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1],
              mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    return macStrOut;
}
#endif

#if 0
char *ip_to_str (uint8_t *ip_addr) {
    static char ipStrOut[100] = "";
    snprintf ((char *)ipStrOut, sizeof (ipStrOut), "%02d.%02d.%02d.%02d", ip_addr[3], ip_addr[2], ip_addr[1],
              ip_addr[0]);
    return ipStrOut;
}
#endif

#if 0
bool parse_substr_name (const char *const inStr, uint16_t inStrLen, char *const outStr, char openBracket,
                        char closedBracket) {
    if ((NULL != outStr) && (NULL != inStr)) {
        if (0 < inStrLen) {
            int i = 0;
            bool snatchMode = false;
            int cnt = 0;
            for (i = 0; i < inStrLen; i++) {
                if (closedBracket == inStr[i]) {
                    snatchMode = false;
                    outStr[cnt] = '\0';
                }
                if (true == snatchMode) {
                    outStr[cnt] = inStr[i];
                    cnt++;
                }
                if (openBracket == inStr[i]) {
                    snatchMode = true;
                    cnt = 0;
                }
            }
        }
    }
    return true;
}
#endif

#if 0
bool parse_holder_name (char *inStr, uint16_t inStrLen, char *holderName) {
    /*TODO: <>*/
    if (NULL != inStr) {
        if (0 < inStrLen) {
            int i = 0;
            for (i = 0; i < inStrLen; i++) {
            }
            strncpy (holderName, "undef", 100);
        }
    }
    return true;
}
#endif

#if 0
// Device: CAN_FLASHER Serial 0x202b17d3015a from IP 192.168.0.11 MAC d4:3b:04:a0:a2:21C
bool parse_mac (char *inStr, uint16_t inStrLen, uint8_t *outMacAddr) {
    bool res = false;
    if (strlen ("MAC") < inStrLen) {
        char *serialStartPtr = strstr (inStr, "MAC ");
        if (NULL != serialStartPtr) {
            res = try_str2mac ((const char *)(serialStartPtr + strlen ("MAC ")), outMacAddr);
        } else {
            printf ("\n lack MAC addr in [%s]", inStr);
        }
    }
    return res;
}
#endif

#if 0
bool parse_ip (char *inStr, uint16_t inStrLen, uint32_t *outIpAddr) {
    bool res = false;
    if (strlen ("IP ") < inStrLen) {
        char *serialStartPtr = strstr (inStr, "IP ");
        if (NULL != serialStartPtr) {
            uint32_t IpLen;
            IpLen = calc_ip_val_len ((serialStartPtr + strlen ("IP ")));
            res = try_strl2ipv4 ((const char *)(serialStartPtr + strlen ("IP ")), IpLen, outIpAddr);
        } else {
            printf ("\n lack IP addr in [%s]", inStr);
        }
    }
    return res;
}
#endif

#if 0
// CanFlasher on CanFlash Version 0.17.1.1.34 GCC Release 11/7/2020 19:34:29 FlashId:E58F0042 Serial:202B17D3015A by
// Arrival
bool parse_serial (char *inStr, uint16_t inStrLen, uint64_t *outSerial64bNumber) {
    bool res = false;
#if DEBUG_PARSE_SERIAL
    printf ("\n inStr[%s]", inStr);
#endif
    if (strlen ("Serial") < inStrLen) {
        uint64_t localSerial64bNumber = 0xFFFFFFFFFFFFFFFF;
        char *serialStartPtr = strstr (inStr, "Serial");
        if (NULL != serialStartPtr) {
            uint16_t hexValLen;
#if DEBUG_PARSE_SERIAL
            printf ("\n serialStartPtr[%s]", serialStartPtr);
            printf ("\n numstr [%s]", (serialStartPtr + strlen ("Serial") + 1));
#endif
            hexValLen = calc_hex_val_len ((serialStartPtr + strlen ("Serial") + 1));
#if DEBUG_PARSE_SERIAL
            printf ("\n hexValLen[%d]", hexValLen);
#endif
            res = try_strl2uint64 ((const char *)(serialStartPtr + strlen ("Serial") + 1), hexValLen,
                                   &localSerial64bNumber);
            if (true == res) {
                (*outSerial64bNumber) = localSerial64bNumber;
            }
        } else {
            printf ("\n lack Serial number in [%s]", inStr);
        }
    }

    return res;
}
#endif

#if 0
bool lower_case_str (char *str) {
    bool res = false;
    if (str) {
        res = true;
        for (int i = 0; str[i]; i++) {
            str[i] = (char)tolower ((int)str[i]);
        }
    }
    return res;
}
#endif

#if 0
char *upper_case_str (char *str) {
    static char out_str[100];
    strncpy (out_str, str, sizeof (out_str));
    int i = 0;
    for (i = 0; out_str[i] != '\0'; i++) {
        if (('a' <= out_str[i]) && (out_str[i] <= 'z')) {
            out_str[i] = out_str[i] - 32;
        }
    }
    return out_str;
}
#endif

#if 0
bool is_camel_case (const char *in) {
    bool res = true;
    uint16_t len = strlen (in);
    char prev_ch = 'a';
    char cur_ch = 'a';
    for (int i = 0; i < len; i++) {
        cur_ch = in[i];
        if (isupper (cur_ch) && isupper (prev_ch)) {
            res = false;
        }
        prev_ch = cur_ch;
    }

    return res;
}
#endif

#if 0
char *toSnakeCase (const char *in) {
    static char out_str[200];
    strcpy (out_str, "");
    const char *inp = in;
    size_t n = 0;
    uint16_t len = strlen (in);
    if (1 == len) {
        if ('_' == in[0]) {
            return out_str;
        }
    }
    bool res = is_camel_case (in);
    if (false == res) {
        strcpy (out_str, in);
        return out_str;
    }
    char prev_ch = 'a';
    while ((n < sizeof (out_str) - 1) && *inp) {
        if (isupper (*inp)) {
            if (n > (sizeof (out_str) - 3)) {
                out_str[n++] = 0;
                return out_str;
            }
            if (islower (prev_ch)) {
                if (0 < n) {
                    out_str[n++] = '_';
                }
                if (islower (prev_ch)) {
                    out_str[n++] = (*inp) + ('a' - 'A');
                }
            } else {
                out_str[n++] = (*inp);
            }

        } else {
            out_str[n++] = (*inp);
        }
        prev_ch = (*inp);
        ++inp;
    }
    out_str[n++] = 0;
    return out_str;
}
#endif

#if 0
char *camel_case_2_snake_case1 (char *camel_case_str) {
    static char out_str[200];
    strcpy (out_str, "");
    int len = strlen (camel_case_str);
    int i_out = 0;
    char prev_ch = 0x00;
    for (int i = 0; i < len; i++) {
        char cur_ch = camel_case_str[i];
        if ((islower (prev_ch)) && (isupper (cur_ch))) {
            out_str[i_out] = prev_ch;
            i_out++;
            out_str[i_out] = '_';
            i_out++;
            out_str[i_out] = tolower (cur_ch);
            i_out++;
        } else if (('_' == prev_ch) && (isupper (cur_ch))) {
            out_str[i_out] = '_';
            i_out++;
            out_str[i_out] = tolower (cur_ch);
            i_out++;
        } else if (('_' == prev_ch) && (islower (cur_ch))) {
            out_str[i_out] = '_';
            i_out++;
            out_str[i_out] = cur_ch;
            i_out++;
        } else if ((islower (prev_ch)) && (islower (cur_ch))) {
            out_str[i_out] = prev_ch;
            i_out++;
            out_str[i_out] = cur_ch;
            i_out++;
        } else if ((isupper (prev_ch)) && (isupper (cur_ch))) {
            out_str[i_out] = prev_ch;
            i_out++;
            out_str[i_out] = cur_ch;
            i_out++;
        } else if (('_' == prev_ch) && ('_' == cur_ch)) {
            out_str[i_out] = prev_ch;
            i_out++;
            out_str[i_out] = cur_ch;
            i_out++;
        } else {
            printf ("\n undef pattern [%c%c]", prev_ch, cur_ch);
        }
        prev_ch = cur_ch;
    }
    return out_str;
}
#endif

#if 0
char *str_append (char *in_str, char letter) {
#ifdef DEBUG_STR_OPS
    printf ("\n%s()", __FUNCTION__);
#endif
    int str_len = 0;
    if (in_str) {
        str_len = strlen (in_str);
    }
    char *out_str = malloc (str_len + 2);
    if (out_str) {
        if (in_str) {
            if (0 < str_len) {
                strncpy (out_str, in_str, str_len);
            }
            free (in_str);
        }
        out_str[str_len] = letter;
        out_str[str_len + 1] = '\0';
    }
    return out_str;
}

#endif

#if 0
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
#endif

#if 0
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
#endif

#if 0
char *str_cat_dyn (char *in_str1, char *in_str2) {
    char *out_str = NULL;
    int len1 = strlen (in_str1);
    int len2 = strlen (in_str2);
    out_str = (char *)malloc (len1 + len2);
    if (out_str) {
        strcpy (out_str, in_str1);
        strcat (out_str, in_str2);
        free (in_str1);
    }
    return out_str;
}
#endif
