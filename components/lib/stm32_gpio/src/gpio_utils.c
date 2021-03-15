#include "gpio_utils.h"

#include <stdint.h>
#include <string.h>

#include "board.h"
#include "convert.h"
#include "gpio_diag_page.h"
#include "gpio_utils.h"
#include "pal_utils.h"

uint16_t pad_to_pin_number (pad_t pad) {
	uint16_t pin_number = 0xFFFF;
	for (int pin = 0; pin < PIN_COUNT; pin++) {
		if(pin_info[pin].pin_pad == pad){
			pin_number = pin_info[pin].mcu_pin;
		}
	}
	return pin_number;
}

/*get abstract pin_pad 0...255 return real MCU pin number 1...177*/
const uint8_t padToMcuPinMum [256] =
    {
        137U,/*0 PA0*/
        134U,/**/
        133U,/**/
        82U,/**/
        120U,/**/
        114U,/**/
        115U,/**/
        112U,/**/
        111U,/**/
        113U,/*9 PA9*/
        142U,/**/
        143U,/**/
        135U,/**/
        136U,/**/
        110U,/**/
        88U,/**/
        67U,/**/
        66U,/**/
        65U,/**/
        64U,/*19*/
        61U,/**/
        36U,/**/
        46U,/**/
        45U,/**/
        81U,/**/
        80U,/**/
        79U,/**/
        78U,/**/
        35U,/**/
        34U,/**/
        33U,/*30*/
        32U,/**/
        13U,/**/
        12U,/**/
        11U,/**/
        9U,/**/
        8U,/**/
        7U,/**/
        6U,/**/
        5U,/**/
        4U,/*40*/
        3U,/**/
        167U,/**/
        166U,/**/
        165U,/**/
        163U,/**/
        162U,/**/
        161U,/**/
        159U,/**/
        158U,/**/
        157U,/*50*/
        156U,/**/
        129U,/**/
        130U,/**/
        109U,/**/
        108U,/**/
        83U,/**/
        76U,/**/
        77U,/**/
        63U,/**/
        17U,/*60*/
        18U,/**/
        1U,/**/
        2U,/**/
        14U,/**/
        15U,/**/
        16U,/**/
        19U,/**/
        20U,/**/
        126U,/**/
        127U,/*70*/
        128U,/**/
        131U,/**/
        132U,/**/
        145U,/**/
        146U,/**/
        160U,/**/
        62U,/**/
        60U,/**/
        59U,/**/
        75U,/*80*/
        74U,/**/
        174U,/**/
        173U,/**/
        169U,/**/
        170U,/**/
        84U,/**/
        85U,/**/
        90U,/**/
        95U,/**/
        96U,/*90*/
        97U,/**/
        98U,/**/
        107U,/**/
        116U,/**/
        119U,/**/
        21U,/**/
        28U,/**/
        29U,/**/
        30U,/**/
        31U,/*100*/
        43U,/**/
        44U,/**/
        49U,/**/
        50U,/**/
        55U,/**/
        56U,/**/
        57U,/**/
        58U,/**/
        124U,/**/
        125U,/*110*/
        138U,/**/
        140U,/**/
        141U,/**/
        144U,/**/
        147U,/**/
        148U,/**/
        93U,/**/
        94U,/**/
        152U,/**/
        151U,/**/
        150U,/**/
        149U,/**/
        117U,/**/
        176U,/**/
        175U,/**/
        172U,/**/
        168U,/**/
        37U,/**/
        38U,/**/
        39U,/*130*/
        40U,/**/
        41U,/**/
        42U,/**/
        47U,/**/
        48U,/**/
        22U,/**/
        23U,/**/
        73U,/**/
        72U,/**/
        71U,/*140*/
        70U,/**/
        105U,/**/
        106U,/**/
        86U,/**/
        87U,/**/
        89U,/**/
        91U,/**/
        92U,/*148*/
        0U,/**/
        0U,/*150*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*160*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*170*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*180*/
        0,/*181*/
        0U,/**/
        0U,/**/
        10U,/*184*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*190*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*200*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        154U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*210*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*220*/
        0U,/**/
        0U,/**/
        0,
        0,
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*230*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*240*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0,/*250*/
        0U,/**/
        0U,/**/
        0U,/**/
        0U,/**/
        0 };/*255*/


/*
1 <- PD14
2 <- PD15
3 <- PC9
4 <-PC8
5 <- PC7
6 <- PC6
7 <- PC5
8 <- PC4
9 <- PC3
10 <- PL8
11 <- PC2
12 <- PC1
13 <- PC0
14 <- PE0
15 <- PE1
16 <- PE2
17 <- PD12
18 <- PD13
19 <- PE3
20 <- PE4
21 <- PG0
22 <- PI8
23 <- PI9
24 -
25 -
26 -
27 -
28 <- PG1
29 <- PG2
30 <- PG3
31 <- PG4
32 <- PB15
33 <- PB14
34 <- PB13
35 <- PB12
36 <- PB5
37 <- PI0
38 <- PI1
39 <- PI2
40 <- PI3
41 <- PI14
42 <- PI15
43 <- PG5
44 <- PG6
45 <- PB7
46 <- PB6
47 <- PI6
48 <- PI7
49 <- PG7
50 <- PG8
51 <- -
52 <- -
53 <- -
54 <- -
55 <- PG9
56 <- PG10
57 <- PG11
58 <- PG12
59 <- PE15
60 <- PE14
61 <- PB4
62 <- PE13
63 <- PD11
64 <- PB3
65 <- PB2
66 <- PB1
67 <- PB0
68 <- -
69 <- -
70 <- PI13
71 <- PI12
72 <- PI11
73 <- PI10
74 <- PF1
75 <- PF0
76 <- PD9
77 <- PD10
78 <- PB11
79 <- PB10
80 <- PB9
81 <- PB8
82 <- PA3
83 <- PD8
84 <- PF6
85 <- PF7
86 <- PJ0
87 <- PJ1
88 <- PA15
89 <- PJ2
90 <- PF8
91 <- PJ3
92 <- PJ4
93 <- PH5
94 <- PH6
95 <- PF9
96 <- PF10
97 <- PF11
98 <- PF12
99 <- -
100<- -
101<- -
102 <--
103 <--
104 <--
105 <-PI14
106 <-PI15
107 <-PF13
108 <-PD7
109 <-PD6
110 <-PA14
111 <-PA8
112 <-PA7
113 <-PA9
114 <-PA5
115 <-PA6
116 <-PF14
117 <-PH11
118<- -
119<- PF15
120<- PA4
121<- -
122<- -
123<- -
124<- PG13
125<- PG14
126<- PE5
127<- PE6
128<- PE7
129<- PD4
130<- PD5
131<- PE9
132<- PE9
133<- PA2
134<- PA1
135<- PA[12]
136<- PA[13]
137<- PA0
138<- PG15
139<- -
140<- PH0
141<- PH1
142<- PA10
143<- PA11
144<- PH2
145<- PE10
146<- PE11
147<- PH3
148<- PH4
149<- PH10
150<- PH9
151<- PH8
152<- PH7
153<- -
154<- PM13
155<- -
156<- PD3
157<- PD2
158<- PD1
159<- PD0
160<- PE12
161<- PC15
162 <-PC14
163 <-PC13
164 -
165<- PC12
166<- PC11
167<- PC9
168<- PH15
169<- PF4
170<- PF5
171<- -
172<- PH14
173<- PF3
174<- PF2
175<- PH13
176<- PH12
177 <--
*/
#ifdef PIN_COUNT
static pad_t find_pin_by_name (const char *const pin_name) {
    uint8_t index;
    pad_t result = NO_PAD;
    for (index = 0; index < PIN_COUNT; index++) {
        if (0 == strcasecmp (pin_name, pin_info [index].pin_name)) {
            result = pin_info [index].pin_pad;
            break;
        }
    }
    return result;
}
#endif /* PIN_COUNT */
/*
 * str:   p12
 * index: 0x0123
 *
 * */
bool parse_port_pin (char const *const str, pad_t *const outPad) {
    bool res = false;
    uint8_t port;
    if ((NULL != outPad) && (NULL != str)) {
        *outPad = NO_PAD;
#ifdef PIN_COUNT
        *outPad = find_pin_by_name (str);
        if (NO_PAD != *outPad) {
            res = true;
        } else {
#endif /* PIN_COUNT */
            port = char2port (str [0]);
            if (PORT_INVALID != port) {
                uint8_t pin = 0xff;
                if (true == try_str2uint8 (&str [1], &pin)) {
                    if (pin <= 15U) {
                        *outPad = PAD_EX(port, pin);
                        res = true;
                    }
                }
            }
#ifdef PIN_COUNT
        }
#endif
    }
    return res;
}

uint8_t char2port (char const inPortChar) {
    uint8_t outPort = PORT_INVALID;
    switch (inPortChar) {
        case 'A':
        case 'a':
            outPort = PORT_A;
            break;
        case 'B':
        case 'b':
            outPort = PORT_B;
            break;
        case 'C':
        case 'c':
            outPort = PORT_C;
            break;
        case 'D':
        case 'd':
            outPort = PORT_D;
            break;
        case 'E':
        case 'e':
            outPort = PORT_E;
            break;
        case 'F':
        case 'f':
            outPort = PORT_F;
            break;
        case 'G':
        case 'g':
            outPort = PORT_G;
            break;
        case 'H':
        case 'h':
            outPort = PORT_H;
            break;
        case 'I':
        case 'i':
            outPort = PORT_I;
            break;
        case 'J':
        case 'j':
            outPort = PORT_J;
            break;
        case 'K':
        case 'k':
            outPort = PORT_K;
            break;
        case 'L':
        case 'l':
            outPort = PORT_L;
            break;
        case 'M':
        case 'm':
            outPort = PORT_M;
            break;
        case 'N':
        case 'n':
            outPort = PORT_N;
            break;
        case 'O':
        case 'o':
            outPort = PORT_O;
            break;
        case 'P':
        case 'p':
            outPort = PORT_P;
            break;
        default:
            outPort = PORT_INVALID;
            break;
    }
    return outPort;
}

char port2char (uint8_t port) {
    char portChar = '?';
    switch (port) {
        case PORT_A:
            portChar = 'A';
            break;
        case PORT_B:
            portChar = 'B';
            break;
        case PORT_C:
            portChar = 'C';
            break;
        case PORT_D:
            portChar = 'D';
            break;
        case PORT_E:
            portChar = 'E';
            break;
        case PORT_F:
            portChar = 'F';
            break;
        case PORT_G:
            portChar = 'G';
            break;
        case PORT_H:
            portChar = 'H';
            break;
        case PORT_I:
            portChar = 'I';
            break;
        case PORT_J:
            portChar = 'J';
            break;
        case PORT_K:
            portChar = 'K';
            break;
        case PORT_L:
            portChar = 'L';
            break;
        case PORT_M:
            portChar = 'M';
            break;
        case PORT_N:
            portChar = 'N';
            break;
        case PORT_O:
            portChar = 'O';
            break;
        case PORT_P:
            portChar = 'P';
            break;
        default:
            portChar = '-';
            break;
    }
    return portChar;
}

void gpio_utils_init (void) {
    (void) gpio_diag_page_init ();
}

const char* pad_name (pad_t pad) {
    static char pad_name_str [6];
    uint8_t pin = pad & 0xFU;

    pad_name_str [0] = port2char ((pad >> 4U) & 0xFU);
    pad_name_str [1] = '[';
    if (pin >= 10U) {
        pad_name_str [2] = '1';
        pad_name_str [3] = '0' + pin - 10U;
        pad_name_str [4] = ']';
        pad_name_str [5] = '\0';
    } else {
        pad_name_str [2] = '0' + pin;
        pad_name_str [3] = ']';
        pad_name_str [4] = '\0';
    }
    return pad_name_str;
}

bool parse_port_set_clear (const char *str, uint16_t *set_value, uint16_t *mask_value) {
    bool parse_result= false;
    *set_value = 0U;
    *mask_value = 0U;
    if (strlen (str) == 16U) {
        const char *p = str;
        uint16_t mask = 0x8000U;
        parse_result = true;
        while (mask != 0U) {
            switch (*p) {
                case '1':
                    *set_value |= mask;
                    *mask_value |= mask;
                    break;
                case '0':
                    *mask_value |= mask;
                    break;
                case 'x':
                case 'X':
                    break;
                default:
                    parse_result = false;
                    break;
            }
            p++;
            mask >>= 1U;
        }
    }
    return parse_result;
}

#ifdef PIN_COUNT
const char* wire_name (pad_t pad) {
    const char *wire_name_ptr = "undef_wire";
    uint8_t index;
    for (index = 0U; index < PIN_COUNT; index++) {
        if (pad == pin_info [index].pin_pad) {
            wire_name_ptr = pin_info [index].pin_name;
            index = PIN_COUNT;
        }
    }
    return wire_name_ptr;
}
#endif

