#include "diag_page.h"

#include "common_stream.h"
#include "diag_page_nums.h"
#include "io_utils.h"
#include "log.h"

#ifndef HAS_MCAL
#include "diag_page_common.h"
#endif

static ostream_t *dbg_stream;

static diag_page_rec_t index_rec = {DIAG_PAGE_INDEX, "Index", &diag_page_index, NULL};

static diag_page_rec_t *diag_head = &index_rec;

void diag_page_init (ostream_t *stream__ini) {
    dbg_stream = stream__ini;
#ifndef HAS_MCAL
    if (false == diag_page_common_init ()) {
        LOG_ERROR (SYS, "Common diagnostic page not initialized");
    }
#endif
}

bool diag_page (uint8_t page__dp, ostream_t *stream__dp) {
    bool success__dp = false;
    diag_page_rec_t *rec__dp = diag_head;
    LOG_NOTICE (SYS, "%s()",__FUNCTION__);
    while (rec__dp != NULL) {
        if (rec__dp->diag_rec_id == page__dp) {
            LOG_NOTICE (SYS, "spot diag page");
            success__dp = rec__dp->f_page (stream__dp);
            break;
        }
        rec__dp = rec__dp->diag_rec_next;
    }

    return success__dp;
}

bool diag_page_index (ostream_t *stream__dpi) {
    diag_page_rec_t *rec__dpi = diag_head;

    while (rec__dpi != NULL) {
        if (0U != rec__dpi->diag_rec_id) {
            oputs (stream__dpi, rx_utoa32 ((uint32_t)rec__dpi->diag_rec_id));
            oputc (stream__dpi, ' ');
            oputs (stream__dpi, rec__dpi->diag_rec_name);
            oputs (stream__dpi, CRLF);
        }
        rec__dpi = rec__dpi->diag_rec_next;
    }

    return true;
}

bool diag_page_add (diag_page_rec_t *rec__dpa) {
    bool success__dpa = true;

    diag_page_rec_t *curr_rec = diag_head;
    diag_page_rec_t *prev_rec = diag_head;

    bool exit_flag = false;
    while ((exit_flag == false) && (curr_rec != NULL)) {
        if (curr_rec == rec__dpa) {
            LOG_ERROR (SYS, "diag_rec %s is already added", rec__dpa->diag_rec_name);
            success__dpa = false;
            exit_flag = true;
        }
        if (curr_rec->diag_rec_id == rec__dpa->diag_rec_id) {
            LOG_ERROR (SYS, "diag_recs %s and %s with same id %u", curr_rec->diag_rec_name, rec__dpa->diag_rec_name,
                       curr_rec->diag_rec_id);
            success__dpa = false;
            exit_flag = true;
        }
        if (curr_rec->diag_rec_id > rec__dpa->diag_rec_id) {
            prev_rec->diag_rec_next = rec__dpa;
            rec__dpa->diag_rec_next = curr_rec;
            exit_flag = true;
        }
        prev_rec = curr_rec;
        curr_rec = curr_rec->diag_rec_next;
    }
    if (exit_flag == false) { /* No errors and not already added */
        prev_rec->diag_rec_next = rec__dpa;
        rec__dpa->diag_rec_next = NULL;
    }
    return success__dpa;
}

bool show_diag_page (uint8_t page__sdp) {
    bool success__sdp = true;
    LOG_NOTICE (SYS, "%s()",__FUNCTION__);
    /* int64_t char_at_start; */
    io_flush ();
    /* char_at_start = dbg_writer.total_char_count; */
    if (diag_page (page__sdp, dbg_stream) == false) {
        success__sdp = false;
    }
    io_flush ();
    /* LOG_DEBUG (SYS, "%lld chars in page", dbg_writer.total_char_count - char_at_start); */
    return success__sdp;
}

bool dump_diag_page (uint8_t page__ddp) {
    bool success__ddp = true;
    ostream_t *stream__ddp = ccp_stream_init ();
    if (diag_page (page__ddp, stream__ddp) == false) {
        success__ddp = false;
    }
    ccp_stream_dump ("!D");
    return success__ddp;
}
