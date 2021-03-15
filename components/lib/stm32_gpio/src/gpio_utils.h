#ifndef GPIO_UTILS_H_
#define GPIO_UTILS_H_

#include <stdint.h>

#include "pal_utils.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t padToMcuPinMum[256];

/*pad to MCU pin num*/
char port2char (uint8_t port);
uint8_t char2port (char const inPortChar);
void gpio_utils_init (void);
const char* pad_name (pad_t pad);
uint16_t pad_to_pin_number(pad_t pad);
const char* wire_name (pad_t pad);
bool parse_port_pin (char const * const str, pad_t * const outPad);
bool parse_port_set_clear (const char* str, uint16_t* set_value, uint16_t* mask_value);

#ifdef __cplusplus
}
#endif

#endif /* PAL_UTILS_H_ */
