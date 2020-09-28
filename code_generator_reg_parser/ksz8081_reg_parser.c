

static bool parse_auto_negotiation_link_partner_ability_register_5 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if ( 5 == reg_addr ) {
        res = true;
    }
    if (reg16b_val & (1<<15)) {
        fprintf (out_file_prt,"\n    reg %02u bit 15:1  RO Next page capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<15))) {
        fprintf (out_file_prt,"\n    reg %02u bit 15:0  RO No next page capability", reg_addr);
    }
    if (reg16b_val & (1<<14)) {
        fprintf (out_file_prt,"\n    reg %02u bit 14:1  RO Link code word received from partner ", reg_addr);
    }
    if (0==(reg16b_val & (1<<14))) {
        fprintf (out_file_prt,"\n    reg %02u bit 14:0  RO Link code word not yet received ", reg_addr);
    }
    if (reg16b_val & (1<<13)) {
        fprintf (out_file_prt,"\n    reg %02u bit 13:1  RO Remote fault detected", reg_addr);
    }
    if (0==(reg16b_val & (1<<13))) {
        fprintf (out_file_prt,"\n    reg %02u bit 13:0  RO No remote fault", reg_addr);
    }
    if (reg16b_val & (1<<12)) {
        fprintf (out_file_prt,"\n    reg %02u bit 12:1  RO Reserved", reg_addr);
    }
    if (0==(reg16b_val & (1<<12))) {
        fprintf (out_file_prt,"\n    reg %02u bit 12:0  RO Reserved", reg_addr);
    }
    if(0==(3 & (reg16b_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:0 RO No pause"); 
    }
    if(1==(3 & (reg16b_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:1 RO Symmetric pause"); 
    }
    if(2==(3 & (reg16b_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:2 RO Asymmetric pause"); 
    }
    if(3==(3 & (reg16b_val>>10))){
        fprintf (out_file_prt,"\n    reg %02u bit 11-10:3 RO Asymmetric and symmetric pause"); 
    }
    if (reg16b_val & (1<<9)) {
        fprintf (out_file_prt,"\n    reg %02u bit  9:1  RO T4 capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<9))) {
        fprintf (out_file_prt,"\n    reg %02u bit  9:0  RO No T4 capability", reg_addr);
    }
    if (reg16b_val & (1<<8)) {
        fprintf (out_file_prt,"\n    reg %02u bit  8:1  RO 100 Mbps full-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<8))) {
        fprintf (out_file_prt,"\n    reg %02u bit  8:0  RO No 100 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<7)) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:1  RO 100 Mbps half-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<7))) {
        fprintf (out_file_prt,"\n    reg %02u bit  7:0  RO No 100 Mbps half-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<6)) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:1  RO 10 Mbps full-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<6))) {
        fprintf (out_file_prt,"\n    reg %02u bit  6:0  RO No 10 Mbps full-duplex capability", reg_addr);
    }
    if (reg16b_val & (1<<5)) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:1  RO 10 Mbps half-duplex capable", reg_addr);
    }
    if (0==(reg16b_val & (1<<5))) {
        fprintf (out_file_prt,"\n    reg %02u bit  5:0  RO No 10 Mbps half-duplex capability", reg_addr);
    }
    return res;
}

static bool parse_ksz8081_reg (uint8_t reg_addr, FILE *out_file_prt) {
    bool res = false;
    uint16_t reg16b_val = ksz8081RegMap[reg_addr].reg_val;
    fprintf (out_file_prt, "\n\nReg: [%s] reg_addr: 0x%02x val: 0x%04x 0b_%s", ksz8081RegMap[reg_addr].reg_name, reg_addr, reg16b_val, utoa_bin24 (reg16b_val));
    switch ( reg_addr ) {
        case 5: 
            proc_reg_cnt++;
            res = parse_auto_negotiation_link_partner_ability_register_5 (reg16b_val, out_file_prt, reg_addr);
        break;
        default:
            fprintf (out_file_prt, "\n Lack of parser for reg %s addr 0x%x val 0x%x", ksz8081_reg_2_name[reg_addr], reg_addr, reg16b_val);
        break;
    }
    return res;
}

 // Support: aabzele@gmail.com Alexander Barunin