#include "spi.h"

#include <stdbool.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

SPI_HandleTypeDef hspi1;
uint32_t spi1_rx_cnt = 0;
uint32_t spi1_tx_cnt = 0;
uint32_t spi1_rxtx_cnt = 0;
uint32_t spi1_err_cnt = 0;

bool init_spi_gpio(void) {
	__GPIOA_CLK_ENABLE()
	;
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

bool spi1_init(void) {
	__SPI1_CLK_ENABLE()
	;

	init_spi_gpio();
	bool res = true;
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		res = false;
	}
	return res;
}

bool spi1_send_byte(uint8_t tx_byte, uint8_t *rx_byte) {
	bool res= true;
	(*rx_byte) = 0;
	uint32_t init_spi1_tx_cnt = spi1_tx_cnt;
	uint32_t init_spi1_rxtx_cnt = spi1_rxtx_cnt;
	if (HAL_SPI_TransmitReceive_IT(&hspi1, &tx_byte, rx_byte, 1) != HAL_OK) {
		res= false;
	}

	if ( true == res ) {
    	res = false;
		for (uint32_t i = 0; i < 0x000FFFFF; i++) {
	    	if (init_spi1_tx_cnt != spi1_tx_cnt) {
	    		res= true;
		    	break;
	    	}
	    	if(init_spi1_rxtx_cnt!=spi1_rxtx_cnt){
	    		res= true;
		    	break;
	    	}
	    }
	}

	return res;
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) {
	GPIO_InitTypeDef GPIO_InitStruct;
	if (hspi->Instance == SPI1) {
		__SPI1_CLK_ENABLE()
		;
		init_spi_gpio();

		HAL_NVIC_SetPriority(SPI1_IRQn, 1, 1);
		HAL_NVIC_EnableIRQ(SPI1_IRQn);
	}

}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi) {
	if (hspi->Instance == SPI1) {

	}

}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi->Instance == SPI1) {
		spi1_rxtx_cnt++;
	}
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
	/* Turn LED1 on: Transfer in transmission process is correct */
	/* Turn LED2 on: Transfer in reception process is correct */

	//transmission process has been finished
	if (hspi->Instance == SPI1) {
		spi1_tx_cnt++;
	}

}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (SPI1 == hspi->Instance) {
		spi1_rx_cnt++;
	}

}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
	if (SPI1 == hspi->Instance) {
		spi1_err_cnt++;
		hspi->State = HAL_SPI_STATE_READY;
		hspi->ErrorCode = 0;
		hspi->Instance->SR = 0x0002;
	}

}

