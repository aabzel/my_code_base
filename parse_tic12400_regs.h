#ifndef PARSE_TIC124h00_REGS_H
#define PARSE_TIC12400_REGS_H

#include "custom_type.h"
#include "tic12400_bits_offsets.h"

#include <stdio.h>

#define REG_ADDR_LEN (strlen("0x21"))
#define REG_VAL_LEN (strlen("0x87654321"))

typedef struct xTic12400Reg_t {
    uint8_t reg8BitAddr;
    uint32_t reg24BitVal;
    char *regName;
} Tic12400Reg_t;

typedef enum {
    PULL_UP = 0,
    PULL_DOWN = 1
} pullMode_t;

typedef struct xTic12400Channel_t {
    uint8_t channel;
    bool state;
    float wettingCurrent;
    float threshold;
    uint8_t pullState;
    uint16_t valueThreshold;
    uint16_t valueVoltage;
    float comparatorThreshold;
    char interruptGeneration [10];
    char interruptMode;
    char inputADCLevel[100];
    char pullMode;
    char inMode [10];
} Tic12400Channel_t;

extern Tic12400Channel_t tic12400channelList [CHANNEL_AMOUNT];
extern Tic12400Reg_t tic12400RegMap [REG_AMOUNT];
extern uint8_t procRegCnd;

bool parse_tic12400_regs_file (char *inFileName, char *outFileName);
bool parse_tic12400_reg (uint8_t regAddr, FILE *outFilePrt);
bool load_tic12400_reg (uint8_t regAddr, uint32_t regVal);

bool parse_in_a_code (uint8_t ina_code, FILE *outFilePrt, uint8_t oldBit, uint8_t littleBit, uint8_t channel);
bool parse_tic12400_in_stat_adc0_register_06h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_in_stat_adc1_register_07h (uint32_t regVal, FILE *outFilePrt);

bool get_adc_channels (uint8_t regAddr, uint8_t *lowChannel, uint8_t *hiChannel);

bool parse_tic12400_device_id_register_01h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_interrupt_status_register_02h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_crc_register_03h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_in_stat_misc_register_04h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_in_stat_comp_register_05h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_in_en_register_1bh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_ana_stat12_register_16h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_config_register_1ah (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_cs_select_register_1ch (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_wc_cfg0_register_1dh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_wc_cfg1_register_1eh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_ccp_cfg0_register_1fh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_ccp_cfg1_register_20h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_comp_register_21h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_int_en_comp1_register_22h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_int_en_comp2_register_23h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg0_register_29h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg1_register_2ah (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg2_register_2bh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg3_register_2ch (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_thres_cfg4_register_2dh (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_mode_register_32h (uint32_t regVal, FILE *outFilePrt);

bool parse_tic12400_ana_statX_register_XXh (uint32_t regVal, FILE *outFilePrt, uint8_t regAddr);

bool parse_poll_time_val (uint8_t pollTime, FILE *outFilePrt);
bool parse_poll_act_time_val (uint8_t pollTime, FILE *outFilePrt);
bool parse_tic12400_in_en_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_mode_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_n_stat_comp_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_ccp_cfg1_bit (uint32_t regVal, uint8_t bitNum, FILE *outFilePrt);
bool parse_tic12400_vs0_stat (uint8_t val, FILE *outFilePrt);
bool parse_tic12400_vs1_stat (uint8_t val, FILE *outFilePrt);
float calc_vs_voltage (void);
bool parse_interrupt_en_comp_mode (uint8_t reg_val, FILE *outFilePrt, uint8_t oldBit, uint8_t littleBit, uint8_t channel);
float interpretation_comparator_threshold_code (uint8_t trCode);
bool parse_comparator_threshold (uint8_t reg_val, FILE *outFilePrt, uint8_t oldBit, uint8_t littleBit);
bool parse_wetting_current (uint8_t reg_val, FILE *outFilePrt, uint8_t oldBit, uint8_t littleBit);
float num2wett_current (uint8_t wcCode);
char interpret_int_code (uint8_t intCode);
bool write_channel_table (FILE *outFilePrt);

bool parse_tic12400_in_stat_matrix0_register_08h (uint32_t regVal, FILE *outFilePrt);
bool parse_tic12400_in_stat_matrix1_register_09h (uint32_t regVal, FILE *outFilePrt);

#endif /* PARSE_TIC12400_REGS_H */