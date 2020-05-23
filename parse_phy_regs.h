#ifndef PARSE_PHY_REGS_H
#define PARSE_PHY_REGS_H

#include "custom_type.h"

#include <stdio.h>

#define RESET_BIT_15 (1<<15)
#define LOOPBACK_14 (1<<14)
#define SPEED_SELECT_13 (1<<13)
#define AUTONEG_EN_12 (1<<12)
#define POWER_DOWN_11 (1<<11)
#define ISOLATE_10 (1<<10)
#define RE_AUTONEG_9 (1<<9)
#define DUPLEX_MODE_8 (1<<8)
#define COLLISION_TEST_7 (1<<7)
#define SPEED_SELECT_6  (1<<6)
#define UNIDIRECT_EN_5 (1<<5)

//Basic status register
#define S100BASE_T4_15 (1<<15)
#define S100BASE_X_FD_14  (1<<14)
#define S100BASE_X_HD_13  (1<<13)
#define S10Mbps_FD_12  (1<<12)
#define S10Mbps_HD_11  (1<<11)
#define S100BASE_T2_FD_10  (1<<10)
#define S100BASE_T2_HD_9  (1<<9)
#define EXTENDED_STATUS_8  (1<<8)
#define UNIDIRECT_ABILITY_7  (1<<7)
#define MF_PREAMBLE_SUPPRESSION_6  (1<<6)
#define AUTONEG_COMPLETE_5  (1<<5)
#define REMOTE_FAULT_4  (1<<4)
#define AUTONEG_ABILITY_3  (1<<3)
#define LINK_STATUS_2  (1<<2)
#define JABBER_DETECT_1  (1<<1)
#define EXTENDED_CAPABILITY_0  (1<<0)

#define S1000BASE_X_FD_15  (1<<15)
#define S1000BASE_X_HD_14  (1<<14)
#define S1000BASE_T_FD_13  (1<<13)
#define S1000BASE_T_HD_12  (1<<12)
#define S100BASE_T1_7  (1<<7)
#define S1000BASE_RTPGE_6 (1<<6)

#define LINK_CONTROL_15 (1<<15) //RW
#define SLAVE_JITTER_TEST_10 (1<<10)//RW
#define TRAINING_RESTART_9 (1<<9) //rw
#define CABLE_TEST_5 (1<<5) //rw
#define CONFIG_EN_2 (1<<2) //rw

#define JUMBO_ENABLE_2 (1<<2)

#define LINK_UP_15 (1<<15)

#define AUTO_OP_15 (1<<15)
#define LDO_MODE_11 (1<<11)
#define CLK_DRIVER_10 (1<<10)
#define CLK_HOLD_9 (1<<9)
#define CONFIG_WAKE_6 (1<<6)
#define CONFIG_INH_5  (1<<5)
#define FORCE_SLEEP_1 (1<<1)

#define LOC_RCVR_STATUS_12  (1<<12)
#define REM_RCVR_STATUS_11  (1<<11)
#define SCR_LOCKED_10  (1<<10)
#define SSD_ERR_9  (1<<9)
#define ESD_ERR_8  (1<<8)
#define RECEIVE_ERR_4  (1<<4)
#define TRANSMIT_ERR_3  (1<<3)

bool parse_phy_regs_file (char *inFileName, char *outFileName);
bool parse_reg (uint8_t regAddr, uint16_t regVal, FILE *outFilePrt);

bool parse_basic_control_register (uint16_t regVal, FILE *outFilePrt);
bool parse_basic_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_phy_identifier_1_register (uint16_t regVal, FILE *outFilePrt);
bool parse_phy_identifier_2_register (uint16_t regVal, FILE *outFilePrt);
bool parse_extended_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_phy_identifier_3_register (uint16_t regVal, FILE *outFilePrt);
bool parse_extended_control_register (uint16_t regVal, FILE *outFilePrt);
bool parse_configuration_register_1 (uint16_t regVal, FILE *outFilePrt);
bool parse_configuration_register_2 (uint16_t regVal, FILE *outFilePrt);
bool parse_symbol_error_counter_register (uint16_t regVal, FILE *outFilePrt);
bool parse_interrupt_source_register (uint16_t regVal, FILE *outFilePrt);
bool parse_interrupt_enable_register (uint16_t regVal, FILE *outFilePrt);
bool parse_communication_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_general_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_external_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_link_fail_counter_register (uint16_t regVal, FILE *outFilePrt);
bool parse_common_configuration_register (uint16_t regVal, FILE *outFilePrt);
bool parse_configuration_register_3 (uint16_t regVal, FILE *outFilePrt);

bool parse_power_mode (uint8_t regVal, FILE *outFilePrt);
bool parse_loopback_mode (uint8_t regVal, FILE *outFilePrt);
bool parse_test_mode (uint8_t regVal, FILE *outFilePrt);
bool parse_phy_state (uint8_t phyState, FILE *outFilePrt);
bool parse_sqi (uint8_t sqi, FILE *outFilePrt);

#endif /* PARSE_PHY_REGS_H */
