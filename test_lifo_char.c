#include "test_lifo_char.h"

#include "lifo_char.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

Lifo_array_t lifiObj;
char array[5];

#define STRING19 "123456789"
Lifo_array_t lifiObj2;
bool test_lifo_array1_char (void) {
    bool res = false;
    char array1[6];
    char outArray[100];
    uint16_t outLen = 0;
    int cmpRes = -1;

    lifo_init (&lifiObj2, sizeof (array1), array1);

    res = lifo_push_array (&lifiObj2, STRING19, strlen (STRING19));
    if (true == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    res = lifo_peek_array (&lifiObj2, outArray, &outLen);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (6 != outLen) {
        return false;
    }

    cmpRes = strcmp ("654321", outArray);
    if (0 != cmpRes) {
        return false;
    }

    strncpy (outArray, "", strlen (outArray));
    res = lifo_pull_array (&lifiObj2, outArray, &outLen);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (6 != outLen) {
        return false;
    }

    cmpRes = strcmp ("654321", outArray);
    if (0 != cmpRes) {
        return false;
    }

    return true;
}

Lifo_array_t lifiObj1;
bool test_lifo_array_char (void) {
    bool res = false;
    char array1[10];
    char outArray[100];
    uint16_t outLen = 0;
    int cmpRes = -1;

    lifo_init (&lifiObj1, sizeof (array1), array1);

    res = lifo_push_array (&lifiObj1, "12345", 5);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    strncpy (outArray, "", strlen (outArray));
    res = lifo_peek_array (&lifiObj1, outArray, &outLen);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (5 != outLen) {
        return false;
    }
    cmpRes = strcmp ("54321", outArray);
    if (0 != cmpRes) {
        return false;
    }

    strncpy (outArray, "", strlen (outArray));
    res = lifo_pull_array (&lifiObj1, outArray, &outLen);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (5 != outLen) {
        return false;
    }

    cmpRes = strcmp ("54321", outArray);
    if (0 != cmpRes) {
        return false;
    }

    return true;
}
bool test_lifo (void) {
    bool res = false;

    res = test_lifo_char ();
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    res = test_lifo_array_char ();
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    res = test_lifo_array1_char ();
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    return true;
}

bool test_lifo_char (void) {
    char outChar;
    bool res;
    lifo_init (&lifiObj, sizeof (array), array);

    res = lifo_push (&lifiObj, '1');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_push (&lifiObj, '2');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_push (&lifiObj, '3');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_push (&lifiObj, '4');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_push (&lifiObj, '5');
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_push (&lifiObj, '6');
    if (true == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }

    res = lifo_pull (&lifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('5' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_pull (&lifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('4' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_pull (&lifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('3' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_pull (&lifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('2' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_pull (&lifiObj, &outChar);
    if (false == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if ('1' != outChar) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    res = lifo_pull (&lifiObj, &outChar);
    if (true == res) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    return true;
}
