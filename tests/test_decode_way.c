#include "test_decode_way.h"

#include "decode_way.h"
#include "uTests.h"

bool test_decode_ways (void) {
    bool res;
    EXPECT_EQ (1, numDecodings ("20"));
    EXPECT_EQ (1836311903, numDecodings ("111111111111111111111111111111111111111111111"));
    EXPECT_EQ (0, numDecodings ("0"));
    EXPECT_EQ (2, numDecodings ("26"));
    EXPECT_EQ (1, numDecodings ("6"));
    EXPECT_EQ (3, numDecodings ("226"));
    EXPECT_EQ (2, numDecodings ("12"));
    EXPECT_EQ (1, numDecodings ("1"));
    return true;
}
