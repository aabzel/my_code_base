
#include "tic12400_register_parser.h"
#include "str_ops.h"

static bool parse_tic12400_int_en_cfg4_register_40 (uint32_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 40 == reg_addr ) {
        res = true;
    }
    if(0==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:0 RW no interrupt generation for VS w.r.t. VS1_THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:1 RW generation on rising edge above VS1_THRES2B for VS", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:2 RW interrupt generation on falling edge below VS1_THRES2B for VS", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:3 RW interrupt generation on falling and rising edge of VS1_THRES2B for VS", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:0 RW no interrupt generation for VS w.r.t. VS1_THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:1 RW generation on rising edge above VS1_THRES2A for VS", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:2 RW interrupt generation on falling edge below VS1_THRES2A for VS", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:3 RW interrupt generation on falling and rising edge of VS1_THRES2A for VS", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:0 RW no interrupt generation for VS w.r.t. VS0_THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:1 RW interrupt generation on rising edge above VS0_THRES2B for VS", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:2 RW interrupt generation on falling edge below VS0_THRES2B for VS", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:3 RW interrupt generation on falling and rising edge of VS0_THRES2B for VS", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:0 RW no interrupt generation for VS w.r.t. VS0_THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:1 RW interrupt generation on rising edge above VS0_THRES2A for VS", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:2 RW interrupt generation on falling edge below VS0_THRES2A for VS", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:3 RW interrupt generation on falling and rising edge of VS0_THRES2A for VS", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:0 RW no interrupt generation for IN23 w.r.t. THRES9", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:1 RW interrupt generation on rising edge above THRES9 for IN23", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:2 RW interrupt generation on falling edge below THRES9 for IN23", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:3 RW interrupt generation on falling and rising edge of THRES9 for IN23", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:0 RW no interrupt generation for IN23 w.r.t. THRES8", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:1 RW interrupt generation on rising edge above THRES8 for IN23", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:2 RW interrupt generation on falling edge below THRES8 for IN23", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:3 RW interrupt generation on falling and rising edge of THRES8 for IN23", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:0 RW no interrupt generation for IN23 w.r.t. THRES3C", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:1 RW interrupt generation on rising edge above THRES3C for IN23", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:2 RW interrupt generation on falling edge below THRES3C for IN23", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:3 RW interrupt generation on falling and rising edge of THRES3C for IN23", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:0 RW no interrupt generation for IN23 w.r.t. THRES3B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:1 RW interrupt generation on rising edge above THRES3B for IN23", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:2 RW interrupt generation on falling edge below THRES3B for IN23", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:3 RW interrupt generation on falling and rising edge of THRES3B for IN23", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:0 RW no interrupt generation for IN23 w.r.t. THRES3A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:1 RW interrupt generation on rising edge above THRES3A for IN23", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:2 RW interrupt generation on falling edge below THRES3A for IN23", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:3 RW interrupt generation on falling and rising edge of THRES3A for IN23", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:0 RW no interrupt generation for IN22 w.r.t. THRES3C", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:1 RW interrupt generation on rising edge above THRES3C for IN22", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:2 RW interrupt generation on falling edge below THRES3C for IN22", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:3 RW interrupt generation on falling and rising edge of THRES3C for IN22", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:0 RW no interrupt generation for IN22 w.r.t. THRES3B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:1 RW interrupt generation on rising edge above THRES3B for IN22", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:2 RW interrupt generation on falling edge below THRES3B for IN22", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:3 RW interrupt generation on falling and rising edge of THRES3B for IN22", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:0 RW no interrupt generation for IN22 w.r.t. THRES3A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:1 RW interrupt generation on rising edge above THRES3A for IN22", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:2 RW interrupt generation on falling edge below THRES3A for IN22", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:3 RW interrupt generation on falling and rising edge of THRES3A for IN22", reg_addr); 
    }
    return res;
}

static bool parse_tic12400_int_en_cfg3_register_39 (uint32_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 39 == reg_addr ) {
        res = true;
    }
    if(0==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:0 RW no interrupt generation for IN21 w.r.t. THRES3C", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:1 RW interrupt generation on rising edge above THRES3C for IN21", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:2 RW interrupt generation on falling edge below THRES3C for IN21", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:3 RW interrupt generation on falling and rising edge of THRES3C for IN21", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:0 RW no interrupt generation for IN21 w.r.t. THRES3B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:1 RW interrupt generation on rising edge above THRES3B for IN21", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:2 RW interrupt generation on falling edge below THRES3B for IN21", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:3 RW interrupt generation on falling and rising edge of THRES3B for IN21", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:0 RW no interrupt generation for IN21 w.r.t. THRES3A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:1 RW interrupt generation on rising edge above THRES3A for IN21", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:2 RW interrupt generation on falling edge below THRES3A for IN21", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:3 RW interrupt generation on falling and rising edge of THRES3A for IN21", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:0 RW no interrupt generation for IN20 w.r.t. THRES3C", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:1 RW interrupt generation on rising edge above THRES3C for IN20", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:2 RW interrupt generation on falling edge below THRES3C for IN20", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:3 RW interrupt generation on falling and rising edge of THRES3C for IN20", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:0 RW no interrupt generation for IN20 w.r.t. THRES3B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:1 RW interrupt generation on rising edge above THRES3B for IN20", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:2 RW interrupt generation on falling edge below THRES3B for IN20", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:3 RW interrupt generation on falling and rising edge of THRES3B for IN20", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:0 RW no interrupt generation for IN20 w.r.t. THRES3A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:1 RW interrupt generation on rising edge above THRES3A for IN20", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:2 RW interrupt generation on falling edge below THRES3A for IN20", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:3 RW interrupt generation on falling and rising edge of THRES3A for IN20", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:0 RW no interrupt generation for IN19 w.r.t. THRES3C", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:1 RW generation on rising edge above THRES3C for IN19", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:2 RW interrupt generation on falling edge below THRES3C for IN19", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:3 RW interrupt generation on falling and rising edge of THRES3C for IN19", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:0 RW no interrupt generation for IN19 w.r.t. THRES3B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:1 RW interrupt generation on rising edge above THRES3B for IN19", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:2 RW interrupt generation on falling edge below THRES3B for IN19", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:3 RW interrupt generation on falling and rising edge of THRES3B for IN19", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:0 RW no interrupt generation for IN19 w.r.t. THRES3A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:1 RW interrupt generation on rising edge above THRES3A for IN19", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:2 RW interrupt generation on falling edge below THRES3A for IN19", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:3 RW interrupt generation on falling and rising edge of THRES3A for IN19", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:0 RW no interrupt generation for IN18 w.r.t. THRES3C", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:1 RW interrupt generation on rising edge above THRES3C for IN18", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:2 RW interrupt generation on falling edge below THRES3C for IN18", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:3 RW interrupt generation on falling and rising edge of THRES3C for IN18", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:0 RW no interrupt generation for IN18 w.r.t. THRES3B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:1 RW interrupt generation on rising edge above THRES3B for IN18", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:2 RW interrupt generation on falling edge below THRES3B for IN18", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:3 RW interrupt generation on falling and rising edge of THRES3B for IN18", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:0 RW no interrupt generation for IN18 w.r.t. THRES3A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:1 RW interrupt generation on rising edge above THRES3A for IN18", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:2 RW interrupt generation on falling edge below THRES3A for IN18", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:3 RW interrupt generation on falling and rising edge of THRES3A for IN18", reg_addr); 
    }
    return res;
}

static bool parse_tic12400_int_en_cfg2_register_38 (uint32_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 38 == reg_addr ) {
        res = true;
    }
    if(0==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:0 RW no interrupt generation for IN17 w.r.t. THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:1 RW interrupt generation on rising edge above THRES2B for IN17", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:2 RW interrupt generation on falling edge below THRES2B for IN17", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:3 RW interrupt generation on falling and rising edge of THRES2B for IN17", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:0 RW no interrupt generation for IN17 w.r.t. THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:1 RW interrupt generation on rising edge above THRES2A for IN17", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:2 RW interrupt generation on falling edge below THRES2A for IN17", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:3 RW interrupt generation on falling and rising edge of THRES2A for IN17", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:0 RW no interrupt generation for IN16 w.r.t. THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:1 RW interrupt generation on rising edge above THRES2B for IN16", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:2 RW interrupt generation on falling edge below THRES2B for IN16", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:3 RW interrupt generation on falling and rising edge of THRES2B for IN16", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:0 RW no interrupt generation for IN16 w.r.t. THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:1 RW interrupt generation on rising edge above THRES2A for IN16", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:2 RW interrupt generation on falling edge below THRES2A for IN16", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:3 RW interrupt generation on falling and rising edge of THRES2A for IN16", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:0 RW no interrupt generation for IN15 w.r.t. THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:1 RW interrupt generation on rising edge above THRES2B for IN15", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:2 RW interrupt generation on falling edge below THRES2B for IN15", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:3 RW interrupt generation on falling and rising edge of THRES2B for IN15", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:0 RW no interrupt generation for IN15 w.r.t. THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:1 RW interrupt generation on rising edge above THRES2A for IN15", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:2 RW interrupt generation on falling edge below THRES2A for IN15", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:3 RW interrupt generation on falling and rising edge of THRES2A for IN15", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:0 RW no interrupt generation for IN14 w.r.t. THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:1 RW interrupt generation on rising edge above THRES2B for IN14", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:2 RW interrupt generation on falling edge below THRES2B for IN14", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:3 RW interrupt generation on falling and rising edge of THRES2B for IN14", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:0 RW no interrupt generation for IN14 w.r.t. THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:1 RW interrupt generation on rising edge above THRES2A for IN14", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:2 RW interrupt generation on falling edge below THRES2A for IN14", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>8))){
        fprintf (out_file_prt,"\n    reg %02u bit 9-8:3 RW interrupt generation on falling and rising edge of THRES2A for IN14", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:0 RW no interrupt generation for IN13 w.r.t. THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:1 RW interrupt generation on rising edge above THRES2B for IN13", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:2 RW interrupt generation on falling edge below THRES2B for IN13", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>6))){
        fprintf (out_file_prt,"\n    reg %02u bit 7-6:3 RW interrupt generation on falling and rising edge of THRES2B for IN13", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:0 RW no interrupt generation for IN13 w.r.t. THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:1 RW interrupt generation on rising edge above THRES2A for IN13", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:2 RW interrupt generation on falling edge below THRES2A for IN13", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>4))){
        fprintf (out_file_prt,"\n    reg %02u bit 5-4:3 RW interrupt generation on falling and rising edge of THRES2A for IN13", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:0 RW no interrupt generation for IN12 w.r.t. THRES2B", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:1 RW interrupt generation on rising edge above THRES2B for IN12", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:2 RW interrupt generation on falling edge below THRES2B for IN12", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>2))){
        fprintf (out_file_prt,"\n    reg %02u bit 3-2:3 RW interrupt generation on falling and rising edge of THRES2B for IN12", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:0 RW no interrupt generation for IN12 w.r.t. THRES2A", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:1 RW interrupt generation on rising edge above THRES2A for IN12", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:2 RW interrupt generation on falling edge below THRES2A for IN12", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>0))){
        fprintf (out_file_prt,"\n    reg %02u bit 1-0:3 RW interrupt generation on falling and rising edge of THRES2A for IN12", reg_addr); 
    }
    return res;
}

static bool parse_tic12400_int_en_cfg1_register_37 (uint32_t reg_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void) code;
    if ( 37 == reg_addr ) {
        res = true;
    }
    if(0==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:0 RW no interrupt generation for IN11", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:1 RW interrupt generation on rising edge above THRESx for IN11", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:2 RW interrupt generation on falling edge below THRESx for IN11", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>22))){
        fprintf (out_file_prt,"\n    reg %02u bit 23-22:3 RW interrupt generation on falling and rising edge of THRESx for IN11", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:0 RW no interrupt generation for IN10", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:1 RW interrupt generation on rising edge above THRESx for IN10", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:2 RW interrupt generation on falling edge below THRESx for IN10", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>20))){
        fprintf (out_file_prt,"\n    reg %02u bit 21-20:3 RW interrupt generation on falling and rising edge of THRESx for IN10", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:0 RW no interrupt generation for IN9", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:1 RW interrupt generation on rising edge above THRESx for IN9", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:2 RW interrupt generation on falling edge below THRESx for IN9", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>18))){
        fprintf (out_file_prt,"\n    reg %02u bit 19-18:3 RW interrupt generation on falling and rising edge of THRESx for IN9", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:0 RW no interrupt generation for IN8", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:1 RW interrupt generation on rising edge above THRESx for IN8", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:2 RW interrupt generation on falling edge below THRESx for IN8", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>16))){
        fprintf (out_file_prt,"\n    reg %02u bit 17-16:3 RW interrupt generation on falling and rising edge of THRESx for IN8", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:0 RW no interrupt generation for IN7", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:1 RW interrupt generation on rising edge above THRESx for IN7", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:2 RW interrupt generation on falling edge below THRESx for IN7", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>14))){
        fprintf (out_file_prt,"\n    reg %02u bit 15-14:3 RW interrupt generation on falling and rising edge of THRESx for IN7", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:0 RW no interrupt generation for IN6", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:1 RW interrupt generation on rising edge above THRESx for IN6", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:2 RW interrupt generation on falling edge below THRESx for IN6", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>12))){
        fprintf (out_file_prt,"\n    reg %02u bit 13-12:3 RW interrupt generation on falling and rising edge of THRESx for IN6", reg_addr); 
    }
    if(0==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:0 RW no interrupt generation for IN5", reg_addr); 
    }
    if(1==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:1 RW interrupt generation on rising edge above THRESx for IN5", reg_addr); 
    }
    if(2==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:2 RW interrupt generation on falling edge below THRESx for IN5", reg_addr); 
    }
    if(3==(0x3 & (reg_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:3 RW interrupt generation on falling and rising edge of THRESx for IN5", reg_addr); 
    }
    return res;
}

bool parse_tic12400_reg (uint8_t reg_addr, FILE *out_file_prt) {
    bool res = false;
    uint32_t reg_val = tic12400RegMap[reg_addr].reg_val;
    fprintf (out_file_prt, "\n\nReg: [%s] reg_addr: 0x%02x val: 0x%04x 0b_%s", tic12400RegMap[reg_addr].reg_name, reg_addr, reg_val, utoa_bin32 (reg_val));
    switch ( reg_addr ) {
        case 37: 
            proc_reg_cnt++;
            res = parse_tic12400_int_en_cfg1_register_37 (reg_val, out_file_prt, reg_addr);
            break;
        case 38: 
            proc_reg_cnt++;
            res = parse_tic12400_int_en_cfg2_register_38 (reg_val, out_file_prt, reg_addr);
            break;
        case 39: 
            proc_reg_cnt++;
            res = parse_tic12400_int_en_cfg3_register_39 (reg_val, out_file_prt, reg_addr);
            break;
        case 40: 
            proc_reg_cnt++;
            res = parse_tic12400_int_en_cfg4_register_40 (reg_val, out_file_prt, reg_addr);
            break;
        default:
            fprintf (out_file_prt, "\n Lack of parser for reg %s addr 0x%x val 0x%x", tic12400_reg_2_name[reg_addr], reg_addr, reg_val);
        break;
    }
    return res;
}

 // Support: aabzele@gmail.com Alexander Barunin