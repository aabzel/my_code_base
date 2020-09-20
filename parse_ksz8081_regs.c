#include "parse_ksz8081_regs.h"

#include "convert.h"
#include "parse_regs.h"
#include "str_ops.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

regKSZ8081_t ksz8081RegMap[KSZ8081_REG_NUM];
static uint16_t proc_reg_cnt = 0;

char *ksz8081_reg_2_name[] = {
    /*0  0h*/ "Basic Control",
    /*1  1h*/ "Basic Status",
    /*2  2h*/ "PHY Identifier 1",
    /*3  3h*/ "PHY Identifier 2",
    /*4  4h*/ "Auto-Negotiation Advertisement",
    /*5  5h*/ "Auto-Negotiation Link Partner Ability",
    /*6  6h*/ "Auto-Negotiation Expansion",
    /*7  7h*/ "Auto-Negotiation Next Page",
    /*8  8h*/ "Link Partner Next Page Ability",
    /*9  9h*/ "Reserved",
    /*10 Ah*/ "Reserved",
    /*11 Bh*/ "Reserved",
    /*12 Ch*/ "Reserved",
    /*13 Dh*/ "Reserved",
    /*14 Eh*/ "Reserved",
    /*15 Fh*/ "Reserved",
    /*16 10h*/ "Digital Reserved Control",
    /*17 11h*/ "AFE Control 1",
    /*18 12h*/ "Reserved",
    /*19 13h*/ "Reserved",
    /*20 14h*/ "Reserved",
    /*21 15h*/ "RXER Counter",
    /*22 16h*/ "Operation Mode Strap Override",
    /*23 17h*/ "Operation Mode Strap Status",
    /*24 18h*/ "Expanded Control",
    /*25 19h*/ "Reserved",
    /*26 1Ah*/ "Reserved",
    /*27 1Bh*/ "Interrupt Control/Status",
    /*28 1Ch*/ "Reserved",
    /*29 1Dh*/ "LinkMD Control/Status",
    /*30 1Eh*/ "PHY Control 1",
    /*31 1Fh*/ "PHY Control 2"};
// 19 registers

static bool parse_basic_control_register_0h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_basic_status_register_1h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_phy_identifier_1_register_2h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_phy_identifier_2_register_3h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_auto_negotiation_advertisement_register_4h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_auto_negotiation_link_partner_ability_register_5h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_auto_negotiation_expansion_register_6h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_auto_negotiation_next_page_register_7h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_link_partner_next_page_ability_register_8h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_digital_reserved_control_register_10h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_afe_control_1_register_11h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_rxer_counter_register_15h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_operation_mode_strap_override_register_16h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_operation_mode_strap_status_register_17h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_expanded_control_register_18h (uint16_t reg_val, FILE *out_file_prt);
static bool parse_interrupt_control_status_register_1bh (uint16_t reg_val, FILE *out_file_prt);

static bool parse_linkmd_control_status_register_1dh (uint16_t reg_val, FILE *out_file_prt) {
    uint8_t Cable_Fault_Counter = 0x00FF & reg_val;
    fprintf (out_file_prt, "\n bit 8:0 RO Distance to fault [%u] %f m", Cable_Fault_Counter,
             0.38f * ((float_t)Cable_Fault_Counter));
    fprintf (out_file_prt, "\n");
}

static bool parse_phy_control_1_register_1eh (uint16_t reg_val, FILE *out_file_prt);
static bool parse_phy_control_2_register_1fh (uint16_t reg_val, FILE *out_file_prt);

static bool load_ksz8081_reg (uint8_t reg_addr, uint16_t reg_val) {
    bool res = false;
    ksz8081RegMap[reg_addr].reg_val = reg_val;
    strcpy (ksz8081RegMap[reg_addr].reg_name, ksz8081_reg_2_name[reg_addr]);
    return res;
}

static bool parse_ksz8081_reg (uint8_t reg_addr, FILE *out_file_prt) {
    bool res = false;
    uint16_t reg16_val = ksz8081RegMap[reg_addr].reg_val;
    fprintf (out_file_prt, "\n\nreg %40s addr 0x%02x val 0x%04x 0b_%s", ksz8081_reg_2_name[reg_addr], reg_addr,
             reg16_val, utoa_bin16 (reg16_val));
    switch (reg_addr) {
    case 0:
        proc_reg_cnt++;
        break;
    case 1:
        proc_reg_cnt++;
        break;

    case 2:
        proc_reg_cnt++;
        break;

    case 3:
        proc_reg_cnt++;
        break;
    case 4:
        proc_reg_cnt++;
        break;
    case 5:
        proc_reg_cnt++;
        break;

    case 6:
        proc_reg_cnt++;
        break;
    case 7:
        proc_reg_cnt++;
        break;

    case 8:
        proc_reg_cnt++;
        break;
    case 9:
        proc_reg_cnt++;
        break;

    case 10:
        proc_reg_cnt++;
        break;

    case 11:
        proc_reg_cnt++;
        break;

    case 12:
        proc_reg_cnt++;
        break;
    case 13:
        proc_reg_cnt++;
        break;
    case 14:
        proc_reg_cnt++;
        break;

    case 15:

        proc_reg_cnt++;
        break;
    case 16:
        proc_reg_cnt++;
        break;

    case 17:
        proc_reg_cnt++;
        break;
    case 18:
        proc_reg_cnt++;
        break;
    case 19:
        proc_reg_cnt++;
        break;
    case 20:
        proc_reg_cnt++;
        break;
    case 21:
        break;
    case 22:
        break;
    case 23:
        break;
    case 24:
        break;
    case 25:
        proc_reg_cnt++;
        break;
    case 26:
        proc_reg_cnt++;
        break;
    case 28:
        proc_reg_cnt++;
        break;
    case 29:
        res = parse_linkmd_control_status_register_1dh (reg16_val, out_file_prt);
        proc_reg_cnt++;
        break;
    case 30:
        proc_reg_cnt++;
        break;
    case 31:
        proc_reg_cnt++;
        break;
    default:
#if DPLOY_LACK
        fprintf (out_file_prt, "\n Lack of parser for reg %s addr 0x%x val 0x%x", ksz8081_reg_2_name[reg_addr],
                 reg_addr, reg16_val);
#endif
        break;
    }
    return res;
}

bool parse_ksz8081_regs_file (char *in_file_name, char *out_file_name) {
    printf ("\n%s()\n", __FUNCTION__);
    char curFileStr[500];
    bool res = false;
    FILE *inFilePrt = NULL;
    printf ("\n>In file: [%s]", in_file_name);
    inFilePrt = fopen (in_file_name, "r");
    if (inFilePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof (curFileStr), inFilePrt)) {

#if DEBUG_IN_FILE_STR
            printf ("\n>[%s]", curFileStr);
#endif
            if ((REG_ADDR_LEN + REG_VAL16_LEN) < strlen (curFileStr)) {
                uint8_t reg8bitAddr;
                uint16_t reg16_bit_val;
                res = parse_8bit_reg_addr (curFileStr, strlen (curFileStr), &reg8bitAddr);
                if (true == res) {
                    res = try_canch_hex_uint16 (curFileStr, strlen (curFileStr), &reg16_bit_val);
                    if (true == res) {
                        load_ksz8081_reg (reg8bitAddr, reg16_bit_val);
                    } else {
                        printf ("\n Unable to parse 16 bit reg val in [%s]", curFileStr);
                    }
                } else {
                    printf ("\n Unable to parse 8 bit reg addr in [%s]", curFileStr);
                }
            }
#if DEBUG_IN_FILE_STR
            printf ("\n[%x] [%x]", reg_addr, reg_val);
#endif
            line++;
        }
        fclose (inFilePrt);
        res = true;
    } else {
        printf ("\nUnable to open file [%s]", in_file_name);
    }

    FILE *out_file_prt = NULL;
    out_file_prt = fopen (out_file_name, "w");
    if (out_file_prt) {
        if (true == res) {
            uint8_t reg_8bit_addr;
            for (reg_8bit_addr = 0; reg_8bit_addr <= 31; reg_8bit_addr++) {
                parse_ksz8081_reg (reg_8bit_addr, out_file_prt);
            }

            printf ("\n processed %u/31 registers %f%% remain %u registers", proc_reg_cnt,
                    cacl_percent ((float)proc_reg_cnt, 31.0), 31 - proc_reg_cnt);
            printf ("\n processed %u/496 bits %f%%", proc_reg_cnt * 16,
                    cacl_percent ((float)proc_reg_cnt * 16.0, 31.0 * 16.0));

            fprintf (out_file_prt, "\n\n Support: aabzele@gmail.com Alexander Barunin");
            fclose (out_file_prt);
        }
    }

    return res;
}
