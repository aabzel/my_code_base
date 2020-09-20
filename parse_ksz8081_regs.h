#ifndef PARSE_KSZ8081_REGS_H
#define PARSE_KSZ8081_REGS_H

#include "custom_type.h"
#include "ksz8081_bits_offsets.h"

#include <stdio.h>

#define UNDEF_REG_NAME "Undef_REG_NAME"

#define KSZ8081_REG_NUM 31U

typedef struct xRegKSZ8081_t {
    uint16_t reg_val;
    char reg_name[100];
} regKSZ8081_t;

extern regKSZ8081_t ksz8081RegMap[KSZ8081_REG_NUM];

bool parse_ksz8081_regs_file (char *in_file_name, char *out_file_name);

#endif /* PARSE_KSZ8081_REGS_H */
