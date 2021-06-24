
#include "test_decode_string.h"

#include "uTests.h"

bool test_encode_string(void) {
  printf("\n%s()", __FUNCTION__);

  char *str_part = strdup("");
  str_part = str_append(str_part, 'a');
  EXPECT_EQ_STR(str_part, "a");
  str_part = str_append(str_part, 'b');
  EXPECT_EQ_STR(str_part, "ab");
  str_part = str_append(str_part, 'c');
  EXPECT_EQ_STR(str_part, "abc");
  str_part = str_append(str_part, 'd');
  EXPECT_EQ_STR(str_part, "abcd");

  EXPECT_EQ_STR("abcabccdcdcdef", decodeString("2[abc]3[cd]ef"));
  EXPECT_EQ_STR("accaccacc", decodeString("3[a2[c]]")); // ok
  EXPECT_EQ_STR("ababab", decodeString("3[ab]"));       // Ok
  EXPECT_EQ_STR("aaabcbc", decodeString("3[a]2[bc]"));  // ok
  EXPECT_EQ_STR("abccdcdcdxyz", decodeString("abc3[cd]xyz"));

  return true;
}
