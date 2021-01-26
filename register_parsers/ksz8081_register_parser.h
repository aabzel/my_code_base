
#ifndef GENERATED_PARSER_ksz8081_H
#define GENERATED_PARSER_ksz8081_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "parse_ksz8081_regs.h"

extern uint16_t proc_reg_cnt;

bool parse_ksz8081_reg (uint8_t reg_addr, FILE *out_file_prt);

#endif /*GENERATED_PARSER_ksz8081_H*/
