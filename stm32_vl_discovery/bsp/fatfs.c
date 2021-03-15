#include "fatfs.h"

#include "ff.h"
#include "ff_gen_drv.h"
#include "user_diskio.h" /* defines USER_Driver as external */

uint8_t retUSER; /* Return value for USER */
char USERPath[4]; /* USER logical drive path */

bool fat_fs_init(void) {
	bool res = false;
	retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
	if (0 == retUSER) {
		res = true;
	}
	return res;
}

/**
 *  Gets Time from RTC
 */
DWORD get_fattime(void) {
	return 0;
}
