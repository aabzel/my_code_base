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
        charStr [i] = (i) + '0';
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
    static char output [1000];
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

void test_heap (void) {
    uint32_t byte = 3;
    float kByte = 4;
    float MByte = 4;
    float GByte = 4;
    while (1) {
        char *ptr = NULL;
        ptr = (char *) malloc (byte);
        if (ptr) {
            byte = (byte * 3) / 2;
            free (ptr);
        } else {
            break;
        }
    } //[2327387742]
    kByte = (float) byte / 1024.0f;
    MByte = (float) kByte / 1024.0f;
    GByte = (float) MByte / 1024.0f;
    printf ("\nmax Available heap size [%u] byte [%f] k_Byte [%f] M_Byte [%f] G_Byte\n", byte, kByte, MByte, GByte);
}

/*
 * This function converts an unsigned binary
 * number to reflected binary Gray code.
 *
 * The operator >> is shift right. The operator ^ is exclusive or.
 */
uint32_t bin_to_gray (uint32_t num) {
    return num ^ (num >> 1);
}

/*
 * This function converts a reflected binary
 * Gray code number to a binary number.
 * Each Gray code bit is exclusive-ored with all
 * more significant bits.
 */
unsigned int GrayToBinary (unsigned int num) {
    unsigned int mask = num >> 1;
    while (mask != 0) {
        num = num ^ mask;
        mask = mask >> 1;
    }
    return num;
}

/*
 * A more efficient version for Gray codes 32 bits or fewer
 * through the use of SWAR (SIMD within a register) techniques.
 * It implements a parallel prefix XOR function.  The assignment
 * statements can be in any order.
 *
 * This function can be adapted for longer Gray codes by adding steps.
 * A 4-bit variant changes a binary number (abcd)2 to (abcd)2 ^ (00ab)2,
 * then to (abcd)2 ^ (00ab)2 ^ (0abc)2 ^ (000a)2.
 */
unsigned int GrayToBinary32 (unsigned int num) {
    num = num ^ (num >> 16);
    num = num ^ (num >> 8);
    num = num ^ (num >> 4);
    num = num ^ (num >> 2);
    num = num ^ (num >> 1);
    return num;
}

uint32_t max_val (uint32_t amountofbit) {
    uint32_t val = 0u;
    for (uint32_t i = 0; i < amountofbit; i++) {
        val |= (1 << i);
    }
    return val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode (int n, int* returnSize) {
    uint32_t maxVal = 0u;
    maxVal = max_val (n);
    int *outArr = NULL;
    *returnSize = maxVal + 1;
    outArr = malloc ((maxVal + 1) * sizeof(int));
    if (outArr) {
        for (uint32_t binVal = 0; binVal <= maxVal; binVal++) {
            outArr [binVal] = bin_to_gray (binVal);
        }
    }
    return outArr;
}
