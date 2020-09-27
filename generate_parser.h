#ifndef GENERATE_REG_PARSER_H
#define GENERATE_REG_PARSER_H

#include <stdio.h>

#include "custom_type.h"

bool parse_uint8_after_prefix(char *cur_file_str, int in_str_len, uint8_t *val, char *prefix);
bool parse_text_after_prefix(char *cur_file_str, int strlen,char *out_text, char *prefix);
//bool parse_reg_name(char *cur_file_str, int strlen,char * reg_nane);
//bool parse_bit_text(char *cur_file_str, int strlen,char *bit_text);
//bool parse_bit_type(char *cur_file_str, int strlen,char *bit_type);

bool parse_bit_val(char *cur_file_str, int strlen, uint8_t *bit_val);
bool parse_bit_num(char *cur_file_str, int strlen, uint8_t *bit_num);
bool parse_reg_addr(char *cur_file_str, int strlen, uint8_t *reg_addr);

bool generate_reg_parser (char *in_file_name, char *out_file_name) ;

#endif /* GENERATE_REG_PARSER_H */



