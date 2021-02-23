#ifndef SRC_DEVICE_ID_H_
#define SRC_DEVICE_ID_H_
#include <stdint.h>
#include "device.h"

#ifdef HAS_C25AA02UID
#include <stdbool.h>
extern bool use_chip_id;
#endif

void  dump_device_id(void);
uint64_t get_device_serial(void);
bool device_has_chip_id(void);
const char* get_mcu_name(void);
const char* get_mcu_mask_id (void);

#endif /* SRC_DEVICE_ID_H_ */
