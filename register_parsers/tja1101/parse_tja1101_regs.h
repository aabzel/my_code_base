#ifndef PARSE_PHY_REGS_H
#define PARSE_PHY_REGS_H

#include "custom_type.h"
#include "tja1101_bits_offsets.h"

#include <stdio.h>

#define UNDEF_REG_NAME "Undef_REG_NAME"

#define TJA1101_REG_NUM 18U

typedef struct xRegTJA1101_t {
    uint8_t regAddr;
    uint16_t regVal;
    char regname[100];
} regTJA1101_t;

extern regTJA1101_t tja1101RegMap[TJA1101_REG_NUM];

const char *reg_name (uint8_t regAddr);
bool parse_tja1101_regs_file (char *inFileName, char *outFileName);
bool parse_tja1101_reg (uint8_t regAddr, uint16_t regVal, FILE *outFilePrt);

bool parse_16bit_val (char *in_str_val, uint32_t len, uint16_t *reg_addr);

bool parse_phy_state (uint8_t phyState, FILE *outFilePrt, uint8_t reg_addr);
bool parse_sqi (uint8_t sqi, FILE *outFilePrt, uint8_t reg_addr);
bool parse_mii_mode (uint8_t mii_mode, FILE *outFilePrt, uint8_t reg_addr);
bool parse_clk_mode (uint8_t clk_mode, FILE *outFilePrt, uint8_t reg_addr);
bool parse_loc_wu_tim (uint8_t loc_wu_tim, FILE *outFilePrt, uint8_t reg_addr);

#endif /* PARSE_PHY_REGS_H */
