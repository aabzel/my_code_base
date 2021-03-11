//#include "code_config.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


#ifdef MATH
#include "algorithms.h"
#endif

#include "convert.h"



#ifdef HAS_PARSE_REG
#include "parse_regs.h"
#endif




#include "uTests.h"
#include "utils.h"


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



    printf ("\n[-] Argc: [%u]", argc);
    for (int i = 0; i < argc; i++) {
        printf ("\n[d] 1");
        printf ("\n[-]  argv[%d] [%s]", i, argv[i]);
    }



#if PRINT_ENV
    print_ent ();
#endif

#ifdef HAS_UTESTS
    EXPECT_TRUE (unit_test ());
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




    printf ("\n\n program finish!\n\n");

    return 0;
}
