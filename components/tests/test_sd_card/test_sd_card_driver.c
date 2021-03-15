#include "test_sd_card_driver.h"

#include <stdint.h>

#include "sd_card_driver.h"
#include "log.h"
#include "rx_io.h"
#include "data_utils.h"
#include "unit_test_check.h"

/*
 tsr test_sd_card_driver+
 */
bool test_sd_card_driver(void) {
	uint32_t block_num = 10;
	//EXPECT_TRUE( sd_card_init ( ));
    uint8_t read_block[512 + 1];
    uint8_t write_array[512 + 1];
	init_array_123(write_array, 512);

	EXPECT_TRUE(sd_write_sector(block_num, write_array));
	EXPECT_TRUE(sd_read_sector(block_num, read_block));

	EXPECT_EQ_MEM(read_block, write_array, 512);

	return true;
}
