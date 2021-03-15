#include <stdint.h>

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

#include "clocks.h"
#include "common_functions.h"
#include "convert.h"
#include "device.h"
#ifdef FAT_FS
#include "fatfs.h"
#endif
#include "gpio.h"
#include "diag_page_common.h"
#include "gpio_diag_page.h"
#include "none_blocking_pause.h"
#include "sd_card_driver.h"
#include "gpio_pwm.h"
#include "log.h"
#include "ff.h"
#include "main_loop.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "spi.h"
#include "timers.h"
#include "uarts.h"

void HAL_MspInit(void) {
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	__GPIOA_CLK_ENABLE ()
	;
	__GPIOB_CLK_ENABLE ()
	;

	__HAL_AFIO_REMAP_SWJ_NOJTAG();
	__HAL_RCC_TIM1_CLK_ENABLE();
	__SPI1_CLK_ENABLE ()
	;

	HAL_NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

	HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);

	HAL_TIM_Base_Start_IT(&htim1);
}

int main(void) {
	bool res = false;
	HAL_Init();
	set_log_level(SYS, LOG_LEVEL_DEBUG);

	res = SystemClock_Config();

	res = gpio_init();

	res = spi1_init();

	res = init_gpio_pwm();

	res = gpio_diag_page_init();

	res = usart1_uart_init();
	uarts_init();
	LOG_NOTICE(SYS, "UART init %s", (true == res) ? "OK" : "Err");

	res = timers_init();
	LOG_NOTICE(SYS, " TIM init %s", (true == res) ? "OK" : "Err");

	configureTimerForRunTimeStats();

	diag_page_common_init ();
#ifdef FAT_FS
	res = fat_fs_init();
	LOG_NOTICE(SYS, " FAT FS init %s", (true == res) ? "OK" : "Err");
#endif

	//res = sd_card_init( );
	//LOG_INFO (SYS, " SD card init ", (true == res) ? "OK" : "Err");


	// print_detected_board_type ();

	LOG_NOTICE(SYS, "FW started");
	LOG_NOTICE(SYS, "main %p", main);
	wait_in_loop_ms (10);
	//some variables for FatFs
	FATFS FatFs; 	//Fatfs handle
	FIL fil; 		//File handle
	FRESULT ret; //Result after operations
	wait_in_loop_ms(100);
	res = true;
	//Open the file system
#ifdef FAT_FS
	ret = f_mount(&FatFs, "", 1); //1=mount now
	if (ret != FR_OK) {
		LOG_ERROR(SYS, "f_mount error: %u", ret);//13
		res = false;
	}else{
		LOG_NOTICE(SYS, " mount OK");
	}
	DWORD free_clusters, free_sectors, total_sectors;
	FATFS *getFreeFs;
	if (true == res) {
    	rx_printf("%s() %u" CRLF, __FUNCTION__, __LINE__);
		//Let's get some statistics from the SD card
		ret = f_getfree("", &free_clusters, &getFreeFs);
		if (ret != FR_OK) {
			LOG_ERROR(SYS, "f_getfree error %u\r\n", ret);
			res = false;
		}
	}
	if (true == res) {
		rx_printf("%s() %u" CRLF, __FUNCTION__, __LINE__);
		//Formula comes from ChaN's documentation
		total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
		free_sectors = free_clusters * getFreeFs->csize;

		LOG_NOTICE(SYS,
				"SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n",
				total_sectors / 2, free_sectors / 2);

		//Now let's try to open file "test.txt"
		ret = f_open(&fil, "test.txt", FA_READ);
		if (ret != FR_OK) {
			rx_printf("%s() %u" CRLF, __FUNCTION__, __LINE__);
			LOG_ERROR(SYS, "f_open error (%i)\r\n");
			res = false;
		}else{
			rx_printf("f_open ok" CRLF);
		}

		f_close(&fil);
	}else{
    	rx_printf("%s() %u" CRLF, __FUNCTION__, __LINE__);
	}
#endif
	common_main_loop();
	while (1) {
	}

	return 0;
}
