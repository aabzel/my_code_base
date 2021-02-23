#include <inttypes.h>
#include "can_driver.h"
#include "rx_io.h"
#include "log.h"
#include "convert.h"

#if defined(HAS_IPP_CAN) || defined(HAS_IPP_CAN1)
can_message_t can1_data [CAN_TX_QUEUE_SIZE];
can_device_t can1 = {
    &hcan1,
    1,
    500,
    FIFO_CAN_INIT(RX_ARRAY_SIZE(can1_data),can1_data),
    0,
    0,
    0,
    0,
    0,
    0,
    false, ERROR_INFO_INIT};
#endif

#if defined(HAS_IPP_CAN2)
can_message_t can2_data [CAN_TX_QUEUE_SIZE];
can_device_t can2 = {
    &hcan2,
    2,
    500,
    FIFO_CAN_INIT(RX_ARRAY_SIZE(can2_data),can2_data),
    0,
    0,
    0,
    0,
    0,
    0,
    false, ERROR_INFO_INIT};
#endif

static void move_to_mailbox(can_device_t *hcan, const can_message_t *msg) {
    uint32_t tir;
    if (msg->id & CANID_EXTENDED_FLAG) {
        tir = ((msg->id & CANID_MASK) << 3) | CAN_TI0R_IDE;
    } else {
        tir = msg->id << 21;
    }
    CAN_TxMailBox_TypeDef *tmbp = &hcan->can_handle->Instance->sTxMailBox [(hcan->can_handle->Instance->TSR & CAN_TSR_CODE) >> 24];
    tmbp->TDTR = msg->dlc;
    const uint32_t* w32=(const uint32_t* )msg->data;
    tmbp->TDLR = w32 [0];
    tmbp->TDHR = w32 [1];
    tmbp->TIR = tir | CAN_TI0R_TXRQ;
}

static void move_to_mailbox_(can_device_t *hcan, int mailbox, const can_message_t *msg) {
    uint32_t tir;
    if (msg->id & CANID_EXTENDED_FLAG) {
        tir = ((msg->id & CANID_MASK) << 3) | CAN_TI0R_IDE;
    } else {
        tir = msg->id << 21;
    }
    CAN_TxMailBox_TypeDef *tmbp = &hcan->can_handle->Instance->sTxMailBox [mailbox];
    tmbp->TDTR = msg->dlc;
    const uint32_t* w32=(const uint32_t* )msg->data;
    tmbp->TDLR = w32 [0];
    tmbp->TDHR = w32 [1];
    tmbp->TIR = tir | CAN_TI0R_TXRQ;
}

static inline bool has_empty_tx_mailbox(const can_device_t *hcan) {
    return (hcan->can_handle->Instance->TSR & CAN_TSR_TME) != 0;
}

bool can_has_empty_tx_mailbox(const can_device_t *hcan) {
    return (hcan->can_handle->Instance->TSR & CAN_TSR_TME) != 0;
}


bool can_tx_mailboxes_empty(const can_device_t *hcan) {
    return ((hcan->can_handle->Instance->TSR & CAN_TSR_TME) == CAN_TSR_TME);
}

bool can_transmit(can_device_t *hcan, const can_message_t* msg) {
    if (hcan == NULL) {
        return false;
    }
    enter_critical ();
    if (has_empty_tx_mailbox (hcan)) {
        move_to_mailbox (hcan, msg);
        hcan->tx_count++;
        exit_critical ();
        return true;
    } else {
        exit_critical ();
        return fifo_can_add(&hcan->fifo, msg);
    }
}

bool can_transmit_force(can_device_t *hcan, const can_message_t* msg) {
    if (hcan == NULL) {
        return false;
    }
    enter_critical ();
    move_to_mailbox_(hcan, 0, msg);
    move_to_mailbox_(hcan, 1, msg);
    move_to_mailbox_(hcan, 2, msg);
    hcan->tx_count++;
    exit_critical ();
    return true;
 }


void can_irq_tx(can_device_t *hcan) {
    /* No more events until a message is transmitted.*/
    hcan->can_handle->Instance->TSR = CAN_TSR_RQCP0 | CAN_TSR_RQCP1 | CAN_TSR_RQCP2;
    while (has_empty_tx_mailbox (hcan) && (fifo_can_get_used(&hcan->fifo) !=0)) {
        const can_message_t* msg = fifo_can_get (&hcan->fifo);
        move_to_mailbox (hcan, msg);
        fifo_can_free1 (&hcan->fifo);
        hcan->tx_count++;
    }
}

static void can_fetch_receive(can_device_t *hcan, int fifo) {
    can_message_t msg;
    uint32_t rir, rdtr;
    CAN_TypeDef * dev = hcan->can_handle->Instance;
    msg.can_number = hcan->number;
    uint32_t* w32=(uint32_t* )msg.data;
    switch (fifo) {
        case 0:
            rir = dev->sFIFOMailBox [0].RIR;
            rdtr = dev->sFIFOMailBox [0].RDTR;
            w32 [0] = dev->sFIFOMailBox [0].RDLR;
            w32 [1] = dev->sFIFOMailBox [0].RDHR;
            /* Releases the mailbox.*/
            dev->RF0R = CAN_RF0R_RFOM0;
            break;
        case 2:
            /* Fetches the message.*/
            rir = dev->sFIFOMailBox [1].RIR;
            rdtr = dev->sFIFOMailBox [1].RDTR;
            w32 [0] = dev->sFIFOMailBox [1].RDLR;
            w32 [1] = dev->sFIFOMailBox [1].RDHR;

            /* Releases the mailbox.*/
            dev->RF1R = CAN_RF1R_RFOM1;
            break;
        default:
            /* Should not happen, do nothing.*/
            return;
    }

    /* Decodes the various fields in the RX frame.*/
    if (rir & CAN_RI0R_IDE) {
        msg.id = (rir >> 3) | CANID_EXTENDED_FLAG;
    } else {
        msg.id = (rir & CAN_RI0R_STID) >> 21;
    }
    msg.dlc = rdtr & CAN_RDT0R_DLC;
    if (!fifo_can_add (&can_rx_queue, &msg)) {
        hcan->rx_queue_full_count++;
    } else {
        hcan->rx_count++;
    }
}

void can_irq_rx0(can_device_t *hcan) {
    while ((hcan->can_handle->Instance->RF0R & CAN_RF0R_FMP0) > 0) {
        (can_fetch_receive (hcan, 0));
    }
    if ((hcan->can_handle->Instance->RF0R & CAN_RF0R_FOVR0) > 0) {
        /* Overflow events handling.*/
        hcan->can_handle->Instance->RF0R = CAN_RF0R_FOVR0;
        hcan->rx_overflow_count++;
    }
}

void can_irq_rx1(can_device_t *hcan) {
    while ((hcan->can_handle->Instance->RF1R & CAN_RF1R_FMP1) > 0) {
        (can_fetch_receive (hcan, 1));
    }
    if ((hcan->can_handle->Instance->RF1R & CAN_RF1R_FOVR1) > 0) {
        /* Overflow events handling.*/
        hcan->can_handle->Instance->RF1R = CAN_RF1R_FOVR1;
        hcan->rx_overflow_count++;
    }
}

typedef union {
    uint32_t val;
    struct {
        bool ewgf :1;
        bool epvf :1;
        bool boff :1;
        bool reserved_1 :1;
        uint8_t lec :3;
        uint8_t reserved_2;
        uint8_t tec;
        uint8_t rec;
    };
} can_esr_t;

static inline int8_t get_can_number(const can_device_t *cand) {
    if (cand == &can1) {
        return 1;
    } else {
        return 2;
    }
}

void can_irq_error(can_device_t *hcand, int can_number) {
    uint32_t msr = hcand->can_handle->Instance->MSR;
    hcand->can_handle->Instance->MSR = CAN_MSR_ERRI | CAN_MSR_WKUI | CAN_MSR_SLAKI;
    /* Wakeup event.*/
    if (msr & CAN_MSR_WKUI) {
        hcand->can_handle->Instance->MCR &= ~CAN_MCR_SLEEP;
    }
    /* Error event.*/
    if (msr & CAN_MSR_ERRI) {
        can_esr_t esr;
        //static uint32_t prev_esr;
        esr.val = hcand->can_handle->Instance->ESR;
        hcand->can_handle->Instance->ESR = 0;
        hcand->error_count++;
        if ((hcand->can_handle->Instance->TSR & CAN_TSR_TERR0) > 0) {
            hcand->can_handle->Instance->TSR |= CAN_TSR_ABRQ0;
            LOG_ERROR (CAN, "CAN%d abort msg 0", can_number);
            hcand->tx_count++;
        }
        if ((hcand->can_handle->Instance->TSR & CAN_TSR_TERR1) > 0) {
            hcand->can_handle->Instance->TSR |= CAN_TSR_ABRQ1;
            LOG_ERROR (CAN, "CAN%d abort msg 1", can_number);
            hcand->tx_count++;
        }
        if ((hcand->can_handle->Instance->TSR & CAN_TSR_TERR2) > 0) {
            hcand->can_handle->Instance->TSR |= CAN_TSR_ABRQ2;
            LOG_ERROR (CAN, "CAN%d abort msg 2", can_number);
            hcand->tx_count++;
        }
        if (is_printf_clean ()) {
            LOG_ERROR (
                CAN,
                "CAN%d ewgf=%u epvf=%u boff=%u lec=%s tec=%u rec=%u",
                can_number,
                esr.ewgf,
                esr.epvf,
                esr.boff,
                lec2str ((can_lec_t) esr.lec),
                esr.tec,
                esr.rec);
        }
    }
}

bool can_busoff (const can_device_t* hcan) {
    return ((hcan->can_handle->Instance->ESR & CAN_ESR_BOFF) == CAN_ESR_BOFF);
}

static inline int get_prescaler_42(int speed) {
    switch (speed) {
        case 125:
            return 24;
        case 250:
            return 12;
        case 500:
            return 6;
        case 1000:
            return 3;
        default:
            return 0;
    }
}

static inline int get_prescaler_36(int speed) {
    switch (speed) {
        case 125:
            return 32;
        case 250:
            return 16;
        case 500:
            return 8;
        case 1000:
            return 4;
        default:
            return 0;
    }
}

bool can_set_speed(can_device_t* hcand, int new_speed, bool loopback) {
    int can_number = get_can_number (hcand);
    HAL_CAN_DeInit (hcand->can_handle);

    switch (HAL_RCC_GetPCLK1Freq ()) {
        case 36000000:
			if(get_prescaler_36(new_speed) == 0)
			{
				LOG_ERROR(CAN, "Unknown CAN speed %d. Can't set CAN%d speed", new_speed, can_number);
				return false;
			}
			hcand->can_handle->Init.Prescaler = get_prescaler_36(new_speed);
			hcand->can_handle->Init.BS1 = CAN_BS1_6TQ;
			hcand->can_handle->Init.BS2 = CAN_BS2_2TQ;
			break;
        case 42000000:
			if(get_prescaler_42(new_speed) == 0)
			{
				LOG_ERROR(CAN, "Unknown CAN speed %d. Can't set CAN%d speed", new_speed, can_number);
				return false;
			}
			hcand->can_handle->Init.Prescaler = get_prescaler_42(new_speed);
			hcand->can_handle->Init.BS1 = CAN_BS1_11TQ;
			hcand->can_handle->Init.BS2 = CAN_BS2_2TQ;
			break;
        default:
			LOG_ERROR(CAN, "Unknown PCLK1 frequency %lu. Can't set CAN%d speed", HAL_RCC_GetPCLK1Freq (), can_number);
			return false;
    }

    hcand->can_handle->Init.Mode = loopback ? CAN_MODE_SILENT_LOOPBACK : CAN_MODE_NORMAL;
    HAL_CAN_Init (hcand->can_handle);
    HAL_StatusTypeDef status;
    if ((status = HAL_CAN_WakeUp (hcand->can_handle)) != HAL_OK) {
        LOG_ERROR(
                CAN,
                "CAN%d can't wakeup. Status=%d, Can State=%d error-code=%" PRIu32,
                can_number,
                status,
                hcand->can_handle->State,
                hcand->can_handle->ErrorCode);
        return false;
    }
    hcand->can_handle->Instance->IER = CAN_IER_TMEIE | CAN_IER_FMPIE0 | CAN_IER_FMPIE1 | CAN_IER_WKUIE | CAN_IER_ERRIE | CAN_IER_LECIE | CAN_IER_BOFIE
            | CAN_IER_EPVIE | /*CAN_IER_EWGIE | */CAN_IER_FOVIE0 | CAN_IER_FOVIE1;
    hcand->speed = new_speed;
    LOG_INFO (CAN, "Set CAN%d speed to %d, loopback mode %s", can_number, new_speed, loopback ? "on" : "off");
    return true;
}

static void set_default_filter(void) {
    CAN_FilterConfTypeDef sFilterConfig;
    HAL_StatusTypeDef status;

    sFilterConfig.FilterNumber = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.BankNumber = 14;

    if ((status = HAL_CAN_ConfigFilter (&hcan1, &sFilterConfig)) != HAL_OK) {
        LOG_ERROR(CAN, "%s: can't init filter. Status=%d, Can State=%d error-code=%" PRIu32, "CAN1", status, hcan1.State, hcan1.ErrorCode);
    }

#ifdef HAS_IPP_CAN2
    /*##-2- Configure the CAN Filter ###########################################*/
    sFilterConfig.FilterNumber = 14;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.BankNumber = 14;
    if ((status = HAL_CAN_ConfigFilter (&hcan1, &sFilterConfig)) != HAL_OK) {
        LOG_ERROR(CAN, "%s: can't init filter. Status=%d, Can State=%d error-code=%" PRIu32, "CAN2", status, hcan1.State, hcan1.ErrorCode);
    }
#endif
}

const table_col_t* can_registers_cols(void) {
    static const table_col_t cols [] =
    {
        {   4, "CAN"},
        {   10, "BTR"},
        {   10, "MCR"},
        {   10, "MSR"},
        {   10, "IER"},
        {   10, "ESR"},
        {   10, "TSR"},
        {   0, NULL},
    };
    return cols;
}

void RX_CAN_Init(void) {
#ifdef HAS_IPP_CAN1
    can_set_speed (&can1, can1.speed, false);
#endif
#ifdef HAS_IPP_CAN2
    can_set_speed (&can2, can2.speed, false);
#endif
    set_default_filter ();
}

void can_report_error_info (can_device_t* canp) {
}

