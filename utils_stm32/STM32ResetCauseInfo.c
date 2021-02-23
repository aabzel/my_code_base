#include "stm32f1xx_hal.h"
#include "STM32ResetCauseInfo.h"
#include "log.h"

uint32_t GetResetCauseInfo(void) {
    uint32_t ResetCause = RCC->CSR;
    RCC->CSR |= RCC_CSR_RMVF | RCC_CSR_PORRSTF;

    return ResetCause;
}

void ReportResetCause(void) {
    uint32_t ResetCause=GetResetCauseInfo();

    if (ResetCause & RCC_CSR_LPWRRSTF) {
        LOG_WARNING (SYS, "Low-power management reset occurs");
    }

    if (ResetCause & RCC_CSR_WWDGRSTF) {
        LOG_WARNING (SYS, "Window watchdog reset occurs");
    }

    if (ResetCause & RCC_CSR_WDGRSTF) {
        LOG_WARNING (SYS, "Independent watchdog reset from VDD domain occurs");
    }

    if (ResetCause & RCC_CSR_SFTRSTF) {
        LOG_WARNING (SYS, "Software reset occurs");
    }

    if (ResetCause & RCC_CSR_PORRSTF) {
        LOG_WARNING (SYS, "POR/PDR reset occurs");
    }

    if (ResetCause & RCC_CSR_PADRSTF) {
        LOG_WARNING (SYS, "Reset from the NRST pin occurs");
    }
}
