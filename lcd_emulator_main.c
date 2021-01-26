#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#include "algorithms.h"
#include "convert.h"

#ifdef HAS_TCP_CLIENT
#include "tcp_client.h"
#endif
#include "win_utils.h"
#include "uTests.h"
#include "utils.h"

#ifdef RAND_GENERATOR
uint64_t GetTimeStamp () {
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}
#endif

int main(int argc, char *argv[]) {
	printf("\n[d] %s(): addr of main 0x%p", __FUNCTION__, main);
	// time_t t;
#ifdef RAND_GENERATOR
	srand ((unsigned)GetTimeStamp ());
#endif

#ifdef HAS_VERBOSE
	printf ("\n[-] Argc: [%u]", argc);
	for (int i = 0; i < argc; i++) {
		printf ("\n[d] 1");
		printf ("\n[-]  argv[%d] [%s]", i, argv[i]);
	}
#endif

	// IPTCP server port tcp server
#if HIDE_CONSOLE
	FreeConsole ();
#endif

#ifdef HAS_UTESTS
	EXPECT_TRUE (unit_test ());
#endif

#ifdef TCP_CLIENT
	printf ("\nDEPLOY_TCP_CLIENT\n");
	get_adapter_info ();
#endif

	bool loop = true;
	while (loop) {
		if (_kbhit()) {
			char ch = _getch( );
			switch (ch) {
			case '8':
				printf("\nUp");
				break;
			case '3':
				printf("\nReset");
				break;
			case '2':
				printf("\nDown");
				break;
			case '4':
				printf("\nLeft");
				break;
			case '6':
				printf("\nRight");
				break;
			case '5':
				printf("\nOK");
				break;
			case '9':
				printf("\nExit");
				loop = false;
				break;
			default:
				printf("\n undef command key: %d %c", ch, ch);
				break;
			}
			printf("\n>");
		}
	}

	printf("\n\n program finish!\n\n");
	getchar();
	return 0;
}
