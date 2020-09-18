#ifndef PARSE_REGS_H
#define PARSE_REGS_H

#include "custom_type.h"

#include <stdio.h>

#define DEPLOY_PARSE_REG 1

#define REG_ADDR_LEN (strlen ("0x21"))
#define REG_VAL32_LEN (strlen ("0x87654321"))
#define REG_VAL16_LEN (strlen ("0x8721"))

bool parse_regs_file (char *inFileName, char *outFileName);

#endif /* PARSE_REGS_H */
