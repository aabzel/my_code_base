#include "can_driver.h"

#include <stddef.h>

#include "bit_utils.h"
#include "stm32f4xx.h"
#include "sys.h"
#include "vega_can_typedefs.h"

CanStatistic_t CanStat[CAN_CNT] = {0};

CAN_TypeDef* get_can_reg(uint8_t can_num) {
    CAN_TypeDef* addr = NULL;
    switch (can_num) {
        case 1:
            addr = CAN1;
            break;
        case 2:
            addr = CAN2;
            break;
        case 3:
            addr = CAN3;
            break;
        default:
            addr = NULL;
            break;
    }
    return addr;
}

bool is_can_filter_active(uint8_t can_num, uint8_t filter_num) {
    bool res = false;
    CAN_TypeDef* CANx = NULL;
    CANx = get_can_reg(can_num);
    if (NULL != CANx) {
        if (filter_num <= 27) {
            if ((1 << filter_num) == ((1 << filter_num) & (CANx->FA1R))) {
                res = true;
            }
        }
    }
    return res;
}

float can_calc_bit_rate(uint32_t can_btr) {
    float bit_rate = 0.0f;
    float t_bit = 0.0f;
    t_bit = can_calc_bit_time(can_btr);
    bit_rate = 1.0f / t_bit;
    return bit_rate;
}

float can_calc_bit_time(uint32_t can_btr) {
    float t_bit = 0.0f;
    float tpclk = 1.0f / ((float)APB1_CLOCK_HZ);
    uint16_t baud_rate_prescaler = 0;
    baud_rate_prescaler = (uint16_t)extract_subval_from_32bit(can_btr, 9, 0);
    float tq = ((float)(baud_rate_prescaler + 1)) * tpclk;
    uint8_t ts1 = (uint8_t)extract_subval_from_32bit(can_btr, 19, 16);
    uint8_t ts2 = (uint8_t)extract_subval_from_32bit(can_btr, 22, 20);
    tq = tq * ((float)(extract_subval_from_32bit(can_btr, 25, 24) + 1));
    float t_bs1 = tq * ((float)(ts1 + 1));
    float t_bs2 = tq * ((float)(ts2 + 1));

    t_bit = tq + t_bs1 + t_bs2;
    return t_bit;
}

CanTxMsg can_frame_to_spl_frame(can_rx_frame_t frame) {
    CanTxMsg spl_meg;
    spl_meg.DLC = frame.dlen;
    spl_meg.StdId = frame.id;
    memcpy(&spl_meg.Data[0], &frame.can_data.data[0], 8);
    return spl_meg;
}

bool can_send(uint8_t can_num, can_rx_frame_t frame) {
    bool res = false;
    CAN_TypeDef* CANx = NULL;
    CANx = get_can_reg(can_num);
    if (NULL != CANx) {
        CanTxMsg spl_meg = can_frame_to_spl_frame(frame);
        CAN_Transmit(CANx, &spl_meg);
    }
    return res;
}

bool is_std_id_allowed(uint8_t can_num, uint16_t std_id) {
    bool res = false;
    CAN_TypeDef* CANx = NULL;
    CANx = get_can_reg(can_num);
    if (NULL != CANx) {
        for (uint8_t fi = 0U; fi < 28U; fi++) {
            uint16_t read_std_id;
            if ((1U << fi) == ((1U << fi) & CANx->FM1R)) {
                read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fi].FR1, 15, 5);
                if (std_id == read_std_id) {
                    res = true;
                    break;
                }
                read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fi].FR1, 31, 21);
                if (std_id == read_std_id) {
                    res = true;
                    break;
                }
                read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fi].FR2, 15, 5);
                if (std_id == read_std_id) {
                    res = true;
                    break;
                }
                read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fi].FR2, 31, 21);
                if (std_id == read_std_id) {
                    res = true;
                    break;
                }
            }
        }
    }
    return res;
}

#define FMR_FINIT ((uint32_t)0x00000001) /* Filter init mode */
bool can_add_id_in_list_filter(CAN_TypeDef* CANx,
                               uint8_t fil_bank_num,
                               uint8_t can_filter_fifo,
                               uint8_t can_filtermode,
                               uint8_t can_filterscale, uint16_t std_id) {
    bool res = true;
    CANx->FMR |= FMR_FINIT;
    if (CAN_Filter_FIFO0 == can_filter_fifo) {
        RESET_BIT_NUM(CANx->FS1R, fil_bank_num);
    } else if (CAN_Filter_FIFO1 == can_filter_fifo) {
        SET_BIT_NUM(CANx->FS1R, fil_bank_num);
    } else {
        res = false;
    }

    if (true == res) {
        if (CAN_FilterMode_IdList == can_filtermode) {
            SET_BIT_NUM(CANx->FM1R, fil_bank_num);
        } else if (CAN_FilterMode_IdMask == can_filtermode) {
            RESET_BIT_NUM(CANx->FM1R, fil_bank_num);
        } else {
            res = false;
        }
    }
    if (true == res) {
        if (CAN_FilterScale_16bit == can_filterscale) {
            RESET_BIT_NUM(CANx->FS1R, fil_bank_num);
        } else if (CAN_FilterScale_32bit == can_filterscale) {
            SET_BIT_NUM(CANx->FS1R, fil_bank_num);
        } else {
            res = false;
        }
    }
    if (true == res) {
        CANx->sFilterRegister[fil_bank_num].FR1 = insert_subval_in_32bit(CANx->sFilterRegister[fil_bank_num].FR1,
                                                                         std_id, 31, 21);
    }
    CANx->FMR &= ~FMR_FINIT;
    return res;
}

static bool update_list_16b_filter(CAN_TypeDef* CANx,
                                   uint8_t fil_bank_num,
                                   uint16_t std_id) {
    bool res = true;
    if (28 <= fil_bank_num) {
        res = false;
    }

    if (0 == CHECK_BIT_NUM(CANx->FM1R, fil_bank_num)) {
        res = false;
    }

    if (1 == CHECK_BIT_NUM(CANx->FS1R, fil_bank_num)) {
        res = false;
    }
    if (true == res) {
        CANx->FMR |= FMR_FINIT;
        res = false;
        uint32_t read_std_id;
        if (false == res) {
            read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fil_bank_num].FR1, 31, 21);
            if (0 == read_std_id) {
                CANx->sFilterRegister[fil_bank_num].FR1 = insert_subval_in_32bit(CANx->sFilterRegister[fil_bank_num].FR1, std_id, 31, 21);
                res = true;
            }
        }
        if (false == res) {
            read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fil_bank_num].FR1, 15, 5);
            if (0 == read_std_id) {
                CANx->sFilterRegister[fil_bank_num].FR1 = insert_subval_in_32bit(CANx->sFilterRegister[fil_bank_num].FR1, std_id, 15, 5);
                res = true;
            }
        }
        if (false == res) {
            read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fil_bank_num].FR2, 31, 21);
            if (0 == read_std_id) {
                CANx->sFilterRegister[fil_bank_num].FR2 = insert_subval_in_32bit(CANx->sFilterRegister[fil_bank_num].FR2, std_id, 31, 21);
                res = true;
            }
        }
        if (false == res) {
            read_std_id = extract_subval_from_32bit(CANx->sFilterRegister[fil_bank_num].FR2, 15, 5);
            if (0 == read_std_id) {
                CANx->sFilterRegister[fil_bank_num].FR2 = insert_subval_in_32bit(CANx->sFilterRegister[fil_bank_num].FR2, std_id, 15, 5);
                res = true;
            }
        }
        CANx->FMR &= ~FMR_FINIT;
    }
    return res;
}

bool add_id_to_list_filter(uint8_t can_num, uint16_t std_id) {
    bool res = false;
    CAN_TypeDef* CANx = NULL;
    res = is_std_id_allowed(can_num, std_id);
    if (false == res) {
        CANx = get_can_reg(can_num);
        for (uint8_t fil_bank_num = 0U; fil_bank_num < 28U; fil_bank_num++) {
            res = is_can_filter_active(can_num, fil_bank_num);
            if (false == res) {
                res = can_add_id_in_list_filter(CANx, fil_bank_num, CAN_Filter_FIFO0, CAN_FilterMode_IdList, CAN_FilterScale_16bit, std_id);
                CANx->FA1R |= (1 << fil_bank_num);
                break;
            } else {
                res = update_list_16b_filter(CANx, fil_bank_num, std_id);
                if (true == res) {
                    break;
                }
            }
        }
    }
    return res;
}

bool can_reset(uint8_t can_num) {
    bool res = false;
    CAN_TypeDef* CANx = NULL;
    CANx = get_can_reg(can_num);
    if (CANx) {
        SET_BIT_NUM(CANx->MCR, 15);
        res = true;
    }
    return res;
}