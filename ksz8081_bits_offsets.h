#ifndef KSZ8081_BIT_OFFSETS_H
#define KSZ8081_BIT_OFFSETS_H
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

#endif /* KSZ8081_BIT_OFFSETS_H */
