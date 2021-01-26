#include "code_config.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "algorithms.h"
#include "combinations.h"
#include "convert.h"
#include "hash_table.h"
#include "linked_list.h"

#if 0
//not allowed in C
int init_by_foo1(void){
	printf("\n[d]%s()",__FUNCTION__);
	return 1;
}

int init_by_foo2(void){
	printf("\n[d]%s()",__FUNCTION__);
	return 2;
}

int a_val1=init_by_foo1();
int a_val2=init_by_foo2();
#endif

#ifdef HAS_LS
#include "ls_l.h"
#endif

#include "compare_version.h"

#ifdef HAS_EVAL_CACHE
#include "evaluate_cache.h"
#endif

#ifdef HAS_PARSE_REG
#include "parse_regs.h"
#endif

#ifdef HAS_GENERATE_REG_PARSER
#include "generate_parser.h"
#endif

#ifdef HAS_PERMUTATION
#include "permutations.h"
#endif

#ifdef HAS_TCP_CLIENT
#include "tcp_client.h"
#endif
#include "win_utils.h"
#include "uTests.h"
#include "utils.h"
#ifdef DEPLOY_TCP_SERVER
#include "tcp_server.h"
#endif
#include "mk_to_dot.h"
#ifdef HAS_SERIAL
#include "scan_serial_port.h"
#endif
#include "simulate_rocket_2d.h"

#ifdef DECRYPT_KEEPASS
#include "parse_keepass.h"
#endif

extern char **environ;

#if PRINT_ENV
static bool print_ent (void) {
    char **ep;
    for (ep = environ; *ep != NULL; ep++) {
        puts (*ep);
    }
    return true;
}

void inc (char *array) {
    array++;
    *(array + 1) = 'P';
    (*(array + 1))++;
    char *ptr = array;
    *(ptr + 2) = 'N';
    char *ptr2 = ptr;
    *ptr2 = 'R';
    (*ptr2)++;
}
#endif

#ifdef RAND_GENERATOR
uint64_t GetTimeStamp () {
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}
#endif

int g_val = 2;
int main (int argc, char *argv[]) {
    printf ("\n[d] %s(): addr of main 0x%p", __FUNCTION__, main);
    // time_t t;
#ifdef RAND_GENERATOR
    srand ((unsigned)GetTimeStamp ());
#endif

#ifdef BEAM_TREAL
    char array[] = {'A', 'G', 'V', 0};
    inc (&array[0]);
    printf ("%s\n", array);
    float x = 9 / 7;
    printf ("\nx=[%f]\n", x);

    long int a = -1;
    unsigned int b = 1;
    printf ("\n[%zu]\n", sizeof (a));
    printf ("\n[%zu]\n", sizeof (b));
    if (a > b) {
        printf ("\na\n");
    } else {
        printf ("\nb\n");
    }
    printf ("\na [%x]\n", (unsigned int)(a));
    printf ("\nb [%x]\n", (unsigned int)(b));
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
#if PRINT_ENV
    print_ent ();
#endif

#ifdef HAS_UTESTS
    EXPECT_TRUE (unit_test ());
#endif

#ifdef HAS_LS
    bool res_ls = explore_dir ();
    if (false == res_ls) {
        printf ("\n\nError explore_dir\n");
    }
#endif

#ifdef TCP_CLIENT
    printf ("\nDEPLOY_TCP_CLIENT\n");
    get_adapter_info ();
#endif

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

#ifdef HAS_GENERATE_REG_PARSER
    //  #error dfdfd
    printf ("\n Generate rarser for registers\n");
    if (5 == argc) {
        bool res;
        res = generate_reg_parser (argv[1], argv[2], argv[3], argv[4]);
        if (false == res) {
            printf ("\nError generate_reg_parser\n");
        }
    } else {
        printf ("\n wrong command options\n");
    }
#endif

#ifdef HAS_PARSE_REG
    printf ("\n Parse registers\n");
    if (2 == argc) {
        bool res;
        res = parse_regs_file (argv[1], NULL);
        if (false == res) {
            printf ("\nError in parsing PHY regs\n");
        }
    } else if (3 == argc) {
        bool res;
        res = parse_regs_file (argv[1], argv[2]);
        if (false == res) {
            printf ("\nError in parsing PHY regs\n");
        }
    } else {
        printf ("\n wrong command options\n");
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
    if (3 == argc) {
        printf ("\nin  file [%s]", argv[1]);
        printf ("\nout file [%s]", argv[2]);
        bool res = proc_mk_file (argv[1], argv[2]);
        if (false == res) {
            printf ("\nUnable to proc mk file %s \n", argv[1]);
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

#if 0
    bool loop=false;
    int cnt=0;
    while (loop){
    	cnt++;
        printf ("\n addr of val:%p val:%d cnt:%p cnt:%d", &g_val, g_val, &cnt,cnt);
        sleep(2);
    }
#endif

    // printf ("\n\n program finish!\n\n");
    // getchar ();
    return 0;
}
