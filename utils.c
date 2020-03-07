#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

char pemutationFile [100];
char kitFile [100];

void init_file_name (void) {
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf (
        pemutationFile,
        "permutation_%d_%d_%d_%d_%d_%d.txt",
        timeinfo->tm_mday,
        timeinfo->tm_mon + 1,
        timeinfo->tm_year + 1900,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);

    sprintf (
        kitFile,
        "kit_%d_%d_%d_%d_%d_%d.txt",
        timeinfo->tm_mday,
        timeinfo->tm_mon + 1,
        timeinfo->tm_year + 1900,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);

}

char *generate_num_string (int n) {
    char *charStr = NULL;
    charStr = malloc (n + 1);
    for (int i = 0; i < n; i++) {
        charStr [i] = (i + 1) + '0';
    }
    charStr [n] = '\0';
    return charStr;
}

void print_array (int *alphabet, int sizeOfAlphabet, int k) {
    printf ("\nAlphabet size: [%d] lettesRemained [%d] ", sizeOfAlphabet, k);
    printf ("{");
    for (int i = 0; i < sizeOfAlphabet; i++) {
        printf ("%d", alphabet [i]);
    }
    printf ("}");
    printf ("\n");
}

// Store the formatted string of time in the output
char * format_time_txt (void) {
    char static output [1000];
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    sprintf (
        output,
        "[%d %d %d %d:%d:%d].txt",
        timeinfo->tm_mday,
        timeinfo->tm_mon + 1,
        timeinfo->tm_year + 1900,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);
    return output;
}


