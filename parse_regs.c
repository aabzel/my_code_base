#include "parse_regs.h"

#include "str_ops.h"
#include "parse_tja1101_regs.h"
#include "parse_tic12400_regs.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

bool parse_regs_file (char *inFileName, char *outFileName) {
    (void) *outFileName;
    bool res = false;
    char *ch = strstr (inFileName, "tic12400");
    if (NULL != ch) {
        res = parse_tic12400_regs_file (inFileName, outFileName);
    }
    ch = strstr (inFileName, "tja1101");
    if (NULL != ch) {
        res = parse_tja1101_regs_file (inFileName, outFileName);
    }
    return res;

}

