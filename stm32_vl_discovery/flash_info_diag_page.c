#include "flash_info_diag_page.h"

#include <inttypes.h>

#include "diag_page.h"
#include "diag_page_nums.h"
#include "device_flash_info.h"

#ifdef HAS_MCAL
#include "uid.h"
#else
#include "device_id.h"
#endif

#ifdef HAS_PARAMS
#include "oprintf.h"
#include "param_commands.h"
#endif

static bool flash_info_diag_page_version (ostream_t *stream);

static bool flash_info_diag_page_version (ostream_t *stream) {
    flash_info_print (stream, &flash_info);
    // uid_print (stream);

#ifdef HAS_PARAMS
    oprintf (stream, "ParametersCRC:0x%08" PRIX32 CRLF, get_params_work_set_crc32 ());
#endif

#ifdef HAS_BL_FLASH_INFO
    oputs (stream, "Bootloader: ");
    flash_info_print (stream, &bl_flash_info);
    oputs (stream, CRLF);
#endif

    return true;
}

bool flash_info_diag_page_init (void) {
    static diag_page_rec_t version_rec = {DIAG_PAGE_VERSION, "Version", flash_info_diag_page_version, NULL};

    return diag_page_add (&version_rec);
}
