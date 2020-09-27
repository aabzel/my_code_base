#include "test_convert.h"

#include "convert.h"

#include "uTests.h"

static bool test_assemble_uint32 (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    uint32_t qword_val = 0x00000000;
    qword_val = assemble_uint32 (0x01, 0x02, 0x03, 0x04);
    EXPECT_EQ (0x01020304, qword_val);
    qword_val = assemble_uint32 (0x04, 0x03, 0x02, 0x01);
    EXPECT_EQ (0x04030201, qword_val);
    return true;
}

bool test_convert (void) {
    printf ("\n[d] %s(): line %u", __FUNCTION__, __LINE__);
    bool res;
    res = test_assemble_uint32 ();
    EXPECT_EQ (true, res);

	uint8_t value;

    EXPECT_TRUE(try_str2uint8 ("1", &value));
    EXPECT_EQ(1, value);

    EXPECT_TRUE(try_str2uint8 ("1 ", &value));
    EXPECT_EQ(1, value);

    return true;
}
