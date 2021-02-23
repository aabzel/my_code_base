#include "can_driver.h"
#include "log.h"
#include "sections.h"

#define CAN_ERROR_REPORT_INTERVAL 1000

static NOINIT can_message_t can_rx_queue_data [CAN_RX_QUEUE_SIZE] CORE2_MEM;
fifo_can_t can_rx_queue = FIFO_CAN_INIT(CAN_RX_QUEUE_SIZE, can_rx_queue_data);

uint8_t can_number_map [MAX_CAN_NUMBER] =
    {
#ifdef HAS_CAN1
        1,
#endif
#ifdef HAS_CAN2
        2,
#endif
    };

can_device_t* can_device_map [MAX_CAN_NUMBER] =
    {
#ifdef HAS_CAN1
        &can1,
#endif
#ifdef HAS_CAN2
        &can2,
#endif
    };

const char* lec2str (can_lec_t lec) {
    const char* result;
    switch (lec) {
        case lec_No_Error:
            result = "NO_ERROR";
            break;
        case lec_Stuff_Error:
            result = "STUFF";
            break;
        case lec_Form_Error:
            result = "FORM";
            break;
        case lec_Acknowledgment_Error:
            result = "ACKNOWLEDGMENT";
            break;
        case lec_Bit_recessive_Error:
            result = "BIT_RECESSIVE";
            break;
        case lec_Bit_dominant_Error:
            result = "BIT_DOMINANT";
            break;
        case lec_CRC_Error:
            result = "CRC_ERROR";
            break;
        case lec_Reset:
            result = "NONE";
            break;
        default:
            result = "???";
            break;
    }
    return result;
}

bool can_queue_empty (const can_device_t* hcan) {
    if (fifo_can_get_used(&hcan->fifo) == 0) {
        return true;
    }
    return false;
}

can_device_t* can_device_by_number (uint8_t number) {
#if defined(HAS_CAN1)
    if (number == 1) {
        return &can1;
    }
#endif
#if defined(HAS_CAN2)
    if (number == 2) {
        return &can2;
    }
#endif
    LOG_WARNING (CAN, "Unknown CAN number - %d", number);
    return NULL;
}

bool can_transmit_n (const can_message_t* msg) {
    if (can_valid_n(msg->can_number)) {
        return can_transmit (can_device_by_number (msg->can_number), msg);
    } else {
        return false;
    }
}

bool can_transmit_to_can_n (uint8_t can_number) {
    if (can_valid_n(can_number)) {
        return can_transmit_to_can (can_device_by_number (can_number));
    } else {
        return false;
    }
}

bool can_transmit_to_can (const can_device_t* hcan) {
    if (hcan == NULL) {
        return false;
    }
    if (can_busoff (hcan)) {
        return false;
    }
    if (fifo_can_get_used(&hcan->fifo) >= fifo_can_get_size(&hcan->fifo)) {
        return false;
    }
    return true;
}

void can_report_errors (void) {
    static uint64_t next_error_report;
    uint64_t now = get_time_ms64 ();
    if (next_error_report < now) {
#if defined(HAS_CAN1)
        can_report_error_info (&can1);
#endif
#if defined(HAS_CAN2)
        can_report_error_info(&can2);
#endif
        next_error_report += CAN_ERROR_REPORT_INTERVAL ;
    }
}

can_device_t* get_first_can(void) {
#if defined(HAS_CAN1)
        return &can1;
#else
#if defined(HAS_CAN2)
        return &can2;
#else
#endif /* HAS_CAN2 */
#endif /* HAS_CAN1 */
}

bool can_valid_n(int can_number) {
    bool res = false;
    switch (can_number) {
#ifdef HAS_CAN1
    case 1:
        res=true;
        break;
#endif

#ifdef HAS_CAN2
    case 2:
        res=true;
        break;
#endif

        default:
            break;
    }
    return res;
}
