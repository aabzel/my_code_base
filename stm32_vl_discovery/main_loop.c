#include "main_loop.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "board.h"
#include "device.h"
#include "uarts.h"
//#include "iwdg.h"*/


#include "task_info.h"

#include "log.h"
#include "rx_uart.h"
#include "rx_io.h"
#include "convert.h"
#include "gpio.h"
#include "uarts.h"


#define LED_OFF     0
#define LED_ON      1



#if 0
static void task_led1(void);
static void task_indication(void);
static void task_inputs(void);
static void task_dump_state(void);
static void dump_state(void);
static void task_aeth(void);
static void task_reth(void);
#endif


uint32_t g_iteration_cnt;

static void task_led1(void)
{

     HAL_GPIO_TogglePin (LD4_GPIO_Port, LD4_Pin);

}


int main_loop(void) {
	g_iteration_cnt = 0;

    configureTimerForRunTimeStats ();
    uarts_init ();
    //start_banner ();
    //print_detected_board_type ();

    set_log_level (SYS, LOG_LEVEL_DEBUG);
    set_log_level (CAN, LOG_LEVEL_CRITICAL);

    LOG_NOTICE(SYS, "FW started");
    LOG_DEBUG(SYS, "g_iteration_cnt %p",&g_iteration_cnt);

    for (;;) {
        MAIN_LOOP_START;
        MEASURE_TASK_INTERVAL(UART, 20, process_uarts);
        /* Toggle LED1 once per second */
        MEASURE_TASK_INTERVAL(LED1, 1000000u,   task_led1);
        g_iteration_cnt++;
    }
    return 0;
}

