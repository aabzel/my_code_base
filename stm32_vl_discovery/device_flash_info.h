/*****************************************************************************
 * @file    device_flash_info.h
 * 
 * @attention Violates #2101-D: MISRA 2012 Rule 1.2: language extensions 
 * are not allowed.
 *****************************************************************************/

#ifndef DEVICE_FLASH_INFO_H_
#define DEVICE_FLASH_INFO_H_

#include <stdint.h>
#include <stdbool.h>
#include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CUBEMX
#define APP_START_ADDRESS       (*((const uint32_t*)0x08010004UL))
#else
extern uint8_t app_start;
#define APP_START_ADDRESS       ((uint32_t) &app_start)
#endif

#define FLASH_INFO_SIGNATURE    0x7C544F52524F547CUL
#define FLASH_INFO_VERSION      2U
#define CRC_EXCLUDE_START       9
#define CRC_EXCLUDE_LEN         39

#define TARGET_NA               0U
#define TARGET_DEBUG            1U
#define TARGET_RELEASE          2U
#define TARGET_OTHER            3U
#define TARGET_DEBUG_CHECK      4U
#define TARGET_RELEASE_CHECK    5U

#ifdef __ghs__
#pragma ghs nowarning 2101
#pragma pack(push, 1)
#endif
/* @formatter:off */
typedef struct {
    uint64_t signature;         /* 00 */
    uint8_t  info_version;      /* 08 */

    /* This Part not used CRC Calculation */
    uint16_t compile_year;      /* 09 */
    uint8_t  compile_month;     /* 0B */
    uint8_t  compile_day;       /* 0C */
    uint8_t  compile_hour;      /* 0D */
    uint8_t  compile_min;       /* 0E */
    uint8_t  compile_sec;       /* 0F */
    uint32_t flash_crc;         /* 10 */
    uint16_t version_build16;   /* 14 */
    uint32_t version_build32;   /* 16 */
    char     reserved1 [22];    /* 1A */

    /* This part used in CRC calculation */
    uint32_t flash_size;
    char     reserved2 [60];
    char     firmware_name [17];
    char     hardware_name [9];
    const char* supported_hardware;
    uint16_t version_generation;
    uint16_t version_major;
    uint16_t version_minor;
    char     reserved3 [2];
    uint16_t version_fix;
    uint8_t  target;
    char     reserved4 [0x67];
} __attribute__((__packed__)) flash_info_t;
/* @formatter:on */
#ifdef __ghs__
#pragma pack(pop)
#pragma ghs endnowarning 2101
#endif

extern const volatile flash_info_t flash_info;

#ifdef FOR_BOOTLOADER
#define HAS_BL_FLASH_INFO
extern const volatile flash_info_t bl_flash_info;
#endif /* FOR_BOOTLOADER */


uint32_t get_flash_crc (const flash_info_t *fi);


static inline uint32_t get_version_build (const flash_info_t *fi) {
    return (fi->info_version == 2U) ? fi->version_build32 : fi->version_build16;
}

/*****************************************************************************
 * @brief   Initializes flash info component.
 * @return  true on success, false otherwise.
 *****************************************************************************/
bool flash_info_init (void);

/*****************************************************************************
 * @brief   Prints application / bootloader firmware information.
 *****************************************************************************/
void flash_info_print (ostream_t *stream, const volatile flash_info_t *fi);

bool is_flash_range_accessable (void const *addr, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_FLASH_INFO_H_ */
