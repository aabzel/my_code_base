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

uint32_t reverseBits (uint32_t num) {
    uint32_t numOfbit = 4 * 8u;
    uint32_t reverseNum = 0u;
    uint32_t i;
    uint32_t temp;

    for (i = 0u; i < numOfbit; i++) {
        temp = (num & (1 << i));
        if (temp) {
            reverseNum |= (1 << ((numOfbit - 1) - i));
        }
    }
    return reverseNum;
}

uint8_t hamming_weight (uint32_t n) {
    uint8_t sum = 0;
    while (n != 0) {
        printf ("\nn      :%s", uint32_to_bin_str (n));
        printf ("\n n-1   :%s", uint32_to_bin_str (n - 1));
        printf ("\nn&(n-1):%s", uint32_to_bin_str (n & (n - 1)));
        printf ("\n");
        sum++;
        n &= (n - 1);
    }
    return sum;
}

char *uint32_to_bin_str (uint32_t const inVal32bit) {
    static char outBitStr [33] = "";
    int8_t rBit = 0;
    uint8_t cell = 0u;
    uint32_t mask = 0u;
    for (rBit = 31; 0 <= rBit; rBit--) {
        cell = (((uint8_t) 31u) - ((uint8_t) rBit));
        if (cell < sizeof(outBitStr)) {
            mask = (uint32_t) (((uint32_t) 1u) << ((uint32_t) rBit));
            if (0u != (inVal32bit & mask)) {
                outBitStr [cell] = '1';
            } else {
                outBitStr [cell] = '0';
            }
        }
    }
    return outBitStr;
}

int **list_of_arr_to_arr_of_arr (list_node_t * const listOfArrays, int * const amountOfArrays, int** returnColumnSizes) {
    int numElem = list_num_of_elements (listOfArrays);
    int **arrayOfPtr;
    arrayOfPtr = NULL;
    if (0 < numElem) {
        *amountOfArrays = numElem;
        arrayOfPtr = (int **) malloc (numElem * sizeof(int));
        int* columnSizes = malloc (numElem * sizeof(int));
        for (int i = 0; i < numElem; i++) {
            list_node_t *curNode = get_node_by_index (listOfArrays, i);
            if (NULL != curNode) {
                columnSizes [i] = curNode->data.arrSize;
                arrayOfPtr [i] = curNode->data.pArr;
            } else {
                printf ("\n lack of element with ind %d in the list listOfArrays", i);
            }
        }
        *returnColumnSizes = columnSizes;
    }

    return arrayOfPtr;

}

void print_bit_representation (float val) {
    union union_type {
        uint32_t vali;
        float val;
    };
    union union_type cnvt;
    cnvt.val = val;
    printf("size of %d", (int )sizeof(float));
    printf ("\n %f %d \n%s\n", cnvt.val, cnvt.vali, uint32_to_bin_str (cnvt.vali));

}


