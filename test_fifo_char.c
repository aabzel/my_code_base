#include "test_fifo_char.h"

#include "fifo_char.h"

#include <stdio.h>
#include <string.h>
//#include <stdint.h>
Fifo_array_t fifiObj;
char array[5];

#define STRING19 "123456789"
bool test_fifo_array1_char (void) {
    bool res = false;
    Fifo_array_t fifiObj1;
    char array1[6];
    char outArray[100];
    uint16_t outLen = 0;
    int cmpRes = -1;

    fifo_init (&fifiObj, sizeof (array1), array1);

    res = fifo_push_array (&fifiObj1, STRING19, strlen (STRING19));
    if (true == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull_array (&fifiObj1, outArray, &outLen);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (6 != outLen) {
        return false;
    }

    cmpRes = strcmp ("123456", outArray);
    if (0 != cmpRes) {
        return false;
    }

    return true;
}

bool test_fifo_array_char (void) {
    bool res = false;
    Fifo_array_t fifiObj1;
    char array1[10];
    char outArray[100];
    uint16_t outLen = 0;
    int cmpRes = -1;

    fifo_init (&fifiObj, sizeof (array1), array1);

    res = fifo_push_array (&fifiObj1, "12345", 5);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull_array (&fifiObj1, outArray, &outLen);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (5 != outLen) {
        return false;
    }

    cmpRes = strcmp ("12345", outArray);
    if (0 != cmpRes) {
        return false;
    }

    return true;
}
bool test_fifo_char (void) {
    bool res = false;

    char outChar;
    fifo_init (&fifiObj, sizeof (array), array);

    res = fifo_push (&fifiObj, '1');
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 1);
        return false;
    }

    res = fifo_push (&fifiObj, '2');
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 2);
        return false;
    }
    res = fifo_push (&fifiObj, '3');
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 3);
        return false;
    }
    res = fifo_push (&fifiObj, '4');
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 4);
        return false;
    }
    res = fifo_push (&fifiObj, '5');
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 5);
        return false;
    }

    res = fifo_push (&fifiObj, '6');
    if (true == res) {
        printf ("\nError: %s %d", __FUNCTION__, 6);
        return false;
    }

    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 7);
        return false;
    }

    if ('1' != outChar) {
        printf ("\nError: %s %d", __FUNCTION__, 8);
        return false;
    }

    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 9);
        return false;
    }

    if ('2' != outChar) {
        printf ("\nError: %s %d", __FUNCTION__, 10);
        return false;
    }

    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 11);
        return false;
    }

    if ('3' != outChar) {
        printf ("\nError: %s %d", __FUNCTION__, 12);
        return false;
    }

    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 13);
        return false;
    }

    if ('4' != outChar) {
        printf ("\nError: %s %d", __FUNCTION__, 14);
        return false;
    }

    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\nError: %s %d", __FUNCTION__, 15);
        return false;
    }

    if ('5' != outChar) {
        printf ("\nError: %s %d", __FUNCTION__, 16);
        return false;
    }
    res = fifo_pull (&fifiObj, &outChar);
    if (true == res) {
        printf ("\nError: %s %d", __FUNCTION__, 17);
        return false;
    }

    res = test_fifo_array_char ();
    if (true == res) {
        printf ("\nError: %s %d", __FUNCTION__, 18);
        return false;
    }

    res = test_fifo_array1_char ();
    if (true == res) {
        printf ("\nError: %s %d", __FUNCTION__, 19);
        return false;
    }

    return true;
}
