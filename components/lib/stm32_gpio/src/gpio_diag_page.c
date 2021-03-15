#include "gpio_diag_page.h"

#include "board.h"
#include "diag_page.h"
#include "gpio_utils.h"
#include "pal.h"
#include "rx_io.h"
#include "rx_uart.h"
#include "str_utils.h"
#include "table_utils.h"

#include <inttypes.h>
#include <string.h>


uint8_t gpio_state_port = PORT_INVALID;

static bool is_print_pin (uint16_t pinIndex, const char *inKeyWord1, const char *inKeyWord2);
static bool diag_page_gpio_state (ostream_t *stream);
#ifdef PIN_COUNT
static bool diag_page_gpio_list (ostream_t *stream);
#endif /* PIN_COUNT */

bool gpio_diag_page_init (void) {
    bool result=true;
    static diag_page_rec_t gpio_state_rec =
        { DIAG_PAGE_GPIO_STATE, "GPIO State", diag_page_gpio_state, NULL };
#ifdef PIN_COUNT
    static diag_page_rec_t gpio_list_rec =
        { DIAG_PAGE_GPIO_LIST, "GPIO list", diag_page_gpio_list, NULL };
    if (!diag_page_add (&gpio_list_rec)) {
        result=false;
    }
#endif /* PIN_COUNT */
    if (!diag_page_add (&gpio_state_rec)) {
        result=false;
    }
    return result;
}



static bool diag_page_gpio_state (ostream_t *stream) {
    uint16_t port_value;
    oprintf (stream, "+------+--------+---------------------+" CRLF);
    oprintf (stream, "| PORT |   PORT | 1111 11             |" CRLF);
    oprintf (stream, "| NAME |  VALUE | 5432 1098 7654 3210 |" CRLF);
    oprintf (stream, "+------+--------+---------------------+" CRLF);
#ifdef PORT_A
    if ((gpio_state_port == PORT_A) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_A);
        oprintf (stream, "|PORT_A| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_B
    if ((gpio_state_port == PORT_B) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_B);
        oprintf (stream, "|PORT_B| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_C
    if ((gpio_state_port == PORT_C) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_C);
        oprintf (stream, "|PORT_C| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_D
    if ((gpio_state_port == PORT_D) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_D);
        oprintf (stream, "|PORT_D| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_E
    if ((gpio_state_port == PORT_E) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_E);
        oprintf (stream, "|PORT_E| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_F
    if ((gpio_state_port == PORT_F) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_F);
        oprintf (stream, "|PORT_F| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_G
    if ((gpio_state_port == PORT_G) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_G);
        oprintf (stream, "|PORT_G| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_H
    if ((gpio_state_port == PORT_H) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_H);
        oprintf (stream, "|PORT_H| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_I
    if ((gpio_state_port == PORT_I) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_I);
        oprintf (stream, "|PORT_I| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_J
    if ((gpio_state_port == PORT_J) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_J);
        oprintf (stream, "|PORT_J| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_K
    if ((gpio_state_port == PORT_K) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_K);
        oprintf (stream, "|PORT_K| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_L
    if ((gpio_state_port == PORT_L) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_L);
        oprintf (stream, "|PORT_L| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif

#ifdef PORT_M
    if ((gpio_state_port == PORT_M) || (gpio_state_port == PORT_INVALID)) {
        port_value = pal_readport(PORT_M);
        oprintf (stream, "|PORT_M| 0x%04" PRIX16 " | %s |" CRLF, port_value, utoa_bin16(port_value));
    }
#endif
    oprintf (stream, "+------+--------+---------------------+" CRLF);
    return true;
}

#ifdef PIN_COUNT
static void flush_stream (ostream_t *stream) {
    if (stream == &dbg_o.s) {
        flush_printf ();
    }
}

static bool diag_page_gpio_list (ostream_t *stream) {
    return diag_page_gpio_list_ex(stream, NULL, NULL);
}

const char *oerc_2_str (uint8_t code) {
    const char *name="undef";
    switch (code) {
        case 0: name="Weak"; break;
        case 1: name="Medium"; break;
        case 2: name="Strong"; break;
        case 3: name="Very Strong"; break;
        default: name="undef"; break;
    }
    return name;
}

static const char *odc_2_str (uint8_t code) {
    const char *name="undef";
    switch (code) {
        case 0: name = "OutBuff dis"; break;
        case 1: name = "Open-drain"; break;
        case 2: name = "Push-pull"; break;
        case 3: name = "Open-source"; break;
        case 4: name = "uSec Ch LVDS"; break;
        case 5: name = "LFAST LVDS"; break;
        default: name="Reserved"; break;
    }
    return name;
}

static const char *pin_pulls_2_str (uint8_t code) {
    const char *name="XX";
    switch (code) {
        case 0: name = "__"; break;
        case 1: name = "_D"; break;
        case 2: name = "U_"; break;
        case 3: name = "UP"; break;
        default: name = "??"; break;
    }
    return name;
}

bool diag_page_gpio_list_ex (ostream_t *stream, const char* name1, const char* name2) {
    static const table_col_t header_stat [] =
        {
            { 4, "N" },
            { PIN_NAME_MAX_LEN+2, "Name" },
            { 7, "Pad" },
            { 7, "PadNum" },
            { 5, "pin" },
            { 6, "State" },
            { 4, "pull" },
        };
    uint16_t index;
    bool printFlag = true;
    table_header (stream, header_stat, (int16_t)(sizeof(header_stat)/sizeof(header_stat[0])));
    for (index = 0; index < PIN_COUNT; index++) {
        printFlag = is_print_pin (index, name1, name2);
        if (true == printFlag) {
            oprintf (stream, TABLE_LEFT "%3u " TABLE_SEPARATOR " %" PIN_NAME_FORMAT " ", (index + 1U), pin_info[index].pin_name);
            oprintf (stream, TABLE_SEPARATOR "%6s ", pad_name(pin_info[index].pin_pad));
            oprintf (stream, TABLE_SEPARATOR "  %03u  ", pin_info[index].pin_pad);
            oprintf (stream, TABLE_SEPARATOR " %03u ", pad_to_pin_number(pin_info[index].pin_pad));
            if (pal_readpad_ex(pin_info[index].pin_pad) == PAL_HIGH) {
                oputs(stream, TABLE_SEPARATOR " HIGH ");
            } else {
                oputs(stream, TABLE_SEPARATOR "  low ");
            }
            uint8_t pin_pulls = 0;
            if (1==pal_readpad_pull_up(pin_info[index].pin_pad)) {
                pin_pulls |= 2;
            }
            if(1==pal_readpad_pull_down(pin_info[index].pin_pad)){
                pin_pulls |= 1;
            }
            oprintf (stream, TABLE_SEPARATOR " %2s ", pin_pulls_2_str(pin_pulls));
            oputs(stream, TABLE_RIGHT CRLF);
            flush_stream (stream);
        }
    }
    table_row_bottom (stream, header_stat, (int16_t)(sizeof(header_stat)/sizeof(header_stat[0])));
    return true;
}
#endif /* PIN_COUNT */

static bool is_print_pin (uint16_t pinIndex, const char *inKeyWord1, const char *inKeyWord2) {
    bool res = false;
    if (pinIndex < PIN_COUNT) {
        if ((NULL == inKeyWord1) && (NULL == inKeyWord2)) {
            res = true;
        } else {
            if( (NULL != inKeyWord1) && (NULL != inKeyWord2) ) {
                if( (NULL != str_case_str (pin_info [pinIndex].pin_name, inKeyWord1) ) &&
                    (NULL != str_case_str (pin_info [pinIndex].pin_name, inKeyWord2) ) ) {
                    res = true;
                }
            }
            if ((NULL != inKeyWord1) && (NULL == inKeyWord2)) {
                if (NULL != str_case_str (pin_info [pinIndex].pin_name, inKeyWord1)) {
                    res = true;
                }
            }
            if ((NULL == inKeyWord1) && (NULL != inKeyWord2)) {
                if (NULL != str_case_str (pin_info [pinIndex].pin_name, inKeyWord2)) {
                    res = true;
                }
            }
        }
    }
    return res;
}
