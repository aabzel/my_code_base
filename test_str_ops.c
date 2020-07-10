#include "test_str_ops.h"

#include "str_ops.h"
#include "uTests.h"

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_lengthOfLongestSubstring (void) {
    int val;
    bool res;
    res = is_diff_chars ("12345", 5);
    if (false == res) {
        return false;
    }

    res = is_diff_chars ("1214", 4);
    if (true == res) {
        return false;
    }

    val = lengthOfLongestSubstring ("pwwkew");
    if (3 != val) {
        // printf ("\npwwkew val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("bpfbhmipx");
    if (7 != val) {
        // printf ("\nbpfbhmipx val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("aab");
    if (2 != val) {
        printf ("\naab val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("abcabcbb");
    if (3 != val) {
        printf ("\nabcabcbb val:%d \n", val);
        return false;
    }

    val = lengthOfLongestSubstring ("bbbbb");
    if (1 != val) {
        printf ("\nbbbbb val:%d \n", val);
        return false;
    }

    return true;
}

bool test_detect_change (void) {
    char *oldSubString;
    char *newSubString;
    int oldSubStringLen = -1;
    int newSubStringLen = -1;
    int cmpRes = 0;
    // "aaabb"
    // "aaa11bb"
    detect_change ("aaabb", "aaa11bb", &oldSubString, &oldSubStringLen, &newSubString, &newSubStringLen);
    if (0 != oldSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (2 != newSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    cmpRes = strncmp (newSubString, "11", 2);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, newSubString);
        return false;
    }

    detect_change ("aaa11bb", "aaabb", &oldSubString, &oldSubStringLen, &newSubString, &newSubStringLen);
    if (2 != oldSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (0 != newSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    cmpRes = strncmp (oldSubString, "11", 2);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, oldSubString);
        return false;
    }

    detect_change ("aa111bb", "aa22bb", &oldSubString, &oldSubStringLen, &newSubString, &newSubStringLen);
    if (3 != oldSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    if (2 != newSubStringLen) {
        printf ("\n%s %d", __FUNCTION__, __COUNTER__);
        return false;
    }
    cmpRes = strncmp (oldSubString, "111", 3);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, oldSubString);
        return false;
    }
    cmpRes = strncmp (newSubString, "22", 2);
    if (0 != cmpRes) {
        printf ("\n%s %d %s", __FUNCTION__, __COUNTER__, newSubString);
        return false;
    }

    return true;
}

//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2
//"aabb"5,   "aa11bb"7  oldSub""0    newSub"11"2
//"abb"5,   "a11bb"7  oldSub""0    newSub"11"2
//"bb"5,   "11bb"7  oldSub""0    newSub"11"2
//"b"5,   "11b"7  oldSub""0    newSub"11"2
//""0,   "11"2  oldSub""0    newSub"11"2

// Examples:
//"aaabb"5,   "aaa11bb"7  oldSub""0    newSub"11"2    < "11" inserted at index 3  oldSubStringLen 0  newSubStringLen: 2
//"aa111bb"7, "aa22bb"6   oldSub"111"3 newSub"22"2    < "11" inserted at index 3  oldSubStringLen 3  newSubStringLen: 2

bool test_reverse (void) {
    int cmpRes = 0;
    char tempStr [100];
    strcpy (tempStr, "12345");
    reverseString (tempStr, 5);
    cmpRes = strcmp (tempStr, "54321");
    if (0 != cmpRes) {
        printf ("\ntempStr [%s]\n", tempStr);
        return false;
    }

    return true;
}

bool test_myAtoi (void) {
    int val;
    char inStr [40];

    strcpy (inStr, "20000000000000000000");
    val = myAtoi (inStr);
    if (INT32_MAX != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "+1");
    val = myAtoi (inStr);
    if (1 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "-91283472332");
    val = myAtoi (inStr);
    if (INT32_MIN != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "4193 with words");
    val = myAtoi (inStr);
    if (4193 != val) {
        printf ("\n%s %d [%s] outVal [%d]", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "-42");
    val = myAtoi (inStr);
    if (-42 != val) {
        printf ("\n%s %d val %d exp(%d)", __FUNCTION__, __COUNTER__, val, -42);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "   -42");
    val = myAtoi (inStr);
    if (-42 != val) {
        printf ("\n%s %d [%s] val %d exp(%d)", __FUNCTION__, __COUNTER__, inStr, val, -42);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
    }

    strcpy (inStr, "words and 987");
    val = myAtoi (inStr);
    if (0 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }

    strcpy (inStr, "21");
    val = myAtoi (inStr);
    if (21 != val) {
        printf ("\n%s %d [%s] val %d", __FUNCTION__, __COUNTER__, inStr, val);
        return false;
    }
    if (val != atoi (inStr)) {
        printf ("\n%s %d [%s] val %d exp val %d", __FUNCTION__, __COUNTER__, inStr, val, atoi (inStr));
        return false;
    }
    return true;
}

bool test_num_to_bin_str (void) {
    int cmpRes = 0;
    cmpRes = strcmp ("1010_1010_1010_1010_1010_1010_1010_1010", uint32_to_bin_str (0xAAAAAAAA));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("0101_0101_0101_0101_0101_0101_0101_0101", uint32_to_bin_str (0x55555555));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("0000_0000_0000_0000_0000_0000_0000_0000", uint32_to_bin_str (0x00000000));
    if (0 != cmpRes) {
        return false;
    }
    cmpRes = strcmp ("1111_1111_1111_1111_1111_1111_1111_1111", uint32_to_bin_str (0xFFFFFFFF));
    if (0 != cmpRes) {
        return false;
    }
    return true;
}

bool test_operand_extract (void) {
    int operLen = -1;
    EXPECT_EQ(1, get_index_in_string ("(f,t)", 5, 0, &operLen));
    EXPECT_EQ(1, operLen);
    operLen = -1;
    EXPECT_EQ(3, get_index_in_string ("(f,t)", 5, 1, &operLen));
    EXPECT_EQ(1, operLen);
    operLen = -1;
    EXPECT_EQ(1, get_index_in_string ("(&(t,f,t),!(t))", 15, 0, &operLen));
    EXPECT_EQ(8, operLen);
    operLen = -1;
    EXPECT_EQ(10, get_index_in_string ("(&(t,f,t),!(t))", 15, 1, &operLen));
    EXPECT_EQ(4, operLen);
    return true;
}

bool test_parse_and (void) {
    EXPECT_TRUE(parse_and ("(t,t,t)", 7));
    EXPECT_FALSE(parse_and ("(t,f,t)", 7));
    EXPECT_FALSE(parse_and ("(t,&(f,t),t)", 12));
    return true;
}
// "(t,f,t)"          3
// "(t,f)"            2
// "(f,t)"            2
// "(&(t,f,t),!(t))"  2
// "(&(t,&(f,t),t),!(t))"  2

bool test_parse_not (void) {
    EXPECT_TRUE(parse_not ("(f)", 3));
    EXPECT_TRUE(parse_not ("!(t)", 4));
    EXPECT_FALSE(parse_not ("!(f)", 4));
    EXPECT_FALSE(parse_not ("(t)", 3));
    EXPECT_FALSE(parse_not ("!(f)", 4));
    return true;
}

bool test_parse_num_operands (void) {
    EXPECT_EQ(1, parse_num_operands ("(f)", 3));
    EXPECT_EQ(1, parse_num_operands ("(t)", 3));
    EXPECT_EQ(4, parse_num_operands ("(t,f,t,t)", 9));
    EXPECT_EQ(3, parse_num_operands ("(t,f,t)", 7));
    EXPECT_EQ(2, parse_num_operands ("(t,f)", 5));
    EXPECT_EQ(2, parse_num_operands ("(&(t,f,t),!(t))", 15));
    EXPECT_EQ(2, parse_num_operands ("(&(t,&(f,t),t),!(t))", 20));
    return true;
}

bool test_parseBoolExpr (void) {
    EXPECT_TRUE(parseBoolExpr ("!(&(f))"));
    EXPECT_FALSE(parseBoolExpr ("&(f)"));
    EXPECT_TRUE(parseBoolExpr ("&(t)"));
    EXPECT_FALSE(parseBoolExpr ("!(&(!(&(f)),&(t),|(f,f,t)))"));
    EXPECT_TRUE(parseBoolExpr ("(t)"));
    EXPECT_FALSE(parseBoolExpr ("(f)"));
    EXPECT_TRUE(parseBoolExpr ("!(f)"));
    EXPECT_FALSE(parseBoolExpr ("|(&(t,f,t),!(t))"));
    EXPECT_TRUE(parseBoolExpr ("|(f,t)"));
    EXPECT_FALSE(parseBoolExpr ("&(t,f)"));
    return true;
}

bool test_calc_paratasis_nesting (void) {
    int amountOfPairs = 0;
    EXPECT_EQ(1, calc_paratasis_nesting ("(t,f,t)", &amountOfPairs));
    EXPECT_EQ(1, amountOfPairs);

    EXPECT_EQ(1, calc_paratasis_nesting ("(t,f)", &amountOfPairs));
    EXPECT_EQ(1, amountOfPairs);

    EXPECT_EQ(2, calc_paratasis_nesting ("(&(t,f,t),!(t))", &amountOfPairs));
    EXPECT_EQ(3, amountOfPairs);

    EXPECT_EQ(3, calc_paratasis_nesting ("(&(t,&(f,t),t),!(t))", &amountOfPairs));
    EXPECT_EQ(4, amountOfPairs);

    return true;
}

bool test_Valid_Parentheses (void) {
    EXPECT_TRUE(is_valid_parentheses ("()[]{}"));
    EXPECT_TRUE(is_valid_parentheses ("(t,f,t)"));
    EXPECT_TRUE(is_valid_parentheses ("(&(t,&(f,t),t),!(t))"));
    return true;
}

bool test_replace_substr (void) {
    char text [100];

    strncpy (text, "aabzelaabzelaabzelaabzel", sizeof(text));
    EXPECT_TRUE(reblace_substring (text, "bz", "MOS"));
    EXPECT_EQ_STR(text, "aaMOSelaaMOSelaaMOSelaaMOSel");

    strncpy (text, "aabzelaabzel", sizeof(text));
    EXPECT_TRUE(reblace_substring (text, "bz", "MOS"));
    EXPECT_EQ_STR(text, "aaMOSelaaMOSel");

    strncpy (text, "aabzel", sizeof(text));
    EXPECT_FALSE(reblace_substring (text, "spb", "mos"));
    EXPECT_EQ_STR(text, "aabzel");

    strncpy (text, "qwertyuioo", sizeof(text));
    EXPECT_TRUE(reblace_substring (text, "rty", "ZXC"));
    EXPECT_EQ_STR(text, "qweZXCuioo");

    strncpy (text, "qwertyuiop", sizeof(text));
    EXPECT_TRUE(reblace_substring (text, "qwe", "ASD"));
    EXPECT_EQ_STR(text, "ASDrtyuiop");

    strncpy (text, "asdfghjkl", sizeof(text));
    EXPECT_TRUE(reblace_substring (text, "jkl", "BNM"));
    EXPECT_EQ_STR(text, "asdfghBNM");

    return true;
}

bool test_str_char_replace (void) {
    char fileName [100];
    int cmpRes = 0;
    strncpy (fileName, "spc58_pass.mk", sizeof(fileName));
    replace_char (fileName, '.', '_');
    cmpRes = strcmp (fileName, "spc58_pass_mk");
    if (0 == cmpRes) {
        return true;
    }
    return false;
}

bool test_count_substring (void) {
    EXPECT_EQ(4, count_substring ("aabzelaabzelaabzelaabzel", "ab"));
    EXPECT_EQ(1, count_substring ("aabzel", "ab"));
    EXPECT_EQ(2, count_substring ("aabzelaabzel", "ab"));
    return true;
}

