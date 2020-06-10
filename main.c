#include "code_config.h"

#include "algorithms.h"
#include "combinations.h"
#include "hash_table.h"
#include "linked_list.h"
#include "parse_regs.h"
#include "permutations.h"
#include "utils.h"
#include "uTests.h"
#include "mk_to_dot.h"

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
#if PRINT_ENV
    print_ent();
#endif

#if DEPLOY_UTESTS
    int ret = unitTest ();
    if (0 != ret) {
        printf ("\n\nUnit Test Error: %d\n", ret);
    } else {
        printf ("\n\nUnit Test fine\n");
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

    printf ("\n\n Done!\n\n");
//    getchar ();
    return 0;
}

