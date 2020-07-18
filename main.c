#include "code_config.h"

#include "algorithms.h"
#include "combinations.h"
#include "hash_table.h"
#include "linked_list.h"
#include "parse_regs.h"
#include "permutations.h"
#include "utils.h"
#include "uTests.h"
#include "tcp_client.h"
#include "tcp_server.h"
#include "mk_to_dot.h"
#include "simulate_rocket_2d.h"
#include "scan_serial_port.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern char **environ;

#if PRINT_ENV
static bool print_ent (void) {
    char **ep;
    for (ep = environ; *ep != NULL; ep++) {
        puts (*ep);
    }
    return true;
}
#endif

int main (int argc, char* argv []);
//int main (int argc, char **argv)
int main (int argc, char* argv []) {
    (void) argc;
    (void) argv;
    // IPTCP server port tcp server
#if HIDE_CONSOLE
    FreeConsole();
#endif
    bool res = false;
#if PRINT_ENV
    print_ent();
#endif

#if DEPLOY_UTESTS
    int ret = unitTest ();
    if (0 != ret) {
        printf ("\n\nUnit Test Error: %d\n", ret);
        exit (ret);
    } else {
        printf ("\n\nUnit Test fine\n");
    }
#endif

#if DEPLOY_TCP_CLIENT
    get_mac ();
#endif

#if DEPLOY_TCP_SERVER
    res = launch_tcp_server(TCP_BOARD_SERVER_PORT);
    if (false == res) {
         printf ("Unable to launch board observation server");
    }
#endif

#if DEPLOY_SCAN_COM

    uint32_t tryCnt;
    for (tryCnt = 0; tryCnt < 100; tryCnt++) {
        res = scan_serial ();
        if (false == res) {
            printf ("Lack of com ports");
        }
    }
#endif

#if DEPLOY_PARSE_REG
    if (3 == argc) {
        bool res;
        res = parse_regs_file (argv [1], argv [2]);
        if (false == res) {
            printf ("\nError in parsing PHY regs\n");
        }
    } else {
        char inFileName [100];
        strncpy (inFileName, "tja1101_reg_map_blob.txt", sizeof(inFileName));
        bool res = parse_regs_file (inFileName, "tja1101_config.txt");
        if (false == res) {
            printf ("\nError in parsing PHY registers from file [%s]\n", inFileName);
        }
    }
#endif
    //perform_exper ();
#if PARSE_MK
    if (3 == argc) {
        //printf ("\n\narg 0  [%s]\n",argv[0]);
        printf ("\nin file [%s]", argv [1]);
        //printf ("\n\nout file [%s]",argv[2]);
        bool res = proc_mk_file (argv [1], argv [2]);
        if (false == res) {
            printf ("\n\nError\n");
        }
    }
#endif
    //permute (alphabet);

#if 0
    int ret = test_case ();
    if (ALLOC_FREE_OK != ret) {
        printf ("errorCode: [%s] \n\n", to_name_str (ret));
    } else {
        printf ("\n uTestOk!\n");
    }
#endif

#if DEPLOY_ROCKET_SIM
    bool res=false;
    res = simulate_roket (20.0f);
    if (false == res) {
        printf ("\nUnable to simulate rocket\n\n");
    }
#endif

    printf ("\n\n Done!\n\n");
    getchar ();
    return 0;
}

