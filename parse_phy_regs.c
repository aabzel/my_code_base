#include "parse_phy_regs.h"

#include "str_ops.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

bool parse_phy_regs_file (char *inFileName, char *outFileName) {
    (void) *outFileName;
    char curFileStr [500];
    bool res = false;
    FILE *inFilePrt = NULL;
    FILE *outFilePrt = NULL;
    inFilePrt = fopen (inFileName, "r");
    outFilePrt = fopen (outFileName, "w");
    if (inFilePrt && outFilePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof(curFileStr), inFilePrt)) {
            unsigned int regAddr;
            unsigned int regVal;
            //printf ("\n>[%s]", curFileStr);
            sscanf (curFileStr, "%x %x", (unsigned int *) &regAddr, (unsigned int *) &regVal);
            parse_reg (regAddr, regVal, outFilePrt);
            //printf ("\n[%x] [%x]", regAddr, regVal);
            line++;
        }
        fclose (inFilePrt);
        fclose (outFilePrt);
        res = true;
    }
    return res;

}

bool parse_reg (uint8_t regAddr, uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regAddr) {
        case 0:
            fprintf (outFilePrt, "\nBasic control register [0h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_basic_control_register (regVal, outFilePrt);
            break;
        case 1:
            fprintf (outFilePrt, "\nBasic status register [1h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_basic_status_register (regVal, outFilePrt);
            break;
        case 2:
            fprintf (outFilePrt, "\nPHY identifier register 1 [2h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_phy_identifier_1_register (regVal, outFilePrt);
            break;
        case 3:
            fprintf (outFilePrt, "\nPHY identifier register 2 [3h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_phy_identifier_2_register (regVal, outFilePrt);
            break;
        case 15:
            fprintf (outFilePrt, "\nExtended status register [15] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_extended_status_register (regVal, outFilePrt);
            break;
        case 16:
            fprintf (outFilePrt, "\nPHY identifier register 3 [16] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_phy_identifier_3_register (regVal, outFilePrt);
            break;
        case 17:
            fprintf (outFilePrt, "\nExtended control register [17] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_extended_control_register (regVal, outFilePrt);
            break;
        case 18:
            fprintf (outFilePrt, "\nConfiguration register 1 [18] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_configuration_register_1 (regVal, outFilePrt);
            break;

        case 19:
            fprintf (outFilePrt, "\nConfiguration register 2 [19] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_configuration_register_2 (regVal, outFilePrt);
            break;
        case 20:
            fprintf (outFilePrt, "\nSymbol error counter register [20] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_symbol_error_counter_register (regVal, outFilePrt);
            break;
        case 21:
            fprintf (outFilePrt, "\nInterrupt source register [21] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_interrupt_source_register (regVal, outFilePrt);
            break;
        case 22:
            fprintf (outFilePrt, "\nInterrupt enable register [22] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_interrupt_enable_register (regVal, outFilePrt);
            break;
        case 23:
            fprintf (outFilePrt, "\nCommunication status register [23] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_communication_status_register (regVal, outFilePrt);
            break;
        case 24:
            fprintf (outFilePrt, "\nGeneral status register [24] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_general_status_register (regVal, outFilePrt);
            break;
        case 25:
            fprintf (outFilePrt, "\nExternal status register [25] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_external_status_register (regVal, outFilePrt);
            break;
        case 26:
            fprintf (outFilePrt, "\nLink-fail counter register[26] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_link_fail_counter_register (regVal, outFilePrt);
            break;
        case 27:
            fprintf (outFilePrt, "\nCommon configuration register[27] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_common_configuration_register (regVal, outFilePrt);
            break;
        case 28:
            fprintf (outFilePrt, "\nConfiguration register 3[28] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            parse_configuration_register_3 (regVal, outFilePrt);
            break;
        default:
            break;
    }
    return res;
}

#define LOOPBACK (1<<14)

bool parse_basic_control_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & RESET_BIT_15) {
        fprintf (outFilePrt, "\n bit 15: PHY reset");
    } else {
        printf ("\n bit 15: normal operation");
    }
    if (regVal & LOOPBACK_14) {
        fprintf (outFilePrt, "\n bit 14: PHY reset");
    } else {
        fprintf (outFilePrt, "\n bit 14: normal operation");
    }

    if (regVal & SPEED_SELECT_13) {
        fprintf (outFilePrt, "\n bit 13: 100 Mbit/s if SPEED_SELECT (MSB) = 0 reserved if SPEED_SELECT (MSB) = 1");
    } else {
        fprintf (outFilePrt, "\n bit 13: 10 Mbit/s if SPEED_SELECT (MSB) = 0 1000 Mbit/s if SPEED_SELECT (MSB) = 1");
    }

    if (regVal & AUTONEG_EN_12) {
        fprintf (outFilePrt, "\n bit 12: Error");
    } else {
        fprintf (outFilePrt, "\n bit 12: Auto negotiation not supported; always 0; a write access is ignored ");
    }

    if (regVal & POWER_DOWN_11) {
        fprintf (
            outFilePrt,
            "\n bit 11: power down and switch to Standby mode (provided ISOLATE = 0; ignored if ISOLATE = 1 and CONTROL_ERR interrupt generated) ");
    } else {
        fprintf (
            outFilePrt,
            "\n bit 11: normal operation (clearing this bit automatically triggers a transition to Normal mode, provided control bits POWER_MODE are set to 0011 Normal mode, see Table 18) ");
    }

    if (regVal & ISOLATE_10) {
        fprintf (
            outFilePrt,
            "\n bit 10: isolate PHY from MII/RMII (provided POWER_DOWN = 0; ignored if POWER_DOWN = 1 and CONTROL_ERR interrupt generated) ");
    } else {
        fprintf (outFilePrt, "\n bit 10: normal operation ");
    }

    if (regVal & RE_AUTONEG_9) {
        fprintf (outFilePrt, "\n bit 9: Error ");
    } else {
        fprintf (outFilePrt, "\n bit 9:  Auto negotiation not supported; always 0; a write access is ignored.");
    }

    if (regVal & DUPLEX_MODE_8) {
        fprintf (outFilePrt, "\n bit 8: only full duplex supported; always 1; a write access is ignored ");
    } else {
        fprintf (outFilePrt, "\n bit 8: Error ");
    }

    if (regVal & COLLISION_TEST_7) {
        fprintf (outFilePrt, "\n bit 7: error! ");
    } else {
        fprintf (outFilePrt, "\n bit 7: COL signal test not supported; always 0; a write access is ignored ");
    }

    if (regVal & SPEED_SELECT_6) {
        fprintf (outFilePrt, "\n bit 6: 1000 Mbit/s if SPEED_SELECT (LSB) = 0 reserved if SPEED_SELECT (LSB) = 1");
    } else {
        fprintf (outFilePrt, "\n bit 6: 10 Mbit/s if SPEED_SELECT (LSB) = 0 100 Mbit/s if SPEED_SELECT (LSB) = 1 ");
    }
    if (regVal & UNIDIRECT_EN_5) {
        fprintf (
            outFilePrt,
            "\n bit 5: enable transmit from MII regardless of whether the PHY has determined that a valid link has been established");
    } else {
        fprintf (outFilePrt, "\n bit 5: enable transmit from MII only when the PHY has determined that a valid link has been established ");
    }
    fprintf (outFilePrt, "\n");
    return res;

}

bool parse_basic_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & S100BASE_T4_15) {
        fprintf (outFilePrt, "\n bit 15: PHY able to perform 100BASE-T4 ");
    } else {
        fprintf (outFilePrt, "\n bit 15: PHY not able to perform 100BASE-T4 ");
    }
    if (regVal & S100BASE_X_FD_14) {
        fprintf (outFilePrt, "\n bit 14: PHY able to perform 100BASE-X full-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 14: PHY not able to perform 100BASE-X full-duplex");
    }
    if (regVal & S100BASE_X_HD_13) {
        fprintf (outFilePrt, "\n bit 13: PHY able to perform 100BASE-X half-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 13: PHY not able to perform 100BASE-X half-duplex ");
    }
    if (regVal & S10Mbps_FD_12) {
        fprintf (outFilePrt, "\n bit 12: PHY able to perform 10 Mbit/s full-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 12: PHY not able to perform 10 Mbit/s full-duplex ");
    }
    if (regVal & S10Mbps_HD_11) {
        fprintf (outFilePrt, "\n bit 11: PHY able to perform 10 Mbit/s half-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 11: PHY not able to perform 10 Mbit/s half-duplex ");
    }
    if (regVal & S100BASE_T2_FD_10) {
        fprintf (outFilePrt, "\n bit 10: PHY able to perform 100BASE-T2 full-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 10: PHY not able to perform 100BASE-T2 full-duplex");
    }
    if (regVal & S100BASE_T2_HD_9) {
        fprintf (outFilePrt, "\n bit 9: PHY able to perform 100BASE-T2 half-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 9: PHY not able to perform 100BASE-T2 half-duplex");
    }
    if (regVal & EXTENDED_STATUS_8) {
        fprintf (outFilePrt, "\n bit 8: extended status information in register 15h");
    } else {
        fprintf (outFilePrt, "\n bit 8: no extended status information in register 15h");
    }
    if (regVal & UNIDIRECT_ABILITY_7) {
        fprintf (
            outFilePrt,
            "\n bit 7: PHY able to transmit from MII regardless of whether the PHY has determined that a valid link has been established");
    } else {
        fprintf (outFilePrt, "\n bit 7: PHY able to transmit from MII only when the PHY has determined that a valid link has been established");
    }
    if (regVal & MF_PREAMBLE_SUPPRESSION_6) {
        fprintf (outFilePrt, "\n bit 6: PHY will accept management frames with preamble suppressed");
    } else {
        fprintf (outFilePrt, "\n bit 6: PHY will not accept management frames with preamble suppressed");
    }
    if (regVal & AUTONEG_COMPLETE_5) {
        fprintf (outFilePrt, "\n bit 5: Autonegotiation process completed");
    } else {
        fprintf (outFilePrt, "\n bit 5: Autonegotiation process not completed");
    }
    if (regVal & REMOTE_FAULT_4) {
        fprintf (outFilePrt, "\n bit 4: remote fault condition detected");
    } else {
        fprintf (outFilePrt, "\n bit 4: no remote fault condition detected");
    }
    if (regVal & AUTONEG_ABILITY_3) {
        fprintf (outFilePrt, "\n bit 3: PHY able to perform Autonegotiation");
    } else {
        fprintf (outFilePrt, "\n bit 3: PHY not able to perform Autonegotiation");
    }
    if (regVal & LINK_STATUS_2) {
        fprintf (outFilePrt, "\n bit 2: link is up");
    } else {
        fprintf (outFilePrt, "\n bit 2: link is down");
    }
    if (regVal & JABBER_DETECT_1) {
        fprintf (outFilePrt, "\n bit 1: jabber condition detected");
    } else {
        fprintf (outFilePrt, "\n bit 1: no jabber condition detected");
    }
    if (regVal & EXTENDED_CAPABILITY_0) {
        fprintf (outFilePrt, "\n bit 0: extended register capabilities");
    } else {
        fprintf (outFilePrt, "\n bit 0: basic register set capabilities only");
    }
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_phy_identifier_1_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    fprintf (outFilePrt, "\n bit 15..0: Organizationally Unique Identifier 0x%04x", regVal);
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_phy_identifier_2_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    uint8_t phyId = extract_subval_from_16bit (regVal, 15, 10);
    fprintf (outFilePrt, "\n bit 15..10: phyId 0x%02x (19 to 24 of the OUI)", phyId);
    uint8_t typeNo = extract_subval_from_16bit (regVal, 9, 4);
    fprintf (outFilePrt, "\n bit 9..4: manufacturer type number 0x%02x", typeNo);
    uint8_t revNo = extract_subval_from_16bit (regVal, 3, 0);
    fprintf (outFilePrt, "\n bit 3..0: manufacturer  revision number 0x%02x", revNo);
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_extended_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & S1000BASE_X_FD_15) {
        fprintf (outFilePrt, "\n bit 15: PHY able to perform 1000BASE-X full-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 15: PHY not able to perform 1000BASE-X full-duplex");
    }
    if (regVal & S1000BASE_X_HD_14) {
        fprintf (outFilePrt, "\n bit 14: PHY able to perform 1000BASE-X half-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 14: PHY not able to perform 1000BASE-X half-duplex ");
    }
    if (regVal & S1000BASE_T_FD_13) {
        fprintf (outFilePrt, "\n bit 13: PHY able to perform 1000BASE-T full-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 13: PHY not able to perform 1000BASE-T full-duplex");
    }
    if (regVal & S1000BASE_T_HD_12) {
        fprintf (outFilePrt, "\n bit 12: PHY able to perform 1000BASE-T half-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 12: PHY not able to perform 1000BASE-T half-duplex");
    }
    if (regVal & S100BASE_T1_7) {
        fprintf (outFilePrt, "\n bit 7: PHY able to 1-pair 100BASE-T1 100 Mbit/s");
    } else {
        fprintf (outFilePrt, "\n bit 7: PHY not able to 1-pair 100BASE-T1 100 Mbit/s");
    }
    if (regVal & S1000BASE_RTPGE_6) {
        fprintf (outFilePrt, "\n bit 6: PHY supports RTPGE");
    } else {
        fprintf (outFilePrt, "\n bit 6: PHY not able to support RTPGE");
    }
    fprintf (outFilePrt, "\n");

    return res;
}

bool parse_extended_control_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & LINK_CONTROL_15) {
        fprintf (outFilePrt, "\n bit 15: link control enabled");
    } else {
        fprintf (outFilePrt, "\n bit 15: link control disabled");
    }
    uint16_t powerMode = extract_subval_from_16bit (regVal, 14, 11);
    res = parse_power_mode (powerMode, outFilePrt);
    if (regVal & SLAVE_JITTER_TEST_10) {
        fprintf (outFilePrt, "\n bit 10: enable Slave jittet test");
    } else {
        fprintf (outFilePrt, "\n bit 10: disable Slave jitter test");
    }
    if (regVal & TRAINING_RESTART_9) {
        fprintf (outFilePrt, "\n bit 9: forces a restart of the training phase");
    } else {
        fprintf (outFilePrt, "\n bit 9: halts the training phase");
    }
    uint16_t testMode = extract_subval_from_16bit (regVal, 8, 6);
    res = parse_test_mode (testMode, outFilePrt);

    if (regVal & CABLE_TEST_5) {
        fprintf (outFilePrt, "\n bit 5: forces TDR-based cable test");
    } else {
        fprintf (outFilePrt, "\n bit 5: stops TDR-based cable test");
    }
    uint16_t loopbackMode = extract_subval_from_16bit (regVal, 4, 3);
    res = parse_loopback_mode (loopbackMode, outFilePrt);
    if (regVal & CONFIG_EN_2) {
        fprintf (outFilePrt, "\n bit 2: configuration register access enabled");
    } else {
        fprintf (outFilePrt, "\n bit 2: configuration register access disabled");
    }

    return res;
}

bool parse_power_mode (uint8_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regVal) {
        case 0:
            fprintf (outFilePrt, "\n bit 14..11: operating mode: no change");
            break;
        case 3:
            fprintf (outFilePrt, "\n bit 14..11: operating mode: Normal mode (command)");
            break;
        case 9:
            fprintf (outFilePrt, "\n bit 14..11: Silent mode (read only)");
            break;
        case 10:
            fprintf (outFilePrt, "\n bit 14..11: Sleep mode (read only)");
            break;
        case 11:
            fprintf (outFilePrt, "\n bit 14..11: Sleep Request mode (command)");
            break;
        case 12:
            fprintf (outFilePrt, "\n bit 14..11: Standby mode (command)");
            break;
        default:
            fprintf (outFilePrt, "\n bit 14..11: Error");
            break;
    }
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_test_mode (uint8_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regVal) {
        case 0:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection: no test mode");
            break;
        case 1:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection 100BASE-T1 test mode 1");
            break;
        case 2:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection 100BASE-T1 test mode 2 ");
            break;
        case 3:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection test mode 3");
            break;
        case 4:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection 100BASE-T1 test mode 4");
            break;
        case 5:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection 100BASE-T1 test mode 5");
            break;
        case 6:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection scrambler and descrambler bypassed");
            break;
        case 7:
            fprintf (outFilePrt, "\n bit 8..6: R/W test mode selection reserved");
            break;
        default:
            fprintf (outFilePrt, "\n bit 8..6: R/W Error");
            break;
    }
    return res;
}

bool parse_loopback_mode (uint8_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regVal) {
        case 0:
            fprintf (outFilePrt, "\n bit 4..3: R/W internal loopback");
            break;
        case 1:
            fprintf (outFilePrt, "\n bit 4..3: R/W external loopback");
            break;
        case 2:
            fprintf (outFilePrt, "\n bit 4..3: R/W external loopback");
            break;
        case 3:
            fprintf (outFilePrt, "\n bit 4..3: R/W remote loopback");
            break;

        default:
            fprintf (outFilePrt, "\n bit 4..3: R/W Error");
            break;
    }
    return res;
}

bool parse_configuration_register_2 (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    uint16_t phyAddr = extract_subval_from_16bit (regVal, 15, 11);
    fprintf (outFilePrt, "\n bit 15..11: r 5bit PHY address: [%d]", phyAddr);
    if (regVal & JUMBO_ENABLE_2) {
        fprintf (outFilePrt, "\n bit 2: rw packets up to 16 kB supported");
    } else {
        fprintf (outFilePrt, "\n bit 2: rw packets up to 4 kB supported");
    }
    return res;
}

bool parse_communication_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res;
    if (regVal & LINK_UP_15) {
        fprintf (outFilePrt, "\n bit 15: r link OK");
    } else {
        fprintf (outFilePrt, "\n bit 15: r link failure");
    }
    if (regVal & LOC_RCVR_STATUS_12) {
        fprintf (outFilePrt, "\n bit 12: r local receiver OK");
    } else {
        fprintf (outFilePrt, "\n bit 12: r local receiver not OK");
    }
    if (regVal & REM_RCVR_STATUS_11) {
        fprintf (outFilePrt, "\n bit 11: r remote receiver OK");
    } else {
        fprintf (outFilePrt, "\n bit 11: r remote receiver not OK");
    }
    if (regVal & SCR_LOCKED_10) {
        fprintf (outFilePrt, "\n bit 10: r descrambler locked");
    } else {
        fprintf (outFilePrt, "\n bit 10: r descrambler unlocked");
    }
    if (regVal & SSD_ERR_9) {
        fprintf (outFilePrt, "\n bit 9: r SSD error detected");
    } else {
        fprintf (outFilePrt, "\n bit 9: r no SSD error detected");
    }
    if (regVal & ESD_ERR_8) {
        fprintf (outFilePrt, "\n bit 8: r ESD error detected");
    } else {
        fprintf (outFilePrt, "\n bit 8: r no ESD error detected");
    }
    uint16_t sqi = extract_subval_from_16bit (regVal, 7, 5);
    res = parse_sqi (sqi, outFilePrt);
    if (regVal & RECEIVE_ERR_4) {
        fprintf (outFilePrt, "\n bit 4: r receive error detected since register last read");
    } else {
        fprintf (outFilePrt, "\n bit 4: r no receive error detected");
    }
    if (regVal & TRANSMIT_ERR_3) {
        fprintf (outFilePrt, "\n bit 3: r transmit error detected since register last read");
    } else {
        fprintf (outFilePrt, "\n bit 3: r no transmit error detected");
    }
    uint16_t phyState = extract_subval_from_16bit (regVal, 2, 0);
    res = parse_phy_state (phyState, outFilePrt);
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_configuration_register_3 (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_phy_identifier_3_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_configuration_register_1 (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_symbol_error_counter_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_interrupt_source_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_interrupt_enable_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_general_status_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_external_status_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_link_fail_counter_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_common_configuration_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\n");
    return true;
}

bool parse_phy_state (uint8_t phyState, FILE *outFilePrt) {
    bool res = false;
    switch (phyState) {
        case 0:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Idle");
            break;
        case 1:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Initializing");
            break;
        case 2:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Configured");
            break;
        case 3:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Offline");
            break;
        case 4:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Active");
            break;
        case 5:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Isolate");
            break;
        case 6:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Cable test");
            break;
        case 7:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Test mode");
            break;
        default:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Test mode");
            break;
    }
    return res;
}

bool parse_sqi (uint8_t sqi, FILE *outFilePrt) {
    bool res = false;
    switch (sqi) {
        case 0:
            fprintf (outFilePrt, "\n bit 7..5: r worse than class A SQI (unstable link)");
            break;
        case 1:
            fprintf (outFilePrt, "\n bit 7..5: r class A SQI (unstable link)");
            break;
        case 2:
            fprintf (outFilePrt, "\n bit 7..5: r class B SQI (unstable link)");
            break;
        case 3:
            fprintf (outFilePrt, "\n bit 7..5: r class C SQI (good link)");
            break;
        case 4:
            fprintf (outFilePrt, "\n bit 7..5: r class D SQI (good link; bit error rate < 1e-10)");
            break;
        case 5:
            fprintf (outFilePrt, "\n bit 7..5: r class E SQI (good link)");
            break;
        case 6:
            fprintf (outFilePrt, "\n bit 7..5: r class F SQI (very good link)");
            break;
        case 7:
            fprintf (outFilePrt, "\n bit 7..5: r class G SQI (very good link)");
            break;
        default:
            fprintf (outFilePrt, "\n bit 2..0: r PHY Test mode");
            break;
    }
    return res;
}

