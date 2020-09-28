#include "parse_regs.h"

#include "parse_tic12400_regs.h"
#include "parse_tja1101_regs.h"
#ifdef HAS_KSZ8081
#include "parse_ksz8081_regs.h"
#endif
#include "str_ops.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parse_regs_file (char *in_file_name, char *out_file_name) {
    printf ("\n%s()\n", __FUNCTION__);
    bool res = false;
    char *ch;
#ifdef HAS_TJA1101
    ch = strstr (in_file_name, "tja1101");
    if (NULL != ch) {
        res = parse_tja1101_regs_file (in_file_name, out_file_name);
        if (false == res) {
            printf ("\nError in parsing tja1101 register blob");
        }
    }
#endif


#ifdef HAS_TIC12400
    ch = strstr (in_file_name, "tic12400");
    if (NULL != ch) {
        res = parse_tic12400_regs_file (in_file_name, out_file_name);
        if (false == res) {
            printf ("\nError in parsing tic12400 register blob");
        }
    }
#endif

#ifdef HAS_KSZ8081
    ch = strstr (in_file_name, "ksz8081");
    if (NULL != ch) {
        res = parse_ksz8081_regs_file (in_file_name, out_file_name);
        if (false == res) {
            printf ("\nError in parsing ksz8081 register blob");
        }
    }
#endif
    return res;
}
