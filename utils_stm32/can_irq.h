#ifndef UTILS_CAN_IRQ_H_
#define UTILS_CAN_IRQ_H_

#ifdef CUBEMX
#include "cubemx.h"
#endif

#ifdef HAS_IPP_CAN1
void CAN1_TX_IRQHandler(void);
void CAN1_SCE_IRQHandler(void);
void CAN1_RX1_IRQHandler(void);
void CAN1_RX0_IRQHandler(void);
void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
#endif

#ifdef HAS_IPP_CAN2
void CAN2_TX_IRQHandler(void);
void CAN2_SCE_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
void CAN2_RX1_IRQHandler(void);
#endif

#endif /* UTILS_CAN_IRQ_H_ */
