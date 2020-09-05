#include "code_config.h"

#include "algorithms.h"
#include "combinations.h"
#include "convert.h"
#include "hash_table.h"
#include "linked_list.h"

#include "compare_version.h"

#ifdef DEPLOY_PARSE_REG
#include "parse_regs.h"
#endif
#include "permutations.h"
#include "tcp_client.h"
#include "uTests.h"
#include "utils.h"
#ifdef DEPLOY_TCP_SERVER
#include "tcp_server.h"
#endif
#include "mk_to_dot.h"
#include "scan_serial_port.h"
#include "simulate_rocket_2d.h"
#include "win_utils.h"

#ifdef DECRYPT_KEEPASS
#include "parse_keepass.h"
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main (int argc, char *argv[]) {
    printf ("\n[-] Argc: [%u]", argc);
    printf ("\n[d] 1");
    for (int i = 0; i < argc; i++) {
        printf ("\n[d] 1");
        printf ("\n[-]  argv[%d] [%s]", i, argv[i]);
    }

    // IPTCP server port tcp server
#if HIDE_CONSOLE
    FreeConsole ();
#endif
#if PRINT_ENV
    print_ent ();
#endif

#ifdef HAS_UTESTS
    printf ("\n[d] line %u", __LINE__);
    int ret = unit_test ();
    if (0 != ret) {
        printf ("\n\nUnit Test Error: %d\n", ret);
        exit (ret);
    } else {
        printf ("\n\nUnit Test fine\n");
    }
#endif
    printf ("\n[d] line %u", __LINE__);
#ifdef DEPLOY_TCP_CLIENT
    printf ("\nDEPLOY_TCP_CLIENT\n");
    get_adapter_info ();
#endif
    printf ("\n[d] line %u", __LINE__);
#ifdef DECRYPT_KEEPASS
    if (3 == argc) {
        bool open_res;
        open_res = try_to_open_kdbx_file (argv[1], argv[2]);
        if (false == open_res) {
            printf ("\n unable to open keepass\n");
        }
    } else {
        printf ("\n wrong params\n");
    }
#endif
    printf ("\n[d] line %u", __LINE__);
#ifdef DEPLOY_TCP_SERVER
    Sleep (4000);
    if (2 == argc) {
        res = try_strl2uint16 (argv[1], strlen (argv[1]), &serverPC.serverPort);
        if (false == res) {
            serverPC.serverPort = DFLT_TCP_BOARD_SERVER_PORT;
        }
    } else {
        serverPC.serverPort = DFLT_TCP_BOARD_SERVER_PORT;
    }
    res = launch_tcp_server (serverPC.serverPort);
    if (false == res) {
        printf ("\nUnable to launch board observation server");
    }
#endif

#ifdef DEPLOY_SCAN_COM
    printf ("\nDEPLOY_SCAN_COM\n");
    if (4 == argc) {
        strncpy (workBenchParam.userName, argv[3], sizeof (workBenchParam.userName));
        // 192.168.0.11 50506
        bool conv_res = false;
        conv_res = try_strl2uint16 (argv[1], strlen (argv[1]), &workBenchParam.serverPort);
        if (true == conv_res) {
            conv_res = try_strl2ipv4 (argv[2], strlen (argv[2]), &workBenchParam.serverIP);
            if (false == conv_res) {
                printf ("\nUnable to parse server IP %s", argv[2]);
                strncpy (workBenchParam.serverIPstr, DFLT_TCP_BOARD_SERVER_IP, sizeof (workBenchParam.serverIPstr));
                conv_res = try_strl2ipv4 (DFLT_TCP_BOARD_SERVER_IP, strlen (DFLT_TCP_BOARD_SERVER_IP),
                                          &workBenchParam.serverIP);
            } else {
                strncpy (workBenchParam.serverIPstr, argv[2], sizeof (workBenchParam.serverIPstr));
                printf ("\nPort %s", argv[1]);
                printf ("\nIP %s", argv[2]);
                Sleep (4000);
            }
        } else {
            printf ("\nUnable to parse server port %s", argv[2]);
            workBenchParam.serverPort = DFLT_TCP_BOARD_SERVER_PORT;
        }
    } else {
        workBenchParam.serverPort = DFLT_TCP_BOARD_SERVER_PORT;
        strncpy (workBenchParam.serverIPstr, DFLT_TCP_BOARD_SERVER_IP, sizeof (workBenchParam.serverIPstr));
    }
    bool pollLoop = true;
    Sleep (4000);
    int cnt = 0;
    int scan_period_ms = 500;
    memset (deviceList, 0x00, sizeof (deviceList));
    while (pollLoop) {
        Sleep (scan_period_ms);
        cnt++;
        printf ("\nUp Time %7.2f", ((float)cnt * scan_period_ms) / 1000.0);
        bool scan_res;
        scan_res = scan_serial ();
        if (false == scan_res) {
            printf ("\nLack of COM ports is system");
            printf ("\n");
        }
    }

#endif
    printf ("\n[d] line %u", __LINE__);
#ifdef DEPLOY_PARSE_REG
    if (4 == argc) {
        bool res;
        res = parse_regs_file (argv[1], argv[2]);
        if (false == res) {
            printf ("\nError in parsing PHY regs\n");
        }
    } else {
        char inFileName[100];
        strncpy (inFileName, "tja1101_reg_map_blob.txt", sizeof (inFileName));
        bool res = parse_regs_file (inFileName, "tja1101_config.txt");
        if (false == res) {
            printf ("\nError in parsing PHY registers from file [%s]\n", inFileName);
        }
    }
#endif
    // perform_exper ();
#ifdef HAS_PARSE_MK
    if (5 == argc) {
        printf ("\nin file [%s]", argv[1]);
        bool res = proc_mk_file (argv[1], argv[2], argv[3], argv[4]);
        if (false == res) {
            printf ("\n\nError\n");
        }
    } else {
        printf ("\n[!] main args error %u\n", argc);
    }
#endif
    // permute (alphabet);

#if 0
    int ret = test_case ();
    if (ALLOC_FREE_OK != ret) {
        printf ("errorCode: [%s] \n\n", to_name_str (ret));
    } else {
        printf ("\n uTestOk!\n");
    }
#endif

#if DEPLOY_ROCKET_SIM
    bool res = false;
    res = simulate_roket (20.0f);
    if (false == res) {
        printf ("\nUnable to simulate rocket\n\n");
    }
#endif
    printf ("\n[d] line %u", __LINE__);
    printf ("\n\n Done!\n\n");
    // getchar ();
    return 0;
}
