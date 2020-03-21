#include "algorithms.h"
#include "combinations.h"
#include "linked_list.h"
#include "permutations.h"
#include "utils.h"
#include "uTests.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main (void);
//int main (int argc, char **argv)
int main (void) {
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



