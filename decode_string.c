#include "decode_string.h"

// Нужет стек для строк
// Нужет стек для натуральных чисел

// Как только встретили [ строку так сразу кладем ее в стек для чисел
// Как только встретили ] так срезу достаём число и строку и вставляем k раз

//   "3[a]2[bc]"        "aaabcbc"
//   "3[a2[c]]"         "accaccacc"
//   "2[abc]3[cd]ef"    "abcabccdcdcdef"
//   "abc3[cd]xyz"      "abccdcdcdxyz"

char *decodeString (char *s) {}
