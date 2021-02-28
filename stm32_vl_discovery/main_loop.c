#include "main_loop.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "device.h"
#include "uarts.h"
//#include "iwdg.h"*/

#include "task_info.h"

#include "convert.h"
#include "gpio.h"
#include "log.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "uarts.h"

#define LED_OFF 0
#define LED_ON 1
