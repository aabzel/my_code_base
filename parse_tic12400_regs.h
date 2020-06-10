#ifndef PARSE_TIC12400_REGS_H
#define PARSE_TIC12400_REGS_H

#include "custom_type.h"

#include <stdio.h>

bool parse_tic12400_regs_file (char *inFileName, char *outFileName);
bool parse_tic12400_reg (uint8_t regAddr, uint32_t regVal, FILE *outFilePrt);

bool parse_tic12400_config_register (uint32_t regVal, FILE *outFilePrt);
bool parse_poll_time_val (uint8_t pollTime, FILE *outFilePrt);
bool parse_poll_act_time_val (uint8_t pollTime, FILE *outFilePrt);

#endif /* PARSE_TIC12400_REGS_H */
