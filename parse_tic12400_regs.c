#include "parse_tic12400_regs.h"
#include "tic12400_bits_offsets.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

bool parse_tic12400_regs_file (char *inFileName, char *outFileName) {
    char curFileStr [500];
    bool res = false;
    FILE *inFilePrt = NULL;
    FILE *outFilePrt = NULL;
    printf ("\n>In file: [%s]", inFileName);
    inFilePrt = fopen (inFileName, "r");
    outFilePrt = fopen (outFileName, "w");
    if (inFilePrt && outFilePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof(curFileStr), inFilePrt)) {
            unsigned int regAddr;
            unsigned int regVal;
            printf ("\n>[%s]", curFileStr);
            sscanf (curFileStr, "%x %x", (unsigned int *) &regAddr, (unsigned int *) &regVal);
            parse_tic12400_reg (regAddr, regVal, outFilePrt);
            printf ("\n[%x] [%x]", regAddr, regVal);
            line++;
        }
        fclose (inFilePrt);
        fclose (outFilePrt);
        res = true;
    }
    return res;
}

char *tic12400_reg_2_name [51] =
    { "REG_RESERVED_00H", //0
        "REG_DEVICE_ID",
        "REG_INT_STAT",
        "REG_CRC",
        "REG_IN_STAT_MISC",
        "REG_IN_STAT_COMP",
        "REG_IN_STAT_ADC0",
        "REG_IN_STAT_ADC1",
        "REG_IN_STAT_MATRIX0",
        "REG_IN_STAT_MATRIX1",
        "REG_ANA_STAT0", //10
        "REG_ANA_STAT1",
        "REG_ANA_STAT2",
        "REG_ANA_STAT3",
        "REG_ANA_STAT4",
        "REG_ANA_STAT5",
        "REG_ANA_STAT6",
        "REG_ANA_STAT7",
        "REG_ANA_STAT8",
        "REG_ANA_STAT9",
        "REG_ANA_STAT10", //20
        "REG_ANA_STAT11",
        "REG_ANA_STAT12",
        "REG_RESERVED_17H",
        "REG_RESERVED_18H",
        "REG_RESERVED_19H",
        "REG_CONFIG",
        "REG_IN_EN",
        "REG_CS_SELECT",
        "REG_WC_CFG0",
        "REG_WC_CFG1", //30
        "REG_CCP_CFG0",
        "REG_CCP_CFG1",
        "REG_THRES_COMP",
        "REG_INT_EN_COMP1",
        "REG_INT_EN_COMP2",
        "REG_INT_EN_CFG0",
        "REG_INT_EN_CFG1",
        "REG_INT_EN_CFG2",
        "REG_INT_EN_CFG3",
        "REG_INT_EN_CFG4", //40
        "REG_THRES_CFG0",
        "REG_THRES_CFG1",
        "REG_THRES_CFG2",
        "REG_THRES_CFG3",
        "REG_THRES_CFG4",
        "REG_THRESMAP_CFG0",
        "REG_THRESMAP_CFG1",
        "REG_THRESMAP_CFG2",
        "REG_MATRIX",
        "REG_MODE" //50
        };

bool parse_tic12400_reg (uint8_t regAddr, uint32_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regAddr) {
        case REG_CONFIG:
            fprintf (outFilePrt, "\nreg %s addr 0x%x val 0x%x", tic12400_reg_2_name [regAddr], regAddr, regVal);
            res = parse_tic12400_config_register (regAddr, outFilePrt);
            break;
        default:
#if DPLOY_LACK
            fprintf (outFilePrt, "\n Lack of parser for reg %s addr 0x%x val 0x%x", tic12400_reg_2_name [regAddr], regAddr, regVal);
#endif
            break;
    }
    return res;
}

bool parse_tic12400_config_register (uint32_t regVal, FILE *outFilePrt) {
    bool res = true;
    if (regVal & RESET_0) {
        fprintf (outFilePrt, "\n  bit 0: Trigger software reset of the device.");
    } else {
        fprintf (outFilePrt, "\n  bit 0: No reset");
    }

    if (regVal & VS_RATIO_23) {
        fprintf (outFilePrt, "\n  bit 23: RW Use voltage divider factor of 10 for the VS measurement");
    } else {
        fprintf (outFilePrt, "\n  bit 23: RW Use voltage divider factor of 3 for the VS measurement");
    }

    if (regVal & ADC_DIAG_T_22) {
        fprintf (outFilePrt, "\n  bit 22: RW Enable ADC self-diagnostic feature");
    } else {
        fprintf (outFilePrt, "\n  bit 22: RW Disable ADC self-diagnostic feature");
    }


    if (regVal & VS_MEAS_EN_17) {
        fprintf (outFilePrt, "\n  bit 17: Enable VS measurement at the end of every polling cycle");
    } else {
        fprintf (outFilePrt, "\n  bit 17: Disable VS measurement at the end of every polling cycle");
    }

    if (regVal & TW_CUR_DIS_CSI_16) {
        fprintf (
            outFilePrt,
            "\n  bit 16: Disable wetting current reduction (to 2 mA) for 10mA and 15mA settings upon TW event for all inputs enabled with CSI.");
    } else {
        fprintf (
            outFilePrt,
            "\n  bit 16: Enable wetting current reduction (to 2 mA) for 10mA and 15mA settings upon TW event for all inputs enabled with CSI");
    }

    if (regVal & TW_CUR_DIS_CSO_13) {
        fprintf (
            outFilePrt,
            "\n  bit 13: RW  Disable wetting current reduction (to 2mA) for 10mA and 15mA settings upon TW event for all inputs enabled with CSO");
    } else {
        fprintf (
            outFilePrt,
            "\n  bit 13: RW  Enable wetting current reduction (to 2mA) for 10mA and 15mA settings upon TW event for all inputs enabled with CSO");
    }

    if (regVal & INT_CONFIG_12) {
        fprintf (outFilePrt, "\n  bit 12: RW  INT pin assertion scheme set to dynamic");
    } else {
        fprintf (outFilePrt, "\n  bit 12: RW  INT pin assertion scheme set to static");
    }

    if (regVal & TRIGGER_11) {
        fprintf (outFilePrt, "\n  bit 11: RW Trigger TIC12400-Q1 normal operation");
    } else {
        fprintf (outFilePrt, "\n  bit 11: RW Stop TIC12400-Q1 from normal operation");
    }

    if (regVal & POLL_EN_10) {
        fprintf (outFilePrt, "\n  bit 10: RW Polling enabled and the device operates in one of the polling modes");
    } else {
        fprintf (outFilePrt, "\n  bit 10: RW Polling disabled. Device operates in continuous mode");
    }

    if (regVal & CRC_T_9) {
        fprintf (outFilePrt, "\n  bit 9: RW trigger CRC calculation");
    } else {
        fprintf (outFilePrt, "\n  bit 9: RW no CRC calculation triggered");
    }

    uint8_t pollActTime = extract_subval_from_32bit (regVal, 8, 5);
    parse_poll_act_time_val (pollActTime, outFilePrt);

    uint8_t pollTime = extract_subval_from_32bit (regVal, 4, 1);
    parse_poll_time_val (pollTime, outFilePrt);
    return res;
}

bool parse_poll_act_time_val (uint8_t pollTime, FILE *outFilePrt) {
    bool res = true;
    switch (pollTime) {
        case 0x0:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 64us");
            break;
        case 0x1:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 128us");
            break;
        case 0x2:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 192us");
            break;
        case 0x3:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 256us");
            break;
        case 0x4:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 320us");
            break;
        case 0x5:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 384us");
            break;
        case 0x6:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 448us");
            break;
        case 0x7:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 512us");
            break;
        case 0x8:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 640us");
            break;
        case 0x9:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 768us");
            break;
        case 0xA:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 896us");
            break;
        case 0xB:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 1024us");
            break;
        case 0xC:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 2048us");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 8-5: Poll Act time 512us ");
            break;
    }
    return res;
}

bool parse_poll_time_val (uint8_t pollTime, FILE *outFilePrt) {
    bool res = true;
    switch (pollTime) {
        case 0x0:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 2ms");
            break;
        case 0x1:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 4ms");
            break;
        case 0x2:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 8ms");
            break;
        case 0x3:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 16ms");
            break;
        case 0x4:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 32ms");
            break;
        case 0x5:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 48ms");
            break;
        case 0x6:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 64ms");
            break;
        case 0x7:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 128ms");
            break;
        case 0x8:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 256ms");
            break;
        case 0x9:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 512ms");
            break;
        case 0xA:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 1024ms");
            break;
        case 0xB:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 2048ms");
            break;
        case 0xC:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 4096ms");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 4-1: Poll time 2ms");
            break;
    }
    return res;
}

