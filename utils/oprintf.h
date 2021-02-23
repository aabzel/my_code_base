#ifndef OPRINTF_H_
#define OPRINTF_H_
#include <stdarg.h>
#include "ostream.h"

#ifdef  __cplusplus
extern "C" {
#endif


#ifdef __ghs__
#pragma ghs nowarning 2101 /* MISRA 2012 Rule 1.2: language extensions are not allowed */
#endif
void oprintf(ostream_t* s, const char *fmt, ...) __attribute__((format(printf, 2, 3)));
#ifdef __ghs__
#pragma ghs endnowarning 2101 /* MISRA 2012 Rule 1.2: language extensions are not allowed */
#endif

#ifdef __ghs__
#pragma ghs nowarning 2068 /* MISRA 2012 Rule 17.1: va_list is not allowed */
#endif
void ovprintf(ostream_t* s, const char *fmt, va_list va);
#ifdef __ghs__
#pragma ghs endnowarning 2068 /* MISRA 2012 Rule 17.1: va_list is not allowed */
#endif

#ifdef  __cplusplus
}
#endif

#endif /* OPRINTF_H_ */



