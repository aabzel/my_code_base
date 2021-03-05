#include "data_utils.h"

#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "bit_order.h"
#include "convert.h"
#include "crc32.h"
#include "log.h"
#include "rx_io.h"
#include "rx_utils.h"
#include "sections.h"
#include "shell.h"

#ifndef H__BITORDER_H
#error bit_order.h must be included
#endif

#ifdef COMPRESS_DATA
#include "lz4.h"
#define LZ4_DATA_BLOCK_SIZE 4 * 1024
typedef union {
    struct {
        uint16_t size; /* IN intel format */
        char data[LZ4_DATA_BLOCK_SIZE];
    } lz4_data;
    uint8_t raw_data[LZ4_DATA_BLOCK_SIZE + sizeof (uint16_t)];
} lz4_buffer_t;

NOINIT static lz4_buffer_t lz4_data_buffer CORE2_MEM;

#endif /* CUBEMX */

#ifdef INTEL_ORDER
#define CONVERT16(x) (x)
#else
#define CONVERT16(x) (swap16 (x))
#endif

data_utils_err_t data_utils_last_err;

#ifdef COMPRESS_DATA
void dump_data64 (const char *cmd, const uint8_t *data, uint16_t data_size, bool not_compress) {
#else /* COMPRESS_DATA */
void dump_data64 (const char *cmd, const uint8_t *data, uint16_t data_size) {
#endif /* COMPRESS_DATA */
    uint32_t crc;
#ifdef COMPRESS_DATA
#ifdef SPC58
#define XCP_LZ4_MEMORY SRAM2 ("noinit")
#else
#define XCP_LZ4_MEMORY NOINIT
#endif
    XCP_LZ4_MEMORY static LZ4_stream_t lz4_context;
    bool compressed = false;
    if (!not_compress) {
        int compressed_size = LZ4_compress_fast_extState (
            &lz4_context, (const char *)data, lz4_data_buffer.lz4_data.data, data_size, LZ4_DATA_BLOCK_SIZE, 1);
        if ((compressed_size != 0) && (compressed_size + 1 + sizeof (uint16_t)) < (int)data_size) {
            compressed = true;
            LOG_DEBUG (SYS, "Compress data from %" PRIu16 "to %" PRIu16, data_size,
                       compressed_size + 1 + (uint16_t)sizeof (uint16_t));
            lz4_data_buffer.lz4_data.size = CONVERT16 (data_size);
            data_size = compressed_size + sizeof (uint16_t);
            data = lz4_data_buffer.raw_data;
        }
    }
#endif /* COMPRESS_DATA */
    flush_printf ();
    crc = crc32 (data, data_size);
    rx_printf ("%s 0x%08" PRIX32 " ", cmd, crc);
#ifdef COMPRESS_DATA
    if (compressed) {
        rx_putstr ("!");
    }
#endif /* COMPRESS_DATA */
    while (data_size) {
        NOINIT static char buff[13] CORE2_MEM;
        uint8_t chunk_size = rx_min32u (data_size, 3 * 3);
        uint32_t s = base64_encode (data, chunk_size, buff);
        buff[s] = 0;
        flush_printf ();
        rx_putstr (buff);
        data_size -= chunk_size;
        data += chunk_size;
    }
    rx_putstr (CRLF);
}

NOINIT uint8_t data_buffer[DATA_BLOCK_SIZE] CORE2_MEM;

bool decode_base64_arg (const char *arg_data, const char *arg_crc, uint32_t *data_size) {
    uint32_t calulated_crc32, data_crc32 = 0;
#ifdef COMPRESS_DATA
    bool compressed = false;
#endif
    int len;
    uint8_t *buffer;
    if (!try_str2uint32 (arg_crc, &data_crc32)) {
        LOG_ERROR (SYS, "Can't convert CRC string to uint32 [%s]", arg_crc);
        data_utils_last_err = DATA_UTILS_ERR_CRC_STR_TO_UINT32;
        return dump_cmd_result_ex (false, "Can't convert CRC string to uint32");
    }
#ifdef COMPRESS_DATA
    if (arg_data[0] == '!') {
        compressed = true;
        arg_data++;
    }
#endif
    len = strlen (arg_data);
    if (len < 4) {
        data_utils_last_err = DATA_UTILS_ERR_TOO_SHORT_DATA;
        return dump_cmd_result_ex (false, "Data string too short");
    }
    buffer = data_buffer;
#ifdef COMPRESS_DATA
    if (len / 4 * 3 > (int)(compressed ? sizeof (lz4_data_buffer) : sizeof (data_buffer))) {
        data_utils_last_err = DATA_UTILS_ERR_TOO_LONG_DATA;
        return dump_cmd_result_ex (false, "Data string too long");
    }
    if (compressed) {
        buffer = lz4_data_buffer.raw_data;
    }
#else
    if (len / 4 * 3 > (int)(sizeof (data_buffer))) {
        data_utils_last_err = DATA_UTILS_ERR_TOO_LONG_DATA;
        return dump_cmd_result_ex (false, "Data string too long");
    }
#endif
    if (!base64_decode (arg_data, len, buffer, data_size)) {
        LOG_ERROR (SYS, "Can't convert base64 string to data [%s] len=%d", arg_data, len);
        data_utils_last_err = DATA_UTILS_ERR_BASE_STR_TO_DATA;
        return dump_cmd_result_ex (false, "Can't convert base64 string to data");
    }
    calulated_crc32 = crc32 (buffer, *data_size);
    if (calulated_crc32 != data_crc32) {
        LOG_ERROR (SYS, "Invalid CRC32 0x%08" PRIX32 " != 0x%08" PRIX32, data_crc32, calulated_crc32);
        data_utils_last_err = DATA_UTILS_ERR_CRC32;
        return dump_cmd_result_ex (false, "Invalid CRC32");
    }
#ifdef COMPRESS_DATA
    if (compressed) {
        int decompressed_size = LZ4_decompress_safe (lz4_data_buffer.lz4_data.data, (char *)data_buffer,
                                                     *data_size - sizeof (uint16_t), sizeof (data_buffer));
        if (decompressed_size < 0) {
            LOG_ERROR (SYS, "LZ4 decompression error %d", decompressed_size);
            data_utils_last_err = DATA_UTILS_ERR_LZ4_DECOMPRESS;
            return dump_cmd_result_ex (false, "LZ4 decompression error");
        }
        if (decompressed_size != CONVERT16 (lz4_data_buffer.lz4_data.size)) {
            LOG_ERROR (SYS, "LZ4 decompression size mismatch %d!=%u", decompressed_size,
                       CONVERT16 (lz4_data_buffer.lz4_data.size));
            data_utils_last_err = DATA_UTILS_ERR_LZ4_DECOMPRESS_SIZE;
            return dump_cmd_result_ex (false, "LZ4 decompression size mismatch");
        }
        *data_size = CONVERT16 (lz4_data_buffer.lz4_data.size);
    }
#endif
    return true;
}

void dump_crc_str (const char *cmd, const uint8_t *data, uint16_t data_size) {
    uint32_t crc;
    flush_printf ();

    crc = crc32 (data, data_size);
    rx_printf ("%s 0x%08" PRIX32 "%s", cmd, crc, data);
    rx_putstr (CRLF);
}

bool init_array_123(uint8_t *const array, uint16_t len){
	bool res = false;
	if (NULL!=array) {
		for (uint16_t i=0; i<len; i++){
			array[i]=0x30+(i%10);
		}
		res = true;
	}
	return res;
}
