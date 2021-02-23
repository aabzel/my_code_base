#if 0
#include "common_stream.h"
#include "data_utils.h"
#include "rx_utils.h"
#include "string_writer.h"

#ifdef SPC58xC
#    include "sections.h"
#    define SECTION SRAM2_NOINIT
#endif /* SPC58xC */

#ifdef SPC58xN
#   include "sections.h"
#   ifdef BOOTLOADER
#       define SECTION SRAM2_NOINIT
#   else /* BOOTLOADER */
#       define SECTION CORE1_RAM_NOINIT
#   endif /* BOOTLOADER */
#endif /* SPC58xN */

#ifndef SECTION
#   define SECTION
#endif /* SECTION */

static char ccp_stream_str [1024*10 + 1] SECTION;
static string_stream_t ccp_stream = STRING_STREAM(ccp_stream_str);

ostream_t* ccp_stream_init(void) {
    ccp_stream.pos = 0;
    ccp_stream.overflow = false;
    return &ccp_stream.s;
}

void ccp_stream_dump(const char* cmd) {
#if defined(CUBEMX)||defined(COMPRESS_DATA)
    dump_data64 (cmd, (const uint8_t*)ccp_stream.data, ccp_stream.pos, true);
#else
    dump_data64 (cmd, (const uint8_t*)ccp_stream.data, ccp_stream.pos);
#endif
}

uint16_t ccp_stream_get_position(void) {
    return ccp_stream.pos;
}

char* ccp_stream_get_data(void) {
    return ccp_stream.data;
}

#endif
