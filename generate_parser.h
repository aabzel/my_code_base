#ifndef GENERATE_REG_PARSER_H
#define GENERATE_REG_PARSER_H

#include <stdbool.h>
#include <stdio.h>

#include "custom_type.h"

#define MAX_NUM_REG 255

typedef struct xReg_map_t {
    uint8_t reg_addr;
    char reg_name[100];
    bool valid;
} xReg_map_t;

extern xReg_map_t RegMap[MAX_NUM_REG];

bool parse_bit_range (char *cur_file_str, int strlen, uint8_t *bit_old, uint8_t *bit_little, char *prefix);
bool parse_uint8_after_prefix (char *cur_file_str, int in_str_len, uint16_t *val, char *prefix);
bool parse_text_after_prefix (char *cur_file_str, int strlen, char *out_text, char *prefix);
// bool parse_reg_name(char *cur_file_str, int strlen,char * reg_nane);
// bool parse_bit_text(char *cur_file_str, int strlen,char *bit_text);
// bool parse_bit_type(char *cur_file_str, int strlen,char *bit_type);

bool parse_bit_val (char *cur_file_str, int strlen, uint16_t *bit_val);
bool parse_bit_num (char *cur_file_str, int strlen, uint8_t *bit_num);
bool parse_reg_addr (char *cur_file_str, int strlen, uint8_t *reg_addr);

bool generate_reg_parser (char *in_file_name, char *out_file_name, char *chip_name, char *reg_bitness);

#endif /* GENERATE_REG_PARSER_H */
