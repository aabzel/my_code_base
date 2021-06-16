#include "can_commands.h"

#include <inttypes.h>

#include "bit_utils.h"
#include "can_driver.h"
#include "convert.h"
#include "data_utils.h"
#include "diag_page_nums.h"
#include "log.h"
#include "io_utils.h"
#include "ostream.h"
#include "table_utils.h"
#include "vega_can_typedefs.h"

bool can_stat_command(int32_t argc, char* argv[]) {
    static const table_col_t cols[] = {{5, "CAN"}, {7, "rx"}, {7, "tx"}};
    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
    for (uint8_t can_num = 0; can_num < CAN_CNT; can_num++) {
        io_printf(TSEP);
        io_printf(" %02u  " TSEP, can_num + 1);
        io_printf(" %04u  " TSEP, CanStat[can_num].rx_cnt);
        io_printf(" %04u  " TSEP, CanStat[can_num].tx_cnt);
        io_printf(CRLF);
    }
    table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));
    return false;
}
bool can_init_command(int32_t argc, char* argv[]) {
    return false;
}

static bool diag_can(uint8_t can_num) {
    bool res = false;
    CAN_TypeDef* can_addr = NULL;
    uint8_t mail_box = 0U;

    io_printf(TSEP);
    io_printf(" %02u  " CRLF, can_num + 1);
    io_printf("%s " CRLF, (MASK_1BIT == (MASK_1BIT & (can_addr->FMR))) ? "Initialization mode for the filters." : "Active filters mode.");
    io_printf("CAN start bank %u " CRLF, extract_subval_from_32bit(can_addr->FMR, 13, 8));

    can_addr = get_can_reg(can_num);

    static const table_col_t cols[] = {
        {6, "can"},
        {9, "Rate"}, /*BTR*/
        {5, "box"},
        {10, "messages"},
        {8, "ID std"},
        {12, "ID ext"},
        {9, "ID"},
        {8, "frame"},
        {11, "timeStamp"},
        {12, "FilMchtInd"},
        {5, "Len"},
        {19, "Data"},
        {8, "bit us"}};
    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
    for (can_num = 1; can_num <= CAN_CNT; can_num++) {
        can_addr = get_can_reg(can_num);
        for (mail_box = 0; mail_box < 2; mail_box++) {
            res = true;
            io_printf(TSEP);
            io_printf(" CAN%u " TSEP, can_num);
            io_printf(" %7.0f " TSEP, can_calc_bit_rate(can_addr->BTR)); /*Rate bis per c*/
            io_printf(" %3u " TSEP, mail_box);                           /*box*/
            if (0 == mail_box) {
                io_printf(" %8u " TSEP, MASK_2BIT & (can_addr->RF0R)); /*messages*/
            } else {
                io_printf(" %8u " TSEP, MASK_2BIT & (can_addr->RF1R)); /*messages*/
            }
            io_printf(" 0x%03x  " TSEP, extract_subval_from_32bit(can_addr->sFIFOMailBox[mail_box].RIR, 31, 21)); /*ID std*/
            io_printf(" 0x%08x " TSEP, extract_subval_from_32bit(can_addr->sFIFOMailBox[mail_box].RIR, 31, 3));
            io_printf("%8s " TSEP, ((1 << 2) == ((1 << 2) & (can_addr->sFIFOMailBox[mail_box].RIR))) ? "Extended" : "Standard");
            io_printf("%7s " TSEP, ((1 << 1) == ((1 << 1) & (can_addr->sFIFOMailBox[mail_box].RIR))) ? "Remote" : "Data");

            io_printf("  %8u " TSEP, extract_subval_from_32bit(can_addr->sFIFOMailBox[mail_box].RDTR, 31, 16));    /*timeStamp*/
            io_printf("   %5u    " TSEP, extract_subval_from_32bit(can_addr->sFIFOMailBox[mail_box].RDTR, 15, 8)); /*FilMchtInd*/
            io_printf(" %2u  " TSEP, MASK_4BIT & (can_addr->sFIFOMailBox[mail_box].RDTR));                         /*DataLength*/

            io_printf(" 0x%08x"
                      "%08x" TSEP,
                      (can_addr->sFIFOMailBox[mail_box].RDHR), (can_addr->sFIFOMailBox[mail_box].RDLR)); /**/
            io_printf(" %f  " TSEP, 1000000.0f * can_calc_bit_time(can_addr->BTR));                      /*sec*/
            io_printf(CRLF);
        }
        table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));
    }

    return res;
}

static const char* LastErrorCodeLUT[8] = {
    /*000*/ "No Err",
    /*001*/ "Stuff Err",
    /*010*/ "Form Err",
    /*011*/ "Acknowledgment Err",
    /*100*/ "Bit recessive Err",
    /*101*/ "Bit dominant Err",
    /*110*/ "CRC Err",
    /*111*/ "Set by software"};

static const char* code2lastErrCode(uint8_t code) {
    const char* name = "undef";
    if (code <= 8) {
        name = LastErrorCodeLUT[code];
    }
    return name;
}

static bool diag_can_errors(uint8_t can_num) {
    bool res = false;
    CAN_TypeDef* can_addr = NULL;
    static const table_col_t cols[] = {
        {6, "can"},
        {5, "RxErr"},
        {5, "TxErr"},
        {10, "LastErrCode"},
        {8, "BusOff"},
        {12, "Error Pass"},
        {9, "Wern Pass"},
    };
    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
    for (can_num = 1; can_num <= CAN_CNT; can_num++) {
        can_addr = get_can_reg(can_num);
        io_printf(TSEP);
        io_printf(" CAN%u " TSEP, can_num);                                                          /**/
        io_printf("  %4u  " TSEP, extract_subval_from_32bit(can_addr->ESR, 31, 24));                 /*REC*/
        io_printf("  %4u  " TSEP, extract_subval_from_32bit(can_addr->ESR, 23, 16));                 /*TEC*/
        io_printf("  %4s  " TSEP, code2lastErrCode(extract_subval_from_32bit(can_addr->ESR, 6, 4))); /*LEC*/
        io_printf("  %1u  " TSEP, ((1 << 2) == ((1 << 2) & (can_addr->ESR))));                       /*BOFF*/
        io_printf("  %1u   " TSEP, ((1 << 1) == ((1 << 1) & (can_addr->ESR))));                      /*EPVF*/
        io_printf("  %1u   " TSEP, (1 == (1 & (can_addr->ESR))));                                    /*EWGF:*/
        io_printf(CRLF);
    }
    table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));

    return res;
}

static bool print_allow_id(uint8_t can_num) {
    bool res = false;
    CAN_TypeDef* can_addr = NULL;
    can_addr = get_can_reg(can_num);
    if (NULL != can_addr) {
        bool is_print = false;
        for (uint8_t fi = 0U; fi < 28U; fi++) {
            is_print = is_can_filter_active(can_num, fi);
            if (true == is_print) {
                if (1 == CHECK_BIT_NUM(can_addr->FM1R, fi)) {
                    if (0 == CHECK_BIT_NUM(can_addr->FS1R, fi)) {
                        io_printf("0x%04x ", extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR1, 15, 5));
                        io_printf("0x%04x ", extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR1, 31, 21));
                        io_printf("0x%04x ", extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR2, 15, 5));
                        io_printf("0x%04x ", extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR2, 31, 21));
                    }
                }
            }
        }
    }
    io_printf(CRLF);
    return res;
}

static bool diag_can_filters(uint8_t can_num) {
    bool res = false;
    CAN_TypeDef* can_addr = NULL;
    static const table_col_t cols[] = {
        {5, "num"},    //FA1R
        {5, "active"}, //FA1R
        {7, "mode"},
        {8, "scale"},
        {7, "FIFO"}, //FFA1R
        {12, "bank reg1"},
        {12, "bank reg2"},
        {10, "std1_sta"},
        {10, "std1_end"},
        {10, "std2_sta"},
        {10, "std2_end"},
    };
    can_addr = get_can_reg(can_num);
    if (NULL != can_addr) {
        table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
        bool is_print = false;
        for (uint8_t fi = 0U; fi < 28U; fi++) {
            is_print = is_can_filter_active(can_num, fi);
            if (true == is_print) {
                io_printf(TSEP);
                io_printf(" %3u " TSEP, fi);
                io_printf(" %3u " TSEP, CHECK_BIT_NUM(can_addr->FA1R, fi));
                io_printf(" %5s " TSEP, CHECK_BIT_NUM(can_addr->FM1R, fi) ? "List" : "Mask");
                io_printf(" %u bit " TSEP, CHECK_BIT_NUM(can_addr->FS1R, fi) ? 32 : 16);
                io_printf(" FIFO%u " TSEP, CHECK_BIT_NUM(can_addr->FFA1R, fi));
                io_printf(" 0x%08x " TSEP, can_addr->sFilterRegister[fi].FR1);
                io_printf(" 0x%08x " TSEP, can_addr->sFilterRegister[fi].FR2);
                io_printf("  0x%04x  " TSEP, extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR1, 15, 5));
                io_printf("  0x%04x  " TSEP, extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR1, 31, 21));
                io_printf("  0x%04x  " TSEP, extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR2, 15, 5));
                io_printf("  0x%04x  " TSEP, extract_subval_from_32bit(can_addr->sFilterRegister[fi].FR2, 31, 21));
                io_printf(CRLF);
            }
        }
        table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));
    }
    return res;
}

static bool diag_can_interrupts(uint8_t can_num) {
    bool res = false;
    CAN_TypeDef* can_addr = NULL;
    static const table_col_t cols[] = {
        {5, "num"},
        {4, "Tx"},
        {5, "Err"},
        {8, "Wakeup"},
        {10, "Fifo1Full"},
        {10, "Fifo1Pend"},
        {10, "Fifo0Full"},
        {10, "Fifo0Pend"},
        {9, "Bus-off"},
        {10, "Fifo0Ovrn"},
        {8, "reg"},
        {7, "bin"},
    };

    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));

    for (can_num = 1; can_num <= CAN_CNT; can_num++) {
        can_addr = get_can_reg(can_num);
        io_printf(TSEP);
        io_printf(" %3u " TSEP, can_num);                                     /**/
        io_printf(" %u  " TSEP, 1 == (1 & can_addr->IER));                    /*TMEIE*/
        io_printf("  %u  " TSEP, (1 << 15) == ((1 << 15) & can_addr->IER));   /*ERRIE*/
        io_printf("   %u   " TSEP, (1 << 16) == ((1 << 16) & can_addr->IER)); /*WKUIE*/
        io_printf("   %u   " TSEP, (1 << 5) == ((1 << 5) & can_addr->IER));   /*FFIE1*/
        io_printf("   %u   " TSEP, (1 << 4) == ((1 << 4) & can_addr->IER));   /*FMPIE1*/
        io_printf("   %u   " TSEP, (1 << 2) == ((1 << 2) & can_addr->IER));   /*FFIE0*/
        io_printf("   %u   " TSEP, (1 << 1) == ((1 << 1) & can_addr->IER));   /*FMPIE0*/
        io_printf("   %u   " TSEP, (1 << 10) == ((1 << 10) & can_addr->IER)); /*BOFIE*/
        io_printf("  %u   " TSEP, (1 << 3) == ((1 << 3) & can_addr->IER));    /*FOVIE0*/
        io_printf(" 0x%08x " TSEP, can_addr->IER);                            /**/
        io_printf(" %s " TSEP, utoa_bin32(can_addr->IER));                    /**/
        io_printf(CRLF);
    }
    table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));

    return res;
}

bool can_errors_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = true;
        res = diag_can_errors(0);
    } else {
        LOG_ERROR(SYS, "Uasege: cad can_num");
    }
    return res;
}

bool can_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = true;
        uint8_t can_num = 1;
        if (true == res) {
            res = try_str2uint8(argv[0], &can_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[0]);
            }
        }

        res = diag_can(can_num);
    } else {
        LOG_ERROR(SYS, "Uasege: cad");
    }
    return res;
}

bool can_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (3 == argc) {
        res = true;
        uint8_t can_num = 1;
        can_rx_frame_t frame;
        if (true == res) {
            res = try_str2uint8(argv[0], &can_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[0]);
            }
        }
        if (true == res) {
            res = try_str2uint32(argv[1], &frame.id);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract ID %s", argv[1]);
            }
        }
        if (true == res) {
            res = try_str2uint64(argv[2], &frame.can_data.data64);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract data %s", argv[2]);
            }
        }
        if (true == res) {
            res = can_send(can_num, frame);
        }
    } else {
        LOG_ERROR(SYS, "Uasege: cad can_num");
    }
    return res;
}

bool can_filter_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (1 == argc) {
        res = true;
        uint8_t can_num = 1;
        if (true == res) {
            res = try_str2uint8(argv[0], &can_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[0]);
            }
        }
        res = diag_can_filters(can_num);
    } else if (0 == argc) {
        res = true;
        res = diag_can_filters(0) && res;
        res = diag_can_filters(1) && res;
        res = diag_can_filters(2) && res;
    } else {
        LOG_ERROR(SYS, "Uasege: cf can_num");
    }
    return res;
}

bool can_interrupts_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = true;
        res = diag_can_interrupts(0);
    } else {
        LOG_ERROR(SYS, "Uasege: cad can_num");
    }
    return res;
}

bool can_check_id_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t can_num = 1;
    if (1 <= argc) {
        if (true == res) {
            res = try_str2uint8(argv[0], &can_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[0]);
            }
        }
    }
    if (2 == argc) {
        res = true;
        uint16_t std_id = 0;
        if (true == res) {
            res = try_str2uint16(argv[1], &std_id);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[1]);
            }
        }
        res = is_std_id_allowed(can_num, std_id);
        io_printf("ID 0x%x %s" CRLF, std_id, res ? "Allowed" : "Ignored");

    } else if (1 == argc) {
        res = print_allow_id(can_num);
    } else {
        LOG_ERROR(SYS, "Uasege: cid can_num std_id");
    }
    return res;
}

bool can_filter_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (2 == argc) {
        res = true;
        uint8_t can_num = 1;
        if (true == res) {
            res = try_str2uint8(argv[0], &can_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[0]);
            }
        }
        uint16_t std_id = 0;
        if (true == res) {
            res = try_str2uint16(argv[1], &std_id);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[1]);
            }
        }
        res = add_id_to_list_filter(can_num, std_id);
        if (true == res) {
            io_printf("set ID 0x%x " CRLF, std_id);
        }
    } else {
        LOG_ERROR(SYS, "Uasege: cid can_num std_id");
    }
    return res;
}

bool can_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (1 == argc) {
        res = true;
        uint8_t can_num = 1;
        if (true == res) {
            res = try_str2uint8(argv[0], &can_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract can_num %s", argv[0]);
            }
        }

        res = can_reset(can_num);
        if (true == res) {
            io_printf("can %u reset ok " CRLF, can_num);
        }
    } else {
        LOG_ERROR(SYS, "Uasege: cid can_num std_id");
    }
    return res;
}