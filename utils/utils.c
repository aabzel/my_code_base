#include "utils.h"

#if 0
#include "algorithms.h"
#include "arrays.h"
#include "bin_heap_array.h"
#include "linked_list.h"
#endif

#include "float_utils.h"
#include "str_ops.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char pemutationFile[100];
char kitFile[100];

static char a2i (char ch, const char **src, int32_t *nump);
static int8_t a2d (char ch);

#define PORT_A 0U
#define PORT_B 1U
#define PORT_C 2U
#define PORT_D 3U
#define PORT_E 4U
#define PORT_F 5U
#define PORT_G 6U
#define PORT_H 7U
#define PORT_I 8U
#define PORT_J 9U
#define PORT_K 10U
#define PORT_L 11U
#define PORT_M 12U
#define PORT_N 13U
#define PORT_O 14U
#define PORT_P 15U

char *portNumToStr (uint8_t port) {
    static char *outStrNone = "NONE";
    switch (port) {
    case PORT_A:
        outStrNone = "PA";
        break;
    case PORT_B:
        outStrNone = "PB";
        break;
    case PORT_C:
        outStrNone = "PC";
        break;
    case PORT_D:
        outStrNone = "PD";
        break;
    case PORT_E:
        outStrNone = "PE";
        break;
    case PORT_F:
        outStrNone = "PF";
        break;
    case PORT_G:
        outStrNone = "PG";
        break;
    case PORT_H:
        outStrNone = "PH";
        break;
    case PORT_I:
        outStrNone = "PI";
        break;
    case PORT_J:
        outStrNone = "PJ";
        break;
    case PORT_K:
        outStrNone = "PK";
        break;
    case PORT_L:
        outStrNone = "PL";
        break;
    case PORT_M:
        outStrNone = "PM";
        break;
    case PORT_N:
        outStrNone = "PN";
        break;
    case PORT_O:
        outStrNone = "PO";
        break;
    case PORT_P:
        outStrNone = "PP";
        break;
    }
    return outStrNone;
}

void print_pad_nums (void) {
    FILE *fileOut = fopen ("Gpio.txt", "w");
    for (uint8_t port = 0U; port <= PORT_P; port++) {
        for (uint8_t pin = 0U; pin <= 15U; pin++) {
            uint8_t padNul = ((port << 4U) | pin);
            fprintf (fileOut, "\n%s%d=%d", portNumToStr (port), pin, padNul);
        }
    }
    fclose (fileOut);
}

void init_file_name (void) {
    time_t rawtime;
    struct tm *timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf (pemutationFile, "permutation_%d_%d_%d_%d_%d_%d.txt", timeinfo->tm_mday, timeinfo->tm_mon + 1,
             timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    sprintf (kitFile, "kit_%d_%d_%d_%d_%d_%d.txt", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

char *generate_num_string (int n) {
    char *charStr = NULL;
    charStr = malloc (n + 1);
    for (int i = 0; i < n; i++) {
        charStr[i] = (i) + '0';
    }
    charStr[n] = '\0';
    return charStr;
}

void print_array_int (int *alphabet, int sizeOfAlphabet) {
    if (NULL == alphabet) {
        return;
    }
    if (sizeOfAlphabet < 0) {
        return;
    }
    printf ("\n<%d>  ", sizeOfAlphabet);
    printf ("[");
    for (int i = 0; i < sizeOfAlphabet; i++) {
        if (i != (sizeOfAlphabet - 1)) {
            printf ("%d, ", alphabet[i]);
        } else {
            printf ("%d", alphabet[i]);
        }
    }
    printf ("]");
}

void init_double_array (double *ptrArray, int size) {
    for (int i = 0; i < size; i++) {
        ptrArray[i] = 0.0;
    }
}

void print_array_double (double *alphabet, int sizeOfAlphabet) {

    printf ("\n{ ");
    for (int i = 0; i < sizeOfAlphabet; i++) {
        printf ("%.3f, ", alphabet[i]);
    }
    printf (" }");
    printf ("\n");
}

// Store the formatted string of time in the output
char *format_time_txt (void) {
    static char output[1000];
    time_t rawtime;
    struct tm *timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    sprintf (output, "[%d %d %d %d:%d:%d].txt", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return output;
}

/*
 * This function converts an unsigned binary
 * number to reflected binary Gray code.
 *
 * The operator >> is shift right. The operator ^ is exclusive or.
 */
uint32_t bin_to_gray (uint32_t num) { return num ^ (num >> 1); }

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
int *grayCode (int n, int *returnSize) {
    uint32_t maxVal = 0u;
    maxVal = max_val (n);
    int *outArr = NULL;
    *returnSize = maxVal + 1;
    outArr = malloc ((maxVal + 1) * sizeof (int));
    if (outArr) {
        for (uint32_t binVal = 0; binVal <= maxVal; binVal++) {
            outArr[binVal] = bin_to_gray (binVal);
        }
    }
    return outArr;
}

#if 0
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
#endif

#if 0
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
#endif

void print_bit_representation (float val) {
    union union_type {
        uint32_t vali;
        float val;
    };
    union union_type cnvt;
    cnvt.val = val;
    printf ("size of %d", (int)sizeof (float));
    printf ("\n %f %d \n%s\n", cnvt.val, cnvt.vali, uint32_to_bin_str (cnvt.vali));
}

long long summ_array (int const *const inArr, int sizeOfArr) {
    long long int sum = 0;
    if (inArr) {
        for (int i = 0; i < sizeOfArr; i++) {
            sum += inArr[i];
        }
    }
    return sum;
}

double avrage_two (int val1, int val2) {
    double avagage = (double)(((double)(((double)val1) + ((double)val2)) / 2.0));
    return avagage;
}

double calc_average (int const *const inArr, int sizeOfArr) {
    double median = 0.0;
    if (inArr) {
        if (0 < sizeOfArr) {
            double sum = (double)summ_array (inArr, sizeOfArr);
            median = sum / sizeOfArr;
        }
    }
    return median;
}

bool is_double_arr_equal (double *arr1, double *arr2, int arrSize) {
    for (int i = 0; i < arrSize; i++) {
        if (!is_floats_equal (arr1[i], arr2[i])) {
            return false;
        }
    }
    return true;
}

void print_sub_str (char *const str, int len) {
    if (str) {
        int i = 0;
        for (i = 0; i < len; i++) {
            printf ("%c", str[i]);
        }
    }
}

#define UNSIGNED_OVERFLOW -4
unsigned summ (unsigned char num, unsigned first, ...) {
    unsigned sum = 0;
    unsigned testsum = 0;
    unsigned *p = &first;
    while (num--) {
        testsum += *p;
        if (testsum >= sum) {
            sum = testsum;
        } else {
            exit (UNSIGNED_OVERFLOW);
        }
        p++;
    }
    return sum;
}

#define DEBUG_STRING 0

bool is_digit (char ch) {
    bool res = false;
    if (('0' <= ch) && (ch <= '9')) {
        res = true;
    }
    return res;
}

// https://learnc.info/c/vararg_functions.html
bool my_printf (const char *formatStr, ...) {
    void *argPtr = &formatStr;
    int curArgNum = 0;
    int numOfArfgs = parse_num_of_args (formatStr);
#if DEBUG_ARGS
    printf ("\n numOfArfgs %d", numOfArfgs);
    print_mem_horisonal ((uint8_t *)&formatStr, 4 * 5 + 1);
    print_mem_horisonal ((uint8_t *)argPtr, 4 * 5 + 1);
#endif

    // char *ptr;
    while ('\0' != (*formatStr)) {
        char ch = *formatStr;
        formatStr++;

        if (ch == '%') {
            ch = *formatStr;
            formatStr++;
            int32_t width = 0;
            if (true == is_digit (ch)) {
                ch = a2i (ch, &formatStr, &width);
                // printf("\n width %d\n",width);
            }
            argPtr += 4;

            curArgNum++;
            switch (ch) {
            case 'b': {
                if (curArgNum <= numOfArfgs) {
                    if (16 == width) {
                        uint16_t *valT;
                        valT = (uint16_t *)argPtr;
                        printf ("%s", utoa_bin16 (*valT));
                    }
                    if (32 == width) {
                        uint32_t *valT;
                        valT = (uint32_t *)argPtr;
                        printf ("%s", uint32_to_bin_str (*valT));
                    }

                } else {
                    return false;
                }
            } break;
            case 's':
#if DEBUG_STRING
                print_mem_horisonal ((uint8_t *)argPtr, 4);
#endif
                if (curArgNum <= numOfArfgs) {
                    char **textPrt;
                    textPrt = argPtr;
                    // argPtr is a pointer to a pointer to the address in text
                    printf ("%s", (*textPrt));
                } else {
                    return false;
                }

                break;
            case 'd':
#if DEBUG_D
                print_mem_horisonal ((uint8_t *)argPtr, 4);
#endif
                if (curArgNum <= numOfArfgs) {
                    int *valT;
                    valT = (int *)argPtr;
                    printf ("%d", *valT);
                } else {
                    return false;
                }

                break;
            case '%':
                curArgNum--;
                putchar ('%');
                break;
            }
        } else {
            putchar (ch);
        }
    }

    return true;
}

bool test_my_printf (void) {
    bool res = false;
    char *home = "home";
    void *voidPtr;
    int *intPtr;
    int argNum = 0;
    char *format = "Stay at %s from %d to %d or you will be fined %d RUB!\n";
#if DEBUG_ADDRESS
    printf ("\n format ptr address: [%p] addr of format prt [%p]", format, &format);
#endif
    int voidPtrSize, intPtrSize;
#if DEBUG_ADDRESS
    printf ("\n home ptr address: [%p] addr of home prt [%p]", home, &home);
#endif
    int from = 30; //
#if DEBUG_ADDRESS
    printf ("\n from in hex: [%x] addr of from[%p]", from, &from);
#endif
    int to = 3; //
#if DEBUG_ADDRESS
    printf ("\n to in hex: [%x] addr of to[%p]", to, &to);
#endif
    int fine = 5000; //
#if DEBUG_ADDRESS
    printf ("\n fine in hex: [%x] addr of fine[%p]", fine, &fine);
#endif
    voidPtrSize = sizeof (voidPtr);
    if (4 != voidPtrSize) {
        printf ("\n voidPtrSize: [%d] ", voidPtrSize);
        return false;
    }
    intPtrSize = sizeof (intPtr);
    if (4 != intPtrSize) {
        printf ("\n intPtrSize: [%d] ", intPtrSize);
        return false;
    }
    argNum = parse_num_of_args (format);
    if (4 != argNum) {
        return false;
    }
    res = my_printf (format, home, from, to, fine);

    printf ("\n   ");
    res = my_printf ("reg val %32b", 0x25);

    printf ("\n   ");
    res = my_printf ("reg val %16b", 0x25);

    return res;
}

bool print_mem_vertical (uint8_t *memPtr, uint32_t numByte, bool printChars) {
    bool res = false;
    // printf ("\nPrint mem:");
    printf ("\n[");
    if (NULL != memPtr) {
        uint32_t i = 0;
        for (i = 0; i < numByte; i++) {
            if (0 == (i % 4)) {
                printf ("\n");
            }
            printf ("\n%p: %02X", &memPtr[i], memPtr[i]);
        }
        printf ("]\n");
        if (true == printChars) {
            printf ("[");
            for (i = 0; i < numByte; i++) {
                printf ("%c", memPtr[i]);
            }
            printf ("]");
        }
        printf ("\nPrint mem end\n");
    }
    return res;
}

bool print_mem_horisonal (FILE *out_file_prt,uint8_t *memPtr, uint32_t numByte, bool gap) {
    bool res = false;
#if 0

    fprintf (out_file_prt, "\n\n %s() %u [byte]",__FUNCTION__, numByte);
    fprintf (stdout, "\n\n %s() %u [byte]",__FUNCTION__, numByte);
    if (NULL != memPtr) {
        uint32_t i = 0;
        fprintf (out_file_prt, "\n\nind : ");
        for (i = 0; i < numByte; i++) {
            if ((0 == (i % 4)) && (0 != i) && (true==gap)) {
                fprintf (out_file_prt, " ");
            }
        	fprintf (out_file_prt,"%02u",i);
        	fprintf (stdout,"%02u",i);
        }
        fprintf (out_file_prt, "\n\nval : ");
        for (i = 0; i < numByte; i++) {
            if ((0 == (i % 4)) && (0 != i) && (true==gap)) {
                fprintf (out_file_prt, " ");
            }
            fprintf (out_file_prt, "%02x", memPtr[i]);
            fprintf (stdout, "%02x", memPtr[i]);
        }
        printf ("\nadr : ");
        for (i = 0; i < numByte; i += 4) {
            printf ("%p", &memPtr[i]);
            printf (" ");
        }
    }
#endif
    return res;
}

int parse_num_of_args (const char *format) {
    const char *ptr;
    int numOfArgs = 0;
    for (ptr = format; *ptr != '\0'; ptr++) {
        if ('%' == (*ptr)) {
            numOfArgs++;
        }
    }
    return numOfArgs;
}

static char a2i (char ch, const char **src, int32_t *nump) {
    const char *p = *src;
    int32_t num = 0, digit = a2d (ch);
    while (digit >= 0) {
        num = num * 10 + digit;
        ch = *p;
        p++;
        digit = a2d (ch);
    }
    *src = p;
    *nump = num;
    return ch;
}
static int8_t a2d (char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else {
        return -1;
    }
}

float cacl_percent (float numerator, float denominator) {
    float percent;
    percent = numerator * 100.0 / denominator;
    return percent;
}

union sharedmem {
    uint32_t bitVal;
    float realVal;
};

float power_of (uint32_t base, int32_t exponent) {
    float result = 1.0f;
    int32_t numberOfTimes;
    if (0 <= exponent) {
        for (numberOfTimes = 0; numberOfTimes < exponent; numberOfTimes++) {
            result *= base;
        }
    } else {
        for (numberOfTimes = 0; numberOfTimes < -exponent; numberOfTimes++) {
            result /= base;
        }
    }
    return result;
}

double fraction (uint32_t mantissa) {
    double value = 1.0f;
    int32_t bitCnt = 0U;
    int32_t bit = 1U;
    for (bit = 0; bit <= 23; bit++) {
        if ((1U << bit) == (mantissa & (1U << bit))) {
            bitCnt++;
            // printf ("\n bit %d", bit);
            value = value + (1.0f / pow ((double)2.0f, (double)23U - bit));
        }
    }
    // printf ("\nbitCnt %d", bitCnt);
    return value;
}

void print_biggest_mantissa (void) {
    uint32_t mantissa = 0xFFFFFFFF;
    double fractiona;
    fractiona = fraction (mantissa);
    printf ("\n fractiona %f", fractiona);
    mantissa = 0x00000000;
    fractiona = fraction (mantissa);
    printf ("\n fractiona %f", fractiona);
}

#if 0
#define BIAS 127
uint16_t float_to_uint16 (float inVal) {
    uint16_t outVal = 0;
    float multiplierright;
    union sharedmem uni;
    uni.realVal = inVal;
    uint32_t mantissa;
    printf ("\n %x %d %f", uni.bitVal, uni.bitVal, uni.realVal);
    printf ("\n num      %s", uint32_to_bin_str (uni.bitVal));
    mantissa = extract_subval_from_32bit (uni.bitVal, 22, 0);
    printf ("\n\r mantissa %d ", mantissa);
    printf ("\n mantissa %s", uint32_to_bin_str (mantissa));
    uint32_t exponent;
    exponent = extract_subval_from_32bit (uni.bitVal, 30, 23);
    printf ("\n\r exponent %d ", exponent);
    printf ("\n exponent %s", uint32_to_bin_str (exponent));

    // power of two
    uint32_t exponentVal = exponent - BIAS;
    printf ("\n\r exponentVal %d ", exponentVal);
    multiplierright = power_of (2U, exponentVal);
    printf ("\n\r multiplierright %f ", multiplierright);

    uint32_t sign;
    sign = extract_subval_from_32bit (uni.bitVal, 31, 31);
    printf ("\n\r sign %d ", sign);
    printf ("\n\r sign %d %s", sign, (sign) ? "neg" : "pos");

    double fractiona, result;

    fractiona = fraction (mantissa);
    printf ("\n\r fractiona %f", fractiona);

    result = fractiona * multiplierright;
    printf ("\n\r result %f", result);

    return outVal;
}
#endif

void print_indent (int indent) {
    for (int i = 0; i < indent; i++) {
        printf (" ");
    }
}

bool print_mac_addr (uint8_t *mac_addr) {
    bool res = false;
    if (NULL != mac_addr) {
        res = true;
        for (uint8_t i = 0; i < 6; i++) {
            printf ("%02x", mac_addr[i]);
            if (i < 5) {
                printf (":");
            }
        }
        printf ("\n");
    }
    return res;
}

uint32_t pack_ipv4 (uint8_t ipAddrByte1, uint8_t ipAddrByte2, uint8_t ipAddrByte3, uint8_t ipAddrByte4) {
    uint8_t ipAddr[4] = {ipAddrByte1, ipAddrByte2, ipAddrByte3, ipAddrByte4};
    uint32_t ipv4bytesLe, ipv4bytesBe;
    memcpy (&ipv4bytesLe, ipAddr, 4);
    ipv4bytesBe = reverse_byte_order_uint32 (ipv4bytesLe);
    return ipv4bytesBe;
}

bool print_mem_ascii (uint8_t *memPtr, uint32_t numByte) {
    bool res = false;
    if (NULL != memPtr) {
        if (0 < numByte) {
            res = true;
            for (uint32_t i = 0; i < numByte; i++) {
                printf ("%c", (char)memPtr[i]);
            }
        }
    }
    return res;
}

// 12 2  [1,2,3,4,5,6]
// 6+5
void amoun_of_way_to_assemble_summ (int summ, int F) {
    // go over all permutation lengt of F with range 1...6
    // check the sum of permutation
    for (int num = 0; num < F; num++) {
    }
}

struct Results solution (int *A, int N, int F, int M) {
    struct Results result;
    // write your code in C99 (gcc 6.2.0)
    // meas  = total_sum / total_try
    result.R = F;
    result.res = (int *)malloc (F * sizeof (int));
    int total_try = N + F;
    int total_sum = total_try * M;
    printf ("\n total_try %u", total_try);
    printf ("\n total_sum %u", total_sum);
    int fogotten_sum = total_sum;
    for (int i = 0; i < N; i++) {
        fogotten_sum -= A[i];
    }
    printf ("\n fogotten_sum %u", fogotten_sum);

    // result.res = ...
    // result.R = ...
    return result;
}

bool is_arr_pat (uint8_t *arr, uint32_t size, uint8_t patt) {
    bool res = true;
    for (uint32_t i = 0; i < size; i++) {
        if (patt != arr[i]) {
            res = false;
        }
    }
    return res;
}

void print_bytes (uint32_t byte) {
    float kByte = 4;
    float MByte = 4;
    float GByte = 4;
    kByte = (float)byte / 1024.0f;
    MByte = (float)kByte / 1024.0f;
    GByte = (float)MByte / 1024.0f;
    printf ("\nmax Available heap size [%u] byte [%f] k_Byte [%f] M_Byte [%f] G_Byte\n", byte, kByte, MByte, GByte);
}

bool is_mem_equal (uint8_t *arr1, uint8_t *arr2, uint32_t size) {
    uint32_t i = 0U;
    uint32_t eqCnt = 0U;
    bool res = false;
    for (i = 0; i < size; i++) {
        if (arr1[i] == arr2[i]) {
            eqCnt++;
        } else {
            res = false;
            i = size + 1;
        }
    }
    if (eqCnt == size) {
        res = true;
    }
    return res;
}

int solution4 (int n) {
    int d[32];
    int l = 0;
    int p;
    printf ("\n");
    while (n > 0) {
        d[l] = n % 2;
        printf ("%u", d[l]);
        n /= 2;
        l++;
    }
    printf ("\n l %u", l);
    for (p = 1; p < 32; ++p) {
        int ok = 1;
        int i;
        for (i = 0; i < l - p; ++i) {
            if (d[i] != d[i + p]) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            return p;
        }
    }
    return -1;
}
