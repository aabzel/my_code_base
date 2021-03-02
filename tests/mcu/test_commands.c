#include "test_commands.h"

#include <stdbool.h>
#include <stdint.h>

bool cmd_test_run(int32_t argc, char *argv[]) {
	bool res = false;
	if (1 == argc) {
		if (true == res) {
	    	res = true;
	    	uint8_t test_num = 0;
			res = try_str2uint8(argv[0], &test_num);
			if (false == res) {
				LOG_ERROR(SYS, "Unable to parse test_num  %s", argv[0]);
			}
		}
	}
	return res;
}
bool cmd_test_all(int32_t argc, char *argv[]) {
	return false;
}
