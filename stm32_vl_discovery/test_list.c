#include "test_list.h"

#include <stdint.h>

#include "unit_test_check.h"

extern uint64_t mul64(uint32_t a, uint32_t b);

unit_test_info_t test_list[UTEST_NUMBER] = { { "test_64bit_mult", test_64bit_mult }, {
		"test_utoa_bin8", test_utoa_bin8 } };

static bool print_mem(uint8_t *addr, uint16_t len) {
	rx_printf(CRLF"0x");
	for (uint32_t pos = 0; pos < len; pos++) {
		rx_printf("%02x", *(addr + pos));
	}
	rx_printf(CRLF);
}

bool test_utoa_bin8(void) {
	EXPECT_STREQ("1010_1010", utoa_bin8(0xaa));
	EXPECT_STREQ("0101_0101", utoa_bin8(0x55));
	return true;
}

bool test_64bit_mult(void) {
	uint64_t exp = 0x00000002CB417800;
	uint64_t res = 12000000 * 1000;
	uint64_t temp10x3 = mul64(1000, 12000000);
	EXPECT_EQ((uint64_t )0x00000002CB417800, temp10x3);
	// exp        3410065408 cb417800 2 3410065408 14646119404580896770
	//  temp10x3: 48         cb417800 2 3410065408 14646119404580896770!
	rx_printf("\n exp: %u  " CRLF, 0x00000002CB417800);
	rx_printf("\n exp: %19x  " CRLF, 0x00000002CB417800);
	rx_printf("\n exp: %d  " CRLF, 0x00000002CB417800);
	rx_printf("\n exp: %lu " CRLF, 0x00000002CB417800);
	rx_printf("\n exp: %llu" CRLF, 0x00000002CB417800);
	print_mem(&exp, 8);
	print_mem(&temp10x3, 8);
	rx_printf("\n temp10x3: %u " CRLF, temp10x3);
	rx_printf("\n temp10x3: %x " CRLF, temp10x3);
	rx_printf("\n temp10x3: %d " CRLF, temp10x3);
	rx_printf("\n temp10x3: %lu" CRLF, temp10x3);
	rx_printf("\n temp10x3: %llu"CRLF, temp10x3);
	return true;
}
