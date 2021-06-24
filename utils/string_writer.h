#ifndef STRING_WRITER_H_
#define STRING_WRITER_H_

#include "ostream.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  ostream_t s;
  char *data;
  const uint16_t size;
  uint16_t pos;
  bool overflow;
} string_stream_t;

#ifdef __ghs__
#pragma ghs nowarning 1862 /* MISRA 2012 Rule D4.9: function-like macro not    \
                              allowed -- use function instead */
#endif
#define STRING_STREAM(str)                                                     \
  { {string_putc, string_puts}, (str), sizeof(str), 0, false }
#ifdef __ghs__
#pragma ghs endnowarning 1862 /* MISRA 2012 Rule D4.9: function-like macro not \
                                 allowed -- use function instead */
#endif

void string_putc(void *_s, char ch);
void string_puts(void *_s, const char *str, int32_t len);

#ifdef __cplusplus
}
#endif

#endif /* STRING_WRITER_H_ */
