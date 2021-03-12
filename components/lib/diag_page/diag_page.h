#ifndef DIAG_PGE_H
#define DIAG_PGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "convert.h"
#include "stream.h"

#define WIDTH_OF_VOLTS_COLUMN (7)

struct diag_page_rec_s;

#define show_diag_report (show_diag_page)
#define diag_report (diag_page)

typedef struct diag_page_rec_s {
    uint8_t diag_rec_id;
    const char *diag_rec_name;
    bool (*f_page) (ostream_t *stream);
    struct diag_page_rec_s *diag_rec_next;
} diag_page_rec_t;

void diag_page_init (ostream_t *stream__ini);
bool diag_page (uint8_t page__dp, ostream_t *stream__dp);
bool diag_page_index (ostream_t *stream__dpi);
bool diag_page_add (diag_page_rec_t *rec__dpa);
bool show_diag_page (uint8_t page__sdp);
bool dump_diag_page (uint8_t page__ddp);
bool diag_page_version (ostream_t *stream);
bool diag_page_sysinfo (ostream_t *stream);

#ifdef __cplusplus
}
#endif

#endif /* DIAG_PGE_H */
