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
char *str_case_str (const char * const text, const char * const pattern) {
    char *retPtr = NULL;
    if ((NULL != text) && (NULL != pattern)) {
        char * textPtr = (char *) text;
        if ('\0' == (*pattern)) {
            retPtr = (char *) text;
        } else {
            for (; '\0' != (*textPtr); ++textPtr) {
                const char *txtPtr = textPtr, *patternPtr = pattern;

                while ((*txtPtr) && ((tolower (*txtPtr)) == tolower (*patternPtr))) {
                    ++txtPtr;
                    ++patternPtr;
                }

                if ('\0' == (*patternPtr)) {
                    retPtr = textPtr;
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

