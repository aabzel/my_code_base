#include "algorithms.h"
#include "combinations.h"
#include "linked_list.h"
#include "permutations.h"
#include "utils.h"
#include "uTests.h"
#include "mk_to_dot.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main (int argc, char* argv []);
//int main (int argc, char **argv)
int main (int argc, char* argv []) {
#if 1
    init_file_name ();

    int ret = unitTest ();
    if (0 != ret) {
        printf ("\n\nUnit Test Error: %d\n", ret);
    } else {
        printf ("\n\nUnit Test fine\n");
#if 0
        test_combine ();
#endif
    }
#endif
    if (2 == argc) {
        printf ("\n\narg 0  [%s]\n",argv[0]);
        printf ("\n\nFile [%s]\n",argv[1]);
        bool res = proc_mk_file (argv [1]);
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

