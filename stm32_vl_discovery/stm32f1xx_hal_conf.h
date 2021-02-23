
#ifndef __STM32F1XX_HAL_CONF_H
#define __STM32F1XX_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core_cm3.h"
#include "stm32f100xb.h"

#define HAL_MODULE_ENABLED

#define HAL_UART_MODULE_ENABLED
#define HAL_USART_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED

#if 0
  #define HAL_ADC_MODULE_ENABLED
  #define HAL_CAN_MODULE_ENABLED
  #define HAL_CAN_LEGACY_MODULE_ENABLED
  #define HAL_CEC_MODULE_ENABLED
  #define HAL_CRC_MODULE_ENABLED
  #define HAL_DAC_MODULE_ENABLED
  #define HAL_ETH_MODULE_ENABLED
  #define HAL_EXTI_MODULE_ENABLED
  #define HAL_HCD_MODULE_ENABLED
  #define HAL_I2C_MODULE_ENABLED
  #define HAL_I2S_MODULE_ENABLED
  #define HAL_IRDA_MODULE_ENABLED
  #define HAL_IWDG_MODULE_ENABLED
  #define HAL_NAND_MODULE_ENABLED
  #define HAL_NOR_MODULE_ENABLED
  #define HAL_PCCARD_MODULE_ENABLED
  #define HAL_PCD_MODULE_ENABLED
  #define HAL_PWR_MODULE_ENABLED
  #define HAL_RTC_MODULE_ENABLED
  #define HAL_SD_MODULE_ENABLED
  #define HAL_SMARTCARD_MODULE_ENABLED
  #define HAL_SPI_MODULE_ENABLED
  #define HAL_SRAM_MODULE_ENABLED
  #define HAL_TIM_MODULE_ENABLED
  #define HAL_WWDG_MODULE_ENABLED
  #define HAL_MMC_MODULE_ENABLED
#endif

#define HSE_VALUE 8000000U /*!< Value of the External oscillator in Hz */

#if !defined(HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT 100U /*!< Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

#if !defined(HSI_VALUE)
#define HSI_VALUE 8000000U /*!< Value of the Internal oscillator in Hz */
#endif /* HSI_VALUE */

#if !defined(LSI_VALUE)
#define LSI_VALUE 40000U /*!< LSI Typical Value in Hz */
#endif /* LSI_VALUE */ /*!< Value of the Internal Low Speed oscillator in Hz                                           \
                            The real value may vary depending on the variations                                        \
                            in voltage and temperature. */

#if !defined(LSE_VALUE)
#define LSE_VALUE 32768U /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined(LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT 5000U /*!< Time out for LSE start up, in ms */
#endif /* LSE_STARTUP_TIMEOUT */


#define VDD_VALUE 3300U /*!< Value of VDD in mv */
#define TICK_INT_PRIORITY 0x0FU /*!< tick interrupt priority */
#define USE_RTOS 0U
#define PREFETCH_ENABLE 1U

#define USE_HAL_ADC_REGISTER_CALLBACKS 0U /* ADC register callback disabled       */
#define USE_HAL_CAN_REGISTER_CALLBACKS 0U /* CAN register callback disabled       */
#define USE_HAL_CEC_REGISTER_CALLBACKS 0U /* CEC register callback disabled       */
#define USE_HAL_DAC_REGISTER_CALLBACKS 0U /* DAC register callback disabled       */
#define USE_HAL_ETH_REGISTER_CALLBACKS 0U /* ETH register callback disabled       */
#define USE_HAL_HCD_REGISTER_CALLBACKS 0U /* HCD register callback disabled       */
#define USE_HAL_I2C_REGISTER_CALLBACKS 0U /* I2C register callback disabled       */
#define USE_HAL_I2S_REGISTER_CALLBACKS 0U /* I2S register callback disabled       */
#define USE_HAL_MMC_REGISTER_CALLBACKS 0U /* MMC register callback disabled       */
#define USE_HAL_NAND_REGISTER_CALLBACKS 0U /* NAND register callback disabled      */
#define USE_HAL_NOR_REGISTER_CALLBACKS 0U /* NOR register callback disabled       */
#define USE_HAL_PCCARD_REGISTER_CALLBACKS 0U /* PCCARD register callback disabled    */
#define USE_HAL_PCD_REGISTER_CALLBACKS 0U /* PCD register callback disabled       */
#define USE_HAL_RTC_REGISTER_CALLBACKS 0U /* RTC register callback disabled       */
#define USE_HAL_SD_REGISTER_CALLBACKS 0U /* SD register callback disabled        */
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS 0U /* SMARTCARD register callback disabled */
#define USE_HAL_IRDA_REGISTER_CALLBACKS 0U /* IRDA register callback disabled      */
#define USE_HAL_SRAM_REGISTER_CALLBACKS 0U /* SRAM register callback disabled      */
#define USE_HAL_SPI_REGISTER_CALLBACKS 0U /* SPI register callback disabled       */
#define USE_HAL_TIM_REGISTER_CALLBACKS 0U /* TIM register callback disabled       */
#define USE_HAL_UART_REGISTER_CALLBACKS 0U /* UART register callback disabled      */
#define USE_HAL_USART_REGISTER_CALLBACKS 0U /* USART register callback disabled     */
#define USE_HAL_WWDG_REGISTER_CALLBACKS 0U /* WWDG register callback disabled      */

#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32f1xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f1xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_EXTI_MODULE_ENABLED
#include "stm32f1xx_hal_exti.h"
#endif /* HAL_EXTI_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
#include "stm32f1xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_ETH_MODULE_ENABLED
#include "stm32f1xx_hal_eth.h"
#endif /* HAL_ETH_MODULE_ENABLED */

#ifdef HAL_CAN_MODULE_ENABLED
#include "stm32f1xx_hal_can.h"
#endif /* HAL_CAN_MODULE_ENABLED */

#ifdef HAL_CAN_LEGACY_MODULE_ENABLED
#include "Legacy/stm32f1xx_hal_can_legacy.h"
#endif /* HAL_CAN_LEGACY_MODULE_ENABLED */

#ifdef HAL_CEC_MODULE_ENABLED
#include "stm32f1xx_hal_cec.h"
#endif /* HAL_CEC_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32f1xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
#include "stm32f1xx_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_CRC_MODULE_ENABLED
#include "stm32f1xx_hal_crc.h"
#endif /* HAL_CRC_MODULE_ENABLED */

#ifdef HAL_DAC_MODULE_ENABLED
#include "stm32f1xx_hal_dac.h"
#endif /* HAL_DAC_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
#include "stm32f1xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_SRAM_MODULE_ENABLED
#include "stm32f1xx_hal_sram.h"
#endif /* HAL_SRAM_MODULE_ENABLED */

#ifdef HAL_NOR_MODULE_ENABLED
#include "stm32f1xx_hal_nor.h"
#endif /* HAL_NOR_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
#include "stm32f1xx_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_I2S_MODULE_ENABLED
#include "stm32f1xx_hal_i2s.h"
#endif /* HAL_I2S_MODULE_ENABLED */

#ifdef HAL_IWDG_MODULE_ENABLED
#include "stm32f1xx_hal_iwdg.h"
#endif /* HAL_IWDG_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32f1xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
#include "stm32f1xx_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_PCCARD_MODULE_ENABLED
#include "stm32f1xx_hal_pccard.h"
#endif /* HAL_PCCARD_MODULE_ENABLED */

#ifdef HAL_SD_MODULE_ENABLED
#include "stm32f1xx_hal_sd.h"
#endif /* HAL_SD_MODULE_ENABLED */

#ifdef HAL_NAND_MODULE_ENABLED
#include "stm32f1xx_hal_nand.h"
#endif /* HAL_NAND_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
#include "stm32f1xx_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
#include "stm32f1xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#include "stm32f1xx_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_USART_MODULE_ENABLED
#include "stm32f1xx_hal_usart.h"
#endif /* HAL_USART_MODULE_ENABLED */

#ifdef HAL_IRDA_MODULE_ENABLED
#include "stm32f1xx_hal_irda.h"
#endif /* HAL_IRDA_MODULE_ENABLED */

#ifdef HAL_SMARTCARD_MODULE_ENABLED
#include "stm32f1xx_hal_smartcard.h"
#endif /* HAL_SMARTCARD_MODULE_ENABLED */

#ifdef HAL_WWDG_MODULE_ENABLED
#include "stm32f1xx_hal_wwdg.h"
#endif /* HAL_WWDG_MODULE_ENABLED */

#ifdef HAL_PCD_MODULE_ENABLED
#include "stm32f1xx_hal_pcd.h"
#endif /* HAL_PCD_MODULE_ENABLED */

#ifdef HAL_HCD_MODULE_ENABLED
#include "stm32f1xx_hal_hcd.h"
#endif /* HAL_HCD_MODULE_ENABLED */

#ifdef HAL_MMC_MODULE_ENABLED
#include "stm32f1xx_hal_mmc.h"
#endif /* HAL_MMC_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr If expr is false, it calls assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 *         If expr is true, it returns no value.
 * @retval None
 */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed ((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed (uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1XX_HAL_CONF_H */

