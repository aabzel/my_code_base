#ifndef __MK_TO_DOT_H
#define __MK_TO_DOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

bool proc_mk_file (char *fileName, char *outFileName);
bool test_parse_mk (void);
bool parse_mk (char *fileStr, char *tempStr, int outStrLen);
int match (const char *string, char *pattern);
bool is_char_of_file (char ch);
bool is_allowed_char_file (char ch);

#ifdef __cplusplus
}
#endif

#endif /* __MK_TO_DOT_H */
