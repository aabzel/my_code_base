#ifndef TEST_LIST_H
#define TEST_LIST_H

#include <stdbool.h>
#include <stdint.h>

#include "unit_test_info.h"

#define UTEST_NUMBER 4U

unit_test_info_t test_list[UTEST_NUMBER];

bool test_64bit_mult(void);
bool test_utoa_bin8 (void);

#endif
