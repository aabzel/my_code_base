#include "sd_card_driver.h"

#include <stdint.h>
#include <string.h>

#include "byte_utils.h"
#include "convert.h"
#include "diskio.h"
#include "sd_card_crc.h"
#include "none_blocking_pause.h"
#include "gpio.h"
#include "log.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "spi.h"

static volatile DSTATUS Stat = STA_NOINIT; /* Disk Status */
static uint8_t power_flag = 0;
uint8_t card_type = 0xFF; /* Type 0:MMC, 1:SDC, 2:Block addressing */

const SdCommand_t respLenTable[] = { { CMD0, 1 },  //GO_IDLE_STATE
		{ CMD8, 4 },  //SEND_IF_COND
		{ CMD9, 19 }, // SEND_CSD
		{ CMD10, 19 }, // SEND_CID
		{ CMD13, 64 + 4 }, //SEND_STATUS SD_STATUS
		{ CMD16, 1 }, // SET_BLOCK_LEN
		{ CMD55, 1 }, // APP_CMD
		{ CMD58, 4 }, // READ_OCR
		{ CMD17, 512 + 4 }, //READ_SINGLE_BLOCK
		{ 0xFF, -1 } };

#define CS_ENABLE()
#ifndef CS_ENABLE()
static void CS_ENABLE (void) {
	HAL_GPIO_WritePin (SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
	HAL_Delay (20);
}
#endif

#define CS_DISABLE()
#ifndef CS_DISABLE()
static void CS_DISABLE (void) {
	HAL_GPIO_WritePin (SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);
	HAL_Delay (20);
}
#endif

/* wait SD ready */
static uint8_t SD_ReadyWait(void) {
	uint8_t rx_byte = 0;
	uint16_t wait = 0;
	/* timeout 500ms */
	/* if SD goes ready, receives 0xFF */
	do {
		rx_byte = spi_read();
		wait++;
		if (16000 < wait) {
			break;
		}
	} while (rx_byte != 0xFF);

	if (0xFF == rx_byte) {
		rx_printf("[d] ready try %u" CRLF, wait);
	}

	return rx_byte;
}

bool is_card_connected(void) {
	bool res = false;
	GPIO_PinState state;
	state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
	if (GPIO_PIN_SET == state) {
		res = false;
	} else if (GPIO_PIN_RESET == state) {
		res = true;
	}
	return res;
}

void sent_agrument(uint32_t arg) {
	spi1_send_byte(arg >> 24);
	spi1_send_byte(arg >> 16);
	spi1_send_byte(arg >> 8);
	spi1_send_byte(arg);
}

uint8_t calculate_crc(uint8_t cmd, uint32_t arg) {
	uint8_t calc_crc = 0;
	uint8_t frame[5];
	frame[0] = cmd;
	uint32_t be_arg = reverse_byte_order_uint32(arg);
	memcpy(&frame[1], &be_arg, 4);
	calc_crc = calc_crc7(&frame[0], 5);
	calc_crc = calc_crc << 1;
	calc_crc |= 0x01;
	return calc_crc;
}

static uint8_t spi_read_until_pat(uint8_t pattern, uint8_t cmd, uint32_t arg,
		uint8_t crc, bool *err) {
	uint8_t rx_byte = 0;
	uint8_t try_cnt = 0;
	do {
		rx_byte = spi_read();
		if (253 < try_cnt) {
			(*err) = true;
			LOG_ERROR(SYS,
					"%s() cmd 0x%02x arg 0x%08x crc 0x%02x Lack of reply after %u try",
					__FUNCTION__, cmd, arg, crc, try_cnt);
			break;
		}
		try_cnt++;
	} while (pattern == rx_byte);

	if (pattern != rx_byte) {
#if 1
		rx_printf(SYS, "[d]  cmd 0x%02x reply after %u try"CRLF, cmd, try_cnt);
#endif
	}

	return rx_byte;
}

static uint8_t send_sd_frame(uint8_t cmd, uint32_t arg) {
	spi1_send_byte(cmd);
	sent_agrument(arg);
	uint8_t calc_crc = calculate_crc(cmd, arg);
	// LOG_INFO (SYS, "Send CRC 0x%02x", calc_crc);
	spi1_send_byte(calc_crc);
#if 1
	rx_printf("%s() 0x%02x/CMD%u=0b%s arg:0x%08x crc:0x%02x" CRLF, __FUNCTION__,
			cmd, calc_cmd_num(cmd), utoa_bin8(cmd), arg, calc_crc);
#endif
	return calc_crc;
}

// returns SD card answer array
uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg) {
	uint8_t in_cmd = cmd | BIT6;
	uint8_t calc_crc = 0;
	uint8_t ret = 0xFF;
	CS_ENABLE();

	ret = SD_ReadyWait();
	if (0xFF != ret) {
		return 0xFF;
	}
	calc_crc = send_sd_frame(in_cmd, arg);

	if (CMD12 == in_cmd) {
		spi_read();
	}

	bool err = false;
	power_flag = 1;
	uint8_t try_cnt = 0;

	CS_ENABLE();

	ret = spi_read_until_pat(0xFF, in_cmd, arg, calc_crc, &err);

	if (false == err) {
#if 0
		LOG_INFO(SYS, "%s() 0x%02x  0x%08x 0x%02x resp 0x%02x",
				__FUNCTION__, in_cmd, arg, calc_crc, ret);
		parse_r1_response(ret);
#endif
	} CS_DISABLE();
	power_flag = 1;
	return ret;
}

bool sent_74_ones(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_Delay(200);
#if 0
	LOG_INFO(SYS, "%s()", __FUNCTION__);
#endif
	bool res = true;
	uint8_t i = 0;
	for (i = 0; i < 10; i++) {
		res &= spi1_send_byte(0xff); // send 74 ones
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_Delay(200);
	return res;
}

bool parse_r1_response(uint8_t response) {
	LOG_INFO(SYS, "%s()       0x%02x 0b%s", __FUNCTION__, response,
			utoa_bin8(response));
	bool res = false;
	// response = swap_bits_u8(response);
	if ((1 << 7) == (response & (1 << 7))) {
		LOG_ERROR(SYS, "Not a R1 response" CRLF);
		res = false;
	} else {
		if ((1 << 0) == (response & (1 << 0))) {
			rx_printf("in idle state	" CRLF);
		}
		if ((1 << 1) == (response & (1 << 1))) {
			rx_printf("Erase reset" CRLF);
		}
		if ((1 << 2) == (response & (1 << 2))) {
			LOG_ERROR(SYS, "Wrong command" CRLF);
		}
		if ((1 << 3) == (response & (1 << 3))) {
			LOG_ERROR(SYS, "CRC Error" CRLF);
		}
		if ((1 << 4) == (response & (1 << 4))) {
			LOG_ERROR(SYS, "erase Error" CRLF);
		}
		if ((1 << 5) == (response & (1 << 5))) {
			LOG_ERROR(SYS, "Address Error" CRLF);
		}
		if ((1 << 6) == (response & (1 << 6))) {
			LOG_ERROR(SYS, "Arg Error" CRLF);
		}
		res = true;
	}
	return res;
}

/* power on */
bool SD_PowerOn(void) {
	uint8_t ret = 0;
	bool res = true;
	bool err = false;
	uint16_t retry = 0;

	sent_74_ones();

	do {
		wait_in_loop_ms(10);
		ret = SD_sendCommand(CMD0, 0);
		parse_r1_response(ret);
		rx_printf("try %u %02x res %02x" CRLF, retry, CMD0, ret);
		if (32 < retry) {
			LOG_ERROR(SYS, "GO_IDLE_STATE lack of answer");
			err = true;
			return false;
		}
		retry++;
	} while (ret != 0x01);

	if (0x01 == ret) {
		res = true;
		LOG_INFO(SYS, "[d] CMD0 fine resp!");
	} CS_DISABLE();

	spi1_send_byte(0xff);
	spi1_send_byte(0xff);

	power_flag = 1;
	return res;
}

DSTATUS SD_disk_initialize(BYTE pdrv ) {
	LOG_INFO(SYS, "%s()  ", __FUNCTION__);
	bool res = false;
	bool err = false;
	uint8_t ret = 0;
	uint8_t type = 0;
	uint8_t SD_version = 2; // default for ver SD = 2
	uint16_t retry = 0;

	res = SD_PowerOn();
	if (false == res) {
		return res;
	}
	retry = 0;
	uint8_t exp_arr[5] = { 0x00, 0x00, 0x01, 0xAA };
	uint8_t real_arr[7] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	int cmp_res = -1;
	do {
		wait_in_loop_ms(10);
		ret = SD_sendCommand(CMD8, 0x000001AA);
		parse_r1_response(ret);
		rx_printf("[d] try %u cmd %02x res %02x" CRLF, retry, CMD8, ret);
		if (16 < retry) {
			LOG_ERROR(SYS, "[!] CMD8 %02x lack of answer", CMD8);
			SD_version = 1;
			err = true;
			break;
		}
		if (0x01 == ret) {
			LOG_INFO(SYS, "[d] CMD8 ret fine");
			spi1_receive_array(real_arr, 4);
			cmp_res = memcmp(real_arr, exp_arr, 4);
		} else {
			cmp_res = -1;
		}
		retry++;
		// check 01000001AA
		//       01000001aa
	} while (0 != cmp_res);

	uint32_t arg_cmd41 = 0;
	if (0 == cmp_res) {
		arg_cmd41 = 0x40000000;
		LOG_INFO(SYS, "[d] CMD8 resp fine");
		retry = 0;
		do {
			wait_in_loop_ms(10);
			ret = SD_sendCommand(CMD55, 0);
			parse_r1_response(ret);

			ret = SD_sendCommand(ACMD41, arg_cmd41);
			parse_r1_response(ret);
			rx_printf("[d] cmd %02x res %02x" CRLF, ACMD41, ret);
			if (15 < retry) {
				LOG_ERROR(SYS, "[!] APP_CMD+SD_SEND_OP_COND lack of answer");
				return false;
			}
			retry++;
		} while (ret != 0x00);
	} else {
		arg_cmd41 = 0x00000000;
		LOG_ERROR(SYS, "[!] CMD8 resp error");
	}

	if (0 == cmp_res) {
		retry = 0;
		card_type = 0;
		do {
			wait_in_loop_ms(10);
			ret = SD_sendCommand(READ_OCR, 0);
			if (0 == ret) {
				spi1_receive_array(real_arr, 4);
				if (real_arr[0] & 0x40) {
					LOG_INFO(SYS, "[d] OCR bit 6 set V2");
				} else {
					LOG_INFO(SYS, "[d] OCR bit 6 reset V2");
					ret = SD_sendCommand(CMD16, 0x200);
					parse_r1_response(ret);
				}
				type = (real_arr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;
			}
			if (254 < retry) {
				break;
			}
			retry++;
		} while (0x00 != ret);
	}
	card_type = type;
	if (type) {
		Stat &= ~STA_NOINIT;
	}

	return Stat;
}
/*
 sdr 1
 sdr 0x51 1
 //8192

 */
/*512 byte each*/
bool sd_read_sector(uint32_t block_num, uint8_t *out_buff) {
	uint16_t i = 0;
	uint8_t ret = 0;
	ret = SD_sendCommand(CMD17, block_num);
	if (0x00 != ret) {
		LOG_ERROR(SYS, "CMD17 read error: %u", ret);
		parse_r1_response(ret);
		return false;
	}CS_ENABLE();
	uint8_t temp;
	// Wait start of packet with data
	do {
		temp = spi_read();
		i++;
		if (0xfffe < i) {
			CS_DISABLE();
			return false;
		}
	} while ((temp != 0xFE));

	spi1_receive_array(out_buff, BLOCK_SIZE_BYTE);

	spi_read(); // CRC
	spi_read(); // CRC

	CS_DISABLE();

	return true;
}

bool sd_rx_data_array(uint8_t *out_buff, uint32_t len) {
	uint8_t rx_byte = 0;
	bool res = false;
	uint16_t i = 0;
	CS_ENABLE();
	// Wait start of packet with data
	do {
		rx_byte = spi_read();
		i++;
		if (0xfffe < i) {
			CS_DISABLE();
			return false;
		}
	} while ((0xFF == rx_byte) || (0x00 == rx_byte));

	if (TOKEN_BLK_WR != rx_byte) {
		return false;
	}

	res = spi1_receive_array(out_buff, len);

	rx_byte = spi_read(); // CRC16
	rx_byte = spi_read(); // CRC16

	CS_DISABLE();
	return res;
}

bool sd_read_multiple_sector(uint32_t block_num, uint8_t *out_buff,
		uint32_t sectors) {
	uint16_t i = 0;
	uint8_t ret = 0;
	uint32_t res_sectors = 0;
	bool res = false;

	ret = SD_sendCommand(CMD18, block_num);
	if (0x00 != ret) {
		LOG_ERROR(SYS, "CMD18 read error");
		return false;
	}

	for (i = 0; i < sectors; i++) {
		res = sd_rx_data_array(out_buff, 512);
		if (true == res) {
			out_buff += 512;
			res_sectors++;
		} else {
			break;
		}
	}
	ret = SD_sendCommand(CMD12, 0);

	CS_DISABLE();
	ret = spi_read();
	ret = spi_read();
	if (res_sectors == sectors) {
		res = true;
	}
	return res;
}

static void parse_write_flag(uint8_t flags) {
	if (flags & 1) {
		LOG_ERROR(SYS, "[!] error" CRLF);
	}
	if (flags & (1 << 1)) {
		LOG_ERROR(SYS, "[!] CRC error" CRLF);
	}
	if (flags & (1 << 2)) {
		LOG_ERROR(SYS, "[!] ECC error" CRLF);
	}
	if (flags & (1 << 3)) {
		LOG_ERROR(SYS, "[!] range error" CRLF);
	}
	if (flags & (1 << 4)) {
		LOG_ERROR(SYS, "[!] write protected error" CRLF);
	}
}

static bool parse_data_response(uint8_t flags) {
	bool res = false;
	if (flags & 1) {
		uint8_t code = 0x07 & (flags >> 1);
		if (2 == code) {
			res = true;
			LOG_INFO(SYS, "[*] data accepted" CRLF);
		}
		if (5 == code) {
			LOG_ERROR(SYS, "[!] data discarded CRC error");
		}
		if (6 == code) {
			LOG_ERROR(SYS, "[!] data discarded write error");
		}
	}
	return res;
}

static bool sd_tx_data_block(const uint8_t *in_buff, uint8_t token) {
	uint16_t cnt = 0;
	uint8_t ret = 0;
	uint16_t wait = 0;
	bool res = false;
	CS_ENABLE();

	ret = SD_ReadyWait();
	if (ret != 0xFF) {
		CS_DISABLE();
		return false;
	} else {
		LOG_INFO(SYS, "[d] bus idle");
	}

	spi1_send_byte(token);

	if (TOKEN_STOP != token) {
		res = spi1_sent_array(in_buff, BLOCK_SIZE_BYTE);
		spi1_send_byte(0xff); // CRC
		spi1_send_byte(0xff); // CRC
		uint8_t i = 0;

		uint8_t flags = 0;

		flags = spi_read();
		res = parse_data_response(flags);
		if (false == res) {
			return false;
		}

		// wait end of write block.  recv buffer clear
		wait = 0;
		do {
			ret = spi_read();
			if (0xfffe < wait) {
				LOG_ERROR(SYS, "end of write time out");
				CS_DISABLE();
				return false;
			}
			wait++;
		} while (0xFF != ret);

		if (0xFF == ret) {
			LOG_INFO(SYS, "[d] end of busy state write block.");
		}
	}

	CS_DISABLE();
	return true;

}

bool sd_write_sector(uint32_t block_num, const uint8_t *in_buff) {
	bool res = false;
	uint8_t ret = 0;
	uint16_t cnt = 0, wait = 0;
	if (NULL == in_buff) {
		return false;
	}

	ret = SD_sendCommand(CMD24, block_num);
	if (0x00 != ret) {
		LOG_ERROR(SYS, "[!] CMD17 write error");
		return false;
	} else {
		res = true;
		sd_tx_data_block(in_buff, TOKEN_BLK_WR);
	}

	CS_DISABLE();
	return res;
}

static uint16_t get_status_reg(void) {
	uint16_t status = 0;
	uint8_t r2_1 = 0;
	uint8_t r2_2 = 0;
	r2_1 = SD_sendCommand(SEND_STATUS, 0x00000000);
	spi1_receive_array(&r2_2, 1);
	status = r2_1;
	status = status << 8;
	status |= r2_2;
	return status;
}

SdCommand_t* get_reg_inst(uint8_t cmd) {
	uint16_t len = 1;
	SdCommand_t *item = NULL;
	uint16_t num_cmds = sizeof(respLenTable) / sizeof(respLenTable[0]);
	for (uint16_t i = 0; i < num_cmds; i++) {
		if (cmd == respLenTable[i].cmd) {
			item = &respLenTable[i];
		}
	}
	return item;
}

bool read_registers(void) {
	uint16_t sd_status = 0;
	uint8_t ret = 0;
	sd_status = get_status_reg();
	bool res = false;
	rx_printf("Status Register: 0x%04x" CRLF, sd_status);
	uint8_t real_arr[260];
	memset(real_arr, 0xFF, sizeof(real_arr));
	SdCommand_t *item = NULL;

	ret = SD_sendCommand(CMD58, 0);
	if (0 == ret) {
		res = true;
		LOG_INFO(SYS, "Read OCR R1 %02x", ret);
		item = get_reg_inst(CMD58);
		if (item) {
			spi1_receive_array(real_arr, item->resp_len_byte);
			print_mem(real_arr, item->resp_len_byte);
		}
	}
	memset(real_arr, 0xFF, sizeof(real_arr));
	ret = SD_sendCommand(CMD9, 0);
	if (0 == ret) {
		res = true;
		LOG_INFO(SYS, "Read CSD R1 %02x ", ret);
		item = get_reg_inst(CMD9);
		if (item) {
			sd_rx_data_array(real_arr, item->resp_len_byte);
			print_mem(real_arr, item->resp_len_byte);
		}
	}
	memset(real_arr, 0xFF, sizeof(real_arr));
	ret = SD_sendCommand(CMD10, 0);
	if (0 == ret) {
		res = true;
		item = get_reg_inst(CMD10);
		if (item) {
			LOG_INFO(SYS, "Read CID R1 %02x ", ret);
			sd_rx_data_array(real_arr, item->resp_len_byte);
			print_mem(real_arr, item->resp_len_byte);
		}
	}
	memset(real_arr, 0xFF, sizeof(real_arr));
	//sdc 0x77 0
	ret = SD_sendCommand(CMD55, 0);
	if (0 == ret) {
		memset(real_arr, 0xFF, sizeof(real_arr));
		ret = SD_sendCommand(CMD13, 0);
		if (0 == ret) {
			item = get_reg_inst(CMD13);
			if (item) {
				LOG_INFO(SYS, "Read SD Status R2 %02x ", ret);
				sd_rx_data_array(real_arr, item->resp_len_byte);
				print_mem(real_arr, item->resp_len_byte);
			}
		}
	}

	return res;
}

uint8_t calc_cmd_num(uint8_t cmd) {
	return (cmd & (~((uint8_t) (1 << 6))));
}

bool sd_control(void) {
	return false;
}

/* power off */
static void SD_PowerOff(void) {
	power_flag = 0;
}

/* check power flag */
static uint8_t SD_CheckPower(void) {
	return power_flag;
}

uint8_t sd_card_status(void) {
	/* return disk status */
	return 1;
}

/* read sector */
DRESULT SD_disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count) {
	DRESULT ret = RES_ERROR;
	/* pdrv should be 0 */
	if (pdrv || !count)
		return RES_PARERR;

	/* no disk */
	if (Stat & STA_NOINIT)
		return RES_NOTRDY;

	/* convert to byte address */
	if (!(card_type & CT_SD2)){
		sector *= 512;
	}

	CS_ENABLE();
	bool res = false;
	if (1 == count) {
		/* READ_SINGLE_BLOCK */
		res = sd_read_sector(sector, buff);
		if (true == res) {
			count = 0;
			ret = RES_OK;
		}
	} else {
		LOG_ERROR(SYS, "Not supported read multiple blocks");
		res = sd_read_multiple_sector(sector, buff, count);
		if (res) {
			ret = RES_OK;
		}
	}

	/* Idle */
	CS_DISABLE();
	//spi_read();

	return ret;
}

/* write sector */
#if _USE_WRITE == 1
DRESULT SD_disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count) {
	bool res = false;
	DRESULT ret = RES_ERROR;
	/* pdrv should be 0 */
	if (pdrv || !count)
		return RES_PARERR;

	/* no disk */
	if (Stat & STA_NOINIT)
		return RES_NOTRDY;

	/* write protection */
	if (Stat & STA_PROTECT)
		return RES_WRPRT;

	/* convert to byte address */
	if (!(card_type & CT_SD2)){
		sector *= 512;
	}

	CS_ENABLE();
	if (1 == count) {
		res = sd_write_sector(sector, buff);
		if (true == res) {
			ret = RES_OK;
		}
	} else {
		/* WRITE_MULTIPLE_BLOCK */
		if (card_type & CT_SD1) {
			ret = SD_sendCommand(CMD55, 0);
			ret = SD_sendCommand(CMD23, count); /* ACMD23 */
		}
		ret = SD_sendCommand(CMD25, sector);
		if (ret == 0) {
			do {
				if (false == sd_tx_data_block(buff, TOKEN_MULT_BLK_WR)) {
					break;
				}
				buff += 512;
			} while (--count);

			/* STOP_TRAN token */
			if (false == sd_tx_data_block(0, TOKEN_STOP)) {
				count = 1;
			}
		}
		if (0 == count) {
			ret = RES_OK;
		}
	}

	/* Idle */
	CS_DISABLE();

	ret = spi_read();

	return ret;
}
#endif /* _USE_WRITE */

DRESULT SD_disk_ioctl(BYTE drv, BYTE ctrl, uint8_t *buff) {
	DRESULT res = RES_ERROR;
	uint8_t n = 0, csd[16]; // *ptr = buff;
	WORD csize = 0;
	uint8_t ret = 0;

	if (drv) {
		return RES_PARERR;
	}
	res = RES_ERROR;

	if (ctrl == CTRL_POWER) {
		switch (buff[0]) {
		case 0:
			SD_PowerOff(); /* Power Off */
			res = RES_OK;
			break;
		case 1:
			SD_PowerOn(); /* Power On */
			res = RES_OK;
			break;
		case 2:
			buff[1] = SD_CheckPower();
			res = RES_OK; /* Power Check */
			break;
		default:
			res = RES_PARERR;
		}
	} else {
		/* no disk */
		if (Stat & STA_NOINIT) {
			return RES_NOTRDY;
		}

		CS_ENABLE();

		switch (ctrl) {
		case GET_SECTOR_COUNT:
			/* SEND_CSD */
			ret = SD_sendCommand(CMD9, 0);
			if ((0 == ret) && sd_rx_data_array(csd, 16)) {
				if ((csd[0] >> 6) == 1) {
					/* SDC V2 */
					csize = csd[9] + ((WORD) csd[8] << 8) + 1;
					*(DWORD*) buff = (DWORD) csize << 10;
				} else {
					/* MMC or SDC V1 */
					n = (csd[5] & 15) + ((csd[10] & 128) >> 7)
							+ ((csd[9] & 3) << 1) + 2;
					csize = (csd[8] >> 6) + ((WORD) csd[7] << 2)
							+ ((WORD) (csd[6] & 3) << 10) + 1;
					*(DWORD*) buff = (DWORD) csize << (n - 9);
				}
				res = RES_OK;
			}
			break;
		case GET_SECTOR_SIZE:
			*(WORD*) buff = 512;
			res = RES_OK;
			break;
		case CTRL_SYNC:
			if (SD_ReadyWait() == 0xFF) {
				res = RES_OK;
			}
			break;
		case MMC_GET_CSD:
			ret = SD_sendCommand(CMD9, 0);
			if ((0 == ret) && sd_rx_data_array(buff, 16)) {
				res = RES_OK;
			}
			break;
		case MMC_GET_CID:
			ret = SD_sendCommand(CMD10, 0);
			if ((ret == 0) && sd_rx_data_array(buff, 16)) {
				res = RES_OK;
			}
			break;
		case MMC_GET_OCR:
			ret = SD_sendCommand(CMD58, 0);
			if (0x00 == ret) {
				spi1_receive_array(buff, 4);
				res = RES_OK;
			}
			break;
		default:
			res = RES_PARERR;
			break;
		} CS_DISABLE();
		spi_read();
	}

	return res;
}

