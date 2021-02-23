#include "iwdg.h"
#include "watchdog.h"
#include "log.h"
#include "device.h"

#define RUNNING_UNDER_DEBUG (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)

#define HardWareWdtToggle()             HAL_GPIO_TogglePin(WDI_GPIO_Port, WDI_Pin)

void wdt_reset_all (void) {
    HAL_IWDG_Refresh (&hiwdg);

#ifdef HARDWARE_WDT
    HardWareWdtToggle();
#endif
}

#ifdef HARDWARE_WDT
void HardWareWdtEnable(bool status) {
    if (status) {
//        if (RUNNING_UNDER_DEBUG) {
//            LOG_WARNING(SYS, "Run under debug. Don't init watchdog (DHCSR=%08lX)", CoreDebug->DHCSR);
//        } else {
            LOG_INFO(SYS,"Enable hardware WDT");
            HAL_GPIO_WritePin (WDI_OE_GPIO_Port, WDI_OE_Pin, GPIO_PIN_RESET);
//        }
    } else {
        LOG_INFO(SYS,"Disable hardware WDT");
        HAL_GPIO_WritePin (WDI_OE_GPIO_Port, WDI_OE_Pin, GPIO_PIN_SET);
    }
}
#endif
