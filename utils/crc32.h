#ifndef SRC_CRC32_H_
#define SRC_CRC32_H_
#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

uint32_t crc32_continued_nuble(uint32_t crc_in_c4, const uint8_t data_c4[], uint32_t len_c4);
uint32_t crc32_nuble(const uint8_t data_4[], uint32_t len_4);

uint32_t crc32(const uint8_t data_8[], uint32_t len_8);
uint32_t crc32_continued(uint32_t crc_in_c8, const uint8_t data_c8[], uint32_t len_c8);

uint32_t crc32_combine (uint32_t crc1, uint32_t crc2, uint32_t len2);

#ifdef  __cplusplus
}
#endif

#endif /* SRC_CRC32_H_ */
