#include "str_utils.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

uint16_t count_substring(char* in_str, char* substr) {
    uint16_t matchCnt = 0u;
    int in_strLen = strlen(in_str);
    if (0 < in_strLen) {
        int subStrLen = strlen(substr);
        char* cur_ptr = strstr(in_str, substr);
        while (NULL != cur_ptr) {
            matchCnt++;
            cur_ptr = strstr(&cur_ptr[subStrLen], substr);
        }
    }

    return matchCnt;
}

// qwertyuioo  "rty", "ZXC"
// qwe***uioo
// cut
// qwe uioo
// insetr
// qwe ZXC uioo
// concatenate
// qweZXCuioo
// DEBUG_REP_STR
bool replace_substring(char* in_out_str, char* orig, char* rep) {
    bool res = false;
#if 0
	printf("\n text %s orig %s rep %s",in_out_str,orig,rep);
#endif
    int text_len = strlen(in_out_str);
    int patt_len = strlen(orig);
    int rep_len = strlen(rep);
    while (0 < count_substring(in_out_str, orig)) {
        char* cur_ptr = strstr(in_out_str, orig);
        if (NULL != cur_ptr) {
#if 0
			printf("\n cur_ptr %s",cur_ptr);
#endif
            memset(cur_ptr, 0x00, patt_len);
            char* suffix;
            suffix = &cur_ptr[patt_len];
			uint32_t size = text_len + patt_len + rep_len;
			if (0 < size) {	
#if 0
			  printf("\n size %u",size);
#endif
              char* temp_str = malloc(size);
              if (temp_str) {
#if 0
				  printf("\n temp [%s][%s][%s]",in_out_str,rep,suffix);
#endif
                  snprintf(temp_str,size, "%s%s%s", in_out_str, rep, suffix);
				  strcpy(in_out_str,temp_str);
#if 0
  				  printf("\n res[%s]",in_out_str);
#endif
                  free(temp_str);
                  temp_str = NULL;
                  res = true;
              }
			}
        }
    }

    return res;
}

bool delete_sub_string(char* in_out_str, char* str_to_del) {
    bool res = false;
    res = replace_substring(in_out_str, str_to_del, "");
    return res;
}

void strrepl(char* str, char from, char to) {
    if (str == NULL) {
        return;
    }

    while (*str != 0) {
        if (*str == from) {
            *str = to;
        }
        str++;
    }
}

static int is_trim_char(char c) { return isspace((unsigned char)c) || c == '\n' || c == '\r'; }

void str_trim(char* str) {
    char* start = str;
    char* end = start + strlen(str) - 1;

    while (end >= start) { /* trim right */
        if (!is_trim_char(*end)) {
            break;
        }
        end--;
    }
    end++;
    *end = '\0';

    while (is_trim_char(*start)) { /* trim left */
        start++;
    }

    if (start != str) /* there is a string */ {
        memmove(str, start, end - start + 1);
    }
}
/*
 Find the first occurrence of pattern in text, ignore case.
 time complexity O(T*P)*/
const char* str_case_str(const char* const text, const char* const pattern) {
    const char* retPtr = NULL;

    if ((NULL != text) && (NULL != pattern)) {
        if (pattern[0] == '\0') {
            retPtr = &text[0];
        } else {
            int32_t i;

            for (i = 0; text[i] != '\0'; ++i) {
                int32_t j = 0;

                for (j = 0; text[i + j] != '\0'; j++) {
                    int32_t symb1 = tolower((int32_t)text[i + j]);
                    int32_t symb2 = tolower((int32_t)pattern[j]);

                    if (symb1 != symb2) {
                        break;
                    }
                }

                if (pattern[j] == '\0') {
                    retPtr = &text[i];
                    break;
                }
            }
        }
    }

    return retPtr;
}

/*in_out_str must be in RAM not in ROM(FLASH)*/
/* exapmle - EXAPMLE*/
bool str2uppercase(char* const in_out_str) {
    bool res = false;
    if (NULL != in_out_str) {
        uint32_t index;
        uint32_t strLen = strlen(in_out_str);
        for (index = 0; index < strLen; index++) {
            if (('a' <= in_out_str[index]) && (in_out_str[index] <= 'z')) {
                in_out_str[index] = in_out_str[index] - 32u;
            }
        }
        res = true;
    }
    return res;
}

/*
 * public domain strtok_r() by Charlie Gordon
 *
 *   from comp.lang.c  9/14/2007
 *
 *      http://groups.google.com/group/comp.lang.c/msg/2ab1ecbb86646684
 *
 *     (Declaration that it's public domain):
 *      http://groups.google.com/group/comp.lang.c/msg/7c7b39328fefab9c
 */

char* rx_strtok_r(char* str, const char* delim, char** nextp) {
    char* ret;

    if (str == NULL) {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0') {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if (*str) {
        *str = '\0';
        str++;
    }

    *nextp = str;

    return ret;
}

bool wildcmp(const char* wild, const char* string) {
    const char *cp = NULL, *mp = NULL;

    while ((*string) && (*wild != '*')) {
        if ((toupper(*wild) != toupper(*string)) && (*wild != '?')) {
            return false;
        }
        wild++;
        string++;
    }

    while (*string) {
        if (*wild == '*') {
            ++wild;
            if (!*wild) {
                return true;
            }
            mp = wild;
            cp = string + 1;
        } else if ((toupper(*wild) == toupper(*string)) || (*wild == '?')) {
            wild++;
            string++;
        } else {
            wild = mp;
            string = cp;
            cp++;
        }
    }

    while (*wild == '*') {
        wild++;
    }
    return !*wild;
}
