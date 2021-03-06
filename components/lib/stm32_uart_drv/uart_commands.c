#include "uart_commands.h"

#include <inttypes.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_uart.h"
#include "diag_page_nums.h"
#include "diag_report.h"
#include "log.h"
#include "ostream.h"
#include "shell.h"
#include "table_utils.h"
#include "uart_driver.h"
#include "uart_common.h"
#include "uart_string_reader.h"

#if 0
static const char* uart_error2str(rx_uart_error_t e) {
    const char* result;
    switch (e) {
        case UART_ERROR_PE:
            result = "PE";
            break;
        case UART_ERROR_FE:
            result = "FE";
            break;
        case UART_ERROR_NE:
            result = "NE";
            break;
        case UART_ERROR_ORE:
            result = "ORE";
            break;
        default:
            result = rx_utoa32(e);
            break;
    }
    return result;
}
#endif

bool diag_page_uarts(ostream_t* stream) {
    LOG_NOTICE(SYS, "%s()", __FUNCTION__);

    static const table_col_t cols[] = {
        {16, "Name"},
        {17, "Total chars"},
        {13, "Lost chars"},
        {11, "Strings"},
        {11, "Errors"},
    };

    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
    io_printf(TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR
                         "%12" PRId64 " " TABLE_SEPARATOR "%10" PRId64
                         " " TABLE_SEPARATOR "%10" PRId64 " " TABLE_RIGHT CRLF,
              "cmd_reader", cmd_reader.total_char_count,
              cmd_reader.lost_char_count, cmd_reader.total_string_count,
              cmd_reader.error_count);

    io_printf(TABLE_LEFT "%15s " TABLE_SEPARATOR "%16" PRId64 " " TABLE_SEPARATOR
                         "%12" PRId64 " " TABLE_SEPARATOR
                         "           " TABLE_SEPARATOR "%10" PRId64
                         " " TABLE_RIGHT CRLF,
              "dbg_o", dbg_o.total_char_count, dbg_o.lost_char_count,
              dbg_o.error_count);

    table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));

    io_printf("rx %u byte " CRLF, huart_dbg.rx_byte_cnt);
    io_printf("tx %u byte " CRLF, huart_dbg.tx_byte_cnt);
    io_printf("tx cpl %u cnt " CRLF, huart_dbg.tx_cpl_cnt);
    return true;
}

bool cmd_uarts(int32_t argc, char* argv[]) {
    (void)argv;
    if (argc != 0) {
        LOG_ERROR(UART, "Usage: uarts: help");
        return dump_cmd_result(false);
    }
    return show_diag_report(DIAG_PAGE_UARTS);
}

// us 8 byte
// us 8 hex_string
bool uart_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (2 == argc) {
        res = true;
        uint8_t uart_num = 0;
        uint8_t array[256];
        uint16_t array_len = 0;
        res = try_str2uint8(argv[0], &uart_num);
        if (false == res) {
            LOG_ERROR(UART, "Unable to parse UART Number [1....8]");
        }

        if (true == res) {
            res = try_str2array(argv[1], array, sizeof(array), &array_len);
            if (false == res) {
                LOG_ERROR(UART, "Unable to extract array %s", argv[1]);
            }
        }

        if (true == res) {
            res = uart_send(uart_num, array, array_len);
            if (false == res) {
                LOG_ERROR(UART, "Unable to send UART");
            }
        }
    } else {
        LOG_ERROR(UART, "Usage: us instance hex_string");
        LOG_INFO(UART, "instance [1...8]");
        LOG_INFO(UART, "hex_string 0x[0...F]+");
    }
    return res;
}

bool uart_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if (2 == argc) {
        res = true;
        uint8_t uart_num = 0;
        uint32_t baudrate = 0;
        res = try_str2uint8(argv[0], &uart_num);
        if (false == res) {
            LOG_ERROR(UART, "Unable to parse UART Number [1....8]");
        }

        if (true == res) {
            res = try_str2uint32(argv[1], &baudrate);
            if (false == res) {
                LOG_ERROR(UART, "Unable to extract baudrate %s", argv[1]);
            }
        }

        if (true == res) {
            res = uart_set_baudrate(uart_num, baudrate);
            if (false == res) {
                LOG_ERROR(UART, "Unable to set baudrate");
            }
        }
    } else {
        LOG_ERROR(UART, "Usage: us instance baudrate");
        LOG_INFO(UART, "instance [1...8]");
        LOG_INFO(UART, "baudrate ");
    }
    return res;
}

/*TODO: calculate */
bool uart_diag_command(int32_t argc, char* argv[]) {
    static const table_col_t cols[] = {
        {5, "Num"}, {7, "manti"}, {7, "fract"}, {7, "overS"}, {10, "baudRate"}, {9, "rx"}, {9, "tx"}, {10, "name"}};
    uint32_t baud_rate = 0;
    uint16_t mantissa;
    uint16_t fraction;
    uint8_t uart_num = 0;
    uint8_t over_sampling = 0;
    table_header(&dbg_o.s, cols, ARRAY_SIZE(cols));
    for (uart_num = 1; uart_num <= 10; uart_num++) {
        io_printf(TSEP);
        io_printf(" %02u  " TSEP, uart_num);
        baud_rate =
            uart_get_baud_rate(uart_num, &mantissa, &fraction, &over_sampling);
        io_printf(" %05u " TSEP, mantissa);
        io_printf(" %05u " TSEP, fraction);
        io_printf(" %02u    " TSEP, over_sampling);
        if (0 < baud_rate) {
            io_printf(" %07u  " TSEP, baud_rate);
        } else {
            io_printf("          " TSEP, baud_rate);
        }
        io_printf(" %07u " TSEP, UartStat[uart_num].rx_cnt);
        io_printf(" %07u " TSEP, UartStat[uart_num].tx_cnt);
        io_printf(" %7s " TSEP, UartStat[uart_num].name);
        io_printf(CRLF);
        vTaskDelay(10);
    }
    table_row_bottom(&dbg_o.s, cols, ARRAY_SIZE(cols));
    return false;
}
