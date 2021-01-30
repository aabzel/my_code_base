#include <conio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "algorithms.h"
#include "convert.h"
#include "input.h"
#include "menu.h"

#ifdef HAS_TCP_CLIENT
#include "tcp_client.h"
#endif
#include "uTests.h"
#include "utils.h"
#include "win_utils.h"

#ifdef RAND_GENERATOR
uint64_t GetTimeStamp () {
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}
#endif

int main (int argc, char *argv[]) {
    printf ("\n[d] %s(): addr of main 0x%p", __FUNCTION__, main);
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
    printf ("\n [d] unit tests fine!\n");
#endif

#ifdef TCP_CLIENT
    printf ("\nDEPLOY_TCP_CLIENT\n");
    get_adapter_info ();
#endif

    bool loop = true;
    menu_init ();
    while (loop) {
        menu_task (NULL);
        // display_u8g2();
        loop = input_task (NULL);
        // gui_task();
    }

    printf ("\n\n program finish!\n\n");
    getchar ();
    return 0;
}
