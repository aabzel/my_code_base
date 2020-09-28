

static bool parse_phy_control_2_register_31 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 31 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW HP Auto MDI/MDI-X mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW Microchip Auto MDI/MDI-X mode", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RW MDI-X mode Transmit on RXP, RXM (Pins 10, 9) and Receive on TXP, TXM (Pins 12, 11)", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RW MDI mode Transmit on TXP, TXM (Pins 12, 11) and Receive on RXP, RXM (Pins 10, 9)", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RW Disable Auto MDI/MDI-X", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RW Enable Auto MDI/MDI-X", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RW Reserved", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RW Force link pass", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RW Normal link operation", reg_addr);
    }
    if (reg16b_val & (1<<10)) {
        fprintf (out_file_prt,"\n reg %02u bit10:1  RW Enable power saving", reg_addr);
    }
    if (0==(reg16b_val & (1<<10))) {
        fprintf (out_file_prt,"\n reg %02u bit10:0  RW Disable power saving", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RW Interrupt pin active high", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RW Interrupt pin active low", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RW Enable jabber counter", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RW Disable jabber counter", reg_addr);
    }
    if (reg16b_val & (1<<3)) {
        fprintf (out_file_prt,"\n reg %02u bit03:1  RW Disable transmitter", reg_addr);
    }
    if (0==(reg16b_val & (1<<3))) {
        fprintf (out_file_prt,"\n reg %02u bit03:0  RW Enable transmitter", reg_addr);
    }
    if (reg16b_val & (1<<2)) {
        fprintf (out_file_prt,"\n reg %02u bit02:1  RW Remote (analog) loopback is enabled", reg_addr);
    }
    if (0==(reg16b_val & (1<<2))) {
        fprintf (out_file_prt,"\n reg %02u bit02:0  RW Normal mode", reg_addr);
    }
    if (reg16b_val & (1<<1)) {
        fprintf (out_file_prt,"\n reg %02u bit01:1  RW Enable SQE test", reg_addr);
    }
    if (0==(reg16b_val & (1<<1))) {
        fprintf (out_file_prt,"\n reg %02u bit01:0  RW Disable SQE test", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RW Disable scrambler", reg_addr);
    }
    if (0==(reg16b_val & (1<<0))) {
        fprintf (out_file_prt,"\n reg %02u bit00:0  RW Enable scrambler", reg_addr);
    }
    return res;
}

static bool parse_basic_control_register_0 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 0 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW/SC Software reset", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW/SC Normal operation", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RW Loopback mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RW Normal operation", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RW 100 Mbps", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RW 10 Mbps", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RW Enable auto-negotiation process", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RW Disable auto-negotiation process", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RW Power-down mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RW Normal operation", reg_addr);
    }
    if (reg16b_val & (1<<10)) {
        fprintf (out_file_prt,"\n reg %02u bit10:1  RW Electrical isolation of PHY from MII", reg_addr);
    }
    if (0==(reg16b_val & (1<<10))) {
        fprintf (out_file_prt,"\n reg %02u bit10:0  RW Normal operation", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RW/SC Auto-Negotiation  Restart auto-negotiation process", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RW/SC Auto-Negotiation Normal operation", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RW Full-duplex", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RW Half-duplex", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RW Test Enable COL test", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RW Test Disable COL test", reg_addr);
    }
    return res;
}

static bool parse_basic_status_register_1 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 1 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RO T4 capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RO Not T4 capable", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RO Capable of 100 Mbps full-duplex", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RO Not capable of 100 Mbps full-duplex", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RO Capable of 100 Mbps half-duplex", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RO Not capable of 100 Mbps half-duplex", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RO Capable of 10 Mbps full-duplex", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RO Not capable of 10 Mbps full-duplex", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RO Capable of 10 Mbps half-duplex", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RO Not capable of 10 Mbps half-duplex", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n reg %02u bit06:1  RO Preamble suppression", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n reg %02u bit06:0  RO Normal preamble", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RO Auto-negotiation process completed", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RO Auto-negotiation process not completed", reg_addr);
    }
    if (reg16b_val & (1<<4)) {
        fprintf (out_file_prt,"\n reg %02u bit04:1  RO/LH Remote fault", reg_addr);
    }
    if (0==(reg16b_val & (1<<4))) {
        fprintf (out_file_prt,"\n reg %02u bit04:0  RO/LH No remote fault", reg_addr);
    }
    if (reg16b_val & (1<<3)) {
        fprintf (out_file_prt,"\n reg %02u bit03:1  RO Can perform auto-negotiation", reg_addr);
    }
    if (0==(reg16b_val & (1<<3))) {
        fprintf (out_file_prt,"\n reg %02u bit03:0  RO Cannot perform auto-negotiation", reg_addr);
    }
    if (reg16b_val & (1<<2)) {
        fprintf (out_file_prt,"\n reg %02u bit02:1  RO/LH Link is up", reg_addr);
    }
    if (0==(reg16b_val & (1<<2))) {
        fprintf (out_file_prt,"\n reg %02u bit02:0  RO/LH Link is down", reg_addr);
    }
    if (reg16b_val & (1<<1)) {
        fprintf (out_file_prt,"\n reg %02u bit01:1  RO/LH Jabber detected", reg_addr);
    }
    if (0==(reg16b_val & (1<<1))) {
        fprintf (out_file_prt,"\n reg %02u bit01:0  RO/LH Jabber not detected (default is low)", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RO Supports extended capability registers", reg_addr);
    }
    if (0==(reg16b_val & (1<<0))) {
        fprintf (out_file_prt,"\n reg %02u bit00:0  RO do not supports extended capability registers", reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_advertisement_register_4 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 4 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW Next page capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW No next page capability", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RW Remote fault supported", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RW No remote fault", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RO T4 capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RO No T4 capability", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RW 100 Mbps full-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RW No 100 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RW 100 Mbps half-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RW No 100 Mbps half-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n reg %02u bit06:1  RW 10 Mbps full-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n reg %02u bit06:0  RW No 10 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RW 10 Mbps half-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RW No 10 Mbps half-duplex capability", reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_link_partner_ability_register_5 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 5 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RO Next page capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RO No next page capability", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RO Link code word received from partner ", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RO Link code word not yet received ", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RO Remote fault detected", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RO No remote fault", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RO T4 capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RO No T4 capability", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RO 100 Mbps full-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RO No 100 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RO 100 Mbps half-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RO No 100 Mbps half-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n reg %02u bit06:1  RO 10 Mbps full-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n reg %02u bit06:0  RO No 10 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RO 10 Mbps half-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RO No 10 Mbps half-duplex capability", reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_expansion_register_6 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 6 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<4)) {
        fprintf (out_file_prt,"\n reg %02u bit04:1  RO/LH Fault detected by parallel detection", reg_addr);
    }
    if (0==(reg16b_val & (1<<4))) {
        fprintf (out_file_prt,"\n reg %02u bit04:0  RO/LH No fault detected by parallel detection", reg_addr);
    }
    if (reg16b_val & (1<<3)) {
        fprintf (out_file_prt,"\n reg %02u bit03:1  RO Link partner has next page capability", reg_addr);
    }
    if (0==(reg16b_val & (1<<3))) {
        fprintf (out_file_prt,"\n reg %02u bit03:0  RO Link partner does not have next page capability", reg_addr);
    }
    if (reg16b_val & (1<<2)) {
        fprintf (out_file_prt,"\n reg %02u bit02:1  RO Local device has next page capability", reg_addr);
    }
    if (0==(reg16b_val & (1<<2))) {
        fprintf (out_file_prt,"\n reg %02u bit02:0  RO Local device does not have next page capability", reg_addr);
    }
    if (reg16b_val & (1<<1)) {
        fprintf (out_file_prt,"\n reg %02u bit01:1  RO/LH New page received", reg_addr);
    }
    if (0==(reg16b_val & (1<<1))) {
        fprintf (out_file_prt,"\n reg %02u bit01:0  RO/LH New page not received yet", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RO Link partner has auto-negotiation capability", reg_addr);
    }
    if (0==(reg16b_val & (1<<0))) {
        fprintf (out_file_prt,"\n reg %02u bit00:0  RO Link partner does not have auto-negotiation capability", reg_addr);
    }
    return res;
}

static bool parse_auto_negotiation_next_page_register_7 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 7 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW Additional next pages will follow", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW Last page", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RO Reserved", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RO Reserved", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RW Message page", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RW Unformatted page", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RW Will comply with message", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RW Cannot comply with message", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RO Previous value of the transmitted link code word equaled logic 1", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RO Previous value of the transmitted link code word equaled logic 0", reg_addr);
    }
    return res;
}

static bool parse_link_partner_next_page_ability_register_8 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 8 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RO Additional next pages will follow", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RO Last page", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RO Successful receipt of link word", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RO No successful receipt of link word", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RO Message page", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RO Unformatted page", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RO Can act on the information", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RO Cannot act on the information", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RO Previous value of transmitted link code word equal to logic 0", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RO Previous value of transmitted link code word equal to logic 1", reg_addr);
    }
    return res;
}

static bool parse_digital_reserved_control_register_16 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 16 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<4)) {
        fprintf (out_file_prt,"\n reg %02u bit04:1  RW Turn PLL off automatically in EDPD mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<4))) {
        fprintf (out_file_prt,"\n reg %02u bit04:0  RW Keep PLL on in EDPD mode", reg_addr);
    }
    return res;
}

static bool parse_afe_control_1_register_17 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 17 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RW Slow-oscillator mode Enable", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RW Slow-oscillator mode Disable", reg_addr);
    }
    return res;
}

static bool parse_operation_mode_strap_override_register_22 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 22 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW Normal operation", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW Factory test mode", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RW Override strap-in for B-CAST_OFF", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RW Unclear", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RW Reserved", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RW Override strap-in for MII back-to-back mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RW Unclear", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RW  Override strap-in for NAND tree mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RW Unclear", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RW Override strap-in for MII mode", reg_addr);
    }
    return res;
}

static bool parse_operation_mode_strap_status_register_23 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 23 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RO Strap to B-CAST_OFF", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RO unclear", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RO Strap to MII back-to-back mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RO unclear", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RO Strap to NAND tree mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RO unclear", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RO Strap to MII mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<0))) {
        fprintf (out_file_prt,"\n reg %02u bit00:0  RO unclear", reg_addr);
    }
    return res;
}

static bool parse_expanded_control_register_24 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 24 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RW Energy-detect power-down mode Disable", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RW Energy-detect power-down mode Enable", reg_addr);
    }
    if (reg16b_val & (1<<10)) {
        fprintf (out_file_prt,"\n reg %02u bit10:1  RW MII output is random latency", reg_addr);
    }
    if (0==(reg16b_val & (1<<10))) {
        fprintf (out_file_prt,"\n reg %02u bit10:0  RW MII output is fixed latency", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n reg %02u bit06:1  RW Restore received preamble to MII output", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n reg %02u bit06:0  RW Remove all seven bytes of preamble before", reg_addr);
    }
    return res;
}

static bool parse_interrupt_control_status_register_27 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 27 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW Enable jabber interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW Disable jabber interrupt", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RW Enable receive error interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RW Disable receive error interrupt", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RW Enable page received interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RW Disable page received interrupt", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RW Enable parallel detect fault interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RW Disable parallel detect fault interrupt", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RW Enable link partner acknowledge interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RW Disable link partner acknowledge interrupt", reg_addr);
    }
    if (reg16b_val & (1<<10)) {
        fprintf (out_file_prt,"\n reg %02u bit10:1  RW Enable link-down interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<10))) {
        fprintf (out_file_prt,"\n reg %02u bit10:0  RW Disable link-down interrupt", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RW Enable remote fault interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RW Disable remote fault interrupt", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RW Enable link-up interrupt", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RW Disable link-up interrupt", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RO/SC Jabber occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RO/SC Jabber did not occur", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n reg %02u bit06:1  RO/SC Receive error occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n reg %02u bit06:0  RO/SC Receive error did not occur", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RO/SC Page receive occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RO/SC Page receive did not occur", reg_addr);
    }
    if (reg16b_val & (1<<4)) {
        fprintf (out_file_prt,"\n reg %02u bit04:1  RO/SC Parallel detect fault occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<4))) {
        fprintf (out_file_prt,"\n reg %02u bit04:0  RO/SC Parallel detect fault did not occur", reg_addr);
    }
    if (reg16b_val & (1<<3)) {
        fprintf (out_file_prt,"\n reg %02u bit03:1  RO/SC Link partner acknowledge occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<3))) {
        fprintf (out_file_prt,"\n reg %02u bit03:0  RO/SC Link partner acknowledge did not occur", reg_addr);
    }
    if (reg16b_val & (1<<2)) {
        fprintf (out_file_prt,"\n reg %02u bit02:1  RO/SC Link-down occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<2))) {
        fprintf (out_file_prt,"\n reg %02u bit02:0  RO/SC Link-down did not occur", reg_addr);
    }
    if (reg16b_val & (1<<1)) {
        fprintf (out_file_prt,"\n reg %02u bit01:1  RO/SC Remote fault occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<1))) {
        fprintf (out_file_prt,"\n reg %02u bit01:0  RO/SC Remote fault did not occur", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RO/SC Link-up occurred", reg_addr);
    }
    if (0==(reg16b_val & (1<<0))) {
        fprintf (out_file_prt,"\n reg %02u bit00:0  RO/SC Link-up did not occur", reg_addr);
    }
    return res;
}

static bool parse_linkmd_control_status_register_29 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 29 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW/SC Enable cable diagnostic test.", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW/SC Indicates cable diagnostic test (if enabled) has completed and the status information is valid for read.", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RO Short cable (<10 meter) has been detected by LinkMD", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RO unclear cable", reg_addr);
    }
    return res;
}

static bool parse_phy_control_1_register_30 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 30 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RO Flow control capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RO No flow control capability", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RO Link is up", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RO Link is down", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n reg %02u bit07:1  RO Polarity is reversed", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n reg %02u bit07:0  RO Polarity is not reversed", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n reg %02u bit06:1  RO Reserved", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n reg %02u bit06:0  RO Reserved", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n reg %02u bit05:1  RO MDI-X", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n reg %02u bit05:0  RO MDI", reg_addr);
    }
    if (reg16b_val & (1<<4)) {
        fprintf (out_file_prt,"\n reg %02u bit04:1  RO Signal present on receive differential pair", reg_addr);
    }
    if (0==(reg16b_val & (1<<4))) {
        fprintf (out_file_prt,"\n reg %02u bit04:0  RO No signal detected on receive differential pair", reg_addr);
    }
    if (reg16b_val & (1<<3)) {
        fprintf (out_file_prt,"\n reg %02u bit03:1  RW PHY in isolate mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<3))) {
        fprintf (out_file_prt,"\n reg %02u bit03:0  RW PHY in normal operation", reg_addr);
    }
    return res;
}

static bool parse_phy_control_2_register_31 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 31 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n reg %02u bit15:1  RW HP Auto MDI/MDI-X mode", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n reg %02u bit15:0  RW Microchip Auto MDI/MDI-X mode", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n reg %02u bit14:1  RW MDI-X mode Transmit on RXP, RXM (Pins 10, 9) and Receive on TXP, TXM (Pins 12, 11)", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n reg %02u bit14:0  RW MDI mode Transmit on TXP, TXM (Pins 12, 11) and Receive on RXP, RXM (Pins 10, 9)", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n reg %02u bit13:1  RW Disable Auto MDI/MDI-X", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n reg %02u bit13:0  RW Enable Auto MDI/MDI-X", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n reg %02u bit12:1  RW Reserved", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n reg %02u bit12:0  RW Reserved", reg_addr);
    }
    if (reg16b_val & (1<<11)) {
        fprintf (out_file_prt,"\n reg %02u bit11:1  RW Force link pass", reg_addr);
    }
    if (0==(reg16b_val & (1<<11))) {
        fprintf (out_file_prt,"\n reg %02u bit11:0  RW Normal link operation", reg_addr);
    }
    if (reg16b_val & (1<<10)) {
        fprintf (out_file_prt,"\n reg %02u bit10:1  RW Enable power saving", reg_addr);
    }
    if (0==(reg16b_val & (1<<10))) {
        fprintf (out_file_prt,"\n reg %02u bit10:0  RW Disable power saving", reg_addr);
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n reg %02u bit09:1  RW Interrupt pin active high", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n reg %02u bit09:0  RW Interrupt pin active low", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n reg %02u bit08:1  RW Enable jabber counter", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n reg %02u bit08:0  RW Disable jabber counter", reg_addr);
    }
    if (reg16b_val & (1<<3)) {
        fprintf (out_file_prt,"\n reg %02u bit03:1  RW Disable transmitter", reg_addr);
    }
    if (0==(reg16b_val & (1<<3))) {
        fprintf (out_file_prt,"\n reg %02u bit03:0  RW Enable transmitter", reg_addr);
    }
    if (reg16b_val & (1<<2)) {
        fprintf (out_file_prt,"\n reg %02u bit02:1  RW Remote (analog) loopback is enabled", reg_addr);
    }
    if (0==(reg16b_val & (1<<2))) {
        fprintf (out_file_prt,"\n reg %02u bit02:0  RW Normal mode", reg_addr);
    }
    if (reg16b_val & (1<<1)) {
        fprintf (out_file_prt,"\n reg %02u bit01:1  RW Enable SQE test", reg_addr);
    }
    if (0==(reg16b_val & (1<<1))) {
        fprintf (out_file_prt,"\n reg %02u bit01:0  RW Disable SQE test", reg_addr);
    }
    if (reg16b_val & (1<<0)) {
        fprintf (out_file_prt,"\n reg %02u bit00:1  RW Disable scrambler", reg_addr);
    }
    if (0==(reg16b_val & (1<<0))) {
        fprintf (out_file_prt,"\n reg %02u bit00:0  RW Enable scrambler", reg_addr);
    }
    return res;
}

 // Support: aabzele@gmail.com Alexander Barunin