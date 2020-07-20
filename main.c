#include "code_config.h"

#include "algorithms.h"
#include "convert.h"
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
    get_adapter_info ();
#endif

#if DEPLOY_TCP_SERVER
    if (1 == argc) {
        res = try_strl2uint16 (argv [0], strlen (argv [0]), &serverPC.serverPort);
        if (false == res) {
            serverPC.serverPort = TCP_BOARD_SERVER_PORT;
        }
    } else {
        serverPC.serverPort = TCP_BOARD_SERVER_PORT;
    }
    res = launch_tcp_server (serverPC.serverPort);
    if (false == res) {
        printf ("\nUnable to launch board observation server");
    }
#endif

#if DEPLOY_SCAN_COM
    if (2 == argc) {
        printf ("\nargv 0 %s", argv [0]);
        printf ("\nargv 1 %s", argv [1]);
        //192.168.0.11 50506
        res = try_strl2uint16 (argv [0], strlen (argv [0]), &workBenchParam.serverPort);
        if (true == res) {
           res = try_strl2ipv4 (argv [1], strlen (argv [1]), &workBenchParam.serverIP);
           if (false == res) {
               printf ("\nUnable to parse server IP %s", argv [1]);
               strncpy (workBenchParam.serverIPstr, TCP_BOARD_SERVER_IP, sizeof(workBenchParam.serverIP));
               res = try_strl2ipv4 (TCP_BOARD_SERVER_IP, strlen (TCP_BOARD_SERVER_IP), &workBenchParam.serverIP);
           }else{
               printf ("\nPort %s", argv [0]);
               printf ("\nIP %s", argv [1]);
            }
        } else {
            workBenchParam.serverPort = TCP_BOARD_SERVER_PORT;
            printf ("\nUnable to parse server port %s", argv [1]);
        }
    } else {
        workBenchParam.serverPort = TCP_BOARD_SERVER_PORT;
        strncpy (workBenchParam.serverIPstr, TCP_BOARD_SERVER_IP, sizeof(workBenchParam.serverIP));
    }
    bool pollLoop = true;
    while (pollLoop) {
        Sleep (500);
        res = scan_serial ();
        if (false == res) {
            //printf ("\nLack of COM ports is system");
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

