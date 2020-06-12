#ifndef PARSE_TIC124h00_REGS_H
#define PARSE_TIC12400_REGS_H

#include "custom_type.h"

#include <stdio.h>

bool parse_tic12400_regs_file (char *inFileName, char *outFileName);
bool parse_tic12400_reg (uint8_t regAddr, uint32_t regVal, FILE *outFilePrt);

bool parse_tic12400_config_register_1ah (uint32_t regVal, FILE *outFilePrt);

bool parse_tic12400_in_stat_comp_register_05h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_in_en_register_1bh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_ccp_cfg0_register_1fh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_ccp_cfg1_register_20h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_comp_register_21h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg0_register_29h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg1_register_2ah (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg2_register_2bh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg3_register_2ch (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg4_register_2dh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_mode_register_32h (uint32_t regVal, FILE *outFilePrt);

bool parse_poll_time_val (uint8_t pollTime, FILE *outFilePrt);
bool parse_poll_act_time_val (uint8_t pollTime, FILE *outFilePrt);
bool parse_tic12400_in_en_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_mode_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_n_stat_comp_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_ccp_cfg1_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);

#endif /* PARSE_TIC12400_REGS_H */
