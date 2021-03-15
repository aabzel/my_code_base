#include "gpio_commands.h"

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#include "diag_page.h"
#include "diag_report.h"
#include "gpio_diag_page.h"
#include "gpio_utils.h"
#include "log.h"
//#include "pal.h"
#include "rx_io.h"
#include "rx_uart.h"

bool cmd_gpio_getp (int32_t argc, char *argv []) {
	bool res = false;
    if ( ((int32_t)1) <argc) {
        rx_printf ( "usage: getp [port]" CRLF
        "sample: getp A" CRLF);
        return dump_cmd_result (false);
    }
    uint8_t port;
    if (argc == 1) {
        if (strlen (argv [0]) > 1) {
            LOG_ERROR (SYS, "Invalid port name length %s", argv [0]);
            return dump_cmd_result (false);
        }
        port = char2port (argv [0] [0]);
        if (port == PORT_INVALID) {
            LOG_ERROR (SYS, "Invalid port name %s", argv [0]);
            return dump_cmd_result (false);
        }

        gpio_state_port = port;
        uint16_t port_value = pal_readport(port);
        rx_printf ( "| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }

    //bool res = show_diag_page (DIAG_PAGE_GPIO_STATE);
    gpio_state_port = PORT_INVALID;
    return res;
}

bool cmd_gpio_setp (int32_t argc, char *argv []) {
    if (argc != 2) {
        rx_printf (""
            "usage: setp port binvalue" CRLF
        "sample: setp A 1010xxxx0101x1x0" CRLF
        "    0 - set bit to LOW" CRLF
        "    1 - set bit to HIGH" CRLF
        "    x - don't change bit value" CRLF);
        return dump_cmd_result (false);
    }
    uint8_t port;
    if (strlen (argv [0]) > 1) {
        LOG_ERROR (SYS, "Invalid port name length %s", argv [0]);
        return dump_cmd_result (false);
    }
    port = char2port (argv [0] [0]);
    if (port == PORT_INVALID) {
        LOG_ERROR (SYS, "Invalid port name %s", argv [0]);
        return dump_cmd_result (false);
    }
    if (strlen (argv [1]) != 16) {
        LOG_ERROR (SYS, "Invalid port value length (must be 16 chars) %s", argv [1]);
        return dump_cmd_result (false);
    }
    uint16_t set_value, mask_value;
    if (!parse_port_set_clear (argv [1], &set_value, &mask_value)) {
        LOG_ERROR (SYS, "Invalid port value string %s", argv [1]);
        return dump_cmd_result (false);
    }
    uint32_t masked_value = ((uint32_t) mask_value << 16U) | set_value;
    //SIUL2.MPGPDO [port].R = masked_value;
    return true;
}

bool cmd_gpio_state (int32_t argc, char *argv []) {
    bool res = false;
    (void) (argv);
    if ((0 != argc) && (1 != argc) && (2 != argc)) {
        rx_printf (""
            "Usage: gpio_state" CRLF
        "Usage: gs M12 - get logic level from portm pin 12" CRLF
        "Usage: gs A1 1 - set port A pin 1 to HIGH" CRLF
        "Usage: gs A3 0 - set port A pin 3 to LOW" CRLF);
        res = false;
    }
    if (0 == argc) {
        res = show_diag_report (DIAG_PAGE_GPIO_STATE);
    }
    if ((1 == argc) || (2 == argc)) {
        bool logicLevel = false;
        pad_t gpio_pad = NO_PAD;
        res = parse_port_pin (argv [0], &gpio_pad);
        if (true == res) {
            if (1 == argc) {
                /*rx_printf ("parse OK pad: [%u]" CRLF, gpio_pad);*/
                logicLevel = pal_readpad_ex(gpio_pad);
                rx_printf ("%d" CRLF, logicLevel);
            }
            if (2 == argc) {
                res = try_str2bool (argv [1], &logicLevel);
                if (true == res) {
                    pal_writepad_ex(gpio_pad, logicLevel);
                    rx_printf ("set %s to %d" CRLF, argv [0], logicLevel);
                } else {
                    rx_printf ("logic level parse error %s" CRLF, argv [0]);
                }
            }
        } else {
            rx_printf ("unable to parse pin [%s]" CRLF, argv [0]);
        }
    }
    return res;
}

bool cmd_gpio_list (int32_t argc, char *argv []) {
    bool res = false;
    if (2 < argc) {
        rx_printf ("Usage: gpio_list [keyWord1] [keyWord2]" CRLF);
        res = false;
    } else {
        res = diag_page_gpio_list_ex (DBG, argv[0], argv[1]);
    }
    return res;
}

bool cmd_gpio_toggle (int32_t argc, char *argv []) {
    bool res = false;
    if (1 != argc) {
        rx_printf ("Usage: gpio_toggle" CRLF
        "Usage: gt M12 - toggle logic level from port m pin 12" CRLF);
        res = false;
    } else {
        pad_t gpio_pad = NO_PAD;
        res = parse_port_pin (argv [0], &gpio_pad);
        if (true == res) {
            bool prevLogicLevel = false;
            bool newLogicLevel = false;
            prevLogicLevel = pal_readpad_ex(gpio_pad);
            pal_toggle_ex(gpio_pad);
            rx_printf ("prev pad %u val %u" CRLF, gpio_pad, prevLogicLevel);
            newLogicLevel = pal_readpad_ex(gpio_pad);
            rx_printf ("new pad %u val %u" CRLF, gpio_pad, newLogicLevel);
            if (prevLogicLevel == newLogicLevel) {
                res = false;
                //const gpio_pin_info_t* pinInfo = get_gio_pin_by_pad (gpio_pad);
                //LOG_ERROR (SYS, "Unable to toggle pin %u %s", get_pin_number(pinInfo, MCU_PACKAGE), pad_name (gpio_pad));
            } else {
                res = true;
            }
        } else {
            rx_printf ("unable to parse pin [%s]" CRLF, argv [0]);
        }
    }
    return res;
}



