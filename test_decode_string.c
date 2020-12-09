
#include "test_decode_string.h"

#include "uTests.h"

bool test_encode_string (void) {
    EXPECT_EQ_STR ("aaabcbc", decodeString ("3[a]2[bc]"));
    EXPECT_EQ_STR ("accaccacc", decodeString ("3[a2[c]]"));
    EXPECT_EQ_STR ("abcabccdcdcdef", decodeString ("2[abc]3[cd]ef"));
    EXPECT_EQ_STR ("abccdcdcdxyz", decodeString ("abc3[cd]xyz"));

    return true;
}
