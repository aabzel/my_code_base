#ifndef STR_UTILS_H_
#define STR_UTILS_H_

#include <stdbool.h>

#include <string.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef __ghs__
#pragma ghs nowarning 1862 /* MISRA 2012 Rule D4.9: function-like macro not allowed -- use function instead */
#pragma ghs nowarning 1830 /* MISRA 2012 Rule 20.10: # or ## operator not allowed */
#endif

#define STRNCPY(dst, src) do { strncpy((dst), (src), sizeof(dst)); (dst)[sizeof(dst)-1]=0;} while (0)
#define STRNCAT(dst, src) do { strncat((dst), (src), sizeof(dst) - strlen(dst) - 1); (dst)[sizeof(dst)-1]=0;} while (0)
#define BZERO_S(s) bzero(&(s), sizeof(s));

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef __ghs__
#pragma ghs endnowarning 1830 /* MISRA 2012 Rule 20.10: # or ## operator not allowed */
#pragma ghs endnowarning 1862 /* MISRA 2012 Rule D4.9: function-like macro not allowed -- use function instead */
#endif

#ifdef __ghs__
#  define LOCATION __BASE__ ":" TOSTRING(__LINE__)
#else
#  define LOCATION __FILE__ ":" TOSTRING(__LINE__)
#endif

void strrepl (char* str, char from, char to);
void str_trim (char *str);
bool wildcmp (const char *wild, const char *string);
bool str2uppercase (char * const inOutStr);
const char *str_case_str (const char * const text, const char * const pattern);
char * rx_strtok_r (char *s, const char *delim, char **lasts);

#ifdef	__cplusplus
}
#endif

#endif /* STR_UTILS_H_ */
