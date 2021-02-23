#ifndef SRC_DATA_UTILS_H_
#define SRC_DATA_UTILS_H_
#include <stdint.h>
#include <stdbool.h>
#include "device.h" 
#include <stddef.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum
{
    DATA_UTILS_ERR_CRC_STR_TO_UINT32,    /*Can't convert CRC string to uint32*/
    DATA_UTILS_ERR_BASE_STR_TO_DATA,     /*Can't convert base64 string to data*/
    DATA_UTILS_ERR_CRC32,                /*Invalid CRC32*/
    DATA_UTILS_ERR_LZ4_DECOMPRESS,       /* LZ4 decompression error*/
    DATA_UTILS_ERR_LZ4_DECOMPRESS_SIZE,  /* LZ4 decompression size mismatch*/
    DATA_UTILS_ERR_TOO_SHORT_DATA,
    DATA_UTILS_ERR_TOO_LONG_DATA
} data_utils_err_t;


/*#if defined(CUBEMX) || defined (NO_EMBEDED)
#define COMPRESS_DATA
#endif*/

#define DATA_BLOCK_SIZE 4*1024
extern uint8_t data_buffer [DATA_BLOCK_SIZE];
extern data_utils_err_t data_utils_last_err;

#define DATA_STRING_STREAM() { { string_putc, string_puts}, (char*)data_buffer, sizeof(data_buffer), 0, false};

#ifdef COMPRESS_DATA
void dump_data64 (const char* cmd, const uint8_t* data, uint16_t data_size, bool not_compress);
#else
void dump_data64 (const char* cmd, const uint8_t* data, uint16_t data_size);
#endif
bool decode_base64_arg (const char *arg_data, const char *arg_crc, uint32_t* data_size);
void dump_crc_str(const char* cmd, const uint8_t* data, uint16_t data_size);

#ifdef  __cplusplus
}
#endif

#endif /* SRC_DATA_UTILS_H_ */
