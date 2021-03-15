#ifndef UNIT_TEST_RUN_H_
#define UNIT_TEST_RUN_H_

#include <stdint.h>
#include <stdbool.h>

extern bool test_failed;

uint32_t unit_test_run (uint32_t index);
void failed_tests_print (void);
void failed_tests_reset (void);

#endif /* UNIT_TEST_RUN_H_ */
