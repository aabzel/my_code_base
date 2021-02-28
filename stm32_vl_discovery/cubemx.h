

#ifndef CUBEMX_H_
#define CUBEMX_H_

#define CUBEMX_PROJECT stm32_vl_discovery
#define CUBEMX_PROJECT_STR "stm32_vl_discovery"

/* Indicate that version_info shall be supported for this CUBEMX target */
#define CUBEMX_WITH_VERSION

/* MCU info */
#define MCU_FAMILY STM32F1
//#define MCU_SUB_FAMILY
#define MCU_PARTNUMBER STM32F100RBT6B

/* General info */
//#define HAS_IPP_IWDG
#define HAS_IPP_NVIC
#define HAS_IPP_RCC
//#define HAS_IPP_SYS
#define HAS_IPP_USART1
#define HAS_IPP_USART
#define HAS_IPP_UART1
#define HAS_IPP_UART

#include "stm32F1xx_hal.h"
#include "stm32F1xx_it.h"

#endif /* CUBEMX_H_ */
