#include "str_ops.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/*
 * Find the first occurrence of pattern in text, ignore case.
 */

// time complexity O(T*P)
const char *str_case_str (const char * const text, const char * const pattern) {
    const char *retPtr = NULL;
    if ((NULL != text) && (NULL != pattern)) {
        int i = 0;
        if ('\0' == (*pattern)) {
            retPtr =  &text[0];
        } else {
            for (; '\0' != text [i]; ++i) {
                int j = 0;
                while (('\0' != text [i + j]) && ((tolower ((int)text [i + j]) == tolower ((int)pattern [j])))) {
                    ++j;
                }
                if ('\0' == (pattern [j])) {
                    retPtr =  &text [i];
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

