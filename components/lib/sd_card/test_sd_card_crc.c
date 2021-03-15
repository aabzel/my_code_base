#include "test_sd_card_crc.h"

#include "sd_card_crc.h"
#include "sd_card_crc16.h"

#ifdef X86
#include <stdio.h>
#include "uTests.h"
#endif

#ifdef MCU
#include "unit_test_check.h"
#endif

static bool test_crc16(void) {
#ifdef X86
	printf("\n[d] %s()", __FUNCTION__);
#endif
	uint16_t crc16;
	uint8_t message[512] = { 0xFF};
	memset(message,0xFF,sizeof(message));
	crc16 = calc_crc16(message, sizeof(message));
	EXPECT_EQ((uint16_t) 0x7FA1, crc16);

	return true;
}

static bool test_crc7(void) {
#ifdef X86
	printf("\n[d] %s()", __FUNCTION__);
#endif
	uint8_t crc;
	uint8_t message40[] = { 0x40, 0x00, 0x00, 0x00, 0x00 };
	crc = calc_crc7(message40, sizeof(message40));
	EXPECT_EQ(0x4A, crc);

	uint8_t message51[] = { 0x51, 0x00, 0x00, 0x00, 0x00 };
	crc = calc_crc7(message51, sizeof(message51));
	EXPECT_EQ(0x2A, crc);

	uint8_t message11[] = { 0x11, 0x00, 0x00, 0x09, 0x00 };
	crc = calc_crc7(message11, sizeof(message11));
	EXPECT_EQ(0x33, crc);

	return true;
}

bool test_crc(void) {
#ifdef X86
	printf("\n[d] %s()", __FUNCTION__);
	print_crc_table();
#endif
	//generate_crc7_table();
	EXPECT_TRUE(test_crc7());
	EXPECT_TRUE(test_crc16());
#ifdef X86
	printf("\n[d] %s() done", __FUNCTION__);
#endif
	return true;
}

