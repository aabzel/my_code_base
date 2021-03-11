
#include "ksz8081_register_parser.h"
#include "str_ops.h"

uint16_t proc_reg_cnt = 0;

static bool parse_basic_control_register_0 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (0 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW/SC Software reset", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RW/SC Normal operation", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RW Loopback mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RW Normal operation", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RW 100 Mbps", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RW 10 Mbps", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RW Enable auto-negotiation process", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RW Disable auto-negotiation process", reg_addr);
    }
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:1  RW Power-down mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:0  RW Normal operation", reg_addr);
    }
    if (reg16b_val & (1 << 10)) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:1  RW Electrical isolation of PHY from MII", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:0  RW Normal operation", reg_addr);
    }
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RW/SC Auto-Negotiation  Restart auto-negotiation process",
                 reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RW/SC Auto-Negotiation Normal operation", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RW Full-duplex", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RW Half-duplex", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RW Test Enable COL test", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RW Test Disable COL test", reg_addr);
    }
    code = (0x7f & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 6-0: %u=0x%x  RO Reserved", reg_addr, code, code);
    return res;
}

static bool parse_basic_status_register_1 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (1 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RO T4 capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RO Not T4 capable", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RO Capable of 100 Mbps full-duplex", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RO Not capable of 100 Mbps full-duplex", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RO Capable of 100 Mbps half-duplex", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RO Not capable of 100 Mbps half-duplex", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RO Capable of 10 Mbps full-duplex", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RO Not capable of 10 Mbps full-duplex", reg_addr);
    }
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:1  RO Capable of 10 Mbps half-duplex", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:0  RO Not capable of 10 Mbps half-duplex", reg_addr);
    }
    code = (0xf & (reg16b_val >> 7));
    fprintf (out_file_prt, "\n    reg %02u bit 10-7: %u=0x%x  RO Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RO Preamble suppression", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RO Normal preamble", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RO Auto-negotiation process completed", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RO Auto-negotiation process not completed", reg_addr);
    }
    if (reg16b_val & (1 << 4)) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:1  RO/LH Remote fault", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:0  RO/LH No remote fault", reg_addr);
    }
    if (reg16b_val & (1 << 3)) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:1  RO Can perform auto-negotiation", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 3))) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:0  RO Cannot perform auto-negotiation", reg_addr);
    }
    if (reg16b_val & (1 << 2)) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:1  RO/LH Link is up", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 2))) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:0  RO/LH Link is down", reg_addr);
    }
    if (reg16b_val & (1 << 1)) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:1  RO/LH Jabber detected", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 1))) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:0  RO/LH Jabber not detected (default is low)", reg_addr);
    }
    if (reg16b_val & (1 << 0)) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:1  RO Supports extended capability registers", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:0  RO do not supports extended capability registers", reg_addr);
    }
    return res;
}

static bool parse_phy_identifier_1_register_2 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (2 == reg_addr) {
        res = true;
    }
    code = (0xffff & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 15-0: %u=0x%x  RO PHY ID Number", reg_addr, code, code);
    return res;
}

static bool parse_phy_identifier_2_register_3 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    (void)code;
    if (3 == reg_addr) {
        res = true;
    }
    code = (0x3f & (reg16b_val >> 10));
    fprintf (out_file_prt,
             "\n    reg %02u bit 15-10: %u=0x%x  RO Assigned to the 19th through 24th bits of the Organizationally "
             "Unique Identifier (OUI). KENDIN Communication’s OUI is 0010A1 (hex).",
             reg_addr, code, code);
    code = (0x3f & (reg16b_val >> 4));
    fprintf (out_file_prt, "\n    reg %02u bit 9-4: %u=0x%x  RO Six-bit manufacturer’s model number", reg_addr, code,
             code);
    code = (0xf & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 3-0: %u=0x%x  RO Four-bit manufacturer’s revision number", reg_addr,
             code, code);
    return res;
}

static bool parse_auto_negotiation_advertisement_register_4 (uint16_t reg16b_val, FILE *out_file_prt,
                                                             uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    (void)code;
    if (4 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW Next page capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RW No next page capability", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RO Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RO Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RW Remote fault supported", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RW No remote fault", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RO Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RR Reserved", reg_addr);
    }
    if (0 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:0 RW No pause", reg_addr);
    }
    if (1 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:1 RW Symmetric pause", reg_addr);
    }
    if (2 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:2 RW Asymmetric pause", reg_addr);
    }
    if (3 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:3 RW Asymmetric and symmetric pause", reg_addr);
    }
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RO T4 capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RO No T4 capability", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RW 100 Mbps full-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RW No 100 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RW 100 Mbps half-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RW No 100 Mbps half-duplex capability", reg_addr);
    }
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RW 10 Mbps full-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RW No 10 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RW 10 Mbps half-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RW No 10 Mbps half-duplex capability", reg_addr);
    }
    if (1 == (0x1f & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 4-0:1 RO IEEE 802.3", reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_link_partner_ability_register_5 (uint16_t reg16b_val, FILE *out_file_prt,
                                                                    uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (5 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RO Next page capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RO No next page capability", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RO Link code word received from partner ", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RO Link code word not yet received ", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RO Remote fault detected", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RO No remote fault", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RO Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RO Reserved", reg_addr);
    }
    if (0 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:0 RO No pause", reg_addr);
    }
    if (1 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:1 RO Symmetric pause", reg_addr);
    }
    if (2 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:2 RO Asymmetric pause", reg_addr);
    }
    if (3 == (0x3 & (reg16b_val >> 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11-10:3 RO Asymmetric and symmetric pause", reg_addr);
    }
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RO T4 capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RO No T4 capability", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RO 100 Mbps full-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RO No 100 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RO 100 Mbps half-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RO No 100 Mbps half-duplex capability", reg_addr);
    }
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RO 10 Mbps full-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RO No 10 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RO 10 Mbps half-duplex capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RO No 10 Mbps half-duplex capability", reg_addr);
    }
    if (1 == (0x1f & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 4-0:1 RO IEEE 802.3", reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_expansion_register_6 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (6 == reg_addr) {
        res = true;
    }
    code = (0x7ff & (reg16b_val >> 5));
    fprintf (out_file_prt, "\n    reg %02u bit 15-5: %u=0x%x  RO Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 4)) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:1  RO/LH Fault detected by parallel detection", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:0  RO/LH No fault detected by parallel detection", reg_addr);
    }
    if (reg16b_val & (1 << 3)) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:1  RO Link partner has next page capability", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 3))) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:0  RO Link partner does not have next page capability", reg_addr);
    }
    if (reg16b_val & (1 << 2)) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:1  RO Local device has next page capability", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 2))) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:0  RO Local device does not have next page capability", reg_addr);
    }
    if (reg16b_val & (1 << 1)) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:1  RO/LH New page received", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 1))) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:0  RO/LH New page not received yet", reg_addr);
    }
    if (reg16b_val & (1 << 0)) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:1  RO Link partner has auto-negotiation capability", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:0  RO Link partner does not have auto-negotiation capability",
                 reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_next_page_register_7 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (7 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW Additional next pages will follow", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RW Last page", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RO Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RO Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RW Message page", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RW Unformatted page", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RW Will comply with message", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RW Cannot comply with message", reg_addr);
    }
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 11:1  RO Previous value of the transmitted link code word equaled logic 1",
                 reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 11:0  RO Previous value of the transmitted link code word equaled logic 0",
                 reg_addr);
    }
    code = (0x7ff & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 10-0: %u=0x%x  RW 11-bit wide field to encode 2048 messages", reg_addr,
             code, code);
    return res;
}

static bool parse_link_partner_next_page_ability_register_8 (uint16_t reg16b_val, FILE *out_file_prt,
                                                             uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (8 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RO Additional next pages will follow", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RO Last page", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RO Successful receipt of link word", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RO No successful receipt of link word", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RO Message page", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RO Unformatted page", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RO Can act on the information", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RO Cannot act on the information", reg_addr);
    }
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 11:1  RO Previous value of transmitted link code word equal to logic 0", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 11:0  RO Previous value of transmitted link code word equal to logic 1", reg_addr);
    }
    code = (0x7ff & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 10-0: %u=0x%x  RO 11-bit wide field to encode 2048 messages", reg_addr,
             code, code);
    return res;
}

static bool parse_digital_reserved_control_register_16 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (16 == reg_addr) {
        res = true;
    }
    code = (0x7ff & (reg16b_val >> 5));
    fprintf (out_file_prt, "\n    reg %02u bit 15-5: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 4)) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:1  RW Turn PLL off automatically in EDPD mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:0  RW Keep PLL on in EDPD mode", reg_addr);
    }
    code = (0xf & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 3-0: %u=0x%x  RW Reserved", reg_addr, code, code);
    return res;
}

static bool parse_afe_control_1_register_17 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (17 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RW Slow-oscillator mode Enable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RW Slow-oscillator mode Disable", reg_addr);
    }
    return res;
}

static bool parse_rxer_counter_register_21 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (21 == reg_addr) {
        res = true;
    }
    code = (0xffff & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 15-0: %u=0x%x  RO/SC Receive error counter for symbol error frames",
             reg_addr, code, code);
    return res;
}

static bool parse_operation_mode_strap_override_register_22 (uint16_t reg16b_val, FILE *out_file_prt,
                                                             uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (22 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW Normal operation", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RW Factory test mode", reg_addr);
    }
    code = (0xf & (reg16b_val >> 11));
    fprintf (out_file_prt, "\n    reg %02u bit 14-11: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 10)) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:1  RO Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:0  RO Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RW Override strap-in for B-CAST_OFF", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RW Unclear", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RW Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RW Override strap-in for MII back-to-back mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RW Unclear", reg_addr);
    }
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RW Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RW  Override strap-in for NAND tree mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RW Unclear", reg_addr);
    }
    code = (0xf & (reg16b_val >> 1));
    fprintf (out_file_prt, "\n    reg %02u bit 4-1: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 0)) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:1  RW Override strap-in for MII mode", reg_addr);
    }
    return res;
}

static bool parse_operation_mode_strap_status_register_23 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (23 == reg_addr) {
        res = true;
    }
    code = (0x7 & (reg16b_val >> 13));
    fprintf (out_file_prt, "\n    reg %02u bit 15-13: %u=0x%x  RO Strap to PHY Address", reg_addr, code, code);
    code = (0x7 & (reg16b_val >> 10));
    fprintf (out_file_prt, "\n    reg %02u bit 12-10: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RO Strap to B-CAST_OFF", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RO unclear", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RW Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RO Strap to MII back-to-back mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RO unclear", reg_addr);
    }
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RW Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RO Strap to NAND tree mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RO unclear", reg_addr);
    }
    code = (0xf & (reg16b_val >> 1));
    fprintf (out_file_prt, "\n    reg %02u bit 4-1: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 0)) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:1  RO Strap to MII mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:0  RO unclear", reg_addr);
    }
    return res;
}

static bool parse_expanded_control_register_24 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (24 == reg_addr) {
        res = true;
    }
    code = (0xf & (reg16b_val >> 12));
    fprintf (out_file_prt, "\n    reg %02u bit 15-12: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:1  RW Energy-detect power-down mode Disable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:0  RW Energy-detect power-down mode Enable", reg_addr);
    }
    if (reg16b_val & (1 << 10)) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:1  RW MII output is random latency", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:0  RW MII output is fixed latency", reg_addr);
    }
    code = (0x7 & (reg16b_val >> 7));
    fprintf (out_file_prt, "\n    reg %02u bit 9-7: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RW Restore received preamble to MII output", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RW Remove all seven bytes of preamble before", reg_addr);
    }
    code = (0x3f & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 5-0: %u=0x%x  RW Reserved", reg_addr, code, code);
    return res;
}

static bool parse_interrupt_control_status_register_27 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (27 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW Enable jabber interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RW Disable jabber interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:1  RW Enable receive error interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14:0  RW Disable receive error interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RW Enable page received interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RW Disable page received interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RW Enable parallel detect fault interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RW Disable parallel detect fault interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:1  RW Enable link partner acknowledge interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:0  RW Disable link partner acknowledge interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 10)) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:1  RW Enable link-down interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:0  RW Disable link-down interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RW Enable remote fault interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RW Disable remote fault interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RW Enable link-up interrupt", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RW Disable link-up interrupt", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RO/SC Jabber occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RO/SC Jabber did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RO/SC Receive error occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RO/SC Receive error did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RO/SC Page receive occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RO/SC Page receive did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 4)) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:1  RO/SC Parallel detect fault occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:0  RO/SC Parallel detect fault did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 3)) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:1  RO/SC Link partner acknowledge occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 3))) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:0  RO/SC Link partner acknowledge did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 2)) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:1  RO/SC Link-down occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 2))) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:0  RO/SC Link-down did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 1)) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:1  RO/SC Remote fault occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 1))) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:0  RO/SC Remote fault did not occur", reg_addr);
    }
    if (reg16b_val & (1 << 0)) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:1  RO/SC Link-up occurred", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:0  RO/SC Link-up did not occur", reg_addr);
    }
    return res;
}

static bool parse_linkmd_control_status_register_29 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (29 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW/SC Enable cable diagnostic test.", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 15:0  RW/SC Indicates cable diagnostic test (if enabled) has completed and the "
                 "status information is valid for read.",
                 reg_addr);
    }
    if (0 == (0x3 & (reg16b_val >> 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14-13:0 RO Normal condition", reg_addr);
    }
    if (1 == (0x3 & (reg16b_val >> 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14-13:1 RO Open condition has been detected in cable", reg_addr);
    }
    if (2 == (0x3 & (reg16b_val >> 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14-13:2 RO Short condition has been detected in cable", reg_addr);
    }
    if (3 == (0x3 & (reg16b_val >> 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 14-13:3 RO Cable diagnostic test has failed", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RO Short cable (<10 meter) has been detected by LinkMD",
                 reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RO unclear cable", reg_addr);
    }
    code = (0x7 & (reg16b_val >> 9));
    fprintf (out_file_prt, "\n    reg %02u bit 11-9: %u=0x%x  RW Reserved", reg_addr, code, code);
    code = (0x1ff & (reg16b_val >> 0));
    fprintf (out_file_prt, "\n    reg %02u bit 8-0: %u=0x%x  RO Distance to fault", reg_addr, code, code);
    return res;
}

static bool parse_phy_control_1_register_30 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (30 == reg_addr) {
        res = true;
    }
    code = (0x3f & (reg16b_val >> 10));
    fprintf (out_file_prt, "\n    reg %02u bit 15-10: %u=0x%x  RO Reserved", reg_addr, code, code);
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RO Flow control capable", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RO No flow control capability", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RO Link is up", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RO Link is down", reg_addr);
    }
    if (reg16b_val & (1 << 7)) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:1  RO Polarity is reversed", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 7))) {
        fprintf (out_file_prt, "\n    reg %02u bit  7:0  RO Polarity is not reversed", reg_addr);
    }
    if (reg16b_val & (1 << 6)) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:1  RO Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 6))) {
        fprintf (out_file_prt, "\n    reg %02u bit  6:0  RO Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 5)) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:1  RO MDI-X", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 5))) {
        fprintf (out_file_prt, "\n    reg %02u bit  5:0  RO MDI", reg_addr);
    }
    if (reg16b_val & (1 << 4)) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:1  RO Signal present on receive differential pair", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit  4:0  RO No signal detected on receive differential pair", reg_addr);
    }
    if (reg16b_val & (1 << 3)) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:1  RW PHY in isolate mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 3))) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:0  RW PHY in normal operation", reg_addr);
    }
    if (0 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:0 RO Still in auto-negotiation", reg_addr);
    }
    if (1 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:1 RO 10BASE-T half-duplex", reg_addr);
    }
    if (2 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:2 RO 100BASE-TX half-duplex", reg_addr);
    }
    if (3 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:3 RO Reserved", reg_addr);
    }
    if (4 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:4 RO Reserved", reg_addr);
    }
    if (5 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:5 RO 10BASE-T full-duplex", reg_addr);
    }
    if (6 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:6 RO 100BASE-TX full-duplex", reg_addr);
    }
    if (7 == (0x7 & (reg16b_val >> 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit 2-0:7 RO Reserved", reg_addr);
    }
    return res;
}

static bool parse_phy_control_2_register_31 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    uint16_t code = 0U;
    (void)code;
    if (31 == reg_addr) {
        res = true;
    }
    if (reg16b_val & (1 << 15)) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:1  RW HP Auto MDI/MDI-X mode", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 15))) {
        fprintf (out_file_prt, "\n    reg %02u bit 15:0  RW Microchip Auto MDI/MDI-X mode", reg_addr);
    }
    if (reg16b_val & (1 << 14)) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 14:1  RW MDI-X mode Transmit on RXP, RXM (Pins 10, 9) and Receive on TXP, TXM "
                 "(Pins 12, 11)",
                 reg_addr);
    }
    if (0 == (reg16b_val & (1 << 14))) {
        fprintf (out_file_prt,
                 "\n    reg %02u bit 14:0  RW MDI mode Transmit on TXP, TXM (Pins 12, 11) and Receive on RXP, RXM "
                 "(Pins 10, 9)",
                 reg_addr);
    }
    if (reg16b_val & (1 << 13)) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:1  RW Disable Auto MDI/MDI-X", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 13))) {
        fprintf (out_file_prt, "\n    reg %02u bit 13:0  RW Enable Auto MDI/MDI-X", reg_addr);
    }
    if (reg16b_val & (1 << 12)) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:1  RW Reserved", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 12))) {
        fprintf (out_file_prt, "\n    reg %02u bit 12:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 11)) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:1  RW Force link pass", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 11))) {
        fprintf (out_file_prt, "\n    reg %02u bit 11:0  RW Normal link operation", reg_addr);
    }
    if (reg16b_val & (1 << 10)) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:1  RW Enable power saving", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 10))) {
        fprintf (out_file_prt, "\n    reg %02u bit 10:0  RW Disable power saving", reg_addr);
    }
    if (reg16b_val & (1 << 9)) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:1  RW Interrupt pin active high", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 9))) {
        fprintf (out_file_prt, "\n    reg %02u bit  9:0  RW Interrupt pin active low", reg_addr);
    }
    if (reg16b_val & (1 << 8)) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:1  RW Enable jabber counter", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 8))) {
        fprintf (out_file_prt, "\n    reg %02u bit  8:0  RW Disable jabber counter", reg_addr);
    }
    code = (0x3 & (reg16b_val >> 6));
    fprintf (out_file_prt, "\n    reg %02u bit 7-6: %u=0x%x  RW Reserved", reg_addr, code, code);
    if (0 == (0x3 & (reg16b_val >> 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit 5-4:0 RW LED1: Speed LED0: Link/Activity", reg_addr);
    }
    if (1 == (0x3 & (reg16b_val >> 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit 5-4:1 RW LED1: Activity LED0: Link", reg_addr);
    }
    if (2 == (0x3 & (reg16b_val >> 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit 5-4:2 RW Reserved", reg_addr);
    }
    if (3 == (0x3 & (reg16b_val >> 4))) {
        fprintf (out_file_prt, "\n    reg %02u bit 5-4:3 RW Reserved", reg_addr);
    }
    if (reg16b_val & (1 << 3)) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:1  RW Disable transmitter", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 3))) {
        fprintf (out_file_prt, "\n    reg %02u bit  3:0  RW Enable transmitter", reg_addr);
    }
    if (reg16b_val & (1 << 2)) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:1  RW Remote (analog) loopback is enabled", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 2))) {
        fprintf (out_file_prt, "\n    reg %02u bit  2:0  RW Normal mode", reg_addr);
    }
    if (reg16b_val & (1 << 1)) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:1  RW Enable SQE test", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 1))) {
        fprintf (out_file_prt, "\n    reg %02u bit  1:0  RW Disable SQE test", reg_addr);
    }
    if (reg16b_val & (1 << 0)) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:1  RW Disable scrambler", reg_addr);
    }
    if (0 == (reg16b_val & (1 << 0))) {
        fprintf (out_file_prt, "\n    reg %02u bit  0:0  RW Enable scrambler", reg_addr);
    }
    return res;
}

bool parse_ksz8081_reg (uint8_t reg_addr, FILE *out_file_prt) {
    bool res = false;
    uint16_t reg16b_val = ksz8081RegMap[reg_addr].reg_val;
    fprintf (out_file_prt, "\n\nReg: [%s] reg_addr: 0x%02x val: 0x%04x 0b_%s", ksz8081RegMap[reg_addr].reg_name,
             reg_addr, reg16b_val, utoa_bin24 (reg16b_val));
    switch (reg_addr) {
    case 0:
        proc_reg_cnt++;
        res = parse_basic_control_register_0 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 1:
        proc_reg_cnt++;
        res = parse_basic_status_register_1 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 2:
        proc_reg_cnt++;
        res = parse_phy_identifier_1_register_2 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 3:
        proc_reg_cnt++;
        res = parse_phy_identifier_2_register_3 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 4:
        proc_reg_cnt++;
        res = parse_auto_negotiation_advertisement_register_4 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 5:
        proc_reg_cnt++;
        res = parse_auto_negotiation_link_partner_ability_register_5 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 6:
        proc_reg_cnt++;
        res = parse_auto_negotiation_expansion_register_6 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 7:
        proc_reg_cnt++;
        res = parse_auto_negotiation_next_page_register_7 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 8:
        proc_reg_cnt++;
        res = parse_link_partner_next_page_ability_register_8 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 16:
        proc_reg_cnt++;
        res = parse_digital_reserved_control_register_16 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 17:
        proc_reg_cnt++;
        res = parse_afe_control_1_register_17 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 21:
        proc_reg_cnt++;
        res = parse_rxer_counter_register_21 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 22:
        proc_reg_cnt++;
        res = parse_operation_mode_strap_override_register_22 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 23:
        proc_reg_cnt++;
        res = parse_operation_mode_strap_status_register_23 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 24:
        proc_reg_cnt++;
        res = parse_expanded_control_register_24 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 27:
        proc_reg_cnt++;
        res = parse_interrupt_control_status_register_27 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 29:
        proc_reg_cnt++;
        res = parse_linkmd_control_status_register_29 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 30:
        proc_reg_cnt++;
        res = parse_phy_control_1_register_30 (reg16b_val, out_file_prt, reg_addr);
        break;
    case 31:
        proc_reg_cnt++;
        res = parse_phy_control_2_register_31 (reg16b_val, out_file_prt, reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n Lack of parser for reg %s addr 0x%x val 0x%x", ksz8081_reg_2_name[reg_addr],
                 reg_addr, reg16b_val);
        break;
    }
    return res;
}

// Support: aabzele@gmail.com Alexander Barunin
