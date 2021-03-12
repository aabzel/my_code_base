#include "diag_page_commands.h"

#include "convert.h"
#include "diag_page_nums.h"
#include "log.h"

bool diag_page_list_cmd (int32_t argc, char *argv[]) {
    bool success = true;
    uint8_t page_number = DIAG_PAGE_INDEX;

    if ((argc != 0) && (argc != 1)) {
        LOG_ERROR (SYS, "Usage: diag_page [page_number]");
        success = dump_cmd_result (false);
    }

    if ((success == true) && (argc >= 1)) {
        if (!try_str2uint8 (argv[0], &page_number)) {
            LOG_ERROR (SYS, "Invalid page number [%s]", argv[0]);
            success = dump_cmd_result (false);
        }
    }

    if (success == true) {
        success = dump_cmd_result (show_diag_page (page_number));
    }

    return success;
}
