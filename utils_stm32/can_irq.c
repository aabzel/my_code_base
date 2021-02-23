#include "can_driver.h"
#include "can_irq.h"

#ifdef HAS_IPP_CAN1
void CAN1_TX_IRQHandler(void) {
    can_irq_tx(&can1);
}
void CAN1_RX0_IRQHandler(void) {
    can_irq_rx0(&can1);
}
void CAN1_SCE_IRQHandler(void) {
    can_irq_error(&can1, 1);
}
void CAN1_RX1_IRQHandler(void) {
    can_irq_rx1(&can1);
}
#endif

#ifdef HAS_IPP_CAN2
void CAN2_TX_IRQHandler(void) {
    can_irq_tx(&can2);
}
void CAN2_SCE_IRQHandler(void) {
    can_irq_error(&can2, 2);
}
void CAN2_RX0_IRQHandler(void) {
    can_irq_rx0(&can2);
}
void CAN2_RX1_IRQHandler(void) {
    can_irq_rx1(&can2);
}
#endif
