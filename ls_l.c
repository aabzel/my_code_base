#include "ls_l.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#define SECS_IN_DAY (24 * 60 * 60)

static char *file_type_2_str(unsigned char d_type){
	char *name="?";
	switch(d_type){
	case DT_UNKNOWN: name="?"; break;
	case DT_REG: name="-"; break;
	case DT_DIR: name="d"; break;
	case DT_FIFO: name="p"; break;
	case DT_SOCK: name="s"; break;
	case DT_CHR: name="c"; break;
	case DT_BLK: name="b"; break;
	case DT_LNK: name="l"; break;
	default: name="?"; break;
	}
	return name;
}
#if 0
static char * display_clock(struct timespec ts) {
	static char name[100] ="";
	sprintf(name,"%2ld:%2ld", (ts.tv_sec % SECS_IN_DAY) / 3600,
			(ts.tv_sec % 3600) / 60 );
	return name;
}
#endif

static char *months[] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

static char* display_date_time(struct tm *tm_ptr) {
	static char name[100] = "";
	sprintf(name, "%s %2d %d %02d:%02d",  months[tm_ptr->tm_mon],tm_ptr->tm_mday,
			1900 + tm_ptr->tm_year, tm_ptr->tm_hour, tm_ptr->tm_min);
	return name;
}

static void st_mode_2_str(char *buf, mode_t mode) {
	if (buf) {
		const char chars[] = "rwxrwxrwx";
		for (uint8_t i = 0; i < 9; i++) {
			buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
		}
		buf[9] = '\0';
	}
}

static char *get_user(uid_t uid) {
    static char buff[100];
	struct passwd *pws;
    pws = getpwuid(uid);
    strncpy(buff,pws->pw_name,sizeof(buff));
    return buff;
}

static char *get_groupname(uid_t uid) {
    static char buff[100];
	struct group *pws;
    pws = getgrgid(uid);
    strncpy(buff,pws->gr_name,sizeof(buff));
    return buff;
}

bool explore_dir(void) {
	printf ("\n\n%s()\n",__FUNCTION__);
	DIR *dirr;
	bool res = false;
	struct dirent *dir;
	dirr = opendir(".");
	char buf[100];
	if (dirr) {
		while ((dir = readdir(dirr)) != NULL) {
			printf("%s", file_type_2_str(dir->d_type));
			struct stat statbuf;
			if(-1 !=stat(dir->d_name, &statbuf) ) {
				st_mode_2_str(buf, statbuf.st_mode);
				printf("%s ", buf);
				printf("%2u ",(unsigned int) statbuf.st_nlink);
				printf("%s ", get_user(statbuf.st_uid));
				printf("%s ", get_groupname (statbuf.st_gid));
			    printf(" %6llu ",(long long unsigned int) statbuf.st_size);
			    struct tm *my_tm = localtime(&statbuf.st_mtim.tv_sec);
			    printf("%s ", display_date_time( my_tm));
			}
			printf(" %s", dir->d_name);

			printf("\n");
		}
		res = true;
		closedir(dirr);
	}
	return res;
}

