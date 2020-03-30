#ifndef __STRING_OPS_H
#define __STRING_OPS_H

#include <stdint.h>
#include <string.h>

// time complexity O(T*P)
const char *str_case_str (const char * const text, const char * const pattern);
char *removeCharFromString (char *str, uint32_t delIndex);

#endif /* __STRING_OPS_H */
