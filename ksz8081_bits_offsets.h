#ifndef KSZ8081_BIT_OFFSETS_H
#define KSZ8081_BIT_OFFSETS_H

 #define KSZ8081_BMCR                        0x00
 #define KSZ8081_BMSR                        0x01 /*REG Number for Basic Status*/
 #define KSZ8081_PHYID1                      0x02  /*REG Number for PHY ID 1 register*/
 #define KSZ8081_PHYID2                      0x03
 #define KSZ8081_ANAR                        0x04
 #define KSZ8081_ANLPAR                      0x05
 #define KSZ8081_ANER                        0x06
 #define KSZ8081_ANNPR                       0x07
 #define KSZ8081_ANLPNPR                     0x08
 #define KSZ8081_DRCON                       0x10
 #define KSZ8081_AFECON1                     0x11
 #define KSZ8081_RXERCTR                     0x15
 #define KSZ8081_OMSO                        0x16
 #define KSZ8081_OMSS                        0x17
 #define KSZ8081_EXCON                       0x18
 #define KSZ8081_ICSR                        0x1B
 #define KSZ8081_LINKMD                      0x1D /*Register 1Dh – LinkMD Control/Status*/
 #define KSZ8081_PHYCON1                     0x1E /*Reg 30 PHY Control 1*/
 #define KSZ8081_PHYCON2                     0x1F /*Reg 31 PHY Control 2*/



// Basic Control
#define RESET_BIT_15 (1 << 15)
#define LOOPBACK_14 (1 << 14)
#define SPEED_SELECT_13 (1 << 13)
#define AUTONEG_EN_12 (1 << 12)
#define POWER_DOWN_11 (1 << 11)
#define ISOLATE_10 (1 << 10)
#define RE_AUTONEG_9 (1 << 9)
#define DUPLEX_MODE_8 (1 << 8)
#define COLLISION_TEST_7 (1 << 7)
// Basic status register
#define S100BASE_T4_15 (1 << 15)
#define S100BASE_X_FD_14 (1 << 14)
#define S100BASE_X_HD_13 (1 << 13)
#define S10BASE_T_FD_12 (1 << 12)
#define S10BASE_T_HD_11 (1 << 11)
#define NO_PREAMBLE_6 (1 << 6)
#define AUTONEG_COMPLETE_5 (1 << 5)
#define REMOTE_FAULT_4 (1 << 4)
#define AUTONEG_ABILITY_3 (1 << 3) // TODO show in diag
#define LINK_STATUS_2 (1 << 2)
#define JABBER_DETECT_1 (1 << 1)
#define EXTENDED_CAPABILITY_0 (1 << 0)

// Register 2h - PHY Identifier 1
// Register 3h - PHY Identifier 2
// Register 4h - Auto-Negotiation Advertisement
// Register 5h - Auto-Negotiation Link Partner Ability
// Register 6h - Auto-Negotiation Expansion
// Register 7h - Auto-Negotiation Next Page
// Register 8h - Link Partner Next Page Ability
// Register 10h – Digital Reserved Control
// Register 11h – AFE Control 1
// Register 15h – RXER Counter
// Register 16h – Operation Mode Strap Override
// Register 17h - Operation Mode Strap Status
// Register 18h - Expanded Control
// Register 1Bh – Interrupt Control/Status
// Register 1Dh – LinkMD Control/Status
// Register 1Eh – PHY Control 1
// Register 1Fh – PHY Control 2


 //PHY Control 1 register
 #define KSZ8081_PHYCON1_PAUSE_EN            (1<<9)
 #define KSZ8081_PHYCON1_LINK_STATUS         (1<<8)
 #define KSZ8081_PHYCON1_POL_STATUS          (1<<7)
 #define KSZ8081_PHYCON1_MDIX_STATE          (1<<5)
 #define KSZ8081_PHYCON1_ENERGY_DETECT       (1<<4)
 #define KSZ8081_PHYCON1_PHY_ISOLATE         (1<<3)
 #define KSZ8081_PHYCON1_OP_MODE             0x0007
 #define KSZ8081_PHYCON1_OP_MODE_AN          0x0000
 #define KSZ8081_PHYCON1_OP_MODE_10BT_HD     (1<<0)
 #define KSZ8081_PHYCON1_OP_MODE_100BTX_HD   (1<<1)
 #define KSZ8081_PHYCON1_OP_MODE_10BT_FD     0x0005
 #define KSZ8081_PHYCON1_OP_MODE_100BTX_FD   0x0006


#endif /* KSZ8081_BIT_OFFSETS_H */
