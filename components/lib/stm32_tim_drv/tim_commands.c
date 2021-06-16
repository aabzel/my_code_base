#include "tim_commands.h"

#include "convert.h"
#include "data_utils.h"
#include "io_utils.h"
#include "log.h"
#include "rtc_driver.h"
/*#include "soft_timers.h"*/
#include "stm32f4xx_it.h"
#include "sys.h"
#include "table_utils.h"
#include "tim.h"
#include "time_utilities.h"

extern uint32_t GetSecondsFromStartup(void);
static bool diag_page_time(void) {
    char buff[50] = "";
    uint32_t time_stamp = GetUnixTime();
    uint32_t up_time = GetSecondsFromStartup();
    time_struct_t time;
    io_printf("time_stamp: %u s" CRLF, time_stamp);
    conv_unixtime_to_time(&time, time_stamp);
    io_printf("up_time: %u s" CRLF, up_time);
    io_printf("time: [day/mom/year][h:m:s]" CRLF);
    snprintf((char*)buff, sizeof(buff), "[%d/%d/%d][%d:%d:%d]", time.day,
             time.mon, time.year, time.hour, time.min, time.sec);
    io_printf("time: %s" CRLF, buff);

    return true;
}

bool time_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = diag_page_time();
    }
    return res;
}

bool diag_page_tim() {
    io_printf("sys tick val %u " CRLF, SysTickReg);
    static const table_col_t cols[] = {
        {5, "Num"},
        {4, "En"},
        {7, "psc"},
        {7, "period"},
        {7, "cnt"},
        {6, "dir"},
        {6, "bus"},
        {11, "period,s"},
        {11, "max peri"},
    };
    uint8_t status = 0;
    uint16_t cnt16 = 0;
    uint8_t tim_num = 0;
    uint16_t prescaler = 0;
    uint16_t period = 0;
    float period_real = 0.0f;
    float period_max = 0.0f;
    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
    float fck;
    float t_psc;
    float tf;
    for (tim_num = 1; tim_num <= HW_TIM_CNT; tim_num++) {
        io_printf(TSEP);
        status = tim_get_status(tim_num);
        cnt16 = tim_get_cnt16(tim_num);
        prescaler = tim_get_prescaler(tim_num);
        period = tim_get_period(tim_num);
        if (1 == TimBusLUT[tim_num - 1]) {
            fck = (float)APB1_CLOCK_HZ;
        } else {
            fck = (float)APB2_CLOCK_HZ;
        }

        tf = 1.0f / fck;
        t_psc = tf * ((float)prescaler);
        period_real = t_psc * ((float)period);
        period_max = calc_tim_max_period(tim_num);

        io_printf(" %02u  " TSEP, tim_num);
        io_printf(" %u  " TSEP, status);
        io_printf(" %05u " TSEP, prescaler);
        io_printf(" %05u " TSEP, period);
        io_printf(" %05u " TSEP, cnt16);
        io_printf(" %04s " TSEP, tim_get_dir(tim_num));
        io_printf(" %04s " TSEP, (1 == TimBusLUT[tim_num - 1]) ? "APB1" : "APB2");
        io_printf("  %7.3f  " TSEP, period_real);
        io_printf("  %7.3f  " TSEP, period_max);
        io_printf(CRLF);
        vTaskDelay(10);
    }
    table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));
    return false;
}

bool tim_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (0 == argc) {
        res = diag_page_tim();
    } else {
    }
    return res;
}
/*
Example: ti 1
 */
bool tim_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (7 == argc) {
        res = true;
        uint8_t tim_num = 0;
        if (true == res) {
            res = try_str2uint8(argv[0], &tim_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract tim_num %s", argv[0]);
            }
        }

        uint32_t period = 0;
        if (true == res) {
            res = try_str2uint32(argv[1], &period);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract period %s", argv[1]);
            }
        }

        uint16_t prescaler = 0;
        if (true == res) {
            res = try_str2uint16(argv[2], &prescaler);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract prescaler %s", argv[2]);
            }
        }

        uint16_t division = 0;
        if (true == res) {
            res = try_str2uint16(argv[3], &division);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract division %s", argv[3]);
            }
        }
        uint16_t counter_mode = 0;
        if (true == res) {
            res = try_str2uint16(argv[4], &counter_mode);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract counter_mode %s", argv[4]);
            }
        }

        uint32_t cnt = 0;
        if (true == res) {
            res = try_str2uint32(argv[5], &cnt);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract cnt %s", argv[5]);
            }
        }

        bool new_state = false;
        if (true == res) {
            res = try_str2bool(argv[6], &new_state);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract new_state %s", argv[6]);
            }
        }

        res = tim_init_ll(tim_num, period, prescaler, division, counter_mode, cnt,
                          new_state);
        if (false == res) {
            LOG_ERROR(SYS, "Unable to init timer");
        }
    } else {
        LOG_ERROR(SYS, "Usage: ti tim_num period prescaler division counter_mode "
                       "cnt new_state");
        LOG_INFO(SYS, "tim_num [1..14]");
        LOG_INFO(SYS, "period [0..0xFFFF]");
        LOG_INFO(SYS, "prescaler [0..0xFFFF]");
        LOG_INFO(SYS, "division [0..0xFFFF]");
        LOG_INFO(SYS, "cnt [0..0xFFFF]");
        LOG_INFO(SYS, "new_state [0 1]");
    }
    return res;
}

bool tim_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (3 == argc) {
        res = true;
        uint8_t tim_num = 0;
        if (true == res) {
            res = try_str2uint8(argv[0], &tim_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract tim_num %s", argv[0]);
            }
        }

        float period = 0;
        if (true == res) {
            res = try_str2float(argv[1], &period);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract period %s", argv[1]);
            }
        }

        float precision = 0;
        if (true == res) {
            res = try_str2float(argv[2], &precision);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract precision %s", argv[2]);
            }
        }

        res = tim_set(tim_num, period, precision);
        if (false == res) {
            LOG_ERROR(SYS, "Unable to set timer");
        }
    } else {
        LOG_ERROR(SYS, "Usage: ts tim_num period precision");
        LOG_INFO(SYS, "tim_num [1..14]");
        LOG_INFO(SYS, "period s");
        LOG_INFO(SYS, "precision s");
    }
    return res;
}

bool tim_set_prescaler_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (2 == argc) {
        res = true;
        uint8_t tim_num = 0;
        if (true == res) {
            res = try_str2uint8(argv[0], &tim_num);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract tim_num %s", argv[0]);
            }
        }

        uint32_t prescaler_us = 0;
        if (true == res) {
            res = try_str2uint32(argv[1], &prescaler_us);
            if (false == res) {
                LOG_ERROR(SYS, "Unable to extract prescaler_us %s", argv[1]);
            }
        }

        res = tim_set_prescaler_us(tim_num, prescaler_us);
        if (false == res) {
            LOG_ERROR(SYS, "Unable to set timer prescaler_us");
        }
    } else {
        LOG_ERROR(SYS, "Usage: tsp tim_num prescaler_us");
        LOG_INFO(SYS, "tim_num [1..14]");
        LOG_INFO(SYS, "prescaler_us [1...1092] us");
    }
    return res;
}
