#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

extern uint32_t spi1_rx_cnt;
extern uint32_t spi1_tx_cnt;
extern uint32_t spi1_err_cnt;
extern uint32_t spi1_rxtx_cnt;
extern SPI_HandleTypeDef hspi1;

bool spi1_send_receive_byte (uint8_t tx_byte, uint8_t *rx_byte);
bool spi1_receive_byte (uint8_t *rx_byte);
bool spi1_send_byte (uint8_t tx_byte);
bool spi1_init (void);

uint8_t SPIx_WriteRead (uint8_t Byte);
uint8_t SPI_ReceiveByte (void);
void SPI_SendByte (uint8_t bt);

#ifdef __cplusplus
}
#endif

#endif // SPI_H
