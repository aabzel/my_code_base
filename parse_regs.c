#include "parse_regs.h"

#include "parse_tic12400_regs.h"
#include "parse_tja1101_regs.h"
#include "str_ops.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parse_regs_file (char *in_file_name, char *out_file_name) {
	printf ("\n%s()\n",__FUNCTION__);
    bool res = false;
    char *ch;
    ch = strstr (in_file_name, "tja1101");
    if (NULL != ch) {
        res = parse_tja1101_regs_file (in_file_name, out_file_name);
        if (false == res) {
            printf ("\nError in parsing tja1101 register blob");
        }
    }

    ch = strstr (in_file_name, "tic12400");
    if (NULL != ch) {
        res = parse_tic12400_regs_file (in_file_name, out_file_name);
        if (false == res) {
            printf ("\nError in parsing tic12400 register blob");
        }
    }
    return res;
}
