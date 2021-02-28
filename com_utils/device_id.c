#include <inttypes.h>
#include <stdint.h>

#include "device_id.h"
#include "rx_io.h"
#include "str_utils.h"

#ifdef CUBEMX
#include "cubemx.h"
//#include "main.h"
#if defined(HAS_CHIP_UID)
#include "STM32_24AA02UID_V1.h"
#include "spi.h"
SPI_HandleTypeDef *hspi;
#endif /*HAS_CHIP_UID*/

#define ID_UNIQUE_ADDRESS 0x1FFFF7E8 //0x1FFF7A10
#define DEVICE_ID_SIZE 12
#define TM_ID_GetUnique8(x) *(((const uint8_t *)ID_UNIQUE_ADDRESS) + x)
#define TM_ID_GetUnique32(x) *(((const uint32_t *)ID_UNIQUE_ADDRESS) + x)

void dump_device_id (void) {
    rx_printf ("0x%08" PRIX32 " 0x%08" PRIX32 " 0x%08" PRIX32 " ", TM_ID_GetUnique32 (0), TM_ID_GetUnique32 (1),
               TM_ID_GetUnique32 (2));
}

uint64_t get_device_serial (void) {
    return ((uint64_t)TM_ID_GetUnique32 (0)) ^ ((uint64_t)TM_ID_GetUnique32 (1)) << 7 ^
           ((uint64_t)TM_ID_GetUnique32 (2)) << 16;
}

#ifndef MCU_PARTNUMBER
#error "Add MCU_PARTNUMBER definition to device_config.h"
#endif
const char *get_mcu_name (void) { return TOSTRING (MCU_PARTNUMBER); }
#endif

