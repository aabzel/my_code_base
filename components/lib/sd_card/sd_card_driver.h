#ifndef SD_CARD_DRV_H
#define SD_CARD_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "diskio.h"

#define BLOCK_SIZE_BYTE (512U)

#define BIT6 (0x40)

/* Definitions for MMC/SDC command */
#define CMD0 (0x40)   /*0b0100_0000 GO_IDLE_STATE */
#define CMD1 (0x41)   /* SEND_OP_COND (MMC) */
#define CMD8 (0x48)   /* SEND_IF_COND SEND_IF_COND */
#define CMD9 (0x49)   /* SEND_CSD */
#define CMD10 (0x4A)  /* SEND_CID */
#define CMD12 (0x4C)  /* STOP_TRANSMISSION */
#define CMD13 (0x4D)  /* SEND_STATUS*/
#define CMD16 (0x50)  /* SET_BLOCKLEN */
#define CMD17 (0x51)  /* READ_SINGLE_BLOCK */
#define CMD18 (0x52)  /* READ_MULTIPLE_BLOCK */
#define CMD23 (0x57)  /* SET_BLOCK_COUNT */
#define CMD24 (0x58)  /* WRITE_BLOCK */
#define CMD25 (0x59)  /* WRITE_MULTIPLE_BLOCK */
#define CMD41 (0x69)  /* SD_SEND_OP_COND (ACMD) */
#define CMD30 (0x5E)  /* SEND_WRITE_PROT */
#define CMD55 (0x77)  /* APP_CMD */
#define CMD58 (0x7A)  /* READ_OCR */
#define ACMD41 (0x69) // (0xC0+41) //192+41=233=0xE9 SEND_OP_COND (SDC)

#define SEND_STATUS CMD13
#define GO_IDLE_STATE CMD0
#define SEND_IF_COND CMD8
#define READ_SINGLE_BLOCK CMD17
#define WRITE_SINGLE_BLOCK CMD24
#define SD_SEND_OP_COND ACMD41
#define APP_CMD CMD55
#define SEND_WRITE_PROT CMD30
#define READ_OCR CMD58

#define TOKEN_BLK_WR 0xFE
#define TOKEN_MULT_BLK_WR 0xFC
#define TOKEN_STOP 0xFD

/* MMC card type flags (MMC_GET_TYPE) */
#define CT_MMC 0x01   /* MMC ver 3 */
#define CT_SD1 0x02   /* SD ver 1 */
#define CT_SD2 0x04   /* SD ver 2 */
#define CT_SDC 0x06   /* SD */
#define CT_BLOCK 0x08 /* Block addressing */


#define SD_CS_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_11

typedef struct xSdCommand_t {
    uint8_t cmd;
    int16_t resp_len_byte;
} SdCommand_t;

bool sent_74_ones (void);
DSTATUS SD_disk_initialize(BYTE pdrv );
bool SD_PowerOn(void);
SdCommand_t *get_reg_inst(uint8_t cmd);
bool parse_r1_response (uint8_t response);
bool is_card_connected (void);
uint8_t SD_sendCommand (uint8_t cmd, uint32_t arg);
bool sd_read_sector (uint32_t block_num, uint8_t *out_buff);
bool sd_write_sector (uint32_t block_num, const uint8_t *in_buff);
bool sd_read_multiple_sector (uint32_t block_num, uint8_t *out_buff, uint32_t sectors);
bool sd_control (void);
uint8_t sd_card_status(void);
DRESULT SD_disk_ioctl(BYTE drv, BYTE ctrl, uint8_t *buff);
bool read_registers (void);
int16_t get_resp_len (uint8_t cmd);
bool receive_response (uint8_t *const array, int32_t len);
uint8_t calc_cmd_num(uint8_t cmd);

DRESULT SD_disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count);

#endif /* SD_CARD_DRV_H */
