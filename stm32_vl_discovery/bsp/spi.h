#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

#define SD_SPI_HANDLE hspi1

extern uint32_t spi1_rx_cnt;
extern uint32_t spi1_tx_cnt;
extern uint32_t spi1_err_cnt;
extern uint32_t spi1_rxtx_cnt;
extern SPI_HandleTypeDef SD_SPI_HANDLE;

bool spi1_send_receive_byte (uint8_t tx_byte, uint8_t *rx_byte);
bool spi1_receive_byte (uint8_t *rx_byte);
bool spi1_send_byte (uint8_t tx_byte);
bool spi1_init (void);
bool spi1_sent_array(const uint8_t *const in_buff, uint32_t arr_len) ;
bool spi1_receive_array(uint8_t *out_buff, uint32_t arr_len);
uint8_t spi_read(void) ;
uint8_t SPIx_WriteRead (uint8_t Byte);
uint8_t SPI_ReceiveByte (void);
void SPI_SendByte (uint8_t bt);

#ifdef __cplusplus
}
#endif

#endif // SPI_H
