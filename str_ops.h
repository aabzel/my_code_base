#ifndef __STRING_OPS_H
#define __STRING_OPS_H

#include <stdint.h>
#include <string.h>

char * str_case_str (const char *s, const char *find);
char *removeCharFromString (char *str, uint32_t delIndex);
 
#endif /* __STRING_OPS_H */
