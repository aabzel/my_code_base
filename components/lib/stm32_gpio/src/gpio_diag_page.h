#ifndef GPIO_DIAG__PAGES_H_
#define GPIO_DIAG__PAGES_H_

#include <stdbool.h>

#include "diag_page_nums.h"
#include "ostream.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern uint8_t gpio_state_port; /* Port number or PORT_INVALID  for all ports */

bool gpio_diag_page_init (void);
bool diag_page_gpio_list_ex (ostream_t *stream, const char* name1, const char* name2);
const char *oerc_2_str (uint8_t code);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_DIAG__PAGES_H_ */
