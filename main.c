#include "algorithms.h"
#include "linked_list.h"
#include "utils.h"
#include "uTests.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main (int argc, char **argv) {
    //init_list ();
    //list_print_fwd ();
    //list_print_reverse ();
    //combine (4, 2);
    //permutation (4) ;
#if 1
    init_file_name ();
    int ret = unitTest ();
    if (0 != ret) {
        printf ("Unit Test Error: %d\n", ret);
    } else {
        combine (5, 2);
        //char alphabet [] = "123";
        //print_combinations(alphabet);
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
    printf ("Done!\n\n");
//    getchar ();
    return 0;
}

