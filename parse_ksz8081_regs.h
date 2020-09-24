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

/*bits Operation Mode Indication REG PHY Control 1*/
typedef enum {
    OP_MODE_STILL_IN_AUTO_NEGOTIATION = 0U,
    OP_MODE_10BASE_T_HALF_DUPLEX = 1U,
    OP_MODE_100BASE_TX_HALF_DUPLEX = 2U,
    OP_MODE_RESERVED1 = 3U,
    OP_MODE_RESERVED2 = 4U,
    OP_MODE_10BASE_T_FULL_DUPLEX = 5U,
    OP_MODE_100BASE_TX_FULL_DUPLEX = 6U,
    OP_MODE_RESERVED3 = 7U
} lantrcv_op_mode_t;

extern regKSZ8081_t ksz8081RegMap[KSZ8081_REG_NUM];

bool parse_ksz8081_regs_file (char *in_file_name, char *out_file_name);

#endif /* PARSE_KSZ8081_REGS_H */
