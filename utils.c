#include "utils.h"
#include "arrays.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

int print_array_to_file (int *array, int numItem) {
    FILE * fp;
    int i;
    fp = fopen ("log.txt", "a");

    /* write 10 lines of text into the file stream*/
    for (i = 0; i < numItem; i++) {
        fprintf (fp, "%d ", array [i]);
    }
    fprintf (fp, "\n");

    fclose (fp);
    return 0;
}
