#include "test_fifo_char.h"

#include "fifo_char.h"

#include <stdio.h>
//#include <stdint.h>
Fifo_array_t fifiObj;
char array [5];

bool test_fifo_char (void) {
    bool res = false;
    char outChar;
    fifo_init (&fifiObj, sizeof(array), array);

    res = fifo_push (&fifiObj, '1');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_push (&fifiObj, '2');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_push (&fifiObj, '3');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_push (&fifiObj, '4');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_push (&fifiObj, '5');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_push (&fifiObj, '6');
    if (true == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('1' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('2' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('3' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('4' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull (&fifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('5' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = fifo_pull (&fifiObj, &outChar);
    if (true == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    return true;
}
