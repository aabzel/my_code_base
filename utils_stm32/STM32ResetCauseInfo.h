#ifndef EXTERNAL_STM32_UTILS_STM32RESETCAUSEINFO_H_
#define EXTERNAL_STM32_UTILS_STM32RESETCAUSEINFO_H_

#include <stdint.h>

uint32_t GetResetCauseInfo(void);

void ReportResetCause(void);

#endif /* EXTERNAL_STM32_UTILS_STM32RESETCAUSEINFO_H_ */
