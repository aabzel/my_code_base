#include "algorithms.h"
#include "combinations.h"
#include "hash_table.h"
#include "linked_list.h"
#include "parse_phy_regs.h"
#include "permutations.h"
#include "utils.h"
#include "uTests.h"
#include "mk_to_dot.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PRINT_ENV 0
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

#if PRINT_ENV
    print_ent();
#endif

#if 1
    init_file_name ();

    int ret = unitTest ();
    if (0 != ret) {
        printf ("\n\nUnit Test Error: %d\n", ret);
    } else {
        //printf ("\n\nUnit Test fine\n");
#if 0
        test_combine ();
#endif
    }
#endif
    bool res = parse_phy_regs_file ("tja1101_reg_map_blob.txt", "tja1101_config.txt");
    if(false==res){
        printf ("\nError\n");
    }
    //perform_exper ();
    if (3 == argc) {
        //printf ("\n\narg 0  [%s]\n",argv[0]);
        printf ("\nin file [%s]", argv [1]);
        //printf ("\n\nout file [%s]",argv[2]);
        bool res = proc_mk_file (argv [1], argv [2]);
        if (false == res) {
            printf ("\n\nError\n");
        }
    }

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

